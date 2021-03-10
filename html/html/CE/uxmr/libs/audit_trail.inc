<?

/**
 * Classe di gestione degli Audit Trail
 *
 * @package Hyper
 */
class audit_trail_core_prototype {

    /**
     * Costruttore dell'oggetto, vengono presi in ingresso le informazione relative alla
     * connessione oracle, al prefisso in banca dati del serviio, alle configurazioni di sistema,
     * e all'array multiplo $vlist contenente lo schema delle form xml, degli esami e delle visite dello studio.
     *
     * @param String $service
     * @param dbconn_hyper $conn
     * @param array $config_service
     * @param array $attributes
     * @param from $xml_form
     * @return audit_trail
     */
    var $actions = array(-1 => 'Data entry error', -2 => 'Documentation of change', '' => 'Data entry update');
    function __construct($service = null, $conn = null, $config_service, $attributes, $xml_form) {
        $this -> conn = $conn;
        $this -> service = $service;
        $this -> config_service = $config_service;
        $this -> attributes = $attributes;
        $this -> xml_form = $xml_form;
        if($xml_form)$this -> table_exist($xml_form);
    }

    /**audit_trail_html($in=null)
     *
     * Questo medoto genera un tabella affiancando la classica tabella riassuntiva del paziente.
     * In tale tabella � presente il link per abilitare/disabilitare la scheda alla modalit� Audit Trail.
     *
     * @param array $in
     * @return $audit_bar
     */
    function audit_trail_html($in = null) {

        $progr = "";
        $progr_link = "";
        unset($bind);
        if ($in['PROGR'] != '') {
            $progr = " and progr=:progr";
            $bind['PROGR'] = $in['PROGR'];
            $progr_link = "&PROGR={$in['PROGR']}";
        }

        $sql_query = "
		select  fine
		  from {$this->service}_coordinate
		  where {$this->config_service['PK_SERVICE']}=:pk_service and esam=:esam and visitnum=:visitnum $progr and VISITNUM_PROGR=:visitnum_progr
		 ";
        $bind['PK_SERVICE'] = $in[$this -> config_service['PK_SERVICE']];
        $bind['ESAM'] = $in['ESAM'];
        $bind['VISITNUM'] = $in['VISITNUM'];
        $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
        $sql = new query($this -> conn);
        $sql -> exec($sql_query, $bind);
        while ($sql -> get_row()) {
            if (isset($sql -> row['FINE']) && $sql -> row['FINE'] == '1') {
                $closed_form = $sql -> row['FINE'];
            }
        }

        if (isset($closed_form) && $closed_form == '1') {
            if ($this -> config_service['lang'] == "en") {
                $link_set_audit_trail = "Set Audit Trail";
                $link_unset_audit_trail = "Unset Audit Trail";
            } else {
                $link_set_audit_trail = "Apri Audit Trail";
                $link_unset_audit_trail = "Chiudi Audit Trail";
            }
            if (isset($in['AUDIT_TRAIL']) && $in['AUDIT_TRAIL'] != '') {
                //&REGISTRY={$this->service} levato...
                $link_audit_trail .= "<p align=center>
								<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
								$link_unset_audit_trail
								</a>
							</p>";
            } else {
                $link_audit_trail .= "<p align=center>
							<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&AUDIT_TRAIL=1\">
							$link_set_audit_trail
							</a>
						</p>
					";
            }

            $audit_bar = "<table class=at_table width=100%   align=center>
				<tr>
					<td class=at_cell  align=center  style=\"vertical-align:top; height:15px;\" NOWRAP>Audit Trail </td>
				</tr>
				<tr>
					<td class=at_cell_2 align=center style=\"height:50px\" NOWRAP>{$link_audit_trail}</td>
				</tr>
				</table>
					";

            if ($this -> config_service['Mobile'] == "1") {
                if (isset($in['AUDIT_TRAIL']) && $in['AUDIT_TRAIL'] != '') {
                    $link_audit_trail = "
								<a style=\"font-size: medium; color: rgb(40, 40, 83);text-decoration: underline;\" href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
								$link_unset_audit_trail
								</a>
							";
                } else {
                    $link_audit_trail = "
							<a style=\"font-size: medium; color: rgb(40, 40, 83);text-decoration: underline;\" href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&AUDIT_TRAIL=1\">
							$link_set_audit_trail
							</a>
						
					";
                }
                $audit_bar = $link_audit_trail;
            }

        } else {
            $audit_bar = "";
        }
        return $audit_bar;
    }

    /**
     * Tale metodo crea l'HTML da inserire nel pop-up presente affianco ad ogni field della scheda in modalit� Audit Trail.
     * Tale HTML presenta la storia del field con i valori cambiati nel corso del tempo a livello di singolo campo.
     * Viene infatti interrogata la tabella S_X_NOMESTUDIO per la presentazione di tali dati.
     *
     * @param array $in
     * @return $popup_at
     */
    function audit_trail_popup($in = null, $progr = null) {
        if($this->attributes['TYPE']=='file_cme'){
            global $xml_dir;
            $document=new xml_document_prototype ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->xml_form->uploaded_file_dir );
            $document->xml_document_by_file($xml_dir.'/'.$this->attributes['XMLTYPEDEFINITION']);
            $table=preg_replace('/^'.$this->service.'_/','',$document->document['QUERYNAME']);
            return "<a href='".CMELayerWCA::detailHref($this->xml_form->tb_vals[$this->attributes['VAR']],$table)."' target='_blank' >A.T.</a>";
        }
        if ($in == '') {
            foreach ($_GET as $key => $val) {
                $in[$key] = $_GET[$key];
                $HTTP_GET_VARS[$key] = $val;
                ${$key} = $_GET[$key];
            }
        }
        if ($this -> config_service['lang'] == "en") {
            $field_features = "FIELD FEATURES";
            $html_field_name = "HTML field name";
            $oracle_table = "Oracle table";
            $oracle_field = "Oracle field";
            $action = "Reason";
            $date = "Date/Time (GMT +2h)";
            $userid = "UserID";
            $value_before = "Value before";
            $value_after = "Value after";
            $value_before_dec = "Uncoded Value before";
            $value_after_dec = "Uncoded Value after";
            $no_AT = "No audit trail for the field, yet";

        } else {
            $field_features = "CARATTERISTICHE CAMPO";
            $html_field_name = "Nome HTML del campo";
            $oracle_table = "Tabella Oracle";
            $oracle_field = "Campo Oracle";
            $action = "Motivo";
            $date = "Data/Ora (GMT +2h)";
            $userid = "Nome Utente";
            $value_before = "Valore precedente";
            $value_after = "Value successivo";
            $value_before_dec = "Decod. Valore precedente";
            $value_after_dec = "Decod. Valore successivo";
            $no_AT = "Nessun dato registrato nell'audit trail";
        }

        $table_vals = '<table class=at_table  >
				<tr>
				<td class=at_titolo cols=1>' . $action . '</td>
				<td class=at_titolo cols=1>' . $date . '</td>
				<td class=at_titolo cols=1>' . $userid . '</td>
				<td class=at_titolo cols=1>' . $value_before . '</td>
				<td class=at_titolo cols=1>' . $value_before_dec . '</td>
				<td class=at_titolo cols=1>' . $value_after . '</td>
				<td class=at_titolo cols=1>' . $value_after_dec . '</td>
				</tr>';

        if ($this -> attributes['TYPE'] == 'checkbox_hyper' || $this -> attributes['TYPE'] == 'checkbox') {
            //			print_r($this->attributes['VALUE_TXT']);
            foreach ($this->attributes['VALUE_TXT'] as $key => $val) {
                //				echo $key;
                $query_vals = new query($this -> conn);
                $sql2 = "select ACTION, to_char(MODDT, 'DD/MM/YYYY HH24:MI:SS') as MODDTPOPUP, VALUE_OLD, D_VALUE_OLD, VALUE_NEW, D_VALUE_NEW, USERID from  S_X_{$this->config_service['service']} where VAR=:var and NOMETAB=:nometab and {$this->config_service['PK_SERVICE']}=:pk_service and VISITNUM=:visitnum and VISITNUM_PROGR=:visitnum_progr and ESAM=:esam and PROGR=:progr order by MODDT";
                unset($bind);
                $bind['VAR'] = $key;
                $bind['NOMETAB'] = $this -> xml_form -> form['TABLE'];
                $bind['PK_SERVICE'] = $in[$this -> config_service['PK_SERVICE']];
                $bind['VISITNUM'] = $in['VISITNUM'];
                $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
                $bind['ESAM'] = $in['ESAM'];
                $bind['PROGR'] = $in['PROGR'];
                $query_vals -> exec($sql2, $bind);
                //				echo "$sql2";
                while ($query_vals -> get_row()) {
                    $field_audit_trail_html .= '
					<tr>
					<td class=at_cell cols=1>' . $query_vals -> row['ACTION'] . '</td>
					<td class=at_cell cols=1>' . $query_vals -> row['MODDTPOPUP'] . '</td>
				    <td class=at_cell cols=1>' . $query_vals -> row['USERID'] . '</td>
					<td class=at_cell cols=1>' . $query_vals -> row['VALUE_OLD'] . '</td>
					<td class=at_cell cols=1>' . $query_vals -> row['D_VALUE_OLD'] . '</td>
					<td class=at_cell cols=1>' . $query_vals -> row['VALUE_NEW'] . '</td>
					<td class=at_cell cols=1>' . $query_vals -> row['D_VALUE_NEW'] . '</td>
					</tr>';
                }

            }
        } elseif ($this -> attributes['TYPE'] == 'ora_hyper' || $this -> attributes['TYPE'] == 'ora') {
            $query_vals = new query($this -> conn);
            $field_var = $this -> attributes['VAR'];
            unset($bind);
            if (isset($in['PROGR']) && $in['PROGR'] != "") {
                $and_progr = "and PROGR=:progr";
                $bind['PROGR'] = $in['PROGR'];
            } elseif (isset($progr) && $progr != "") {
                /*Field progressivi*/
                $and_progr = "and PROGR=:progr";
                $bind['PROGR'] = $progr;
                $field_var = $this -> attributes['VAR'] . "_PROGR_" . $progr;
            } else {$and_progr = "";
            }
            $sql2 = "select ACTION, to_char(MODDT,'DD/MM/YYYY HH24:MI:SS') as MODDTPOPUP, VALUE_OLD, D_VALUE_OLD, VALUE_NEW, D_VALUE_NEW, USERID from  S_X_{$this->config_service['service']} where VAR=:var and NOMETAB=:nometab and {$this->config_service['PK_SERVICE']}=:pk_service and VISITNUM=:visitnum and VISITNUM_PROGR=:visitnum_progr and ESAM=:esam $and_progr  order by MODDT";
            $bind['VAR'] = $field_var;
            $bind['NOMETAB'] = $this -> xml_form -> form['TABLE'];
            $bind['PK_SERVICE'] = $in[$this -> config_service['PK_SERVICE']];
            $bind['VISITNUM'] = $in['VISITNUM'];
            $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
            $bind['ESAM'] = $in['ESAM'];
            $query_vals -> exec($sql2, $bind);
            //			echo $sql2;
            while ($query_vals -> get_row()) {
                $field_audit_trail_html .= '
				<tr>
				<td class=at_cell cols=1>' . $query_vals -> row['ACTION'] . '</td>
				<td class=at_cell cols=1>' . $query_vals -> row['MODDTPOPUP'] . '</td>
			    <td class=at_cell cols=1>' . $query_vals -> row['USERID'] . '</td>
				<td class=at_cell cols=1>' . substr($query_vals -> row['VALUE_OLD'], 0, 2) . ':' . substr($query_vals -> row['VALUE_OLD'], 2, 2) . '</td>
				<td class=at_cell cols=1>' . $query_vals -> row['D_VALUE_OLD'] . '</td>
				<td class=at_cell cols=1>' . substr($query_vals -> row['VALUE_NEW'], 0, 2) . ':' . substr($query_vals -> row['VALUE_NEW'], 2, 3) . '</td>
				<td class=at_cell cols=1>' . $query_vals -> row['D_VALUE_NEW'] . '</td>
				</tr>';
            }

        } else {
            $query_vals = new query($this -> conn);
            $field_var = $this -> attributes['VAR'];
            unset($bind);
            if (isset($in['PROGR']) && $in['PROGR'] != "") {
                $and_progr = "and PROGR=:progr";
                $bind['PROGR'] = $in['PROGR'];
            } elseif (isset($progr) && $progr != "") {
                /*Field progressivi*/
                $and_progr = "and PROGR=:progr";
                $bind['PROGR'] = $progr;
                $field_var = $this -> attributes['VAR'] . "_PROGR_" . $progr;
            } else {$and_progr = "";
            }
            if ($this -> config_service['Mobile'] == 1) {
                $sql2 = "select ACTION, to_char(MODDT,'DD/MM/YYYY HH24:MI:SS') as MODDTPOPUP, VALUE_OLD, D_VALUE_OLD, VALUE_NEW, D_VALUE_NEW, 
						 ( select USERID_INS  from {$this->xml_form->form['TABLE']} where  
							{$this->config_service['PK_SERVICE']}=:pk_service
							and VISITNUM=:visitnum and VISITNUM_PROGR=:visitnum_progr and ESAM=:esam $and_progr )
							||(select subjid from {$this->config_service['service']}_REGISTRATION 
							where  {$this->config_service['PK_SERVICE']}=:pk_service ) AS USERID 
						from  S_X_{$this->config_service['service']} where VAR=:var and NOMETAB=:nometab and {$this->config_service['PK_SERVICE']}=:pk_service and VISITNUM=:visitnum and VISITNUM_PROGR=:visitnum_progr and ESAM=:esam $and_progr  order by MODDT";
            } else {
                $sql2 = "select ACTION, to_char(MODDT,'DD/MM/YYYY HH24:MI:SS') as MODDTPOPUP, VALUE_OLD, D_VALUE_OLD, VALUE_NEW, D_VALUE_NEW, USERID 
						from  S_X_{$this->config_service['service']} where VAR=:var and NOMETAB=:nometab and {$this->config_service['PK_SERVICE']}=:pk_service and VISITNUM=:visitnum and VISITNUM_PROGR=:visitnum_progr and ESAM=:esam $and_progr  order by MODDT";
            }
            $bind['VAR'] = $field_var;
            $bind['NOMETAB'] = $this -> xml_form -> form['TABLE'];
            $bind['PK_SERVICE'] = $in[$this -> config_service['PK_SERVICE']];
            $bind['VISITNUM'] = $in['VISITNUM'];
            $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
            $bind['ESAM'] = $in['ESAM'];
            $query_vals -> exec($sql2, $bind);
            if (isset($_GET['debug_at'])) {echo "SQL per field : " . $sql2 . "<hr>";
            }

            while ($query_vals -> get_row()) {
                $field_audit_trail_html .= '
				<tr>
				<td class=at_cell cols=1>' . $query_vals -> row['ACTION'] . '</td>
				<td class=at_cell cols=1>' . $query_vals -> row['MODDTPOPUP'] . '</td>
			    <td class=at_cell cols=1>' . $query_vals -> row['USERID'] . '</td>
				<td class=at_cell cols=1>' . $query_vals -> row['VALUE_OLD'] . '</td>
				<td class=at_cell cols=1>' . $query_vals -> row['D_VALUE_OLD'] . '</td>
				<td class=at_cell cols=1>' . $query_vals -> row['VALUE_NEW'] . '</td>
				<td class=at_cell cols=1>' . $query_vals -> row['D_VALUE_NEW'] . '</td>
				</tr>';
            }
        }

        if ($query_vals -> row['MODDTPOPUP'] == '') {
            if (isset($_GET['debug_at2'])) {
                echo "Field con moddtpopup vuota: " . $field_var . " Visit: " . $in['VISITNUM'] . "<hr>";
            }
            return '';
            //$field_audit_trail_html = '<tr><td class=at_cell colspan=7>' . $no_AT . '</td></tr>';
        }

        if ($_GET['AUDIT_TRAIL'] != '' && $_GET[$this -> config_service['PK_SERVICE']] != '' && isset($_GET['CRF'])) {
            /**
             * Dossier del paziente con Audit Trail
             */
            $add_visitnum = "_" . $in['VISITNUM'];
        }

        $table_vals .= $field_audit_trail_html . '</table>';

        $audit_trail = '<table class=at_table  >
			<td class=at_head colspan=2>' . $field_features . '</td>
			<tr>
				<td class=at_cell>' . $field_features . '</td>
				<td class=at_cell>' . $this -> xml_form -> form['TABLE'] . '.' . $this -> attributes['VAR'] . '</td>
			<tr>
			<tr>
				<td class=at_cell>' . $oracle_table . '</td>
				<td class=at_cell>' . $this -> xml_form -> form['TABLE'] . '</td>
			<tr>
			<tr>
				<td class=at_cell>' . $oracle_field . '</td>
				<td class=at_cell>' . $this -> attributes['VAR'] . '</td>
			<tr>
			<!--tr>
				<td class=at_cell>Label</td>
				<td class=at_cell>' . $this -> attributes['DESCRIPTION'] . '</td>
			<tr-->
			</table>
						' . $table_vals;

        $popup_at .= '<a ><div  id="AT_' . $this -> attributes['VAR'] . $add_visitnum . '"  style="display:none" >' . $audit_trail . '</div><div  style="vertical-align:top;background-color:transparent;text-align:center;" onclick="if(!menuShown){Tip(document.getElementById(\'AT_' . $this -> attributes['VAR'] . $add_visitnum . '\').innerHTML, STICKY, true,  PADDING, 6, CLOSEBTN, true,DELAY, 300,TITLEBGCOLOR,\'#00FF00\',BORDERCOLOR,\'#00FF00\');menuShown=true;}" onmouseover="document.body.style.cursor=\'pointer\'";  onmouseout="document.body.style.cursor=\'default\'";><b >A.T.<b> &nbsp;&nbsp;</a></div>';

        if (isset($progr) && $progr != "") {
            /** per field progressivi **/
            $audit_trail = '<table class=at_table  >
			<td class=at_head colspan=2>' . $field_features . '</td>
			<tr>
				<td class=at_cell>' . $field_features . '</td>
				<td class=at_cell>' . $this -> xml_form -> form['TABLE'] . '.' . $this -> attributes['VAR'] . "_PROGR_" . $progr . '</td>
			<tr>
			<tr>
				<td class=at_cell>' . $oracle_table . '</td>
				<td class=at_cell>' . $this -> xml_form -> form['TABLE'] . '</td>
			<tr>
			<tr>
				<td class=at_cell>' . $oracle_field . '</td>
				<td class=at_cell>' . $this -> attributes['VAR'] . "_PROGR_" . $progr . '</td>
			<tr>
			</table>
						' . $table_vals;
            $popup_at = '<a ><div  id="AT_' . $this -> attributes['VAR'] . "_PROGR_" . $progr . '"  style="display:none" >' . $audit_trail . '</div><div  style="vertical-align:top;background-color:transparent;text-align:center; " onclick="if(!menuShown){Tip(document.getElementById(\'AT_' . $this -> attributes['VAR'] . "_PROGR_" . $progr . '\').innerHTML, STICKY, true,  PADDING, 6, CLOSEBTN, true,DELAY, 300,TITLEBGCOLOR,\'#00FF00\',BORDERCOLOR,\'#00FF00\');menuShown=true;}" onmouseover="document.body.style.cursor=\'pointer\'";  onmouseout="document.body.style.cursor=\'default\'";><b >A.T.<b> &nbsp;&nbsp;</a></div>';

        }

        return $popup_at;
    }

    /**
     * Tale metodo viene chiamato al salvataggio e all'invio di una scheda.
     * Viene creato un array con i valori presenti in banca dati realtivi al paziente e alle coordinate attuali.
     * Vengono confrontati i valori prensenti nell'array session_vars con l'array costruito e in caso di differenza
     * viene inserito un record nella tabella S_X_NOMESTUDIO che conterr� tutto lo storico a livello di campo.
     *
     *
     * @param array $xml_form, var $from_eq, array $session_vars
     * @return void
     */
    function audit_trail_difference($xml_form = null, $from_eq = null, $session_vars = null) {
        global $in;
        if ($this -> table_exist($xml_form)) {
            $in['remote_userid'] = strtoupper($_SERVER['REMOTE_USER']);
            /*Tale metodo viene chiamato in salva_form e invia_form, presente nello study_prorotype.inc*/
            //			$debug=1;
            if ($debug == 1) {
                echo "Campi valorizzati che si trovano in POST (cambiati e non) :<br>";
                echo "<pre>";
                print_r($_POST);
                echo "</pre>";
                echo "Tabella della form:<br>";
                print_r($xml_form -> form['TABLE']);
            }
            /* In $_POST , come in session_vars ho i valori che ho checkato nella form 'aperta', diversi da quelli in DB
             * in teoria (un utente potrebbe pure cambiare e tornare indietro
             * rimettendo il valore in DB).
             * Prendo la chiave primaria da session vars e mi prendo il record in DB,lo metto in un array
             * Si fa un ciclo confrontando tale array con session_vars
             */

            if ($_POST[$xml_form -> PK_SERVICE] != 'next') {
                if ($debug == 1) {
                    echo "<br />Chiave primaria del servizio:<br>";
                    echo "<pre>";
                    echo $xml_form -> PK_SERVICE;
                    echo "</pre>";
                    echo "Valore della chiave primaria:<br>";
                    echo $POST[$xml_form -> PK_SERVICE];
                }

                $session = new query($this -> conn);
                $session -> set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DDMMYYYY'");
                $session -> ins_upd();
                unset($bind);
                if ($from_eq != null) {
                    $sql = "select * from {$xml_form->form['TABLE']}
					where center=:center
					and $xml_form->PK_SERVICE=:pk_service
					and esam=:esam
					and visitnum=:visitnum
					and visitnum_progr=:visitnum_progr
					and progr=:progr";
                    $bind['CENTER'] = $session_vars['CENTER'];
                    $bind['PK_SERVICE'] = $_GET[$xml_form -> PK_SERVICE];
                    $bind['ESAM'] = $session_vars['ESAM'];
                    $bind['VISITNUM'] = $session_vars['VISITNUM'];
                    $bind['VISITNUM_PROGR'] = $session_vars['VISITNUM_PROGR'];
                    $bind['PROGR'] = $session_vars['PROGR'];
                } else {
                    $sql = "select * from {$xml_form->form['TABLE']} where center=:center and $xml_form->PK_SERVICE=:pk_service and esam=:esam and visitnum=:visitnum and visitnum_progr=:visitnum_progr and progr=:progr";
                    $bind['CENTER'] = $_POST['CENTER'];
                    $bind['PK_SERVICE'] = $_POST[$xml_form -> PK_SERVICE];
                    $bind['ESAM'] = $_POST['ESAM'];
                    $bind['VISITNUM'] = $_POST['VISITNUM'];
                    $bind['VISITNUM_PROGR'] = $_POST['VISITNUM_PROGR'];
                    $bind['PROGR'] = $_POST['PROGR'];
                }

                $query = new query($this -> conn);
                $query -> exec($sql, $bind);

                $query -> get_row();
                $equery_old_values = $query -> row;
            }

            if ($debug == 1) {
                echo "<br><br>Query in DB per il record vecchio (anche campi non valorizzati) :<br>";
                echo $sql;
                echo "<br><br>Record vecchio in DB:";
                echo "<pre>";
                print_r($equery_old_values);
                echo "</pre>";
            }

            /*Caso della form di registrazione, prendo il currval della sequence della primary key del servizio */
            if ($_POST[$xml_form -> PK_SERVICE] == 'next') {
                if ($_POST['ESAM'] == 0 && $_POST['VISITNUM'] == 0) {
                    return;
                    $pk_service = $xml_form -> config_service['service'] . "_PK_SEQ.nextval";
                } else {
                    $pk_service = $xml_form -> config_service['service'] . "_PK_SEQ.currval";
                }
            } else if ($from_eq != null) {
                $pk_service = $_GET[$xml_form -> PK_SERVICE];
            } else {
                $pk_service = $_POST[$xml_form -> PK_SERVICE];
            }

            if (isset($_POST['PROGR']) && $_POST['PROGR'] != '') {$progr = $_POST['PROGR'];
            } else if ($from_eq != null && $_GET['PROGR'] != null) { $progr = $_GET['PROGR'];
            } else {$progr = 1;
            }

            //			print_r($xml_form);

            //$action=$this->CheckAction($xml_form,$from_eq);
            $action = $this -> interpret_action($in['ID_QUERY']);

            foreach ($xml_form->fields as $key => $val) {
                //				print($key."->".$val."<br>"); print_r($val); echo "<br>";
                //				print_r($xml_form->fields[$key]['VALUE']);

                //Gestione Checkbox
                foreach ($xml_form->fields[$key]['VALUE'] as $k => $v) {

                    if ($xml_form -> fields[$key]['TYPE'] == 'checkbox_hyper' || $xml_form -> fields[$key]['TYPE'] == 'checkbox') {
                        //					Per i checkbox: $k � il nome della colonna in db
                        //						print($k."->".$v."<br>");
                        //					$_POST[$k] � il valore : 1 se checckato , null se non checkato
                        //						print_r($_POST[$k]);
                        //						print_r($xml_form->fields[$key]['TYPE']);
                        if ($_POST[$k] != '') {

                            //Quando checko
                            //							print_r($equery_old_values[$k]." -> valore vecchio");
                            if ($equery_old_values[$k] == '' || $equery_old_values[$k] == 0) {
                                //								$action="Update";// da rivedere

                                $values['VISITNUM'] = $_POST['VISITNUM'];
                                $values['VISITNUM_PROGR'] = $_POST['VISITNUM_PROGR'];
                                $values['ESAM'] = $_POST['ESAM'];
                                $values['PROGR'] = $progr;
                                $values[$xml_form -> PK_SERVICE] = $pk_service;
                                $values['CENTER'] = $_POST['CENTER'];
                                $values['NOMETAB'] = $xml_form -> form['TABLE'];
                                $values['VAR'] = $k;
                                $values['FIELD'] = $xml_form -> fields[$key]['DESCRIPTION'];
                                $values['VALUE_NEW'] = $_POST[$k];
                                $values['D_VALUE_NEW'] = '';
                                $values['VALUE_OLD'] = '';
                                $values['D_VALUE_OLD'] = '';
                                $values['MODDT'] = sysdate;
                                //$values['USERID']=$_POST['USERID_INS'];//userid corrente!!
                                $values['USERID'] = $in['remote_userid'];
                                $values['ACTION'] = $action;

                                $ins_sql = new query($this -> conn);

                                $ins_sql -> insert($values, "S_X_{$xml_form->config_service['service']}");

                                //$this -> conn -> commit();

                            }

                        } else {

                            //Quando de-checko
                            $sql_checkbox = "select nvl($k,99) as UNCHECK, ge.* from  {$xml_form->form['TABLE']} ge where center=:center and {$xml_form->PK_SERVICE}=:pk_service
												and esam=:esam and visitnum=:visitnum and visitnum_progr=:visitnum_progr and progr=:progr
													";
                            unset($bind);
                            $bind['CENTER'] = $_POST['CENTER'];
                            $bind['PK_SERVICE'] = $_POST[$xml_form -> PK_SERVICE];
                            $bind['ESAM'] = $_POST['ESAM'];
                            $bind['VISITNUM'] = $_POST['VISITNUM'];
                            $bind['VISITNUM_PROGR'] = $_POST['VISITNUM_PROGR'];
                            $bind['PROGR'] = $_POST['PROGR'];
                            $query2 = new query($this -> conn);
                            $query2 -> exec($sql_checkbox, $bind);

                            $query2 -> get_row();
                            $uncheck = $query2 -> row['UNCHECK'];
                            //							print_r($uncheck);
                            //							print_r($k);
                            if ($uncheck != '' && $uncheck != 0 && $uncheck != 99) {
                                //Prima era checkato e ora l'ho decheckato, e metto null nell'audit trail
                                //								$action="Update";
                                //il valure old sar� quello che trovo dalla select nella S_ , il value new sar� null.

                                $values['VISITNUM'] = $_POST['VISITNUM'];
                                $values['VISITNUM_PROGR'] = $_POST['VISITNUM_PROGR'];
                                $values['ESAM'] = $_POST['ESAM'];
                                $values['PROGR'] = $progr;
                                $values[$xml_form -> PK_SERVICE] = $pk_service;
                                $values['CENTER'] = $_POST['CENTER'];
                                $values['NOMETAB'] = $xml_form -> form['TABLE'];
                                $values['VAR'] = $k;
                                $values['FIELD'] = $xml_form -> fields[$key]['DESCRIPTION'];
                                $values['VALUE_NEW'] = '';
                                $values['D_VALUE_NEW'] = '';
                                $values['VALUE_OLD'] = $uncheck;
                                $values['D_VALUE_OLD'] = '';
                                $values['MODDT'] = sysdate;
                                //$values['USERID']=$_POST['USERID_INS'];//userid corrente!!
                                $values['USERID'] = $in['remote_userid'];
                                $values['ACTION'] = $action;

                                $ins_sql = new query($this -> conn);

                                $ins_sql -> insert($values, "S_X_{$xml_form->config_service['service']}");

                                //$this -> conn -> commit();

                            }
                        }
                    }
                }
                //Fine Gestione Checkbox

                if (isset($_POST['PROGR']) && $_POST['PROGR'] != '') {$progr = $_POST['PROGR'];
                } else {$progr = 1;
                }

                // Gestione decodifiche
                if ($debug == 1) {
                    print_r($val['VAR'] . " -> NOMECAMPO ");
                    print_r($_POST[$val['VAR']] . "   -> VALORE<br>");
                }

                $valore = $_POST[$val['VAR']];
                //				print_r($xml_form->fields[$key]['VALUE'][$valore]);

                if ($xml_form -> fields[$key]['VALUE'][$valore] != '') {
                    //					print_r($val['VAR']." -> NOMECAMPO ");
                    //					print_r($_POST[$val['VAR']]."   -> VALORE<br>");
                    $dec_new_value = $xml_form -> fields[$key]['VALUE'][$valore];
                    //					print_r($equery_old_values['D_'.$xml_form->fields[$key]['VAR']]);
                    $dec_old_value = $equery_old_values['D_' . $xml_form -> fields[$key]['VAR']];
                } else {
                    $dec_new_value = '';
                    $dec_old_value = '';
                }
                // Fine Gestione decodifiche

                if ($xml_form -> fields[$key]['TYPE'] == 'ora_hyper') {
                    $_POST[$xml_form -> fields[$key]['VAR']] = $_POST[$xml_form -> fields[$key]['VAR'] . "_H"] . $_POST[$xml_form -> fields[$key]['VAR'] . "_M"];
                }
                if ($xml_form -> fields[$key]['TYPE'] == 'date_hyper') {
                    /**  Gestione NA e NK salvati in POST con form in compilazione : Valore nuovo **/
                    $_POST[$xml_form -> fields[$key]['VAR']] = $_POST[$xml_form -> fields[$key]['VAR'] . "D"] . $_POST[$xml_form -> fields[$key]['VAR'] . "M"] . $_POST[$xml_form -> fields[$key]['VAR'] . "Y"];
                    if (preg_match("/\-9911/", $_POST[$xml_form -> fields[$key]['VAR']])) {
                        $_POST[$xml_form -> fields[$key]['VAR']] = str_replace("-9911", "NA", $_POST[$xml_form -> fields[$key]['VAR']]);
                    }
                    if (preg_match("/\-9922/", $_POST[$xml_form -> fields[$key]['VAR']])) {
                        $_POST[$xml_form -> fields[$key]['VAR']] = str_replace("-9922", "NK", $_POST[$xml_form -> fields[$key]['VAR']]);
                    }

                    /**  Gestione NA e NK salvati in Db con form in compilazione : Valore vecchio **/
                    $months_nn['NA'] = -9911;
                    $months_nn['NK'] = -9922;
                    if (substr($equery_old_values[$xml_form -> fields[$key]['VAR'] . 'RC'], 0, 2) != 'OK') {
                        $dd = substr($equery_old_values[$xml_form -> fields[$key]['VAR'] . 'RC'], 0, 2);
                    } else
                        $dd = substr($equery_old_values[$xml_form -> fields[$key]['VAR']], 0, 2);
                    if (substr($equery_old_values[$xml_form -> fields[$key]['VAR'] . 'RC'], 2, 2) != 'OK') {
                        $mm = substr($equery_old_values[$xml_form -> fields[$key]['VAR'] . 'RC'], 2, 2);
                    } else
                        $mm = substr($equery_old_values[$xml_form -> fields[$key]['VAR']], 2, 2);
                    if (substr($equery_old_values[$xml_form -> fields[$key]['VAR'] . 'RC'], 4, 2) != 'OK') {
                        $yyyy = substr($equery_old_values[$xml_form -> fields[$key]['VAR'] . 'RC'], 4, 2);
                    } else
                        $yyyy = substr($equery_old_values[$xml_form -> fields[$key]['VAR']], 4, 4);

                    $equery_old_values[$xml_form -> fields[$key]['VAR']] = $dd . $mm . $yyyy;
                    /**  Fine Gestione NA e NK salvati in Db con form in compilazione **/
                }

                // Gestione NA, NK, ecc.. nei campi textbox_hyper
                // 				if ($xml_form->fields[$key]['TYPE']=='textbox_hyper' && (
                // 					$equery_old_values[$xml_form->fields[$key]['VAR']] == "-9911" ||
                // 					$equery_old_values[$xml_form->fields[$key]['VAR']] == "-9922" ||
                // 					$equery_old_values[$xml_form->fields[$key]['VAR']] == "-9933" ||
                // 					$equery_old_values[$xml_form->fields[$key]['VAR']] == "-9944" ||
                // 					$equery_old_values[$xml_form->fields[$key]['VAR']] == "-9955" ||
                // 					$equery_old_values[$xml_form->fields[$key]['VAR']] == "-9900"
                // 				)) {
                // 					$_POST[$xml_form->fields[$key]['VAR']]=str_replace("NA", "-9911", $_POST[$xml_form->fields[$key]['VAR']]);
                // 					$_POST[$xml_form->fields[$key]['VAR']]=str_replace("NK", "-9922", $_POST[$xml_form->fields[$key]['VAR']]);
                // 					$_POST[$xml_form->fields[$key]['VAR']]=str_replace("ND", "-9933", $_POST[$xml_form->fields[$key]['VAR']]);
                // 					$_POST[$xml_form->fields[$key]['VAR']]=str_replace("NP", "-9944", $_POST[$xml_form->fields[$key]['VAR']]);
                // 					$_POST[$xml_form->fields[$key]['VAR']]=str_replace("TE", "-9955", $_POST[$xml_form->fields[$key]['VAR']]);
                // 					$_POST[$xml_form->fields[$key]['VAR']]=str_replace("OT", "-9900", $_POST[$xml_form->fields[$key]['VAR']]);
                // 				}

                if ($debug == 1) {
                    echo $xml_form -> fields[$key]['VALUE'];
                    echo "<hr>Colonna in DB della form, vecchio-nuovo<br>";
                    echo $_GET['EQFIELD'];
                    echo $xml_form -> fields[$key]['VAR'];
                    // valore dell'array per quella colonna
                    echo "<br>";
                    echo $equery_old_values[$xml_form -> fields[$key]['VAR']];
                    echo "<br>";
                    echo $_POST[$xml_form -> fields[$key]['VAR']];
                    echo "<br>";
                }

                //Logger::info($equery_old_values[$xml_form->fields[$key]['VAR']]);
                //Logger::info($_POST[$xml_form->fields[$key]['VAR']]);

                if ($equery_old_values[$xml_form -> fields[$key]['VAR']] != $_POST[$xml_form -> fields[$key]['VAR']] && $xml_form -> fields[$key]['TYPE'] != 'checkbox_hyper' && $xml_form -> fields[$key]['TYPE'] != 'checkbox' && $xml_form -> fields[$key]['TYPE'] != 'password_hyper') {
                    //					$action="Update";// da rivedere

                    $values['VISITNUM'] = $_POST['VISITNUM'];
                    $values['VISITNUM_PROGR'] = $_POST['VISITNUM_PROGR'];
                    $values['ESAM'] = $_POST['ESAM'];
                    $values['PROGR'] = $progr;
                    $values[$xml_form -> PK_SERVICE] = $pk_service;
                    $values['CENTER'] = $_POST['CENTER'];
                    $values['NOMETAB'] = $xml_form -> form['TABLE'];
                    $values['VAR'] = $xml_form -> fields[$key]['VAR'];
                    $values['FIELD'] = $xml_form -> fields[$key]['DESCRIPTION'];
                    $values['VALUE_NEW'] = $_POST[$xml_form -> fields[$key]['VAR']];
                    $values['D_VALUE_NEW'] = $dec_new_value;
                    $values['VALUE_OLD'] = $equery_old_values[$xml_form -> fields[$key]['VAR']];
                    $values['D_VALUE_OLD'] = $equery_old_values['D_' . $xml_form -> fields[$key]['VAR']];
                    $values['MODDT'] = sysdate;
                    //$values['USERID']=$_POST['USERID_INS'];//userid corrente!!
                    $values['USERID'] = $in['remote_userid'];

                    $values['ACTION'] = $action;

                    $ins_sql = new query($this -> conn);

                    $ins_sql -> insert($values, "S_X_{$xml_form->config_service['service']}");

                    //$this -> conn -> commit();

                }
            } //fine foreach superiore dei fileds
        }
    }

    /**
     * Tale metodo viene chiamato al salvataggio e all'invio di una scheda.
     * Viene creato un array con i valori presenti in banca dati realtivi al paziente e alle coordinate attuali.
     * Vengono confrontati i valori prensenti nell'array session_vars con l'array costruito e in caso di differenza
     * viene inserito un record nella tabella S_X_NOMESTUDIO che conterr� tutto lo storico a livello di campo.
     *
     *
     * @param array $xml_form, var $from_eq, array $session_vars
     * @return void
     */
    function audit_trail_diff_all_in($xml_form = null, $from_eq = null, $session_vars = null, $progr) {
        $in['remote_userid'] = strtoupper($_SERVER['REMOTE_USER']);
        $xml_form -> session_vars['PROGR'] = $progr;
        if ($this -> table_exist($xml_form)) {
            $session = new query($this -> conn);
            $session -> set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DDMMYYYY'");
            $session -> ins_upd();
            unset($bind);
            $bind['CENTER'] = $session_vars['CENTER'];
            $bind['ESAM'] = $session_vars['ESAM'];
            $bind['VISITNUM'] = $session_vars['VISITNUM'];
            $bind['VISITNUM_PROGR'] = $session_vars['VISITNUM_PROGR'];

            if ($from_eq != null) {//da rivedere per le eQ
                $sql = "select * from {$xml_form->form['TABLE']}
						where center='{$session_vars['CENTER']}'
						and $xml_form->PK_SERVICE='{$_GET[$xml_form->PK_SERVICE]}'
						and esam='{$session_vars['ESAM']}'
						and visitnum='{$session_vars['VISITNUM']}'
						and visitnum_progr='{$session_vars['VISITNUM_PROGR']}'
						and progr='{$session_vars['PROGR']}'";
                $bind['PK_SERVICE'] = $_GET[$xml_form -> PK_SERVICE];
                $bind['PROGR'] = $session_vars['PROGR'];
            } else {
                $sql = "select * from {$xml_form->form['TABLE']} where
						center='{$session_vars['CENTER']}' and $xml_form->PK_SERVICE='{$session_vars[$xml_form->PK_SERVICE]}' and
						esam='{$session_vars['ESAM']}' and
						visitnum='{$session_vars['VISITNUM']}' and
						visitnum_progr='{$session_vars['VISITNUM_PROGR']}' and
						progr='{$progr}'";
                $bind['PK_SERVICE'] = $session_vars[$xml_form -> PK_SERVICE];
                $bind['PROGR'] = $progr;
            }
            $session -> exec($sql, $bind);
            $session -> get_row();
            $equery_old_values = $session -> row;

        }

        $action = $this -> CheckAction($xml_form, $from_eq);

        foreach ($xml_form->fields as $key => $val) {

            $valore = $session_vars[$val['VAR'] . "_PROGR_" . $progr];
            if ($xml_form -> fields[$key]['VALUE'][$valore] != '') {
                $dec_new_value = $xml_form -> fields[$key]['VALUE'][$valore];
                $dec_old_value = $equery_old_values['D_' . $xml_form -> fields[$key]['VAR']];
            } else {
                $dec_new_value = '';
                $dec_old_value = '';
            }
            if ($equery_old_values[$xml_form -> fields[$key]['VAR']] != $session_vars[$xml_form -> fields[$key]['VAR'] . "_PROGR_" . $progr] && $xml_form -> fields[$key]['TYPE'] != 'checkbox_hyper' && $xml_form -> fields[$key]['TYPE'] != 'checkbox' && $xml_form -> fields[$key]['TYPE'] != 'hidden') {

                $values['VISITNUM'] = $session_vars['VISITNUM'];
                $values['VISITNUM_PROGR'] = $session_vars['VISITNUM_PROGR'];
                $values['ESAM'] = $session_vars['ESAM'];
                $values['PROGR'] = $progr;
                $values[$xml_form -> PK_SERVICE] = $session_vars[$xml_form -> PK_SERVICE];
                $values['CENTER'] = $session_vars['CENTER'];
                $values['NOMETAB'] = $xml_form -> form['TABLE'];
                $values['VAR'] = $xml_form -> fields[$key]['VAR'] . "_PROGR_" . $progr;
                $values['FIELD'] = $xml_form -> fields[$key]['DESCRIPTION'];
                $values['VALUE_NEW'] = $session_vars[$xml_form -> fields[$key]['VAR'] . "_PROGR_" . $progr];
                $values['D_VALUE_NEW'] = $dec_new_value;
                $values['VALUE_OLD'] = $equery_old_values[$xml_form -> fields[$key]['VAR']];
                $values['D_VALUE_OLD'] = $equery_old_values['D_' . $xml_form -> fields[$key]['VAR']];
                $values['MODDT'] = sysdate;
                //$values['USERID']=$_POST['USERID_INS'];//userid corrente!!
                $values['USERID'] = $in['remote_userid'];
                $values['ACTION'] = $action;

                $ins_sql = new query($this -> conn);
                $ins_sql -> insert($values, "S_X_{$xml_form->config_service['service']}");
                //$this -> conn -> commit();
            }
        }
    }

    function CheckAction($xml_form = null, $from_eq = null) {
        $action = '';

        if ($this -> config_service['lang'] == "en") {
            $txt_first_insert = "Original Entry";
            $txt_DE_error = "Change/update by Investigator";
            $txt_DM_notify = "Obvious correction by Data Manager";

        } else {
            $txt_first_insert = "Primo inserimento";
            $txt_DE_error = "Modifica/aggiunta dato";
            $txt_DM_notify = "Correzione ovvia del Data Manager";
        }

        $sql_query = "select * from {$xml_form->config_service['service']}_COORDINATE where $xml_form->PK_SERVICE='{$xml_form->session_vars[$xml_form->PK_SERVICE]}'
						and esam={$xml_form->session_vars['ESAM']} and visitnum={$xml_form->session_vars['VISITNUM']} and progr={$xml_form->session_vars['PROGR']} and visitnum_progr={$xml_form->session_vars['VISITNUM_PROGR']}
		";
        $query = new query($this -> conn);
        $query -> set_sql($sql_query);
        $query -> exec();
        $query -> get_row();

        if ($from_eq == '') {
            // casi 2,3,7
            if ($query -> row['INIZIO'] == 0 && $query -> row['FINE'] == 0) {
                // caso 2:
                $action = $txt_first_insert;

            } elseif ($query -> row['INIZIO'] == 1 && $query -> row['FINE'] == 0) {
                //caso 3:
                $action = $txt_DE_error;
            } elseif ($query -> row['INIZIO'] == 1 && $query -> row['FINE'] == 1) {
                //caso 7:
                $action = $txt_DM_notify;
            }
        }
        // casi 4,5,6 nella classe integrazioni-inc
        return $action;
    }

    /**
     * Crea la tabella per il funzionamento dell'audit trail se non esiste
     *
     * @param form $xml_form
     * @return boolean
     */
    function table_exist($xml_form = null) {

        //creazione tabella se non esiste
        $query_check_existence = "select table_name from user_tables where table_name=upper('S_X_{$xml_form->config_service['service']}')";
        $query = new query($this -> conn);
        $query -> set_sql($query_check_existence);
        $query -> exec();
        if ($query -> get_row()) {
            //			print_r($query->row['TABLE_NAME']);
            //			print_r($query_check_existence);
            return true;
        } else {
            // da fare....
            $query_create = "
			create table S_X_{$xml_form->config_service['service']}
			(
			  $xml_form->PK_SERVICE         NUMBER,
			  ESAM           NUMBER,
			  PROGR          NUMBER,
			  VISITNUM       NUMBER,
			  VISITNUM_PROGR NUMBER,
			  CENTER         VARCHAR2(40),
			  VALUE_NEW      VARCHAR2(1000),
			  D_VALUE_NEW    VARCHAR2(1000),
			  VALUE_OLD      VARCHAR2(1000),
			  D_VALUE_OLD    VARCHAR2(1000),
			  NOMETAB        VARCHAR2(30),
			  VAR            VARCHAR2(50),
			  FIELD          VARCHAR2(50),
			  MODDT          DATE,
			  ACTION         VARCHAR2(200),
			  USERID         VARCHAR2(20)
			)
			";
            $sql = new query($this -> conn);
            $sql -> set_sql($query_create);
            $sql -> ins_upd();
        }
    }

    function audit_trail_txt($session_vars) {
        if ($this -> attributes['TB'] != 'no' && $this -> attributes['VAR'] != '' && $this -> attributes['TYPE'] != 'hidden') {
            return $this -> audit_trail_popup($session_vars);
        }
    }

    function audit_trail_form_js($form) {
        return "
        
        <script>
        var menuShown;
        </script>
        
        ";
    }
    
    function audit_trail_form_body($form) {
        return '        
       <script type="text/javascript" src="libs/js_tooltip/wz_tooltip.js"></script>        
        ';
    }

    function interpret_action($action) {
        if (isset($this -> actions[$action]) && $this -> actions[$action] != '') {
            return $this -> actions[$action];
        } else if ($action > 0) {
            return 'eQuery n. '.$action;
        } else {
            return $action;
        }
    }

}
?>
