<?

/**
 * Classe inbox
 *
 */
class inbox
{

    function __construct($conn, $lang)
    {
        $this->conn = $conn;
        $this->lang = $lang;
        $this->set_testi();
        $this->allinea_db();
    }

    /*
     * Gestione delle richieste ajax
     */
    function req($richiesta)
    {
        if ($richiesta['operazione'] == 'new_mail') {
            print $this->do_new_mail();
        } elseif ($richiesta['operazione'] == 'send_mail') {
            print $this->do_send_mail();
        } elseif ($richiesta['operazione'] == 'pannello_bacheca') {
            print $this->do_inbox('bacheca');
        } elseif ($richiesta['operazione'] == 'pannello_inbox') {
            print $this->do_inbox('inbox');
        } elseif ($richiesta['operazione'] == 'pannello_sent') {
            print $this->do_inbox('sent');
        }
    }

    function allinea_db()
    {
        $query = new query($this->conn);
        $tables_to_create['INBOX_MESSAGGI'] = "CREATE TABLE INBOX_MESSAGGI (ID_MESSAGGIO NUMBER NOT NULL, DATA_INVIO DATE NOT NULL, USERID VARCHAR2(32 CHAR) NOT NULL, OGGETTO VARCHAR2(255 CHAR) NOT NULL, CORPO CLOB NOT NULL, DESTINATARI CLOB NOT NULL, CONSTRAINT INBOX_MESSAGGI_PK PRIMARY KEY (ID_MESSAGGIO) ENABLE)";
        $tables_to_create['INBOX_CORRISPONDENZA'] = "CREATE TABLE INBOX_CORRISPONDENZA (ID_CORRISPONDENZA NUMBER NOT NULL, ID_MESSAGGIO NUMBER NOT NULL, USERID VARCHAR2(32 CHAR) NOT NULL, DATA_VISUALIZZAZIONE DATE, DATA_ELIMINAZIONE DATE, CONSTRAINT INBOX_CORRISPONDENZA_PK PRIMARY KEY (ID_CORRISPONDENZA), CONSTRAINT INBOX_CORRISPONDENZA_FK1 FOREIGN KEY ( ID_MESSAGGIO ) REFERENCES INBOX_MESSAGGI ( ID_MESSAGGIO ) ENABLE)";
        foreach ($tables_to_create as $tabella => $sql) {
            $check_str = "select count(*) EXIST from user_tables where table_name='{$tabella}'";
            if ($query->get_row($check_str) && $query->row['EXIST'] == 0) {
                $query->exec($sql);
            }
            $check_str = "select count(*) EXIST from user_objects where object_name='{$tabella}_SEQ'";
            if ($query->get_row($check_str) && $query->row['EXIST'] == 0) {
                $query->exec("CREATE SEQUENCE {$tabella}_SEQ INCREMENT BY 1 START WITH 1 MAXVALUE 999999999999 MINVALUE 1 NOCACHE ORDER");
            }
        }
    }

    function layout_menu($active = false, $target, $colore, $icona)
    {
        return "<li class=\"" . ($active ? "active " : "") . "cl_{$target}\"><a data-target=\"{$target}\" onclick=\"inbox_pannello('{$target}');\" href=\"#{$target}\" data-toggle=\"tab\"><i class=\"{$colore} icon-{$icona} bigger-130\"></i><span class=\"bigger-110\">%{$target}%</span></a></li>";
    }

    function get_titolo()
    {
        return $this->testi['Posta in arrivo'];
    }

    function get_home()
    {
        $html = $this->get_layout();

        return $html;
    }

    function get_onload()
    {
        return "";
    }

    function get_navbar()
    {
        return $this->get_mail('navbar', 'inbox');
    }

    function get_layout()
    {
        $html = <<<DATI
        <div class="col-xs-12">
            <div class="tabbable">
                <ul class="inbox-tabs nav nav-tabs padding-16 tab-size-bigger tab-space-1" id="inbox-tabs">
                    <li class="li-new-mail pull-right">
                        <a class="btn-new-mail" href="#write" onclick="inbox_nuovomessaggio();" >
                            <span class="btn bt1n-small btn-purple no-border">
                                <i class="icon-envelope bigger-130"></i>
                                <span class="bigger-110">%Nuovo messaggio%</span>
                            </span>
                        </a>
                    </li>
                    %menu%
                </ul>
                %messaggi%
                %footer%                                                                                            
            </div>
        </div>
DATI;
        $menu = $this->layout_menu((!isset($_GET['msg']) ? true : false), 'bacheca', 'blue', 'inbox');
        //$menu .= $this -> layout_menu(false, 'inbox', 'blue', 'inbox');
        $menu .= $this->layout_menu(false, 'sent', 'blue', 'location-arrow');
        if (isset($_GET['msg'])) {
            $menu .= $this->layout_menu(true, 'message', 'blue', 'external-link');

        }
        $html = str_replace('%menu%', $menu, $html);
        if (!isset($_GET['msg'])) {
            $html = str_replace('%messaggi%', $this->do_inbox('messaggio'), $html);
        } else {
            $html = str_replace('%messaggi%', $this->get_mail('messaggio', 'inbox'), $html);
        }
        $html = str_replace('%footer%', $this->do_footer_mail(), $html);
        return $this->localizza_html($html);

    }

    function get_rubrica($formato)
    {
        $query = new query($this->conn);
        $html = "";
        unset($list);
        unset($bind);
        $bind['USERID'] = $_SERVER['REMOTE_USER'];

        $T['U'] = $this->testi['Utenti'];
        $T['P'] = $this->testi['Profili'];
        $T['C'] = $this->testi['Centri'];
        $T['S'] = $this->testi['Studi'];

        // Tutti gli utenti associati ai miei studi
        $rubrica_utenti = $query->exec("SELECT 'U' TIPO, u.userid ID, a.NOME || ' ' || a.COGNOME DESCRIZIONE FROM (SELECT DISTINCT USERID FROM USERS_STUDIES WHERE STUDY_PREFIX IN (SELECT STUDY_PREFIX FROM USERS_STUDIES WHERE ACTIVE = 1 AND USERID   = :userid ) AND ACTIVE  = 1 AND USERID <> :userid ) u, ana_utenti_1 a WHERE u.userid = a.userid (+)", $bind);
        if ($query->numrows > 0) {
            $html .= "<optgroup label=\"{$T['U']}\">";
        }
        while ($query->get_row()) {
            $html .= "<option value='" . $query->row['TIPO'] . $query->row['ID'] . "'>" . $query->row['DESCRIZIONE'] . " (" . $query->row['ID'] . ") </option>";
            $list[] = 'U:' . $query->row['ID'];
        }
        // Tutti i siti associati ai miei studi
        $rubrica_siti = $query->exec("SELECT DISTINCT 'C' TIPO, us.site_id ID, s.DESCR || ' (' || us.site_id || ')' DESCRIZIONE FROM users_sites_studies us, sites s WHERE us.study_prefix IN (SELECT STUDY_PREFIX FROM USERS_STUDIES WHERE ACTIVE = 1 AND USERID = :userid) and s.id = us.SITE_ID and s.active = 1", $bind);
        if ($query->numrows > 0) {
            $html .= "<optgroup label=\"{$T['C']}\">";
        }
        while ($query->get_row()) {
            $html .= "<option value='" . $query->row['TIPO'] . $query->row['ID'] . "'>" . $query->row['DESCRIZIONE'] . "</option>";
            $list[] = 'C:' . $query->row['ID'];
        }

        // Tutti i profili associati ai miei studi
        $rubrica_profili = $query->exec("select 'P' tipo, code as code, study_prefix as study_prefix, code || '-' || study_prefix id, code || '-' || study_prefix descrizione from studies_profiles where ACTIVE = 1 and study_prefix IN (SELECT STUDY_PREFIX FROM USERS_STUDIES WHERE ACTIVE = 1 AND USERID = :userid)", $bind);
        if ($query->numrows > 0) {
            $html .= "<optgroup label=\"{$T['P']}\">";
        }
        while ($query->get_row()) {
            $html .= "<option value='" . $query->row['TIPO'] . $query->row['ID'] . "'>" . mlOut('Profile_' . $query->row['CODE'] . '.profileName') . " (" . $query->row['STUDY_PREFIX'] . ")</option>";
            $list[] = 'P:' . $query->row['ID'];
        }

        // Tutti i siti che posso vedere
        $rubrica_studi = $query->exec("select 'S' TIPO, prefix ID, descr || ' (' || prefix || ')' DESCRIZIONE from studies where prefix in (SELECT distinct STUDY_PREFIX FROM USERS_STUDIES WHERE ACTIVE = 1 AND USERID = :userid)", $bind);
        if ($query->numrows > 0) {
            $html .= "<optgroup label=\"{$T['S']}\">";
        }
        while ($query->get_row()) {
            $html .= "<option value='" . $query->row['TIPO'] . $query->row['ID'] . "'>" . $query->row['DESCRIZIONE'] . "</option>";
            $list[] = 'S:' . $query->row['ID'];
        }
        if ($formato == 'options') {
            return $html;
        } elseif ($formato == 'array') {
            return $list;
        } else {
            return "";
        }

    }

    function get_messaggio($messaggio)
    {

        $id_messaggio = $messaggio['ID_MESSAGGIO'];
        $mittente = $messaggio['MITTENTE'];
        $oggetto = $messaggio['OGGETTO'];
        $corpo = $messaggio['CORPO'];
        $data_invio = $messaggio['DATA_INVIO'];

        $html = "
        <div id=\"messaggi\">
<div id=\"id-message-list-navbar\" class=\"message-navbar align-center clearfix\">
                <div class=\"messagebar-item-left\">
                    <a class=\"btn-back-message-list no-hover-underline\" href=\"#\" onclick=\"inbox_pannello('bacheca');\">
                        <i class=\"icon-arrow-left blue bigger-110 middle\"></i>
                        <b class=\"middle bigger-110\">%Indietro%</b>
                    </a>
                </div>
  <div class=\"message-bar\">
    <div class=\"message-infobar\" id=\"id-message-infobar\">
      <span class=\"blue bigger-150\">{$oggetto}</span>
      <span class=\"grey bigger-110\"></span>
    </div>
  </div>
</div>
<div class=\"message-content\" id=\"id-message-content\">
    <div class=\"message-header clearfix\">
        <div class=\"pull-left\">
            <span class=\"blue bigger-125\"></span>
            <div class=\"space-4\"></div>
            
            <span class=\"blue\">{$mittente}</span> <i class=\"icon-time bigger-110 orange middle\"></i> <span class=\"orange\">{$data_invio}</span>
        </div>
        <div class=\"action-buttons pull-right\">
        </div>
    </div>
    <div class=\"hr hr-double\"></div>
    <div style=\"position: relative; overflow: hidden; width: auto; height: 200px;\" class=\"slimScrollDiv\"><div style=\"overflow: hidden; width: auto; height: 200px;\" class=\"message-body\">
            {$corpo}
    </div>
    <div style=\"background: none repeat scroll 0% 0% rgb(0, 0, 0); width: 7px; position: absolute; top: 0px; opacity: 0.4; display: none; border-radius: 7px; z-index: 99; right: 1px; height: 200px;\" class=\"slimScrollBar ui-draggable\"></div><div style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; background: none repeat scroll 0% 0% rgb(51, 51, 51); opacity: 0.2; z-index: 90; right: 1px;\" class=\"slimScrollRail\"></div>
</div></div>
</div>

";
        unset($bind);
        $bind['USERID'] = $_SERVER['REMOTE_USER'];
        $bind['ID_MESSAGGIO'] = $id_messaggio;
        $queryUpd = new query($this->conn);
        $sqlUpd = "update inbox_corrispondenza set data_visualizzazione = sysdate where id_messaggio = :id_messaggio and userid = :userid and data_visualizzazione is null";
        $queryUpd->exec($sqlUpd, $bind);
        $this->conn->commit();
        return $html;
    }

    function get_navbarbtn()
    {
        unset($bind);
        $bind['USERID'] = $_SERVER['REMOTE_USER'];
        $sql = "select count(*) conteggio from inbox_corrispondenza where data_visualizzazione is null and data_eliminazione is null and userid = :userid";
        $query_cont = new query($this->conn);
        $query_cont->exec($sql, $bind);
        if ($query_cont->get_row()) {
            $conteggio = $query_cont->row['CONTEGGIO'];
        }
        $html = "<div class=\"btn btn-app btn-xs btn-warning ace-settings-btn\" id=\"ace-settings-btn\">
                        <i class=\"icon-envelope bigger-125" . ($conteggio != 0 ? " icon-animated-vertical" : "") . "\"></i>";
        $html = "";
        if ($conteggio > 0) {
            $html .= "<span class=\"white badge badge-important\">{$conteggio}</span>";
        }
        /*
        $html .= "
        		
        		</div>";
        */
        return $html;
    }

    function get_mail($formato, $tipo)
    {
        $query = new query($this->conn);
        unset($bind);
        if (isset($_GET['msg']) && $formato != 'navbar') {
            $bind['ID_MESSAGGIO'] = $_GET['msg'];
            $formato = 'messaggio';
            if (isset($_GET['sent'])) {
                $tipo = "sent";
            }
        }
        $bind['USERID'] = $_SERVER['REMOTE_USER'];
        $html = "";
        if ($tipo == 'inbox') {
            $sql = "select * from (select rownum ord, m.id_messaggio, m.data_invio, m.corpo, m.userid, a.nome || ' ' || a.cognome mittente, m.oggetto, c.data_visualizzazione from inbox_messaggi m, inbox_corrispondenza c, ana_utenti_1 a where c.userid = :userid and m.id_messaggio = c.ID_MESSAGGIO and m.userid = a.userid (+) and c.data_eliminazione is null order by data_invio desc) " . ($bind['ID_MESSAGGIO'] != '' ? 'where id_messaggio = :id_messaggio' : '') . ($formato == 'navbar' ? 'where ord between 1 and 5' : '');
            $query->exec($sql, $bind);

            /*
            if ($formato == 'navbar') {
                $html .= "
                <li class='inbox_bar-header'>
                                    <i class='icon-envelope-alt'></i>
                                    Inbox
                                </li>";
            }
            */
            if ($query->numrows == 0) {
                $html .= "<div style=\"text-align:center\"><a  href=\"index.php?inbox#write\">
								<i class=\"el-icon-edit\"></i>&nbsp; " . mlOut("MSG.NewMessage", "New message") . "
							</a></div><div class=\"message-item\">%Nessun messaggio%</div>";
            }
            while ($query->get_row()) {

                if ($formato == 'html') {
                    $html .= "<div class=\"message-item" . ($query->row['DATA_VISUALIZZAZIONE'] == "" ? " message-unread" : "") . "\" data-messaggio=\"{$query->row['ID_MESSAGGIO']}\">
        <i class=\"orange2\"></i>
        <span title=\"%utente% {$query->row['USERID']}\" class=\"sender\">{$query->row['MITTENTE']}</span>
        <span class=\"time\" style=\"padding-right:150px;\">{$query->row['DATA_INVIO']}</span>        
        <span class=\"summary\">
            <span class=\"text\">
                <a href=\"index.php?inbox&msg={$query->row['ID_MESSAGGIO']}\">{$query->row['OGGETTO']}</a>
            </span>
        </span>
    </div>";
                } elseif ($formato == 'navbar') {
                    $html .= "
                    	<li>
                                    <a href=\"index.php?inbox&msg={$query->row['ID_MESSAGGIO']}\" style=\"font-size:11px;\" >
									" . ($query->row['DATA_VISUALIZZAZIONE'] == '' ? "<i class=\"fa fa-exclamation\"></i>" : "") . "
											<i class=\"icon-envelope " . ($query->row['DATA_VISUALIZZAZIONE'] == '' ? "  icon-animated-vertical" : "") . "\"></i>
									<span class=\"msg-body\">
									<span class=\"msg-title\">
									<span class=\"blue\">{$query->row['MITTENTE']}:</span>
									{$query->row['OGGETTO']}
									</span><br/>
									<span class=\"msg-time\">
									<i class=\"icon-time\"></i>
									<span>{$query->row['DATA_INVIO']}</span>
									</span>
									</span>
									</a>
									</li>
									";
                } elseif ($formato == 'messaggio') {
                    $html .= $this->get_messaggio($query->row);
                }
            }
            //el-icon-pencil diverso da icon-pencil. sono 2 librerie diverse con dimensione icone diverse.
            //possiamo usare anche icon-pencil ma con accortezza di ridefinire il padding.
            if ($formato == 'navbar') {
                $html = "
                		<li class=\"divider\"></li>
                		<li class=\"dropdown-header\" style=\"text-align:center;\"><i class=\"icon-envelope-alt\"></i>
							" . mlOut("System.lastMessages", "Last Messages") . "
                	     </li>
                			<!--
				                <div class='navbar_footer'>
                                    <a href=\"index.php?inbox\">
                                        See all messages
                                        <i class=\"el-icon-eye-open\"></i>
                                    </a>
                                </div>
                		-->
                		" . $html . "<li>
                                    <a href=\"index.php?inbox#write\" style=\"padding-left:10px;\">
                						<i class=\"icon-pencil\" style=\"margin-right:3px;\"></i> " . mlOut("System.newMessage", "New Message") . "
                					</a>
                				</li>
                			    <li>
                                    <a href=\"index.php?inbox\">
                						<i class=\"el-icon-eye-open\"></i> " . mlOut("System.Messages", "InBox") . "
                					</a>
                				</li>
                								
                								";
            }
        } elseif ($tipo == 'sent') {
            $sql = "SELECT a.nome || ' ' || a.cognome mittente, m.id_messaggio, m.data_invio, m.oggetto, m.corpo, m.destinatari FROM inbox_messaggi m, ana_utenti_1 a WHERE m.userid = :userid and m.userid = a.userid (+) " . ($bind['ID_MESSAGGIO'] != '' ? 'and id_messaggio = :id_messaggio ' : '') . "ORDER BY data_invio DESC";
            $query->exec($sql, $bind);
            if ($query->numrows == 0) {
                $html .= "<div class=\"message-item\">%Nessun messaggio%</div>";
            }
            while ($query->get_row()) {

                if ($formato == 'messaggio') {
                    $html .= $this->get_messaggio($query->row);
                } else {

                    $html .= "<div class=\"message-item\" data-messaggio=\"{$query->row['ID_MESSAGGIO']}\">
        <!--label class=\"inline\">
            <input type=\"checkbox\" class=\"ace\">
            <span class=\"lbl\"></span>
        </label-->
        <i class=\"orange2\"></i>
        <span title=\"%utente% {$query->row['USERID']}\" class=\"sender\">{$query->row['MITTENTE']}</span>
        <span class=\"time\" style=\"padding-right:150px;\">{$query->row['DATA_INVIO']}</span>        
        <span class=\"summary\">
            <span class=\"text\">
                <a href=\"index.php?inbox&msg={$query->row['ID_MESSAGGIO']}&sent\">{$query->row['OGGETTO']}</a>
            </span>
        </span>
    </div>";
                }
            }
        } elseif ($tipo == 'bacheca') {
            $sql = "SELECT m.id_messaggio, a.nome || ' ' || a.cognome mittente,
  m.userid,
  m.data_invio,
  case when m.userid = :userid then 1 else 0 end inviata, 
  m.oggetto,
  m.corpo, 
  case when m.userid = :userid then data_invio else (select data_visualizzazione from inbox_corrispondenza where id_messaggio = m.id_messaggio and userid = :userid) end data_visualizzazione   
FROM inbox_messaggi m, ana_utenti_1 a
WHERE (m.userid     = :userid
OR m.id_messaggio IN
  (SELECT id_messaggio FROM inbox_corrispondenza WHERE userid = :userid
  )) and a.userid = m.userid  
order by data_invio desc";
            $query->exec($sql, $bind);
            if ($query->numrows == 0) {
                $html .= "<div class=\"message-item\">%Nessun messaggio%</div>";
            }
            while ($query->get_row()) {
                if ($query->row['INVIATA'] == 1) {
                    $icona = 'reply';
                } else {
                    $icona = 'share-alt';
                }
                $html .= "<div class=\"message-item" . ($query->row['DATA_VISUALIZZAZIONE'] == "" ? " message-unread" : "") . "\" data-messaggio=\"{$query->row['ID_MESSAGGIO']}\">
        <i class=\"icon-{$icona}\"> </i>
        <span title=\"%utente% {$query->row['USERID']}\" class=\"sender\">{$query->row['MITTENTE']}</span>
        <span class=\"time\" style=\"padding-right:150px;\">{$query->row['DATA_INVIO']}</span>        
        <span class=\"summary\">
            <span class=\"text\">
                <a href=\"index.php?inbox&msg={$query->row['ID_MESSAGGIO']}" . ($query->row['INVIATA'] == 1 ? "&sent" : "") . "\">{$query->row['OGGETTO']}</a>
            </span>
        </span>
    </div>";
            }

        }

        return $this->localizza_html($html);
    }

    function do_inbox($tipo)
    {
        $html = <<<DATI
<div id="messaggi">   
    %tab%    
    %messaggi%
</div>
DATI;
        $html = str_replace('%messaggi%', $this->get_mail('html', $tipo), $html);
        $html = str_replace('%tab%', $this->do_tab($tipo), $html);
        return $this->localizza_html($html);
    }

    function do_tab($tipo)
    {
        $html = <<<DATI
    <div class="message-navbar align-center clearfix" id="id-message-list-navbar">
        <div class="message-bar">
            <div id="id-message-infobar" class="message-infobar">
                <span class="blue bigger-150">%{$tipo}%</span>
                <span class="grey bigger-110"></span>
            </div>
        </div>
    </div>
 
DATI;
        return $this->localizza_html($html);

    }

    function do_footer_mail()
    {
        $html = <<<DATI
        <div class="message-footer clearfix"></div>     
DATI;
        return $this->localizza_html($html);
    }

    function do_new_mail()
    {
        $html = <<<DATI
        <div class="message-navbar align-center clearfix" id="id-message-new-navbar">
            <div class="message-bar">
            
            </div>
            <div class="message-item-bar">
                <div class="messagebar-item-left">
                    <a class="btn-back-message-list no-hover-underline" href="#" onclick="inbox_pannello('bacheca');">
                        <i class="icon-arrow-left blue bigger-110 middle"></i>
                        <b class="middle bigger-110">%Indietro%</b>
                    </a>
                </div>
            </div>
        </div>
        <form class="form-horizontal message-form  col-xs-12" id="id-message-form">
            <div>            
                <div class="">
                    <label for="form-field-recipient" class="col-sm-12 pull-left">%Destinatari%:</label>
                    <div class="col-xs-12">
                          <select name="to" data-placeholder="%Scegli un destinatario%..." class="form-control" id="form-field-recipient" multiple="multiple">
                                %rubrica%
                            </select>
                    <div>    
                        
                <div class="hr hr-18 dotted"></div>                
                <div class="">
                    <label for="form-field-subject" class="col-sm-12 pull-left">%Oggetto%:</label>
               <div class="col-xs-12">
                        <div class="input-icon block col-xs-12 no-padding">
                            <input type="text" id="form-field-subject" name="subject" maxlength="50">
                        </div>
                    </div>
                </div>                
                <div class="hr hr-18 dotted"></div>                
                <div class="">
                    <label class="col-sm-12 pull-left">
                        <span class="inline space-24 hidden-480"></span>
                        %Messaggio%:
                    </label>
                    <div class="col-sm-12">
                        <div class="wysiwyg-editor rich-editor" id="bootbox_editor_content">
                        </div>
                    </div>        
                </div>
                <div class="hr-18"></div>
        		<br/>
                <div style="">
                    <span class="inline btn-send-message col-sm-12">
                        <button class="btn btn-sm btn-primary no-border pull-left" type="button" onclick="inbox_send();">
                            <span class="bigger-110">%Invia%</span>
                            <i class="icon-arrow-right icon-on-right"></i>
                        </button>
                    </span>
                </div>
        		<br/><br/><br/><br/>
                <div class="hr-18"></div>
            </div> </div>
        </form>    
DATI;

        $html = str_replace('%rubrica%', $this->get_rubrica('options'), $html);
        return $this->localizza_html($html);
    }

    function do_send_mail()
    {

        if ($_GET['destinatari'] == '') {
            $this->errore("%Destinatari non inseriti%");
        } elseif ($_GET['oggetto'] == '') {
            $this->errore("%Oggetto non inserito%");
        } elseif ($_GET['messaggio'] == '') {
            $this->errore("%Messaggio non inserito%");
        }
        if ($this->destinatari_verificapermessi($_GET['destinatari'])) {
            $elencodestinatari = $this->destinatari_elencousers($_GET['destinatari']);
            unset($bind);
            $bind['DESTINATARI'] = $_GET['destinatari'];
            $bind['OGGETTO'] = strip_tags($_GET['oggetto']);
            $bind['CORPO'] = strip_tags($_GET['messaggio'], '<p><a><b><font><i><strike><u><br>');
            $bind['USERID'] = $_SERVER['REMOTE_USER'];

            $query = new query($this->conn);
            $query->exec("select inbox_messaggi_seq.nextval id_messaggio from dual");
            if ($query->get_row()) {
                $bind['ID_MESSAGGIO'] = $query->row['ID_MESSAGGIO'];
            } else {
                $this->errore("%Errore sequence% INBOX_MESSAGGI_SEQ");
            }
            foreach ($elencodestinatari as $id => $destinatario) {
                $destinatari_txt[] = "'" . $destinatario . "'";
            }
            $query->exec("insert into inbox_messaggi (ID_MESSAGGIO, USERID, OGGETTO, CORPO, DESTINATARI, DATA_INVIO ) values (:id_messaggio, :userid, :oggetto, :corpo, :destinatari, sysdate )", $bind);
            $query->exec("insert into inbox_corrispondenza select inbox_corrispondenza_seq.nextval, :id_messaggio, USERID, null, null from UTENTI where USERID in (" . implode(',', $destinatari_txt) . ")", $bind);
            if ($this->conn->commit()) {
                $html = '
                <div class="alert alert-success" style="margin-bottom:0px">
                    <button data-dismiss="alert" class="close" type="button"><i class="icon-remove"></i></button>
                    <p><strong><i class="icon-ok"></i>' . mlOut("System.MsgSent", "Message sent!") . '</strong></p>
              </div>';
                $html .= $this->do_inbox('bacheca');
                $html .= "";
            } else {
                $this->errore("%Errore nell'invio del messaggio%");
            }
        } else {
            $html = "ERR:%Destinatari non validi%";
        }
        return $this->localizza_html($html);
    }

    function destinatari_split($destinatari)
    {
        foreach (explode(';', $destinatari) as $id => $destinatario_val) {
            $destinatario = explode(':', $destinatario_val);
            $destinatari_array[$destinatario[0]][] = $destinatario[1];
        }
        return $destinatari_array;
    }

    function destinatari_elencousers($destinatari, $formato = 'text')
    {
        $sql = null;
        if ($formato == 'text') {
            $destinatari_array = $this->destinatari_split($destinatari);
        } elseif ($formato == 'array') {
            $destinatari_array = $destinatari;
        }
        unset($bind);
        $bind['USERID'] = $_SERVER['REMOTE_USER'];
        foreach ($destinatari_array as $categoria => $lista) {
            foreach ($lista as $key => $value) {
                $bind[$categoria . $key] = $value;
            }
            $binded = $this->genera_bind($categoria, count($lista));
            switch ($categoria) {
                case 'U' :
                    $sqlUtenti[] = "SELECT DISTINCT USERID FROM USERS_STUDIES WHERE STUDY_PREFIX IN (SELECT STUDY_PREFIX FROM USERS_STUDIES WHERE ACTIVE = 1) AND ACTIVE  = 1 and userid in ({$binded})";
                    break;
                case 'P' :
                    $sqlUtenti[] = "SELECT DISTINCT userid FROM users_profiles WHERE profile_id IN (SELECT id FROM studies_profiles WHERE active = 1 AND code || '-'|| study_prefix in ({$binded}) )";
                    break;
                case 'C' :
                    $sqlUtenti[] = "SELECT DISTINCT us.userid FROM users_sites_studies us, sites s WHERE us.study_prefix IN (SELECT STUDY_PREFIX FROM USERS_STUDIES WHERE ACTIVE = 1) AND s.id = us.SITE_ID AND s.active = 1 and us.site_id in ({$binded})";
                    break;
                case 'S' :
                    $sqlUtenti[] = "SELECT DISTINCT userid from users_studies where active = 1 and study_prefix in ({$binded})";
                    break;
                default :
                    break;
            }
        }
        foreach ($sqlUtenti as $id => $query) {
            $sql .= (($id == 0) ? '' : ' UNION ') . $query;
        }
        $query = new query($this->conn);
        $query->exec("select * from (" . $sql . ") where userid <> :userid", $bind);
        while ($query->get_row()) {
            $elenco[] = $query->row['USERID'];
        }
        return $elenco;
    }

    function destinatari_verificapermessi($destinatari_array)
    {
        $destinatari_ammessi = $this->get_rubrica('array');
        $result = array_diff(explode(';', $destinatari_array), $destinatari_ammessi);
        if (empty($result)) {
            return true;
        } else {
            return false;
        }
    }

    function genera_bind($prefisso, $num)
    {
        $bind = null;
        for ($i = 0; $i < $num; $i++) {
            $bind .= ':' . $prefisso . $i . ($num - 1 == $i ? "" : ",");
        }
        return strtolower($bind);
    }

    function errore($messaggio)
    {
        die("ERR:" . $this->localizza_html($messaggio));
    }

    function localizza_html($html)
    {
        foreach ($this->testi as $key => $value) {
            $html = str_replace('%' . $key . '%', $value, $html);
        }
        return $html;
    }

    function set_testi()
    {
        $this->testi['Posta in arrivo'] = "Inbox";
        $this->testi['Indietro'] = "Back";
        $this->testi['Destinatari non validi'] = "Recipients not valid";
        $this->testi['Messaggi non letti'] = "New messages";
        $this->testi['Nuovo messaggio'] = "New message";
        $this->testi['Scegli un destinatario'] = "Choose a recipient";
        $this->testi['Oggetto'] = "Subject";
        $this->testi['Messaggio'] = "Message";
        $this->testi['Invia'] = "Send";
        $this->testi['Destinatari'] = "Recipients";
        $this->testi['Utenti'] = "Users";
        $this->testi['Profili'] = "Profiles";
        $this->testi['Centri'] = "Sites";
        $this->testi['Studi'] = "Studies";
        $this->testi['Nessun messaggio'] = "";
        $this->testi['bacheca'] = "Inbox";
        $this->testi['inbox'] = "Inbox";
        $this->testi['sent'] = "Sent Messages";
        $this->testi['message'] = "Message";
        if ($this->lang == 'it') {
            foreach ($this->testi as $key => $value) {
                $this->testi[$key] = $key;
            }
            $this->testi['bacheca'] = "Bacheca";
            $this->testi['inbox'] = "In arrivo";
            $this->testi['sent'] = "Inviata";
            $this->testi['message'] = "Messaggio";
        }

    }

}
