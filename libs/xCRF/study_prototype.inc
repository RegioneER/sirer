<?php
include_once "xmrwf.inc.php";
//test luigi
//Append CROs
include_once "navigation_bar.inc";
include_once "audit_trail.inc";
include_once "SourceDataVerification.inc";
include_once "SysTables.inc";
include_once "DoubleDataEntry.inc";
include_once "LogActivities.inc";
include_once "DocumentGenerator.inc";
include_once "ConcurrentAccess.inc";


/**
 * Clase Prototipo di gestione dello Studio
 *
 * @package CORE
 */
class Study_prototype
{
    var $breadcrumb;
    var $sidebar;
    var $title;
    var $navbar;
    var $xml_dir;
    var $page_title;
    var $service;
    var $visit_structure_xml;
    /**
     * Connessione al DB
     *
     * @var dbconn
     */
    var $conn;
    //var $centers;
    /**
     * Variabile Centro
     *
     * @var String
     */
    var $center;
    var $vlist;
    /**
     * Nome delle form
     *
     * @var array
     */
    var $es_name;
    /**
     * specifiche form
     *
     * @var array
     */
    var $es_form;
    var $patient_table;
    var $session_vars;
    /**
     * Codice html del body della pagina
     *
     * @var String
     */
    var $body;
    var $onload;
    var $script;
    var $percorso;
    var $user;
    /**
     * Parametri di configurazione del servizio
     *
     * @var array
     */
    var $config_service;
    var $uploaded_file_dir;
    var $workflow;
    var $pk_service;
    var $mostra_ana_comune;
    var $lang = 'it';
    var $testi;
    var $hrefs;
    /**
     * Parametri di configurazione
     *
     * @var array
     */
    var $config;
    var $vlist_root;
    var $xmr_root;
    var $notifica;
    /**
     * Errori
     *
     * @var array
     */
    var $errors;
    /**
     * Oggetti equery
     *
     * @var array
     */
    var $equery_objs;
    var $integrazione;
    /**
     * Multi profilo
     * $profile_id @number
     * $gestori @Array
     */
    var $profile_id;
    var $configurer;
    var $admin_profili;
    var $user_profili;
    var $admin_profili_html;
    /**
     * Footer della homepage
     *
     * @var String
     */
    var $footer = "
			<table width=\"100%\" >
				<tr>
					<td align=\"center\">
						In collaboration with: <br/><a href=\"http://www.cineca.it/\"><img src=\"/images/logoblu.gif\" alt=\"\" /></a><br/></a>
					</td>
				</tr>
			</table>";

    /**
     * Gestisce i testi configurabili
     *
     * @param String $testo
     * @return String
     */
    function testo($testo)
    {
        $this->testi ['is incomplete'] = "is incomplete";
        $this->testi ['The form'] = "The form";
        $this->testi ['add_form'] = "Add a new esam";
        $this->testi ['apply_changes'] = "Apply changes";
        $this->testi ['save_neccessary'] = "Attention, it is necessary to use the following button in order to apply the changes.";
        $this->testi ['Home'] = "Home";
        $this->testi ['Registro Lista Pazienti'] = "Registry Patients List";
        $this->testi ['Registro Lista Centri'] = "Registry Center List";
        $this->testi ['Vista Paziente'] = "Patient's View";
        $this->testi ['Search'] = "Search";
        $this->testi ['ModifyForm'] = "Modify form";
        $this->testi ['notNecessary'] = "Not necessary";
        $this->testi ['necessary'] = "Necessary";
        $this->testi ['sendAnswer'] = "Send answer";
        $this->testi ['cancel'] = "Cancel";
        $this->testi ['Registry'] = "Registry";
        $this->testi ['Center'] = "Center";
        $this->testi ['Visit'] = "Visit";
        $this->testi ['Esam'] = "Esam";
        $this->testi ['eQueryDate'] = "eQuery Date";
        $this->testi ['eQueryList'] = "eQuery List";
        $this->testi ['newEquery'] = "New eQuery";
        $this->testi ['eQueryType'] = "eQuery Type";
        $this->testi ['eQueryType1'] = "eQuery Type 1";
        $this->testi ['eQueryType2'] = "eQuery Type 2";
        $this->testi ['eQueryTypeNull'] = "eQuery Type Null";
        $this->testi ['Dateofanswer'] = "Date of answer";
        $this->testi ['Modify'] = "Modify";
        $this->testi ['closeDate'] = "close date";
        $this->testi ['ChangeNecessary'] = "Change is necessary";
        $this->testi ['ChangeNotNecessary'] = "Change is not necessary";
        $this->testi ['ChangeMadeAt'] = "Changes made to the";
        $this->testi ['noPatient'] = "There are no patients in this center";
        $this->testi ['searchEq'] = "Search eQuery";
        $this->testi ['openedEq'] = "List of open eQueries";
        $this->testi ['openedEqS'] = "Show open eQuery";
        $this->testi ['closedEq'] = "View closed eQueries";
        $this->testi ['closedEqL'] = "List of closed eQueries 	";
        $this->testi ['allEq'] = "View all eQueries";
        $this->testi ['alldEqL'] = "List of all eQuery";
        $this->testi ['newEq'] = "New eQuery";
        $this->testi ['sendedEq'] = "eQuery Sent";
        $this->testi ['receivedEq'] = "eQuery Received";
        $this->testi ['visualizzaScheda'] = "Show form";
        $this->testi ['userNotCenter'] = "USER NOT IN CENTER LIST";
        //LUIGI: controllo sui diritti di cancellazione
        $this->testi ['NOTDELETABLE'] = "No rights to delete the esam or visit";
        //LUIGI: controllo sui diritti di creazione
        $this->testi ['NOTCREABLE'] = "No rights to create the visit";
        $this->testi ['userNotHaveCenter'] = "USER CAN'T VIEW THIS CENTER: AUTHORIZATION DENIED";
        $this->testi ['badRequest'] = "THE REQUEST IS NOT PROPERLY FORMED, THEREFORE IT CANNOT BE PROCESSED.";
        $this->testi ['mismatchedCenter'] = "MISMATCHED CENTER AND PATIENT: AUTHORIZATION DENIED";
        $this->testi ['schedaInviata'] = "<p align=center><b>This form has been sent !!!<br>Impossible to modify</p>";
        $this->testi ['Lista completa'] = "Complete patient's view";
        $this->testi ['gest_prof'] = "Profile Administration";

        foreach ($this->testi as $key => $val) {
            mlOut("System." . $key, $val);
        }
        return mlOut("System." . $testo, $testo);
    }

    /**
     * Costruttore
     *
     * @param String $xml_dir
     * @param String $service
     * @param String $visit_structure_xml
     * @param dbconn $conn
     * @param array $session_vars
     * @param array $config_service
     * @param String $user
     * @param boolean $configure
     * @param unknown_type $workflow_name
     * @return Study_prototype
     */
    function Study_prototype($xml_dir, $service, $visit_structure_xml, $conn, $session_vars, $config_service, $user, $configure = false, $workflow_name = null)
    {
        $this->xml_dir = $xml_dir;
        $this->uploaded_file_dir = preg_replace("!xml$!", "uploaded_file", $xml_dir);
        $this->service = $service;
        $this->visit_structure_xml = $visit_structure_xml;
        $this->conn = $conn;
        $this->session_vars = $session_vars;
        $this->config_service = $config_service;
        if (isset ($this->config_service ['lang']))
            $this->lang = $this->config_service ['lang'];
        else
            $this->config_service ['lang'] = $this->lang;
        $this->user = $user;
        $this->notifica = true;

        $sql_center = "select uc.CENTER, uc.TIPOLOGIA from {$this->service}_UTENTI_CENTRI uc where uc.userid='{$this->session_vars['remote_userid']}'";
        $sql = new query ($this->conn);
        $sql->get_row($sql_center);
        $this->center = $sql->row ['CENTER'];

        $exams = $this->visit_structure_xml;
        //		echo $this->xml_dir;
        if ($this->xmr->depth > 0)
            $dir = str_replace("/" . $this->service, "", $this->xml_dir);
        else
            $dir = $this->xml_dir;

        $this->xmr_root = new xmrwf ("study.xml", $conn);
        $this->ml = $this->xml->ml;

        $this->xmr_root->setConfigParam(true);
        $this->config = $this->xmr_root->getConfigService();
        $this->config_service['service_root'] = $this->xmr_root->prefix;
        $this->config['mostraDataInvio'] = $this->config_service['mostraDataInvio'];
        $this->vlist_root = new xml_esams_list ($dir . '/' . $exams, $this->config, $this->session_vars, $this->conn, $this->xmr_root->dir . '/xml');

        if (isset ($this->session_vars [$this->config_service ['PK_SERVICE']]))
            $this->pk_service = $this->session_vars [$this->config_service ['PK_SERVICE']];

        if (isset ($workflow_name)) {
            include_once "WF/bootstrap.inc.php";
            $sql_query = "select id from workflow where descr='$workflow_name'";

            $sql = new query ($this->conn);
            $sql->get_row($sql_query);
            $this->workflow = new WF_PROTOTYPE ($this->conn, $this->session_vars, $sql->row ['ID'], $this);

            $this->getAdminProfili();

        }

        if ($configure) {
            $this->CheckXMR();
            return;
        }
        $this->session_vars['PREFIX'] = $this->service;
        $this->session_vars['USERID'] = $this->session_vars['remote_userid'];
        include_once "ProfileConfigurer.class.php";
        $this->configurer = new ProfileConfigurer($this);

        /*
		$this->CheckVisione ();
		$this->session_vars['USER_TIP']=$this->configurer->policy;
		$this->visit_structure_xml=$this->configurer->visit_structure_xml;
		$this->VisitStructure ();
		*/
        $this->checkStudyConsistence();
        $this->session_vars['USER_PROFILE'] = $this->user->profilo;

        if (isset($this->config_service['eQuery']) && $this->config_service['eQuery'] == 1) {
            if (isset($this->pk_service)) $this->integrazione = new integrazioni($this->config_service, $this->conn, $this->user->userid, $this->user->profilo, $this->session_vars ['USER_TIP'], $this->session_vars, $this->xml_dir);
        }
    }

    function checkStudyConsistence()
    {
        if (isset($this->config_service['checkConsistence']) && $this->config_service['checkConsistence']) {
            if (((
                        (isset($_GET['ESAM']) && $_GET['ESAM'] != '') &&
                        (isset($_GET['PROGR']) && $_GET['PROGR'] != '') &&
                        (isset($_GET['VISITNUM']) && $_GET['VISITNUM'] != '')
                    ) || (
                        (isset($_POST['ESAM']) && $_POST['ESAM'] != '') &&
                        (isset($_POST['PROGR']) && $_POST['PROGR'] != '') &&
                        (isset($_POST['VISITNUM']) && $_POST['VISITNUM'] != '')
                    )
                ) && $this->pk_service != 'next') {
                if ((isset($_GET['ESAM']) && $_GET['ESAM'] != '') &&
                    (isset($_GET['VISITNUM']) && $_GET['VISITNUM'] != '')) {
                    $visit = $_GET['VISITNUM'];
                    $esam = $_GET['ESAM'];
                    $progr = $_GET['PROGR'];
                    $vprog = $_GET['VISITNUM_PROGR'];
                    $form = $_GET['form'];
                }
                if ((isset($_POST['ESAM']) && $_POST['ESAM'] != '') &&
                    (isset($_POST['VISITNUM']) && $_POST['VISITNUM'] != '')) {
                    $visit = $_POST['VISITNUM'];
                    $esam = $_POST['ESAM'];
                    $progr = $_POST['PROGR'];
                    $vprog = $_POST['VISITNUM_PROGR'];
                    $form = $_POST['form'];
                }
                $esamSpec = $this->vlist->esams[$visit][$esam];

                if (!isset($this->vlist->esams[$visit][$esam])) {
                    error_page($this->user->userid, "Errore!!! Scheda non esistente", "Errore!!! Scheda non esistente");
                }
                if ($esamSpec['PROGR'] == '' || strtoupper($esamSpec['PROGR']) != strtoupper("yes")) {
                    $progr -= 0;
                    if ($progr > 1) {
                        error_page($this->user->userid, "Errore!!! Scheda non progressiva", "Errore!!! Scheda non progressiva");
                    }
                }
                $visitSpec = $this->vlist->visitnums[$visit];

                if ($visitSpec['PROGR'] == '' || strtoupper($visitSpec['PROGR']) != strtoupper("yes")) {
                    $vprog -= 0;
                    if ($vprog > 0) {
                        error_page($this->user->userid, "Errore!!! Visita non progressiva", "Errore!!! Visita non progressiva");
                    }
                }
                if (isset($form) && $form != '' && $esamSpec['XML'] != $form) {
                    error_page($this->user->userid, "Errore! File xml non consistente!", "");
                }
                $sql_abilitato_1 = "select max(abilitato) as ABILITATO from {$this->service}_COORDINATE where {$this->config_service['PK_SERVICE']}=:pk_service and esam=:esam and visitnum=:visitnum and visitnum_progr=:visitnum_progr";
                $binded['esam'] = $esam;
                $binded['visitnum'] = $visit;
                $binded['visitnum_progr'] = $vprog;
                $binded['pk_service'] = $this->pk_service;
                $sql = new query($this->conn);
                $enabled = false;


                if ($sql->get_row($sql_abilitato_1, $binded)) {
                    if ($sql->row['ABILITATO'] == 1) $enabled = true;
                }

                if (isset($esamSpec['CORR'])) {
                    $sql_corr_query = "select fine as FINE from {$this->service}_COORDINATE where {$this->config_service['PK_SERVICE']}=:pk_service and esam=:esame_corr and visitnum=:visitnum and visitnum_progr=:visitnum_progr and progr=:progr";
                    $bind['visitnum'] = $visit;
                    $bind['visitnum_progr'] = $vprog;
                    $bind['progr'] = $_GET['PROGR'];
                    $bind['esame_corr'] = $esamSpec['CORR'];
                    $bind['pk_service'] = $this->pk_service;
                    $sql_corr = new query($this->conn);
                    $sql_corr->get_row($sql_corr_query, $bind);
                    if ($sql_corr->row['FINE'] == 1) {
                        $enabled = true;
                    }
                }

                if ($esam != 0 && !$enabled) {
                    error_page($this->user->userid, "Errore! Scheda non abilitata!", "");
                }
            }
        } else {
            return;
        }
    }

    /**
     * Restituisce lo stato (WF) dell'oggetto di studio
     *
     * @param String $prefix
     * @return number
     */
    function GetStato($prefix = null)
    {
        if (!isset ($prefix))
            $prefix = $this->workflow->prefix;
        $stato = new WF_STATO ($this->conn, null, $this->workflow->prefix);
        if ($this->pk_service == '' || $this->pk_service == 'next') {
            $id_stato = 1;
            return $id_stato;
        }
        $sql_query = "select ID_STATO from {$prefix}_STATO where PK_SERVICE={$this->pk_service}";
        $sql = new query ($this->conn);
        if ($sql->get_row($sql_query)) {
            $id_stato = $sql->row ['ID_STATO'];
        } else
            $id_stato = 1;
        return $id_stato;
    }

    /**
     * Abilita la visita
     *
     * @param number $visita
     * @param number $visitnum_progr
     * @return boolean
     */
    function abilita_visita($visita, $visitnum_progr = '0')
    {

        $sql = new query ($this->conn);
        foreach ($this->vlist->esams [$visita] as $key => $val) {
            if ($val ['DEFAULT'] == 'yes') {

                $array [$this->config_service ['PK_SERVICE']] = $this->pk_service;
                $array ['VISITNUM'] = $visita;
                $array ['VISITNUM_PROGR'] = $visitnum_progr;
                $array ['ESAM'] = $key;
                $array ['PROGR'] = 1;
                $array ['ABILITATO'] = 1;
                $table = $this->service . "_COORDINATE";
                $sql->insert($array, $table, null, true);
            }
        }

        return $this->conn->commit();
    }

    /**
     * Elimina visita progressiva (obsoleta)
     *
     * @param number $visita
     * @param number $visitnum_progr
     * @return boolean
     */
    function elimina_visita_progr($visita, $visitnum_progr = '0')
    {

        if ($visitnum_progr != '0') {
            $sql = new query ($this->conn);
            $str = "delete from {$this->service}_coordinate where visitnum=$visita and visitnum_progr=$visitnum_progr and {$this->config_service['PK_SERVICE']}='$this->pk_service'";
            $str = "delete from {$this->service}_coordinate 
				where visitnum=:visitnum and visitnum_progr=:visitnum_progr and {$this->config_service['PK_SERVICE']}=:pk_service"; //binded
            $bindVars["visitnum"] = $visita;
            $bindVars["visitnum_progr"] = $visitnum_progr;
            $bindVars["pk_service"] = $this->pk_service;
            $sql->ins_upd($str, $bindVars); //binded
        }
        return $this->conn->commit();
    }

    /**
     * Controlla la struttura dell'XMR
     *
     */
    function CheckXMR()
    {
        $sql_view_ = null;
        $option_role = null;
        $this->body = "<p class=titolo>Configuration tool</p>";
        $do_command ['storico_id_seq'] [0] = "
			create sequence STORICO_ID
				minvalue 1
				maxvalue 99999999
				start with 21
				increment by 1
				cache 20
		";
        $do_command ['coordinate'] [0] = "
			create table {$this->service}_COORDINATE
			(
			  VISITNUM       NUMBER not null,
			  VISITNUM_PROGR NUMBER not null,
			  PROGR          NUMBER not null,
			  ESAM           NUMBER not null,
			  INIZIO         NUMBER(1),
			  FINE           NUMBER(1),
			  INSERTDT       DATE,
			  MODDT          DATE,
			  USERID         VARCHAR2(256 CHAR),
			  VISITCLOSE     NUMBER(1) default 0,
			  INV_QUERY      VARCHAR2(256),
			  {$this->config_service['PK_SERVICE']}        NUMBER not null,
			  ABILITATO      NUMBER,
			  CREATE_USER	 VARCHAR2(256),
			  LAST_MOD_USER	 VARCHAR2(256),
			  SEND_DT        DATE,
			  EQ_ACTION      NUMBER
			)
		";
        $do_command ['coordinate'] [1] = "
			alter table {$this->service}_COORDINATE
  			add constraint PK_{$this->service}_COORDINATE primary key (VISITNUM, VISITNUM_PROGR, ESAM, {$this->config_service['PK_SERVICE']}, PROGR)
		";
        $do_command ['equery'] [0] = "
  			create table {$this->service}_EQUERY
			(
			  ID             NUMBER not null,
			  CENTER         VARCHAR2(256),
			  {$this->config_service['PK_SERVICE']}        NUMBER,
			  VISITNUM       NUMBER,
			  VISITNUM_PROGR NUMBER,
			  ESAM           NUMBER,
			  PROGR          NUMBER,
			  Q_USERID       VARCHAR2(256 CHAR),
			  QUESTION       VARCHAR2(4000 CHAR),
			  QUEST_DT       DATE,
			  TO_BE_VALIDATE NUMBER,
			  ANSWER         VARCHAR2(4000 CHAR),
			  ANS_DT         DATE,
			  A_USERID       VARCHAR2(256 CHAR),
			  VALIDATA       NUMBER,
			  CHIUSA         NUMBER,
			  VAL_DT         DATE,
			  VAL_USERID     VARCHAR2(256 CHAR),
			  CHIUSA_DT      DATE,
			  REGISTRY       VARCHAR2(256 CHAR)
			)
  		";
        $do_command ['equery'] [1] = "
			alter table {$this->service}_EQUERY
  			add constraint PK_{$this->service}_EQUERY primary key (ID)
			";
        $sql_query = "select count(*) as conto from user_all_tables where table_name='{$this->service}_COORDINATE'";

        $sql = new query ($this->conn);
        $sql->set_sql($sql_query);
        $sql->exec();//non richiede binding
        $sql->get_row();

        if ($sql->row ['CONTO'] == 0) {
            foreach ($do_command ['coordinate'] as $key => $val) {
                $sql->set_sql($val);
                $sql->ins_upd(); //bind non necessario
                $this->body .= "<li>Tabella coordinate creata</li>";
            }
        } else {
            $this->body .= "<li>Tabella coordinate gi&agrave; presente</li>";
        }
        $sql_query = "select count(*) as conto from user_all_tables where table_name='{$this->service}_EQUERY'";
        $sql = new query ($this->conn);
        $sql->set_sql($sql_query);
        $sql->exec();//non richiede binding
        $sql->get_row();
        if ($sql->row ['CONTO'] == 0) {
            foreach ($do_command ['equery'] as $key => $val) {
                $sql->set_sql($val);
                $sql->ins_upd(); //bind non necessario
                $this->body .= "<li>Tabella equery creata</li>";
            }
        } else {
            $this->body .= "<li>Tabella equery gi&agrave; presente</li>";
        }
        $sql_query = "select count(*) as conto from user_sequences where sequence_name='STORICO_ID'";
        $sql = new query ($this->conn);
        $sql->set_sql($sql_query);
        $sql->exec();//non richiede binding
        $sql->get_row();
        if ($sql->row ['CONTO'] == 0) {
            foreach ($do_command ['storico_id_seq'] as $key => $val) {
                $sql->set_sql($val);
                $sql->ins_upd(); //bind non necessario
                $this->body .= "<li>Sequence storico_id creata</li>";
            }
        } else {
            $this->body .= "<li>Sequence storico_id gi&agrave; presente</li>";
        }
        if ($this->config_service ['PK_SEQ'] != '') {
            $do_command ['pk_seq'] [0] = "
				create sequence {$this->service}_PK_SEQ
					minvalue 1
					maxvalue 99999999
					start with 1
					increment by 1
					cache 20
			";
            $sql_query = "select count(*) as conto from user_sequences where sequence_name='{$this->service}_PK_SEQ'";
            $sql = new query ($this->conn);
            $sql->set_sql($sql_query);
            $sql->exec();//non richiede binding
            $sql->get_row();
            if ($sql->row ['CONTO'] == 0) {
                foreach ($do_command ['pk_seq'] as $key => $val) {
                    $sql->set_sql($val);
                    $sql->ins_upd(); //bind non necessario
                    $this->body .= "<li>Sequence {$this->service}_PK_SEQ creata</li>";
                }
            } else {
                $this->body .= "<li>Sequenze {$this->service}_PK_SEQ gi&grave; presente</li>";
            }
        }
        if ($this->config_service ['ROLE_TB'] != '') {
            $do_command ['RULE_TB'] = "
				create table {$this->service}_ROLE(
					ID number,
					ROLE varchar2(200 CHAR),
					WHERE_ varchar2(4000 CHAR)
				)
			";
            $sql_query = "select count(*) as conto from user_all_tables where table_name='{$this->service}_ROLE'";
            $sql = new query ($this->conn);
            $sql->set_sql($sql_query);
            $sql->exec();//non richiede binding
            $sql->get_row();
            if ($sql->row ['CONTO'] == 0) {
                $sql->set_sql($do_command ['RULE_TB']);
                $sql->ins_upd(); //bind non necessario
                $this->body .= "<li>Tabella ROLE creata</li>";
            } else {
                $this->body .= "<li>Tabella ROLE gi&agrave; presente</li>";
            }
            if (isset ($_GET ['DEL_ROLE_ID']) && $_GET ['DEL_ROLE_ID'] != '') {
                $sql_delete = "delete from {$this->service}_ROLE where ID=:id"; //binded
                $bindVars = "";
                $bindVars["id"] = $_GET['DEL_ROLE_ID'];
                $sql->ins_upd($sql_delete, $bindVars); //binded
                $this->conn->commit();
                ob_clean();
                header('location: ssup.php');
                $this->conn->commit();
                die();
                die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=ssup.php\"></head></html>");
            }
            if (isset ($_GET ['ADD_ROLE']) && $_GET ['ADD_ROLE'] != '') {
                $sql_max = "select max(id) as maxid from {$this->service}_ROLE";
                $sql->set_sql($sql_max);
                $sql->exec();//non richiede binding
                $sql->get_row();
                $max = $sql->row ['MAXID'] - 0;
                $max++;
                $sql_insert = "insert into {$this->service}_ROLE (ID, ROLE) values ($max, '{$_GET['ADD_ROLE']}')";
                $sql_insert = "insert into {$this->service}_ROLE (ID, ROLE) values (:max, :add_role)";  //binded
                $bindVars = "";
                $bindVars["max"] = $max;
                $bindVars["add_role"] = $_GET['ADD_ROLE'];
                $sql->ins_upd($sql_insert, $bindVars); //binded
                $this->conn->commit();
                ob_clean();
                header('location: ssup.php');
                $this->conn->commit();
                die();
                die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=ssup.php\"></head></html>");
            }
            if (isset ($_POST ['modwhere'])) {
                foreach ($_POST as $key => $val) {
                    if (preg_match("!_WHERE_$!", $key)) {
                        $WHERE_ = $val;
                        $WHERE_ = str_replace("\\'", "''", $WHERE_);

                        $id = str_replace("_WHERE_", "", $key);
                        $pk ['ID'] = $id;
                        $sql_update = "update {$this->service}_ROLE set WHERE_='{$WHERE_}' where id=$id";
                        $sql_update = "update {$this->service}_ROLE set WHERE_=:where_ where id=:id";
                        $bindVars = "";
                        $bindVars["where_"] = $WHERE_;
                        $bindVars["id"] = $id;
                        $sql->ins_upd($sql_update, $bindVars); //binded
                    }
                }
                $this->conn->commit();
                ob_clean();
                header('location: ssup.php');
                $this->conn->commit();
                die();
                die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=ssup.php\"></head></html>");
            }
            if (isset ($_GET ['ROLE_VIEW'])) {

                $sql_view = "
				create or replace view {$this->service}_utenti_centri as
				";
                $sql_query = "select * from {$this->service}_ROLE";
                $sql->set_sql($sql_query);
                $sql->exec();//non richiede binding
                while ($sql->get_row()) {
                    if ($sql_view_ != '')
                        $sql_view_ .= "
						union
						";
                    $sql_view_ .= "
						select a.userid, c.center as center, '{$sql->row['ROLE']}' as tipologia
			    		from ana_utenti a, {$this->service}_centri c where {$sql->row['WHERE_']}
					";
                }
                $sql_view .= $sql_view_;
                //$sql->ins_upd ($sql_view); //bind non necessario
                ob_clean();
                header('location: ssup.php');
                $this->conn->commit();
                die();
                die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=ssup.php\"></head></html>");
            }
            $sql_query = "select * from {$this->service}_ROLE";
            $sql->set_sql($sql_query);
            $sql->exec();//non richiede binding
            $this->body .= "<form method=post>
			<input type='hidden' name='modwhere' value='yes'>
				<table border=1 cellpadding=0 cellspacing=0 width=98%>
					<tr>
						<td>Elimina</td>
						<td>Ruolo</td>
						<td colspan=2>Where</td>
					</tr>
			";
            while ($sql->get_row()) {
                $this->body .= "
					<tr>
						<td><a href=\"ssup.php?DEL_ROLE_ID={$sql->row['ID']}\">elimina</a></td>
						<td><b>{$sql->row['ROLE']}</b></td>
						<td><textarea cols=40 rows=4 name='{$sql->row['ID']}_WHERE_'>{$sql->row['WHERE_']}</textarea></td>
						<td><b>Attenzione la tabella di anagrafica ha come alias \"a\", quella dei centri invece &egrave; \"c\". Ricordarsi di inserirlo nelle clausole (ad es. a1.userid=c.center)!!!</b></td>
					</tr>
				";
            }
            if (isset ($this->workflow)) {
                $acts = new WF_ATTORI ($this->conn, $this->workflow->prefix);
                foreach ($acts->attori as $key => $val) {
                    $role [count($role)] = $val->getNome();
                }
            } else {
                $role [0] = "DE";
                $role [1] = "DM";
                $role [2] = "RO";
            }
            foreach ($role as $key => $val) {
                $option_role .= "<option value=\"{$val}\">$val</option>";
            }
            $this->body .= "
				<tr>
					<td colspan=3>
						<input type='submit' value='salva'>
						<input type='button' value='Rigenera vista' onclick=\"window.location.href='ssup.php?ROLE_VIEW=REG';\">
					</td>
				</tr>
			</table>
			</form>
			<a href=\"#\" onclick=\"document.getElementById('add_role').style.display=''; return false;\">Add role</a>
			<div id='add_role' style=\"display:none\">
				<select onchange=\"window.location.href=window.location.href+'?ADD_ROLE='+this.value;\">
					<option></option>
					$option_role
				</select>
			</div>
			";
        }
        if ($this->config_service ['CENTER_TB'] != '') {
            $do_command ['CENTER_TB'] = "
				create table {$this->service}_CENTER_TB(
					WHERE_ varchar2(4000 CHAR)
				)
			";
            $sql_query = "select count(*) as conto from user_all_tables where table_name='{$this->service}_CENTER_TB'";
            $sql = new query ($this->conn);
            $sql->set_sql($sql_query);
            $sql->exec();//non richiede binding
            $sql->get_row();
            if ($sql->row ['CONTO'] == 0) {
                $sql->ins_upd($do_command ['CENTER_TB']); //bind non necessario
                $this->body .= "<li>Tabella CENTER_TB creata</li>";
            } else {
                $this->body .= "<li>Tabella CENTER_TB gi&agrave; presente</li>";
            }
            if (isset ($_POST ['modcenter'])) {
                $sql_delete = "delete from {$this->service}_CENTER_TB";
                $sql->ins_upd($sql_delete); //bind non necessario
                $this->conn->commit();
                $where_ = str_replace("\\'", "'", $_POST ['WHERE_']);
                $WHERE_ = str_replace("\\'", "''", $_POST ['WHERE_']);
                $sql_insert = "insert into {$this->service}_CENTER_TB (WHERE_) values ('$WHERE_')";
                $sql_insert = "insert into {$this->service}_CENTER_TB (WHERE_) values (:where_)"; //binded
                $bindVars = "";
                $bindVars["where_"] = $WHERE_;
                $sql->ins_upd($sql_insert, $bindVars);//binded
                $this->conn->commit();
                $sql_view = "
				create or replace view {$this->service}_centri as
					select userid as center, azienda_ente as denom, userid as resp_userid
					from ana_utenti
					where $where_
				";
                $sql->ins_upd($sql_view); //bind non necessario
                ob_clean();
                header('location: ssup.php');
                $this->conn->commit();
                die();
                die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=ssup.php\"></head></html>");
            }
            $sql_query = "select * from {$this->service}_CENTER_TB";
            $sql->set_sql($sql_query);
            $sql->exec();//non richiede binding
            $sql->get_row();
            $this->body .= "<form method=POST>
				Clusola di where<br>
				<input type='hidden' name='modcenter' value='yes'>
				<textarea name=\"WHERE_\" cols=\"40\" rows=\"4\">{$sql->row['WHERE_']}</textarea>
				<br>
				<input type=\"submit\" value=\"Salva e rigenera la vista\">
			</form>
			";
        }
    }

    /**
     * Controlli sulla visione dell'utente
     *
     */
    function CheckVisione()
    {
        $conn = $this->conn;
        $service = $this->service;

        $remote_userid = $this->user->userid;
        if (!isset($this->session_vars['USER_PROFILE'])) {
            $this->session_vars['USER_PROFILE'] = $this->user->profile_code;
        }
        $in = $this->session_vars;
        if ($this->config_service['BookPkService'] && (isset($this->session_vars['INVIOCO']) || $this->session_vars['CREATE'] == 'Update DB') && $this->session_vars['ESAM'] === '0') {
            $check_se_nuovo = "select count(*) conto from {$this->service}_REGISTRAZIONE where {$this->config_service['PK_SERVICE']}=:pk_service";
            $query = new query($this->conn);
            $bind['PK_SERVICE'] = $this->pk_service;
            $query->get_row($check_se_nuovo, $bind);
            if ($query->row['CONTO'] == '0') {
                $pk_service = $this->pk_service;
                $this->pk_service = 'next';
                $replaced = true;
            }
        }
        //controllo il centro dell'oggetto (es. paziente o pratica) richiesto
        if ($this->pk_service != '' && $this->pk_service != 'next') {
            $check_str = "select count(*) vista from user_objects where object_name='{$service}_PK_OBJ_CENTER'";
            $check_query = new query($conn);
            $check_query->set_sql($check_str);
            $check_query->exec();//non richiede binding
            $check_query->get_row();
            if ($check_query->row['VISTA'] == 0) {
                //mail("c.contino@cineca.it,g.delsignore@cineca.it", "DA SISTEMARE Errore[".$in['remote_userid']."]","Manca l'oggetto {$service}_PK_OBJ_CENTER","From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n");
            } else {
                $real_center_str = "select center from {$service}_PK_OBJ_CENTER where pk_service=:pk_service";
                $real_center_query = new query($conn);
                //$real_center_query->set_sql($real_center_str);
                unset($bind_pk);
                $bind_pk['PK_SERVICE'] = $this->pk_service;
                $real_center_query->exec($real_center_str, $bind_pk);//binded
                $real_center_query->get_row();
                $real_center = $real_center_query->row['CENTER'];
                if ($real_center != $this->session_vars ['CENTER'] && $this->session_vars ['CENTER'] != '')
                    error_page($remote_userid, $this->testo("badRequest"), $this->testo("mismatchedCenter"));
                else if ($this->session_vars ['CENTER'] == '') $this->session_vars ['CENTER'] = $real_center;
            }

        }
        $query = new query ($conn);

        //$sql = "select uc.CENTER, uc.TIPOLOGIA from " . $service . "_UTENTI_CENTRI uc where uc.userid=:userid";
        $sql = "select CENTER, TIPOLOGIA
		from {$service}_UTENTI_CENTRI
		where userid=:userid";
        unset($bind_userid);
        $bind_userid['USERID'] = strtoupper($remote_userid);
        $bind_userid['PREFIX'] = strtoupper($service);
        $query->exec($sql, $bind_userid);//binded
        if ($query->numrows == 0)
            error_page($remote_userid, $this->testo("userNotCenter"), $this->testo("userNotHaveCenter"));
        if ($query->numrows == 1) {
            $query->get_row();
            $this->session_vars ['USER_TIP'] = $query->row ['TIPOLOGIA'];
            if (isset ($this->session_vars ['CENTER']) && $this->session_vars ['CENTER'] != $query->row ['CENTER'])
                error_page($remote_userid, $this->testo("userNotCenter"), $this->testo("userNotHaveCenter"));
            //			if (isset ( $this->session_vars ['CENTER'] ) && $this->session_vars ['CENTER'] != $query->row ['CENTER'] && $in ['SEARCH'] == "")
            if (isset ($this->center) && $this->center != $query->row ['CENTER'] && $in ['SEARCH'] == "")
                error_page($remote_userid, $this->testo("userNotCenter"), $this->testo("userNotHaveCenter"));
            $this->session_vars ['CENTER'] = $query->row ['CENTER'];
            $this->centers = "'" . $query->row ['CENTER'] . "'";
        } else {
            $flag_centro = false;
            while ($query->get_row()) {
                if ($this->centers != '')
                    $this->centers .= ",";
                $this->session_vars ['USER_TIP'] = $query->row ['TIPOLOGIA'];
                $this->centers .= "'" . $query->row ['CENTER'] . "'";
                if ($this->session_vars ['CENTER'] == $query->row ['CENTER']) $flag_check_centro = true;
            }
            //echo $query->tb_res();
            if (!$flag_check_centro && $this->session_vars ['CENTER'] != '') error_page($remote_userid, $this->testo("userNotCenter"), $this->testo("userNotHaveCenter"));
        }
        /*
		if (isset ( $this->workflow )) {
			$this->session_vars ['USER_PROFILE'] = $this->session_vars ['USER_TIP'];
			$stato = new WF_STATO ( $this->conn, null, $this->workflow->prefix );
			$stato->getById ( $this->GetStato () );
			//			print_r($stato);
			$functionCheck = "VisibilitaStato_" . $this->GetStato ();
			$attore_stato = $stato->getAttore ();
			//print_r($attore_stato);

			if (isset ( $this->pk_service ) && $this->pk_service != '' && $attore_stato != '') {
				if (method_exists ( $this, $functionCheck )) {
					$this->{$functionCheck} ();
				}

			}
			if ($attore_stato != '' && $this->session_vars ['USER_TIP'] == $attore_stato->getNome ()) {
				$this->session_vars ['USER_TIP'] = 'DE';
			} else if ($attore_stato != '' && $this->user->profilo == $this->config_service ['DM'] && $this->user->profilo != '') {
				$this->session_vars ['USER_TIP'] = "DM";
			} else {
				$this->session_vars ['USER_TIP'] = 'RO';
			}
		}
		*/
        global $in;
        $in = $this->session_vars;
        if ($this->config_service['BookPkService'] && $replaced) {
            $this->pk_service = $pk_service;
        }


    }

    /**
     * Costruisce la struttura dello studio
     *
     */
    function VisitStructure()
    {
        $in = null; //TODO: controllare, mi sembra errore!!!
        $VISITNUM = null; //TODO: controllare, mi sembra errore!!!
        $xml_dir = $this->xml_dir;
        $visit_structure_xml = $this->visit_structure_xml;
        $service = $this->service;

        //controllo che ci sia WF, se c'e prendo nomi degli attori, cerco visite_exams per quegli attori,
        //se non ci sta, prendi visite_exams.xml
        if (isset ($this->workflow)) {
            $nome_attore = str_replace(" ", "_", $this->session_vars ['USER_PROFILE']);
            $visit_file_attore = str_replace(".xml", "_" . $nome_attore . ".xml", $visit_structure_xml);
            if (file_exists($xml_dir . '/' . $visit_file_attore))
                $visit_structure_xml = $visit_file_attore;

            //
        }
        //echo "Stai usando questo visite_exams= $xml_dir /NO_PRE/  $visit_structure_xml ";
        $vlist = new xml_esams_list ($xml_dir . '/' . $visit_structure_xml, $this->config_service, $this->session_vars, $this->conn);
        if (isset($_GET[$this->config_service['PK_SERVICE']]) && is_numeric($_GET[$this->config_service['PK_SERVICE']])) $this->patient_folder = $vlist->buildEsamsList();
        if ($vlist->page ['LEGEND'] == 'yes') {
            $legend_upper = new legend ($this->config_service);
        }

        foreach ($vlist->visitnums as $key => $val) {
            $vis_name [$key] = $val ['TEXT'];
        }
        if (isset ($vlist->esams) && is_array($vlist->esams)) {
            foreach ($vlist->esams as $key => $val) {
                if (isset ($val) && is_array($val)) {
                    reset($val);
                    $cval = current($val);
                    if (!array_key_exists('XML', $cval)) {
                        $val = $val[0]; //Gestisco la possibilità di avere visite progressive.
                    }
                    foreach ($val as $kv => $vv) {
                        $es_name [$kv] = $vv ['TESTO'];
                        $es_form [$key] [$kv] = $vv ['XML'];
                    }
                }
            }
        }
        $form_reg = new xml_form ();
        $reg_form = $es_form[0][0];
        if ($reg_form == '') {
            error_page($in['remote_userid'], "Esam number 0 not found", array('LINEA' => __LINE__, 'FILE' => __FILE__));
        }
        $form_reg->xml_form_by_file($xml_dir . "/" . $reg_form);
        $patients_table = $form_reg->form ['TABLE'];

        $coordinate = strtoupper($service) . "_COORDINATE";
        if (isset ($ESAM)) {
            if (!isset ($form)) {
                $form = $es_form [$VISITNUM] [$ESAM];
                $this->session_vars ['form'] = $es_form [$VISITNUM] [$ESAM];
            }
        }

        $this->es_form = $es_form;
        $this->es_name = $es_name;
        $this->vlist = $vlist;
        $this->patient_table = $patients_table;
        global $patients_table;
        $patients_table = $this->patient_table;

    }

    /**
     * Genera il codice HTML della HomePage
     *
     */
    function HomePage()
    {
        $in = null; //TODO: controllare, mi sembra errore!!!
        $body = null;
        if (isset ($this->workflow)) {
            $prof_add = str_replace(" ", "_", $this->session_vars ['USER_PROFILE']);
            if (isset($_GET['PREFIX']) && $_GET['PREFIX'] != "")
                $xml_page = "home_{$_GET['PREFIX']}.xml";
            else
                $xml_page = "home_{$prof_add}.xml";

        } else
            $xml_page = 'home.xml';
        $legend_upper = "";
        if (preg_match("/^MS/", $in ['remote_userid']) || preg_match("/^AIFA/", $in ['remote_userid']))
            $xml_page = 'home_ms.xml';
        if ($in ['USER_TIP'] == 'DM')
            $xml_page = 'home_dm.xml';
        if ($in ['USER_TIP'] == 'RO')
            $xml_page = 'home_ro.xml';

        $body .= "<!--$xml_page-->";
        $this->xml_page = $xml_page;
        $page = new xml_page ($this->xml_dir . '/' . $xml_page, $this->admin_profili);
        $body .= $page->page_html();
        $body .= $this->footer;

        //Nuovo modo di generare il menu briciola di pane
        $this->percorso = $this->breadcrumb("home");
        $this->body .= $this->percorso;

        $this->body .= $body;
    }

    /**
     * Gestisce la pagine dei listati
     *
     * @param String $percorso_base
     */
    function ListPage($percorso_base = null)
    {
        //modifica effettutata da G.Tufano
        //il 26/05/2011. Ora per vedere un pager  sufficiente settare la variabile RPP nel config.inc locale
        //per es: $config_service['RPP'] = 25;
        if (isset($this->config_service['RPP']) && $this->config_service['RPP'] != '') {
            $RPP = $this->config_service['RPP'];
            if ($_GET['PAGE'] == "")
                $page = 1;
            else
                $page = $_GET['PAGE'];
        }

        /*
		$str="select count(*) conto from {$this->service}_utenti_centri where userid='{$this->user->userid}'";
		$sql=new query($this->conn);
		$sql->get_row($str);
		$list=str_replace ( ".xml", "_center.xml", $_GET['list'] );
		if($sql->row['CONTO']>1 && $this->session_vars['CENTER']==''){
			if(file_exists($this->xml_dir. "/" . $list ))
			$_GET['list']=$list;
			$page = "";
			unset($this->config_service['RPP']);
		}
		*/

        $list = $_GET ['list'];
        if ($list == '') {
            $list = 'patients_list.xml';
        }
        $prof_add = str_replace(" ", "_", $this->user->profile_code);
        $profile_list = str_replace(".xml", "_{$prof_add}.xml", $list);

        if (file_exists($this->xml_dir . "/" . $profile_list)) $list = $profile_list;
        if (isset ($this->workflow) && $list == 'patients_list.xml') {
            $prof_add = str_replace(" ", "_", $this->session_vars ['USER_PROFILE']);
            $list = str_replace(".xml", "_{$prof_add}.xml", $list);
        }
        $list_o = new xml_list ($this->xml_dir . "/" . $list, $page, $RPP, null, null, $this->session_vars, $this->vlist);
        //viene chiamato patients_list solo in caso sia davvero patients_list. se no altra_list
        if ($list == 'patients_list.xml') {
            $this->percorso = $this->breadcrumb("patients_list");
        } else {
            $titolo = $list_o->list['TITOLO'];
            $this->percorso = $this->breadcrumb("altra_list", $titolo);
        }

        $this->body .= $this->percorso;

        $this->body .= $list_o->list_html($this->session_vars);
        $legend = new legend ($this->config_service);
        $this->body .= $legend->html_legend_lista;
    }

    /**
     * Lista degli esami
     *
     * @param String $percorso_base
     */
    function ExamsLists($percorso_base = null)
    {
        $body = null;
        $forms_not_valid = null;
        $percorso = null;
        $conn = $this->conn;
        $this->patient_table = "";
        $showPatientFolder = true;
        if (isset($this->config_service['disablePatientView'][$this->user->profile_code]) && $this->config_service['disablePatientView'][$this->user->profile_code]) $showPatientFolder = false;
        if (!$showPatientFolder) {
            error_page($this->user->userid, "NOT_PERMITTED", "NOT_PREMITTED");
        }
        //Nuovo modo di generare il menu briciola di pane
        $this->percorso = $this->breadcrumb("exam_list");
        $body .= $this->percorso;

        $exams = $this->visit_structure_xml;
        global $xml_forms_not_valid;
        $this->make_patient_table();
        $body .= $this->patient_table;
        $body .= "<div class=\"br_separator\"></div>" . $this->tb_riassuntiva();
        if (isset ($this->workflow) && (!isset ($this->show_gantt) || $this->show_gantt))
            $body .= "
			<p align=center>
				<a href=\"#\" onclick=\"show_hide('img_rep');return false;\">Mostra/nascondi diagramma temporale</a><br>
				<img style=\"display:none\" id='img_rep' src=\"gantt.php?WF_ID={$this->workflow->id}&PK_SERVICE={$this->pk_service}\">
			</p>";
        else
            $body .= "<div class=\"br_separator\"></div>";

        if ($this->xmr->depth > 0 && $this->session_vars ['VISITNUM'] == '' && $this->mostra_ana_comune) {
            //	$dir= str_replace("/".$this->service,"",$this->xml_dir);
            $xmr = new xmrwf ("study.xml", $conn);
            $xmr->setConfigParam(true);
            $config = $xmr->getConfigService();
            //	$vlist_2 = new xml_esams_list ( $dir . '/' . $exams,$config,$this->session_vars, $this->conn);
            $body .= str_replace("index.php", "../index.php", $this->vlist_root->esams_list_html($config ['service']));
            $body .= "<table width='95%' align=center><tr><td>";
        }

        $vlist = new xml_esams_list ($this->xml_dir . '/' . $exams);
        $body .= $this->vlist->esams_list_html();

        $ret = "";
        //INFO: Serve questo link??
        $go = mlOut("System.exams.enter", "Enter") . " ";
        $data = " " . mlOut("System.exams.data", "data");

        if (isset($this->xmr->substudies) && is_array($this->xmr->substudies)) foreach ($this->xmr->substudies as $curr_study) {
            $str = "select count(*) conto from {$curr_study->configurations['PREFIX']}_coordinate where  {$curr_study->configurations['PK_SERVICE']}='{$this->pk_service}'";
            $sql = new query ($this->conn);
            $sql->get_row($str);
            $link = $curr_study->configurations ['PREFIX'] . "/" . $this->hrefs ['Vista Paziente'];
            if ($sql->row ['CONTO'] > 0)
                $ret .= "<p align=\"left\">$go<a href=\"$link\">" . $curr_study->workflow ['DESCR'] . "$data&nbsp;&gt;&gt;</a></p>";
        }
        if ($this->xmr->depth != '0') {
            $link = "../" . $this->hrefs ['Vista Paziente'];
            $ret .= "<p align=\"left\">$go<a href=\"$link\">" . $this->xmr_root->workflow ['DESCR'] . "$data&nbsp;&gt;&gt;</a></p>";
        }
        $body .= $ret;
        if ($this->xmr->depth > 0 && $this->session_vars ['VISITNUM'] == '' && $this->mostra_ana_comune) {
            $body .= "</td></tr></table>";
        }
        $legend = new legend ($this->config_service);
        //if($this->session_vars['VISITNUM']!="" || $this->session_vars['GROUP']!="")
        //$body.='<p align="right"><a href="index.php?exams=visite_exam.xml&'.$this->config_service['PK_SERVICE'].'='.$this->session_vars[$this->config_service['PK_SERVICE']].'&CENTER='.$this->session_vars['CENTER'].'">'.$this->testo("Lista completa").'</a></p>';

        $body .= $legend->html_legend_visita;
        if (isset ($xml_forms_not_valid) && is_array($xml_forms_not_valid))
            foreach ($xml_forms_not_valid as $key => $val) {
                $forms_not_valid .= "<li>$val</li>";
            }
        if ($forms_not_valid != '') {
            $forms_not_valid = "<font color='red'><b>Attention: these forms can't be sent:</b></font><ul>$forms_not_valid</ul>Compile all mandatory fields";
        }
        $body = $forms_not_valid . $body;
        $body = $percorso . $body;
        $this->body = $body;
    }

    /**
     * Costruisce la tabella riassuntiva dell'oggetto dello studio
     *
     */
    function tb_riassuntiva()
    {

        return;
    }


    /**
     * Aggiunge una visita progressiva
     *
     * @param number $visitnum
     */
    function addVProgr($visitnum)
    {
        if ($this->integrazione->eq_enabled) {
            if ($this->integrazione->eq_int == '') {
                $this->integrazione->createEq();
            }
        }
        $sql = new query ($this->conn);
        $sql_query = "select max(visitnum_progr)+1 as vprogr from {$this->service}_coordinate
		where {$this->config['PK_SERVICE']}={$this->pk_service}
		and visitnum=$visitnum
		";
        $sql->get_row($sql_query);
        $vprogr = $sql->row ['VPROGR'];
        if ($vprogr == '') $vprogr = 0;
        $val_list = $this->vlist->esams [$visitnum][0]; //Prendo la prima visita progressiva (es. le form attive sulla prima visita progressiva che dovrei sempre avere)
        $hasOneDefault = false;
        foreach ($val_list as $key => $val) {
            if ($val ['DEFAULT'] == 'yes') {
                $hasOneDefault = true;
            }
            break;
        }
        foreach ($val_list as $key => $val) {
            if (!$hasOneDefault || $val ['DEFAULT'] == 'yes') {
                $goon = true;
                if ($val ['CONDITION_VAR'] != '') {
                    $splits = explode(".", $val ['CONDITION_VAR']);
                    $sql_query = "select {$splits[1]} from {$splits[0]} where {$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}";
                    $sql2 = new query ($this->conn);
                    $sql2->get_row($sql_query);
                    if ($sql2->row [$splits [1]] != $val ['CONDITION_VALUE'])
                        $goon = false;
                }
                if ($goon) {
                    $values ['VISITNUM'] = $visitnum;
                    $values ['VISITNUM_PROGR'] = $vprogr;
                    $values ['ESAM'] = $key;
                    $values ['PROGR'] = 1;
                    $values [$this->config ['PK_SERVICE']] = $this->pk_service;
                    $values ['ABILITATO'] = 1;
                    if (isset($this->integrazione->eq_int) && $this->integrazione->eq_int != '') {
                        $values['EQ_ACTION'] = 1;
                        $values['INV_QUERY'] = $this->integrazione->eq_int;
                    }
                    $pk = '';
                    $sql->insert($values, "{$this->service}_coordinate", $pk);
                }
            }
        }
        if (method_exists($this, "vProgrAddRules")) {
            $this->vProgrAddRules($visitnum, $vprogr);
        }
        $this->conn->commit();
        $redirect = "index.php?{$this->config['PK_SERVICE']}={$this->pk_service}&exams&VISITNUM=$visitnum";
        header("location:$redirect");
        die ();
    }

    /**
     * Elimina una visita progressiva
     *
     * @param number $visitnum
     * @param number $vprogr
     */
    function DelVisitProgr($visitnum, $vprogr, $redir = true)
    {
        if ($this->integrazione->eq_enabled) {
            if ($this->integrazione->eq_int == '') {
                $this->integrazione->createEq();
            }
            $bind['PK_SERVICE'] = $this->pk_service;
            $bind['VISITNUM'] = $visitnum;
            $bind['VISITNUM_PROGR'] = $vprogr;
            $sql_delete = "delete from {$this->service}_coordinate
            where {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr and eq_action=1";
            $sql = new query($this->conn);
            $sql->ins_upd($sql_delete, $bind);//binded

            $sql_update = "update {$this->service}_coordinate set inv_query={$this->integrazione->eq_int}, eq_action=2 where
            {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr
            ";
            $sql = new query($this->conn);
            $sql->ins_upd($sql_update, $bind);//binded
            $this->conn->commit();
            $redirect = "index.php?{$this->config['PK_SERVICE']}={$this->pk_service}&exams&VISITNUM=$visitnum";
            header("location:$redirect");
            die ($redirect);
        }
        $sql = new query ($this->conn);
        foreach ($this->vlist->esams [$visitnum] as $key => $val) {
            $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
            $xml_form->xml_form_by_file($this->xml_dir . '/' . $val ['XML']);
            $tbs [$xml_form->form ['TABLE']] = true;
        }
        unset($bindInsert);
        $bindInsert['PK_SERVICE'] = $this->pk_service;
        $bindInsert['VISITNUM'] = $visitnum;
        $bindInsert['VISITNUM_PROGR'] = $vprogr;
        foreach ($tbs as $key => $val) {
            $sql_storico = "insert into s_{$key} select '{$this->user->userid}', sysdate, storico_id.nextval, 'E', null, {$key}.* from {$key}
            where {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr";
            $sql->ins_upd($sql_storico, $bindInsert); //binded
        }
        $sql_delete = "delete from {$this->service}_coordinate where {$this->config['PK_SERVICE']}={$this->pk_service} and visitnum=$visitnum and visitnum_progr=$vprogr";
        unset($bindDelete);
        $bindDelete['PK_SERVICE'] = $this->pk_service;
        $bindDelete['VISITNUM'] = $visitnum;
        $bindDelete['VISITNUM_PROGR'] = $vprogr;
        $sql->ins_upd($sql_delete, $bindDelete);//binded
        if (!$this->config_service['ALLOW_BLANK_VPROGR']) {
            $sql_query = "select max(visitnum_progr) as maxvprogr from {$this->service}_coordinate
            where {$this->config['PK_SERVICE']}={$this->pk_service}
            and visitnum=$visitnum
            ";
            $sql->get_row($sql_query);
            $maxvprogr = $sql->row ['MAXVPROGR'];

            for ($i = $vprogr; $i < $maxvprogr; $i++) {
                $nextvprogr = $i + 1;
                $sql_insert_coord = "
                insert into {$this->service}_coordinate
                (VISITNUM,VISITNUM_PROGR,PROGR,ESAM,INIZIO,FINE,INSERTDT,MODDT,USERID,VISITCLOSE,INV_QUERY,{$this->config['PK_SERVICE']},ABILITATO)
                select
                VISITNUM,$i,PROGR,ESAM,INIZIO,FINE,INSERTDT,MODDT,USERID,VISITCLOSE,INV_QUERY,{$this->config['PK_SERVICE']},ABILITATO
                from {$this->service}_coordinate where
                {$this->config['PK_SERVICE']}=:pk_service
                and visitnum=:visitnum
                and visitnum_progr=:visitnum_progr
                ";
                unset($bindInsert);
                $bindInsert['PK_SERVICE'] = $this->pk_service;
                $bindInsert['VISITNUM'] = $visitnum;
                $bindInsert['VISITNUM_PROGR'] = $nextvprogr;
                $sql->ins_upd($sql_insert_coord, $bindInsert);//binded
                foreach ($tbs as $key => $val) {
                    $sql_storico = "insert into s_{$key} select '{$this->user->userid}', sysdate, storico_id.nextval, 'S', null, {$key}.* from {$key}
                    where {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr";
                    $sql->ins_upd($sql_storico, $bindInsert);//binded
                    $sql_update = "update $key set visitnum_progr=$i
                    where {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr";
                    $sql->ins_upd($sql_update, $bindInsert);//binded
                }
                $sql_delete_coord = "delete from {$this->service}_coordinate
                where
                {$this->config['PK_SERVICE']}=:pk_service
                and visitnum=:visitnum
                and visitnum_progr=:visitnum_progr";
                unset($bindDelete);
                $bindDelete['PK_SERVICE'] = $this->pk_service;
                $bindDelete['VISITNUM'] = $visitnum;
                $bindDelete['VISITNUM_PROGR'] = $nextvprogr;
                $sql->ins_upd($sql_delete_coord, $bindDelete);//binded
            }
        }
        $this->conn->commit();

        if ($redir == true) {
            $redirect = "index.php?{$this->config['PK_SERVICE']}={$this->pk_service}&exams&VISITNUM=$visitnum";
            header("location:$redirect");
            die ($redirect);
        }
    }

    function gestToken($token, $responseType)
    {
        include_once "tokenUtils.inc.php";
        $tokenInfo = TokenUtils::getTokenInfo($this->conn, $this->service, $token);
        if ($tokenInfo['ACTION'] == 'cerca') {
            $this->doCercaAction($tokenInfo);
        }
        if ($tokenInfo['ACTION'] == 'sfoglia') {
            $this->doSfogliaAction($tokenInfo);
        }
    }

    function doSfogliaAction($tokenInfo)
    {
        $data = [];
        $data['status'] = "OK";
        $data['action'] = "index.php?xcrfToken=" . urlencode($tokenInfo['TOKEN_VALUE']) . "&format=" . $_GET['format'];
        $sfogliaFields = $tokenInfo['ARGS']['sfogliaFields'];
        $thisField = "";
        $thisMode = "";
        $idx = 1;
        $bind = [];
        $clauseFields = [];
        $clauseModes = [];
        $data['LEVELS'] = [];
        $data['selectable'] = false;
        $selectableLevel = $tokenInfo['ARGS']['selectableLevel'];
        foreach ($sfogliaFields as $field => $mode) {
            if (isset($_GET['L' . $idx])) {
                $data['LEVELS']["L" . $idx] = $_GET['L' . $idx];
                $clauseFields['L' . $idx] = $field;
                $clauseModes['L' . $idx] = $mode;
                $bind['L' . $idx] = strtoupper($_GET['L' . $idx]);
                $data['action'] .= "&L" . $idx . "=" . urlencode($_GET['L' . $idx]);

            } else {
                if ($idx >= $selectableLevel) $data['selectable'] = true;
                $thisField = $field;
                $thisMode = $mode;
                if ($idx >= count($sfogliaFields)) $data['action'] = null;
                break;
            }
            $idx++;
        }
        $data['nextLevel'] = $idx;
        $where = "";
        if (count($clauseFields) > 0) {
            foreach ($clauseFields as $idx => $field) {
                //    if ($where!="") $where.=" and ";
                $where .= " and UPPER($field)=:{$idx}";
            }
            //$where="where ".$where;
        }
        $mapFields = $tokenInfo['ARGS']['mapFields'];
        $data['mapFields'] = $mapFields;
        $fields = "";
        $groupBy = "";
        foreach ($mapFields as $field => $map) {
            if ($groupBy != "") {
                $groupBy .= ", ";
                $fields .= ", ";
            }
            $fields .= "min(UPPER($field)) as $field";
            $groupBy .= $field;
        }
        if ($groupBy != "") $groupBy = "group by UPPER({$thisField})";

        $sql_level = "select distinct UPPER({$thisField}) as THIS_LEVEL, $fields from {$tokenInfo['ARGS']['table']} where UPPER({$thisField}) is not null {$where} {$groupBy} order by upper($thisField) asc";
        $q = new query($this->conn);
        $q->exec($sql_level, $bind);

        $data['results'] = [];
        while ($q->get_row()) {
            $data['results'][] = $q->row;
        }

        header('Content-Type: application/json');
        echo json_encode($data);
    }


    function doCercaAction($tokenInfo)
    {
        $data = [];
        $data['status'] = "OK";
        if (isset($_POST) && count($_POST) > 0) {
            //$data['token_info']=$tokenInfo;
            $data['mapFields'] = $tokenInfo['ARGS']['mapFields'];
            $searchFields = $tokenInfo['ARGS']['searchFields'];
            $where = "";
            foreach ($searchFields as $field => $mode) {
                if ($where != "") $where .= " or ";
                switch ($mode) {
                    case "fullmatch":
                        $where .= "UPPER({$field}) like '%'||:q||'%'";
                        break;
                }
            }
            $bind['q'] = strtoupper($_POST['q']);
            $mapFields = $tokenInfo['ARGS']['mapFields'];
            $fields = "";
            foreach ($mapFields as $field => $map) {
                if ($fields != "") $fields .= ", ";
                $fields .= $field;
            }

            if (isset($_POST['page']) && $_POST['page'] > 0) {
                $page = $_POST['page'];
            } else {
                $page = 1;
            }
            $rpp = 20;
            $first = ($page - 1) * $rpp;

            $paging = " offset {$first} rows fetch next {$rpp} rows only";

            $sql_count = "select count(*) as C from " . $tokenInfo['ARGS']['table'] . " where " . $where;
            $q = new query($this->conn);
            $q->get_row($sql_count, $bind);
            $data['total'] = $q->row['C'];
            $sql_query = "select " . $fields . " from " . $tokenInfo['ARGS']['table'] . " where " . $where . " " . $paging;
            $q->exec($sql_query, $bind);
            $res = [];
            while ($q->get_row()) {
                $res[] = $q->row;
            }
            $data['page'] = $page;
            $data['pages'] = ceil($data['total'] / $rpp);
            $data['results'] = $res;

        } else {
            $field = [];
            $field['label'] = mlOut($tokenInfo['ARGS']["xmlForm"] . ".cerca", "cerca...");
            $field['name'] = "q";
            $field['type'] = "text";
            $data['form']['fields'][] = $field;
            $data['form']['action'] = "index.php?xcrfToken=" . urlencode($tokenInfo['TOKEN_VALUE']);
        }
        header('Content-Type: application/json');
        echo json_encode($data);
    }

    /**
     * Controller
     *
     */
    function Controller()
    {
        //die("CONT");
        //Verifico alcune tabelle di sistema
        if ($this->config_service['production'] != 1) {
            //Controlla allineamento tabella ACTIVITI_MESSAGES
            $sqlexists = new query($this->conn);
            $sqlexists->set_sql("select count(*) as CONTO from user_objects where object_name='{$this->service}_ACTIVITI_MESSAGES' ");
            $sqlexists->exec();
            $sqlexists->get_row();
            if ($sqlexists->row['CONTO']==0) {
                $creatab = "
						CREATE TABLE {$this->service}_ACTIVITI_MESSAGES
						(
						  PROCESSID  VARCHAR2(200 CHAR),
						  MESSAGE    VARCHAR2(200 CHAR),
						  REDIRECT   VARCHAR2(2000 CHAR)
						)
					";
                $creapktab = "
						ALTER TABLE {$this->service}_ACTIVITI_MESSAGES ADD (
						  CONSTRAINT PK_{$this->service}_ACTIVITI_MESSAGES
						  PRIMARY KEY
						  (PROCESSID)
						  ENABLE VALIDATE)
					";
                $sqlallinea = new query($this->conn);
                $sqlallinea->exec($creatab);
                $sqlallinea->exec($creapktab);
            }
            //Eventuali altre tabelle da controllare
        }
        //Inserisco in libreria il codice di tb_variabili in modo da renderlo uniforme e generico per tutti i servizi
        if ($_GET['tb_variabili']) {
            global $in;
            global $user;
            //var_dump($user);
            //ini_set("display_errors",1);
            //error_reporting(E_ALL);
            if ($in['EXCEL'] != '') {
                putenv("NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1");
            }
            /*
            $user=new user($this->conn, $in['remote_userid'], $this->xmr_root);

            $config_service['filetxt']=$filetxt;

            if (class_exists("Study_{$xmr->prefix}")){
                $class_name="Study_".$xmr->prefix;
            }
            else $class_name="Study";

            $study_=new $class_name($xml_dir, $service, "visite_exams.xml", $conn, $in, $config_service, $user,false, $config_service['WF_NAME'], $xmr);

            */
            $vlist = $this->vlist;
            $es_name = $this->es_name;
            $es_form = $this->es_form;
            $patients_table = $this->patient_table;
            $coordinate = "{$this->service}_COORDINATE";
            $conn = $this->conn;
            $xmr = $this->xmr_root;
            $output = "<table border=1 width=95% align=center>";

            $sql_query = "
select table_name , column_name , data_type , data_length  from user_tab_columns where table_name like '{$xmr->prefix}%' and table_name not like '{$xmr->prefix}WF_%'
";
//			echo $sql_query;
            $sql = new query ($conn);
            $sql->exec($sql_query);
            $db_fields = array();
            while ($sql->get_row()) {
                $db_fields[$sql->row['TABLE_NAME']][$sql->row['COLUMN_NAME']] = $sql->row;
            }
//			print_r($db_fields);


            foreach ($vlist->visitnums as $key => $val) {
                $output .= "<tr><td colspan=8 class=int>{$val['TEXT']}</td></tr>";

                foreach ($vlist->esams [$key] as $esam => $v_esam) {
                    if ($in['EXCEL'] == '') $style = " class=sc4bis width=20%";
                    else $style = "";

                    $form = $v_esam['XML'];
                    $xml_form = new xml_form ($conn, $this->service, $this->config_service, $in, $this->uploaded_file_dir);
                    $xml_form->xml_form_by_file($this->xml_dir . '/' . $form);

                    $output .= "
		<tr>
		<td colspan=8 class=int>N.ro: $esam - XML: {$v_esam['XML']} - Title: {$v_esam['TESTO']} - Table: {$xml_form->form['TABLE']} </td>
		</tr>
		<tr>
		<td $style>Column Name</td>
		<td $style>Data Type</td>
		<td $style>Data Length</td>
		<td $style>Txt</td>
		<td $style>Type</td>
		<td $style>Mandatory</td>
		<td $style>Condition</td>
		<td $style>TB</td>
		</tr>
		";

                    $xml_form = new xml_form ();
                    $xml_form->xml_form_by_file($this->xml_dir . '/' . $v_esam ['XML']);
                    foreach ($xml_form->fields as $key => $val) {
                        if ($val ['VAR'] != '') {
                            $obbligatorio = 'No';
                            $testo = $val ['TESTO'];
                            $search = array("'<script[^>]*?>.*?</script>'si",  // Rimozione del javascript
                                "'<[\/\!]*?[^<>]*?>'si",           // Rimozione dei tag HTML
                                "'([\r\n])[\s]+'",                 // Rimozione degli spazi bianchi
                                "'&(quot|#34);'i",                 // Sostituzione delle entit HTML
                                "'&(amp|#38);'i",
                                "'&(lt|#60);'i",
                                "'&(gt|#62);'i",
                                "'&(nbsp|#160);'i",
                                "'&(iexcl|#161);'i",
                                "'&(cent|#162);'i",
                                "'&(pound|#163);'i",
                                "'&(copy|#169);'i",
                                "'&#(\d+);'e");                    // Valuta come codice PHP

                            $replace = array("",
                                "",
                                "\\1",
                                "\"",
                                "&",
                                "<",
                                ">",
                                " ",
                                chr(161),
                                chr(162),
                                chr(163),
                                chr(169),
                                "chr(\\1)");

                            $testo = preg_replace($search, $replace, $testo);

                            $tipo = $val ['TYPE'];
                            $variabile = "[{$val ['VAR']}]";
                            if ($val ['TYPE'] == 'textbox') {
                                $variabile .= "<br>{$val['VAR_TYPE']}({$val['VAR_SIZE']})";
                            }
                            if ($val ['TYPE'] == 'select' || $val ['TYPE'] == 'radio' || $val ['TYPE'] == 'select_hyper' || $val ['TYPE'] == 'radio_hyper') {
                                $variabile = "[{$val ['VAR']}](Code)<br>[D_{$val ['VAR']}](decode)";
                                foreach ($val['VALUE'] as $idx => $decode) {
                                    $variabile .= "<li>$idx => $decode</li>";
                                }
                            }
                            if ($val ['TYPE'] == 'hidden') {
                                $obbligatorio = 'Auto';
                            }
                            if ($val ['TYPE'] == 'checkbox' || $val ['TYPE'] == 'checkbox_hyper') {
                                $variabile = '';
                                foreach ($val['VALUE'] as $idx => $decode) {
                                    if ($decode != '') $variabile .= "<li>$decode => [$idx]</li>";
                                    else $variabile .= "<li>[$idx]</li>";
                                }
                            }
                            if ($val ['SEND'] != '')
                                $obbligatorio = "Si";
                            $condizioni = '';
                            if ($val ['CONDITION'] != '') {
                                $vars = explode("|", $val ['CONDITION']);
                                $vals = explode("|", $val ['CONDITION_VALUE']);
                                foreach ($vars as $idx => $vl) {
                                    if (preg_match("/^!/", $vals[$idx])) {
                                        $vals[$idx] = str_replace("!", $vals[$idx]);
                                        if ($vals[$idx] == '') $condizioni .= "<li>[{$vars[$idx]}] != null</li>";
                                        else $condizioni .= "<li>[{$vars[$idx]}] != {$vals[$idx]}</li>";
                                    } else $condizioni .= "<li>[{$vars[$idx]}] = {$vals[$idx]}</li>";
                                }
                            }

                            $tb = "Yes";
                            if ($val ['TB'] != '')
                                $tb = 'No';
                            if ($in['EXCEL'] == '') $style = " class=input valign=top";
                            else {
                                $style = "";
                            }
                            //					echo $variabile;

                            /**
                             * Parte relativa al data type e data length
                             */

                            if ($val ['TYPE'] == 'select' || $val ['TYPE'] == 'radio' || $val ['TYPE'] == 'select_hyper' || $val ['TYPE'] == 'radio_hyper') {
                                $ora_type = $db_fields[$xml_form->form['TABLE']][$val ['VAR']]['DATA_TYPE'] . "(Code)<br>" . $db_fields[$xml_form->form['TABLE']]['D_' . $val ['VAR']]['DATA_TYPE'] . "(decode)";
                                $ora_length = $db_fields[$xml_form->form['TABLE']][$val ['VAR']]['DATA_LENGTH'] . "(Code)<br>" . $db_fields[$xml_form->form['TABLE']]['D_' . $val ['VAR']]['DATA_LENGTH'] . "(decode)";
                            } else {
                                $ora_type = $db_fields[$xml_form->form['TABLE']][$val ['VAR']]['DATA_TYPE'];
                                $ora_length = $db_fields[$xml_form->form['TABLE']][$val ['VAR']]['DATA_LENGTH'];
                            }

                            $output .= "
								<tr>
								<td $style>$variabile &nbsp;</td>
								<td $style>$ora_type &nbsp;</td>
								<td $style>$ora_length &nbsp;</td>
								<td $style>$testo &nbsp;</td>
								<td $style>$tipo &nbsp;</td>
								<td $style>$obbligatorio &nbsp;</td>
								<td $style>$condizioni &nbsp;</td>
								<td $style>$tb &nbsp;</td>
								</tr>
								
								";

                        }
                    }

                }
            }
            $output .= "</table>";

            if ($in['EXCEL'] != '') {
                $export_file = "file_variabili.xls";
                //header('Content-Type: application/vnd.ms-excel;');                 // This should work for IE & Opera
                //header("Content-type: application/x-msexcel");                    // This should work for the rest
                //header('Content-Disposition: attachment; filename="'.basename($export_file).'"');
                //header("Content-type: application/vnd.ms-excel");
                //header("Content-Disposition: attachment; filename=".$export_file);
                $output = str_replace("<li>", "", $output);
                $output = str_replace("</li>", "", $output);
                echo $output;
                die();
            }
            //$filetxt = preg_replace ( "/<!--body-->/", $output, $filetxt );
            echo $output;

            die();
        }

        if (isset($_GET['unset'])) {
            unset($_SESSION['labels']);
            $qString = "";
            foreach ($_GET as $k => $v) {
                if ($k != 'unset') {
                    if ($qString != "") $qString .= "&";
                    $qString .= $k . "=" . $v;
                }
            }
            header("Location: index.php?" . $qString);
            die();
        }


        //Verifico alcune tabelle di sistema
        if ($this->config_service['production'] != 1) {
            //Controlla allineamento tabella ACTIVITI_MESSAGES
            $sqlexists = new query($this->conn);
            $sqlexists->set_sql("select count(*) as CONTO from user_objects where object_name='{$this->service}_ACTIVITI_MESSAGES' ");
            $sqlexists->exec();
            $sqlexists->get_row();
            if ($sqlexists->row['CONTO']==0) {
                $creatab = "
						CREATE TABLE {$this->service}_ACTIVITI_MESSAGES
						(
						  PROCESSID  VARCHAR2(200 CHAR),
						  MESSAGE    VARCHAR2(200 CHAR),
						  REDIRECT   VARCHAR2(2000 CHAR)
						)
					";
                $creapktab = "
						ALTER TABLE {$this->service}_ACTIVITI_MESSAGES ADD (
						  CONSTRAINT PK_{$this->service}_ACTIVITI_MESSAGES
						  PRIMARY KEY
						  (PROCESSID)
						  ENABLE VALIDATE)
					";
                $sqlallinea = new query($this->conn);
                $sqlallinea->exec($creatab);
                $sqlallinea->exec($creapktab);
            }
            //Eventuali altre tabelle da controllare
        }

        if (isset($_GET['xcrfToken'])) {
            $format = "xml";
            if (isset($_GET['format'])) $format = $_GET['format'];
            $this->gestToken($_GET['xcrfToken'], $format);
            die();
        }
        if (isset($_GET['report'])) {
            $this->page_title = "";
            $reportLink = $this->configurer->link_params[$_GET['report']];
            $this->body = "<iframe id=\"fullHeightContainer\" src=\"{$reportLink}\">";
            /*
			$this->body="
					<script>
					var reportLink='/pentahoee/{$reportLink}';
					</script>
					<div id='reportContent'></div>
					";
			*/
            $paths[] = array("el-icon-home", "Home page", "");
            $paths[] = array("el-icon-graph", "Report", "");
            $this->breadcrumb = new BreadCrumb($paths);
            return;
        }
        if (!isset($_GET['VISITNUM_PROGR']) && isset($_GET['VISITNUM'])) {
            $_GET['VISITNUM_PROGR'] = "0";
        }
        if (isset($_GET['setLabel'])) {
            mlUpdateLabel($_GET['label'], $_GET['value']);
            header('Cache-Control: no-cache, must-revalidate');
            header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
            header('Content-type: application/json');
            die(json_encode("ok"));
        }
        if (isset($_GET['editLabels'])) {
            if ($this->config_service['lang'] == 'en') $flag = "gb";
            else $flag = $this->config_service['lang'];
            $this->page_title = "<span class='flag-icon flag-icon-{$flag}'></span> " . mlOut("System.Localization Management");
            $sql_query = "
					select distinct LABEL from {$this->service}_I18N order by LABEL asc";
            $sql = new query($this->conn);
            $sql->exec($sql_query);
            $i = 0;
            $lastChapter = "";
            $this->body .= "<form class=\"form-horizontal\">";
            while ($sql->get_row()) {
                $labelSplit = explode(".", $sql->row['LABEL']);
                $chapter = $labelSplit[0];
                if (count($labelSplit) > 1)
                    if ($chapter != $lastChapter) {
                        if ($lastChapter != "") $this->body .= "</div>";
                        $this->body .= "<h5>" . $chapter . " <i  id=\"{$chapter}-plus\" class=\"fa fa-plus-square-o\" onclick=\"$('#{$chapter}').show(); $('#{$chapter}-minus').show(); $(this).hide();\"></i> <i class=\"fa fa-minus-square-o\" onclick=\"$('#{$chapter}').hide(); $('#{$chapter}-plus').show(); $(this).hide();\" style=\"display:none\" id=\"{$chapter}-minus\"></i></h5>";
                        $this->body .= "<div id=\"{$chapter}\" style=\"display:none\">";
                        $lastChapter = $chapter;
                    }

                $i++;
                $this->script .= "<script>
			function updateLabel{$i}(){
				$('#id_icon_{$i}').removeClass('fa fa-check green');
							$('#id_icon_{$i}').removeClass('fa fa-warning red');
							$('#id_icon_{$i}').addClass('icon-spinner icon-spin orange');
							var param='label=" . trim(make_js($sql->row['LABEL'])) . "';
							param+='&value='+$('#id_{$i}').val();
							$.ajax({
						        type: 'GET',
						        url: 'index.php?setLabel&'+param,
						        contentType: 'application/json; charset=utf-8',
						        success: function(data){
									if (data=='ok') {
										$('#id_icon_{$i}').removeClass('icon-spinner icon-spin orange');
										$('#id_icon_{$i}').addClass('fa fa-check green');
									}else {
										$('#id_icon_{$i}').removeClass('icon-spinner icon-spin orange');
										$('#id_icon_{$i}').addClass('fa fa-warning red');
									}
									
								},
						        failure: function(errMsg) {
						            console.log('sono qui errore');
						        }
  });								
			
			}
						</script>";
                $field_value = mlOut($sql->row['LABEL']);
                $field_value = str_replace("\"", "'", $field_value);
                $this->body .= "<div class=\"form-group\">
						<label id=\"lbl_{$i}\" class=\"col-sm-5 control-label no-padding-right\" for=\"id_{$i}_\">
						{$sql->row['LABEL']}&nbsp;<i class=\"fa fa-edit\" onclick=\"RichTextBox('{$i}')\"></i>&nbsp;:
						</label><i id=\"id_icon_{$i}\" ></i> 
						<input class=\"col-sm-5\" id=\"id_{$i}\" onchange=\"updateLabel{$i}();\" type=\"text\" value=\"" . $field_value . "\" name=\"WEIGHT\" size=\"40\">
						</div>";
            }

            $this->body .= "</form>";
            return;
        }
        if (isset($_GET['reloadLabels'])) {
            unset($_SESSION['labels']);
            header('Location: index.php');
            die();
        }
        if (isset($_GET['clearFormLabels'])) {
            $sql = new query($this->conn);
            $sql_query = "select count(*) as c from utenti_visteammin where userid=:userid";
            $bind['userid'] = $this->user->userid;
            $sql->get_row($sql_query, $bind);
            if ($sql->row['C'] > 0) {
                $adminUser = true;
            } else {
                $adminUser = false;
            }
            if ($adminUser) {
                $fname = $_GET['form'];
                if (!$fname) {
                    $fname = $this->vlist->esams[$_GET['VISITNUM']][$_GET['ESAM']]['XML'];
                }
                $formPrefix = str_replace(".xml", "", $fname);
                if ($formPrefix) {
                    mlClearFormLabels($formPrefix);
                }
            }
            header('Location: index.php?' . str_replace("&clearFormLabels=1", "", $_SERVER['QUERY_STRING']));
            die();
        }
        if (isset($_GET['getLanguages'])) {
            header('Cache-Control: no-cache, must-revalidate');
            header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
            header('Content-type: application/json');
            foreach ($this->config_service['aLanguages'] as $key => $val) {
                if ($this->config_service['lang'] != $key)
                    $ret[$key] = $val;
            }
            die(json_encode($ret));
        }
        if (isset($_GET['setLanguage'])) {
            setcookie("{$this->service}_selected_lang", $_GET['setLanguage'], time() + 60 * 60 * 24 * 180);
            unset($_SESSION['labels']);
            die(json_encode("OK"));
        }
        if (isset($_GET['getUserProfiles'])) {
            header('Cache-Control: no-cache, must-revalidate');
            header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
            header('Content-type: application/json');

            foreach ($this->user->usersProfiles as $code => $decode) {
                if ($code != $this->user->profile_code) $profiles[$code] = $decode;
            }
            if (count($profiles) <= 0) die("{\"RETURN\":\"NULL\"}");
            die(json_encode($profiles));
        }

        if (isset($_GET['setUserProfile'])) {
            $sql_get_id = "select ID from STUDIES_PROFILES where STUDY_PREFIX=:prefix and CODE=:code";
            $bind['PREFIX'] = $this->service;
            $bind['CODE'] = $_GET['setUserProfile'];
            $bind['USERID'] = $this->user->userid;
            $sql = new query($this->conn);
            $sql->exec($sql_get_id, $bind);
            $sql->get_row();
            $id = $sql->row['ID'];
            $sql_update = "update USERS_PROFILES set ACTIVE=0 where USERID=:userid AND PROFILE_ID in (select ID from STUDIES_PROFILES where STUDY_PREFIX=:prefix)";
            $sql->ins_upd($sql_update, $bind);
            $sql_update2 = "update USERS_PROFILES set ACTIVE=1 where USERID=:userid AND PROFILE_ID=:id";
            $bind['ID'] = $id;
            $sql->ins_upd($sql_update2, $bind);
            $this->conn->commit();
            header('Cache-Control: no-cache, must-revalidate');
            header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
            header('Content-type: application/json');
            die(json_encode("OK"));
        }

        if (isset($_GET['REOPEN_FORM'])) { //GENHD-364 -> reopen for esource forms
            //var_dump($this->session_vars);
            $in = $this->session_vars;
            if (($in ['USER_TIP'] == 'DE' || $in ['USER_TIP'] == 'CO_PI' || $in ['USER_TIP'] == 'SUB_PI' || $in ['USER_TIP'] == 'ST') && isset ($this->session_vars ['ESAM'])) {//GENHD-364 il DE pu? riaprire le form di eSource.
                $form = $in['form'];
                if (!$form) {
                    $form = $in['FORM'];
                }
                $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                $xml_form->xml_form_by_file($this->xml_dir . '/' . $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['XML']);
                $reopenFormDE = $xml_form->form ['REOPEN_DE'];
                //die($reopenFormDE);
                //var_dump($form);
                if ($form == "eSource.xml" || (substr($form, 0, strlen("Upload")) === "Upload") || $reopenFormDE) {
                    $sql_query = " update {$this->service}_coordinate c set c.visitclose=0, c.fine=0 
                        where {$this->xmr->pk_service} = :CODPAT AND  visitnum=:visitnum and esam=:esam
                        and c.progr = :PROGR and c.visitnum_progr=:VISITNUM_PROGR
                        ";
                    //TODO_ BINDING!
                    $bind[$this->xmr->pk_service] = $in[$this->xmr->pk_service];
                    $bind['VISITNUM'] = $in['VISITNUM'];
                    $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
                    $bind['ESAM'] = $in['ESAM'];
                    $bind['PROGR'] = $in['PROGR'];
                    $sql = new query($this->conn);
                    $sql->ins_upd($sql_query, $bind);
                    $this->conn->commit();
                }
            }
            header("location: ?{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}&CENTER={$in['CENTER']}&form={$in['form']}");
            die();
        }

        if (isset($_GET['AddForm'])) {
            $eCoord = explode(".", $_GET['AddForm']);
            $visitnum = $eCoord[0];
            $esam = $eCoord[1];
            $centerClause = "center in (select center from {$this->service}_UTENTI_CENTRI where userid=:userid)) and ";
            $sql_query = "
			select c.INIZIO, c.visitclose, c.abilitato, c.progr, c.{$this->xmr->pk_service} PK_SERVICE
			from {$this->service}_coordinate c
			where {$this->xmr->pk_service} in (select {$this->xmr->pk_service} from {$this->patient_table} where {$centerClause} visitnum=:visitnum and esam=:esam
			and c.progr = (select max(c1.progr) from {$this->service}_COORDINATE c1 where c.visitnum=c1.visitnum and c.esam=c1.esam and c.visitnum_progr=c1.visitnum_progr and c.{$this->xmr->pk_service}=c1.{$this->xmr->pk_service})
			";
            $bind['USERID'] = $this->session_vars['remote_userid'];
            $bind['VISITNUM'] = $visitnum;
            $bind['ESAM'] = $esam;
            $sql = new query($this->conn);
            $sql->exec($sql_query, $bind);
            while ($sql->get_row()) {
                if ($sql->row['VISITCLOSE'] == '0' && $sql->row['ABILITATO'] == '1') {
                    if ($this->vlist->esams[$visitnum][$esam]['PROGR'] == 'yes' && $this->vlist->esams[$visitnum][$esam]['CORR'] == '') {
                        if ($sql->row['INIZIO'] == '1') {
                            $progr = $sql->row['PROGR'] + 1;

                        } else {
                            $progr = $sql->row['PROGR'];
                        }
                    } else {
                        if ($this->vlist->esams[$visitnum][$esam]['CORR'] != '') {
                            if ($sql->row['INIZIO'] == '1') {
                                $progr = $sql->row['PROGR'];

                            } else continue;
                        } else {
                            if ($sql->row['INIZIO'] == '1') continue;
                            $progr = $sql->row['PROGR'];
                        }
                    }
                    $link = "index.php?{$this->xmr->pk_service}={$sql->row['PK_SERVICE']}&VISITNUM={$visitnum}&ESAM={$esam}&PROGR={$progr}";
                    $code = $sql->row['PK_SERVICE'];
                    $row['code'] = $code;
                    $row['link'] = $link;
                }
                $ret[] = $row;
            }
            header('Cache-Control: no-cache, must-revalidate');
            header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
            header('Content-type: application/json');
            die(json_encode($ret));
        }
        if (isset($_GET['fastSearch'])) {
            //
            //var_dump($this->xmr);
            $sql_query = "select distinct ";
            $pattern = strtoupper($_GET['term']);
            $fieldsList = "r.{$this->xmr->pk_service} as {$this->xmr->pk_service}, c.ESAM, c.VISITNUM, c.PROGR, c.VISITNUM_PROGR";
            $tablesList = "{$this->service}_COORDINATE c, {$this->patient_table} r";
            $wheres = "";
            $wheresAnd = "c.{$this->xmr->pk_service}=r.{$this->xmr->pk_service}";
            foreach ($this->configurer->fastSearch as $key => $val) {
                if ($wheres != "") $wheres .= " or ";
                $where = "";
                if ($val['TYPE'] == 'date') $where = "to_char({$val['FIELD']}, 'DD/MM/YYYY') like '%'||:pattern||'%'";
                if ($val['TYPE'] == 'number') {
                    if (is_numeric($pattern)) $where = "{$val['FIELD']} = :pattern";
                    else $where = "1<>1";
                }
                if ($val['TYPE'] == 'string') $where = "UPPER({$val['FIELD']}) like '%'||:pattern||'%'";
                $wheres .= $where;

                $split = explode(".", $val['FIELD']);
                $table = $split[0];

                if ($fieldsList != "") $fieldsList .= ", ";
                if ($val['TYPE'] == 'date') $fieldsList .= "to_char({$val['FIELD']}, 'DD/MM/YYYY') as F{$key}";
                else $fieldsList .= $val['FIELD'] . " as f{$key}";
                $fieldsList .= ",{$table}.VISITNUM||'-'||{$table}.ESAM||'-'||{$table}.VISITNUM_PROGR||'-'||{$table}.PROGR as L{$key}";
                $fieldsList .= ", case when " . $where . " then 1 else 0 end as C{$key}";
                $fSplit = explode(".", $val['FIELD']);
                if (!isset($tables[$fSplit[0]])) {
                    if ($tablesList != "") $tablesList .= ",";
                    $tablesList .= $fSplit[0];
                    if ($wheresAnd != "") $wheresAnd .= " and ";
                    $wheresAnd .= "{$fSplit[0]}.{$this->xmr->pk_service}(+)=C.{$this->xmr->pk_service}";
                    $tables[$fSplit[0]] = true;
                }
            }
            //if ($this->user->profile_scope!="global")
            $wheresAnd .= " and r.CENTER in (select CENTER from {$this->service}_UTENTI_CENTRI where userid=:userid)";
            $sql_query .= $fieldsList . " from " . $tablesList . " where ({$wheresAnd}) and (" . $wheres . ")";
            $sql = new query($this->conn);
            $bind['PATTERN'] = $pattern;
            $bind['USERID'] = $this->session_vars['remote_userid'];
            $bind['PREFIX'] = $this->service;
            //echo $sql_query;
            $sql->exec($sql_query, $bind);
            while ($sql->get_row()) {
                $res[$sql->row[$this->xmr->pk_service]]['header'] = "";
                foreach ($this->configurer->fastSearch as $key => $val) {
                    if ($val['SHOW_ALWAYS']) {
                        $res[$sql->row[$this->xmr->pk_service]]['header'] .= "<br/><small>{$val['LABEL']}: {$sql->row["F".$key]}</small>";
                    } else {
                        if ($sql->row["C" . $key] == 1) {
                            $res[$sql->row[$this->xmr->pk_service]][$key]['value'] = $sql->row["F" . $key];
                            $coords = $sql->row['L' . $key];
                            $coords = explode("-", $coords);
                            $res[$sql->row[$this->xmr->pk_service]][$key]['links'] = "index.php?{$this->xmr->pk_service}={$sql->row[$this->xmr->pk_service]}&ESAM={$coords[1]}&VISITNUM={$coords[0]}&VISITNUM_PROGR={$coords[2]}&PROGR={$coords[3]}";
                            $noShow[$sql->row[$this->xmr->pk_service]][$key] = false;
                            if ($val['SHOW_NEVER']) $noShow[$sql->row[$this->xmr->pk_service]][$key] = true;
                        }
                    }
                }
            }
            foreach ($res as $key => $val) {
                $showPatientView = true;
                if (isset($this->config_service['disablePatientView'][$this->user->profile_code]) && $this->config_service['disablePatientView'][$this->user->profile_code]) {
                    $showPatientView = false;
                    $thisRow['link'] = "";
                } else
                    $thisRow['link'] = "index.php?{$this->xmr->pk_service}={$key}&exams";
                $thisRow['label'] = mlOut("System.PK_LABEL", "Patient Code") . ": {$key}" . $val['header'];
                foreach ($val as $fIdx => $fVal) {
                    if ($noShow[$key][$fIdx]) continue;
                    if ($fIdx != 'header') {
                        if (preg_match("!{$this->xmr->pk_service}$!i", $this->configurer->fastSearch[$fIdx]['FIELD'])) continue;
                        $fVal = preg_replace("!{$pattern}!i", "<b>{$pattern}</b>", $fVal);
                        if (!$showPatientView) {
                            $link = "<a href=\"{$fVal['links']}\">";
                            $closeLink = "</a>";
                        } else {
                            $link = "";
                            $closeLink = "";
                        }
                        $thisRow['label'] .= "<br/>$link<small>{$this->configurer->fastSearch[$fIdx]['LABEL']}:{$fVal['value']}</small>$closeLink";
                    }
                }
                $ret[] = $thisRow;
            }
            header('Cache-Control: no-cache, must-revalidate');
            header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
            header('Content-type: application/json');
            if (count($ret) == 0) {
                $thisRow['label'] = "Nessun risultato";
                $ret[] = $thisRow;
            }
            die(json_encode($ret));
        }
        $this->title = $this->getStudyTitle();

        /**
         * INiZIO MERGE CRO
         * vmazzeo dmengoli 04-02-2014
         */
        if (class_exists('SDV_module')) {
            //die("SDV!!");
            if ($_GET['sdv_action'] == "eSignature" && !isset($_GET['form'])) {
                $_GET['form'] = "SDV_esign.xml";
                global $in;
                $in['form'] = "SDV_esign.xml";
                $this->session_vars['form'] = "SDV_esign.xml";
            }
            $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], $this->vlist, $this->xml_dir);
            $result = $sdv->before_Controller();
            if ($result != '') {
                $this->body .= $result;
                return;
            }

        }
        global $filetxt;
        global $in;

        if (isset($_GET['time'])) {
            echo date('l jS \of F Y h:i:s A');
            echo " inizio controller hyperlibs<hr>";
        }

        /**
         * Gestione dei report di Pentaho
         * modificato comportamento rispetto a quello implementato da Delsignore
         *
         * Verrocchio 07/05/2011
         */
        if ($this->session_vars['rep_link'] == 'true') {
            // Istanzio la classe così crea le tabelle
            include_once($_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/report_linker.php");
            $module = new linkModule($this->conn, $this->xmr);
            //			require_once $_SERVER['DOCUMENT_ROOT']."/../libs/xCRF/PentahoLib.inc";
            //			$pentaho_lib = new PentahoLib($this->config_service["WF_NAME"], $this->config_service["service"]);
            //			$pentaho_lib->CreateServiceTrigger();
            //			$pentaho_lib->InsertExistingUser();
            //			$pentaho_lib->setDefaultAdmin();
            if (true || $this->session_vars['new_window'] == true || $this->session_vars['new_window'] == 1) {
                $this->session_vars['new_window'] = '';
                $module->controller($this->session_vars);
                $this->body = $module->getResult();

            } elseif (!isset($this->session_vars['REQUEST'])) {
                if (strtolower($this->config_service['lang']) == 'en') {
                    $testo['open_report_button'] = "Open report manager in a new window";
                } else {
                    $testo['open_report_button'] = "Apre il manager dei report in una nuova finestra";
                }

                $this->body .=
                    "<table width=\"90%\" align=\"center\">
						<tr>
						<td align=\"center\">
						<input type=\"button\" value=\"" . $testo['open_report_button'] . "\" onclick=\"window.open('https://" . $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF'] . "?rep_link=true&new_window=1','report','');\" />
								</td>
								</tr>
								</table>";
                $this->session_vars['rep_link'] = '';
                // SETTO il parametro per togliere il banner della nuova finestra
                $query = new query($this->conn);
                $query->exec("SELECT COUNT(*) AS CONTO FROM {$this->service}_REP_LINKS_THEME WHERE CONSTANT='LK_HEIGHT' AND GROUP_LINK='0'");
                $query->get_row();
                if ($query->row['CONTO'] > 0) {
                    $query->exec("UPDATE {$this->service}_REP_LINKS_THEME SET VALUE='0px' WHERE CONSTANT='LK_HEIGHT' AND GROUP_LINK='0'");
                    $this->conn->commit();
                } else {
                    $query->exec("INSERT INTO {$this->service}_REP_LINKS_THEME VALUES('LK_HEIGHT', '0px', '0')");
                    $this->conn->commit();
                }
            }
        }

        /**
         * Logging
         */
        $this->log = new LogActivities($this->session_vars, strtolower($this->config_service['lang']), $this->service, $this->xmr->configurations['PK_SERVICE'], $this->config_service);
        $this->log->DoLog($this->config_service['force_log']);

        /**
         * Accesso concorrente
         */
        $this->concurrent_access = new ConcurrentAccess($this->session_vars, strtolower($this->config_service['lang']), $this->service, $this->xmr->configurations['PK_SERVICE']);

        /**
         * Gestione eQ a livello di campo.
         * @param array $_GET , $_POST
         * Inizializzazione coordinate delle schede progressive.
         */
        //		$_GET[$this->xmr->configurations['PK_SERVICE']] è il CODPAT o chiave primaria del servizio

        if ((!isset($_GET ['VISITNUM_PROGR']) || isset($_GET ['ESAM'])) && !isset($this->session_vars['VISITNUM_PROGR'])) {
            if (isset($_GET[$this->xmr->configurations['PK_SERVICE']])) {
                $_GET ['VISITNUM_PROGR'] = 0;
                $this->session_vars['VISITNUM_PROGR'] = 0;
            }
        }
        // TODO: crea malfunzionamento su esami progressivi in visite progressive!!!!
        /*
		if ( !isset($_GET ['PROGR']) || isset($_GET ['ESAM']) ) {
			if ( isset($_GET[$this->xmr->configurations['PK_SERVICE']]) && !isset($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN']) && !isset($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['PROGR'])){
				$_GET ['PROGR']=1;
				$this->session_vars['PROGR']=1;
			}
		}
		*/
        /**
         * Valorizzazione dell'identificativo dell'eQ.
         */
        if (isset($_GET ['ESAM']) && isset($_GET ['exams'])) {
            if ($this->config_service['eQuery'] == 1) {
                $sql_eqint = "select eq_int from {$this->service}_eqfield where {$this->xmr->pk_service}={$_GET [$this->xmr->pk_service]} and esam={$_GET ['ESAM']}
				";
                $sql2 = new query ($this->conn);
                $sql2->set_sql($sql_eqint);
                $sql2->exec();
                $sql2->get_row();

                $this->integrazione->eq_int = $sql2->row['EQ_INT'];
            }
        }

        /**
         * Approvazione dell'eQ su singolo campo da parte del profilo APPROV_ROLE:
         */
        if (isset($_GET['APPROVA_EQFIELD']) && $_GET['APPROVA_EQFIELD'] != '') {
            $eq_int = $_GET['EQ_INT_FIELD'];
            $eqfield = $_GET['EQFIELD'];
            $d_eqfield = $_GET['D_EQFIELD'];
            $field_ora_approv = $_GET['DATEORA'];
            //			echo $eq_int; echo $eqfield;echo $field_ora_approv;
            $this->integrazione->ApprovaEqField($eq_int, $eqfield, $d_eqfield);
            $this->integrazione->ApprovaEq($this->vlist, $this->xml_dir, $this->config_service, $this->session_vars, $this->uploaded_file_dir, $field_ora_approv);
            $body = "";
            $body .= "<form method='post'>
					<TABLE align=center class=\"bordi\" width=\"70%\">
					<tr>
					<td align=center colspan=4 cols=2><b><font size=\"3\" color=\"green\">eQ Approvata</font></td>
					</tr>
					</table>
					<div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div>
					<TABLE align=center class=\"bordi\" width=\"70%\">
					<tr>
					<td cols=\"2\" align=center><a href=\"index.php?\"><font > << Home Page</font></a></td>
					</tr>
					</table>
					<div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div>
					";
            $this->body .= $body;
            //			header("location: index.php?{$this->xmr->configurations['PK_SERVICE']}={$this->pk_service}&SendAIFA=yes&APPR_EQ_DONE=yes");
            //REDIRECT?
            //if (!isset($REALTIME_EQUERIES)){
            $sql2 = new query ($this->conn);
            $sql2->get_row("SELECT CENTER FROM {$this->service}_{$this->config_service['RegTable']} WHERE {$this->config_service['PK_SERVICE']} = {$in[$this->config_service['PK_SERVICE']]}");

            header("location: ?{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}&CENTER={$sql2->row['CENTER']}");
            die();
            //}
            //else{
            //	return true;
            //}

        }
        /**
         * Rifiuto dell'eQ su singolo campo da parte del profilo APPROV_ROLE:
         */
        if (isset($_GET['RIFIUTA_EQFIELD']) && $_GET['RIFIUTA_EQFIELD'] != '') {
            $eq_int = $_GET['EQ_INT_FIELD'];
            $eqfield = $_GET['EQFIELD'];
            $d_eqfield = $_GET['D_EQFIELD'];
            //				echo $eq_int; echo $eqfield;
            //				die();
            $this->integrazione->RifiutaEqField($eq_int, $eqfield, $d_eqfield);
            $body = "";
            $body .= "<form method='post'>
					<TABLE align=center class=\"bordi\" width=\"70%\">
					<tr>
					<td align=center colspan=4 cols=2><b><font size=\"3\" color=\"red\">eQ Rifiutata</font></td>
					</tr>
					</table>
					<div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div>
					<TABLE align=center class=\"bordi\" width=\"70%\">
					<tr>
					<td cols=\"2\" align=center><a href=\"index.php?\"><font > << Home Page</font></a></td>
					</tr>
					</table>
					<div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div><div class=\"br_separator\"></div>
					";
            $this->body .= $body;
            //REDIRECT?
            if (!$in['PROGR']) {
                $in['PROGR'] = 1;
            }
            $sql2 = new query ($this->conn);
            $sql2->get_row("SELECT CENTER FROM {$this->service}_{$this->config_service['RegTable']} WHERE {$this->config_service['PK_SERVICE']} = {$in[$this->config_service['PK_SERVICE']]}");
            header("location: ?{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}&CENTER={$sql2->row['CENTER']}");

        }


        /**
         * Generazione e salvataggio della eQ in DB
         */
        if (isset($_POST['EQUERY_INT'])) {
            $this->body = $this->integrazione->SaveEqInt();
        }

        /**
         * Generazione dell'eQ da parte del profile APPROV_ROLE.
         * Caso in cui il DM effettua un eQ, compila le textarea e genera l'eQ
         */
        if (isset($_POST['salva_eq_dm'])) {
            //			print_r($_POST);
            $this->integrazione->GenerateEqDM($_POST);
        }
        /**
         * Gestione liste equery
         */
        if (isset($_GET ['EQ_DE'])) {
            $this->HomePage();
        }
        if (isset($_GET ['EQ_DM'])) {
            $this->HomePage();
        }
        /**
         * Fine gestione eQ a livello di campo.
         */

        if (isset($_GET['time'])) {
            echo date('l jS \of F Y h:i:s A');
            echo " Prima controller libs in hyperlibs<hr>";
        }

        if (isset($_GET['time'])) {
            echo date('l jS \of F Y h:i:s A');
            echo " Dopo controller libs in hyperlibs<hr>";
        }

        if (isset ($in['remote_userid'])) {
            //			echo $in['remote_userid'];
            $filetxt = preg_replace("/<!--fulluserid-->/", $in['remote_userid'], $filetxt);
            $remote_userid = substr($in['remote_userid'], 0, 3);
            $filetxt = preg_replace("/<!--userid-->/", $remote_userid, $filetxt);
        }

        //Gestione CRF Bianca e Annotata

        if (isset ($_GET ['CRF'])) {
            if (isset($this->config_service['LANDSCAPE_MODE']) && $this->config_service['LANDSCAPE_MODE'] == true) $this->body = $this->crf(true);
            else    $this->body = $this->crf();
        }
        if (isset ($_GET ['CRF_BLANK'])) {

            $this->body = $this->crf_blank();

        }
        if (isset ($_GET ['CRF_ANNOTE'])) {

            $this->body = $this->crf_blank();
        }
        //Fine gestione CRF Bianca e Annotata


        /**
         * Creazione file di configurazione per Browse Table
         * Creazione report di installazione
         */
        /*
		$today = date("Ymd");
		$filename= "Parsing_InstallationReport_".$today;
		if(!file_exists($filename)){
			//Creazione file di configurazione per Browse Table
			$this->Parsing();
			//Creazione report di installazione
			$this->InstallationReport();

			system('rm -f Parsing_InstallationReport_[0-9]*');

			$fp = fopen(''.$filename.'', 'w');


		}
		*/
        if (isset($_GET['time'])) {
            echo date('l jS \of F Y h:i:s A');
            echo " Fine controller hyperlibs<hr>";
        }

        if (isset ($_GET ['HYPERFILE'])) {
            $this->HomePage();
        }

        /**
         *  Gestione Main - Sub
         */

        if (isset ($_GET ['SEND_MAINSUB'])) {
            $this->SendMainSub();
        }

        if ($_GET ['CANCELLA_LA_SCHEDA'] == 'yes') {
            $this->pk_service = $_GET [$this->config_service ['PK_SERVICE']];
            $esam = $_GET ['ESAM'];
            $visitnum = $_GET ['VISITNUM'];
            $visitnum_progr = $_GET ['VISITNUM_PROGR'];
            $progr = $_GET ['PROGR'];
            $center = $_GET ['CENTER'];
            $this->CancelProgrEsam($visitnum, $visitnum_progr, $esam, $progr, $center);
        }
        if (isset($_GET ['PROGR']) && isset($_GET ['ESAM']) && isset($_GET ['VISITNUM']) && isset($_GET ['VISITNUM_PROGR'])) {
            $this->pk_service = $_GET [$this->config_service ['PK_SERVICE']];
            $esam = $_GET ['ESAM'];
            $visitnum = $_GET ['VISITNUM'];
            $visitnum_progr = $_GET ['VISITNUM_PROGR'];
            $progr = $_GET ['PROGR'];
            if (strtolower($this->config_service['lang']) == 'en') {
                $link_txt = "Back to records list";
            } else {
                $link_txt = "Torna alla lista dei record";
            }

            if ($this->vlist->esams[$visitnum][$esam]['SUB'] == "yes") {
                $link = "index.php?CENTER=" . $in['CENTER'] . "&{$this->config_service['PK_SERVICE']}=" . $in[$this->config_service['PK_SERVICE']] . "&VISITNUM=" . $in['VISITNUM'] . "&ESAM=" . $esam . "&form=" . $this->vlist->esams[$visitnum][$esam]['XML'] . "";
                $this->body .= '
						<p align=left><a href="' . $link . '" >&lt;&lt;' . $link_txt . '</a></p>';
            } elseif ($this->vlist->esams[$visitnum][$esam]['MAIN'] == "yes") {
                $this->body .= $this->MainSentLink($in);
            }
        }
        if ($_GET ['REOPEN_MAINSUB'] == 'yes') {
            //die("ENTRO?");
            $this->pk_service = $_GET [$this->config_service ['PK_SERVICE']];
            $esam = $_GET ['ESAM'];
            $visitnum = $_GET ['VISITNUM'];
            $visitnum_progr = $_GET ['VISITNUM_PROGR'];
            $progr = $_GET ['PROGR'];
            $center = $_GET ['CENTER'];
            $this->MainSubReOpen($visitnum, $visitnum_progr, $esam, $progr, $this->pk_service, $center);
        }

        /**
         * Fine Gestione Main - Sub
         */


        /**
         * Source Data Verification
         */
        if (isset($_POST['source_data_verification']) && $this->config_service['SDV'] == "1" && isset($this->config_service['SDV'])) {
            $form = $this->vlist->esams[$this->session_vars['VISITNUM']][$this->session_vars['ESAM']]['XML'];
            $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
            $xml_form->xml_form_by_file($this->xml_dir . '/' . $form);

            $SDV = new SourceDataVerification($this->service, $this->conn, $this->config_service, $this->vlist);
            $SDV->SDV_validate($_POST, $xml_form);
        }
        //print_r($_GET);
        if (isset($_GET['SDV_LIST'])) {
            $str = "select count(*) conto from {$this->service}_utenti_centri where userid='{$this->user->userid}'";
            $sql = new query($this->conn);
            $sql->get_row($str);
            if ($sql->row['CONTO'] > 1 && $this->session_vars['CENTER'] == '') {
                $list = "patients_list_center.xml";
                //echo $this->xml_dir. "/" . $list ;
                if (file_exists($this->xml_dir . "/" . $list)) {
                    $_GET['list'] = $list;
                    $list = $_GET ['list'];
                    $list_o = new xml_list ($this->xml_dir . "/" . $list, null, null, null, null, $this->session_vars, $this->visit_structure);
                    //Nuovo modo di generare il menu briciola di pane
                    $this->percorso = $this->breadcrumb("patients_list");
                    $this->body .= $this->percorso;
                    //Inserisco qui il titolo del report
                    switch (strtoupper($_GET['SDV_LIST'])) {
                        case "STATUS":
                            $this->body .= "<p style=\"font-size: large;text-align:center;\">SDV STATUS List</p>";
                            break;
                        case "SIGNATURE":
                            $this->body .= "<p style=\"font-size: large;text-align:center;\">SDV SIGNATURE Report</p>";
                            break;
                        case "VIOLATION":
                            $this->body .= "<p style=\"font-size: large;text-align:center;\">SDV PROTOCOL VIOLATION Report</p>";
                            break;
                    }
                    $this->body .= $list_o->list_html($this->session_vars);
                    //https://pierrelcsv.test.hypernetproject.com/uxmr/index.php?&list=patients_list.xml&CENTER=070
                    $this->body = preg_replace('/list=(.+)\.xml/', "SDV_LIST={$_GET['SDV_LIST']}", $this->body);
                    //$this->body = preg_replace('/list=patients_list.xml/', "SDV_LIST={$_GET['SDV_LIST']}", $this->body);
                }
                if ($list != 'patients_list_center.xml') {
                    $legend = new legend ($this->config_service);
                }
                $this->body .= $legend->html_legend_lista;

            } else {
                $SDV = new SourceDataVerification($this->service, $this->conn, $this->config_service, $this->vlist);
                switch (strtoupper($_GET['SDV_LIST'])) {
                    case "STATUS":
                        $this->body .= "<p style=\"font-size: large;text-align:center;\">SDV STATUS List</p>";
                        $this->body .= $SDV->ListStatusHtml($this->session_vars, SDV_LTYPE_STATUS);
                        $legend = new legend ($this->config_service);
                        $this->body .= $legend->html_legend_lista;
                        break;
                    case "SIGNATURE":
                        $this->body .= "<p style=\"font-size: large;text-align:center;\">SDV SIGNATURE Report</p>";
                        $this->body .= $SDV->ListStatusHtml($this->session_vars, SDV_LTYPE_SIGNATURE);
                        break;
                    case "VIOLATION":
                        $this->body .= "<p style=\"font-size: large;text-align:center;\">SDV PROTOCOL VIOLATION Report</p>";
                        $this->body .= $SDV->ListStatusHtml($this->session_vars, SDV_LTYPE_VIOLATION);
                        break;
                }
                //$legend = new legend ( $this->config_service );
                //$this->body .= $legend->html_legend_lista;
            }
        }

        /**
         * Creazione tabelle di sistema e di lookup
         */
        if (isset($_GET['SYS_TABLES'])) {

            $sys_tables = new SysTables($this->service, $this->conn, $this->config_service, $this->vlist, $this->xml_dir);
            $cornice = $sys_tables->CorniceHtml();
            $done_html = "<div style=\"margin:auto;text-align:center;font-weight:bold;color:green;\"><h2>Tabella generata con successo!</h2></div>";
            $this->body .= "<form method=\"POST\" name=\"SYS_TABLES\" action=\"\" style=\"margin:auto;text-align:center;\">";
            $this->body .= "Select Table:  <select name=\"TABLE\" onchange=\"doRedirect(this.value); \">
			<option value='' >&nbsp;</option>
			<option value=\"ESTA\" >{$this->service}_SYS_ESTA</option>
			<option value=\"LKUP\" >{$this->service}_SYS_LKUP</option>
			<option value=\"VRLB\" >{$this->service}_SYS_VRLB</option>
			<option value=\"OTHVR\" >{$this->service}_SYS_OTHVR</option>
			<option value=\"VISIT\" >{$this->service}_SYS_VISIT</option>
			</select>";
            $this->body .= " <div class=\"br_separator\"></div>  <input type='submit' name='Generate_Tables' value='Generate' ></input>";
            if ($_POST['TABLE'] == 'ESTA') {
                //Popolamento tabella di sistema contenente corrispondenza nome form - tabella - num esame
                $sys_tables->SysEsta();
                $this->body .= $done_html;
            } elseif ($_POST['TABLE'] == 'LKUP') {
                //Popolamento tabella di sistema contenente le lookup di tutti i campi con decodifica
                $sys_tables->SysLkup();
                $this->body .= $done_html;
            } elseif ($_POST['TABLE'] == 'VRLB') {
                //Popolamento tabella di sistema contenente le lookup di Tutte le variabili di tutte le tabelle dello studio
                $sys_tables->SysVrlb();
                $this->body .= $done_html;
            } elseif ($_POST['TABLE'] == 'OTHVR') {
                //Popolamento tabella di sistema contenente le lookup di Tutte le variabili speciali  di tutte le tabelle dello studio
                $sys_tables->SysOthvr();
                $this->body .= $done_html;
            } elseif ($_POST['TABLE'] == 'VISIT') {
                //Popolamento tabella di sistema contenente le lookup di Tutte le variabili speciali  di tutte le tabelle dello studio
                $sys_tables->SysVisit();
                $this->body .= $done_html;
            }
            $this->body = preg_replace("/<!--form-->/", $this->body, $cornice);

        }
        /**
         * FINE MERGE CRO
         */

        /*
		 * vmazzeo 23.02.2015
		 * gestione REALTIME eQUERY per CRO exom
		 *
		 * **************INIZIO**************
		 */
        //print_r($this->session_vars);
        //die();
        if (!isset($_POST['ajax_call']) && isset($_POST['REALTIME_EQUERIES']) && $_POST['REALTIME_EQUERIES'] != "[ { } ]" && $this->session_vars['USER_TIP'] != "DM") { //Solo con utente data entry!
            $realtime_equeries = json_decode($_POST['REALTIME_EQUERIES']);
            // echo "<pre>";
            // print_r($realtime_equeries);
            // echo "</pre>";
            // die();
            foreach ($realtime_equeries as $realtime_equery) {

                $realtime_equery = (array)$realtime_equery;
                $realtime_equery = (array)$realtime_equery[0];
                $generate_eq_dm = array_merge($realtime_equery, $this->session_vars);
                $generate_eq_dm['REALTIME_EQUERIES'] = 1;
                // echo "<pre> oggetto<br/>";
                // print_r($realtime_equery);
                // echo "</pre>";
                $generate_eq_dm['USERID_INS'] = 'REALTIME_EQUERY';
                // echo "<pre> GENERO lA QUERY <br/>";
                // print_r($generate_eq_dm);
                // echo "</pre>";
                //die();
                $this->integrazione->GenerateEqDM($generate_eq_dm); //GENERO LA REALTIME EQUERY COME DM dummy "REALTIME_EQUERY"

                $form = $this->vlist->esams[$this->session_vars['VISITNUM']][$this->session_vars['ESAM']]['XML'];
                $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                $xml_form->xml_form_by_file($this->xml_dir . '/' . $form);

                foreach ($realtime_equery as $key => $value) {
                    $_POST[$key] = $value;//COPIO TUTTO IN $_POST PERCHE' integrazione->SaveEqDE cerca le variabili di $_POST TODO:modificare?!?
                    $_GET[$key] = $value;//COPIO TUTTO IN $_GET PERCHE' integrazione->ApprovaEq cerca le variabili di $_GET TODO:modificare?!?
                }
                // echo "<pre> RISPONDO ALLA QUERY <br/>";
                // print_r($_POST);
                // print_r($_GET);
                // echo "</pre>";
                //die();
                $this->integrazione->SaveEqDE($xml_form); //RISPONDO ALLA EQUERY APPENA CREATA CON RISPOSTA UGUALE AL TESTO DEL BOTTONE CLICCATO
                //SVUOTO TUTTO IN $_POST PER NON AVERE CONFLITTI CON LE EQUERY APPENA RISPOSTE
                foreach ($realtime_equery as $key => $value) {
                    unset($_POST[$key]);
                    unset($_GET[$key]);
                }
                // echo "<pre> HO RSISPOSTO e unsettato le post  ALLA QUERY <br/>";
                // print_r($_POST);
                // echo "</pre>";
                // //die();
                // echo "<pre> APPROVO LA QUERY <br/>";
                // print_r($this->integrazione->eq_int);
                // echo "</pre>";
                //die();
                $generate_eq_dm['EQ_INT_FIELD'] = $this->integrazione->eq_int;
                $this->integrazione->ApprovaEqField($this->integrazione->eq_int, $realtime_equery['EQFIELD'], "D_" . $realtime_equery['EQFIELD'], $generate_eq_dm['REALTIME_EQUERIES']); //APPROVO LA QUERY COME DM dummy "REALTIME_EQUERY"
                $this->integrazione->ApprovaEq($this->vlist, $this->xml_dir, $this->config_service, $generate_eq_dm, $this->uploaded_file_dir);
                //die();
            }
        }
        /*
		 * **************FINE**************
		 *
		 * vmazzeo 23.02.2015
		 * gestione REALTIME eQUERY per CRO exom
		 *
		 */

//		$test_date=date("H:i:s.u");
//
        if (isset($_GET['SFOGLIA']) || isset($_POST['SFOGLIA'])) {
            $this->SfogliaPage();
            return;
        }
        if (isset($this->session_vars['CMELayer']) && !isset($this->session_vars['DocPrat'])) {
            include_once("CMELayer.inc");
            if (!class_exists("CMELayerWCA")) {
                include_once($_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/CMELayer.inc");
                eval("class CMELayerWCA extends CMELayerWCAPrototype{}");
            }
            $configuration['SERVICE'] = $this->service;
            $configuration['PK_SERVICE'] = $this->config_service['PK_SERVICE'];
            $configuration['queryNames'] = $this->config_service['QUERYNAMES'];
            $CME = new CMELayerWCA($this->conn, $configuration, $this->session_vars, $this->config_service);
            $CME->controller();
            $this->body .= $CME->html;
            return;
        }
        if (isset($_GET['XmrFileUpload'])) {
            include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/field_big_file.inc";
            field_big_file::showApplet($this);
        }
        if (isset($_POST['XmrFileUpload'])) {
            include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/field_big_file.inc";
            field_big_file::gestSaving($this);
        }
        if (isset($this->session_vars['pdf_esame'])) {
            $visitnum_progr = $this->session_vars['VISITNUM_PROGR'] ? $this->session_vars['VISITNUM_PROGR'] : 0;
            $progr = $this->session_vars['PROGR'] ? $this->session_vars['PROGR'] : 1;
            return $this->pdf_esame($this->session_vars['ESAM'], $this->session_vars['VISITNUM'], $visitnum_progr, $progr);
        }
        if (isset ($this->workflow)) {
            if ($this->pk_service != '')
                $this->workflow->MakeAutomaticChange();

            //se il multiprofilo  abiltiato per questo xmr
            if ($this->config_service['multi_profilo'][$this->service] && $this->config_service['multi_profilo_prefix'][$this->service] == $this->workflow->prefix) {
                //$cookie_name="MultiProfilo_".$this->workflow->prefix;
                $cookie_name = "MultiProfilo_" . $this->workflow->prefix . "_" . $this->user->userid;

                //CAMBIO DEL PROFILO DA GET/COOKIE
                if (isset($_GET['profile']) && $_GET['profile'] != "" && preg_match("/[0-9]+/", $_GET['profile']) /*&& array_key_exists($_GET['profile'],$this->workflow->profile_list)*/) {
                    //controllare che questo utente posso farlo
                    $this->profile_id = $_GET['profile'];
                    setcookie($cookie_name, $_GET['profile'], time() + 3600);
                    //setcookie($cookie_name, $this->user->userid,time()+3600);
                    $url = preg_replace("/\&profile=[0-9]/i", "", $_SERVER['REQUEST_URI']);

                    if (!preg_match("/\?/", $url)) $url = $url . "?";
                    $url = rtrim($url, '?');

                    header("Location: $url");
                    die();
                }

                //SE esiste questa vista  abilitato il multiprofilo
//				$sql_query="select * from user_objects where object_name = '{$this->workflow->prefix}_ASSIGN_PROFILI'";
//	//			echo $sql_query;
//				$sql_check=new query($this->conn);
//				$sql_check->set_sql($sql_query);
//				$sql_check->exec();//commentata
//				if($sql_check->numrows>0) {
//					$sql_query="select PROFILE from {$this->workflow->prefix}_ASSIGN_PROFILI where USERID='{$this->user->userid}' AND PREDEF_ID='Yes'";
//	//				echo $sql_query;
//					$sql_att=new query($this->conn);
//					$sql_att->set_sql($sql_query);
//					$sql_att->exec();//commentata
//					$sql_att->get_row();
//	//				echo "<!--PROFILE: ".	$sql_att->row['PROFILE']."-->";
//				}
                //estraggo gli user dei profili
                $sql_query = "select table_name from user_objects where object_name = '{$this->workflow->prefix}_ASSIGN_PROFILI'";
                $sql_check = new query($this->conn);
                $sql_check->set_sql($sql_query);
                $sql_check->exec();    //non richiede binding

                if (isset($_COOKIE[$cookie_name]) && $_COOKIE[$cookie_name] != "" /*&& array_key_exists($_COOKIE[$cookie_name],$this->workflow->profile_list)*/) {
                    //considerare il nome utente
                    $this->profile_id = $_COOKIE[$cookie_name];
                } else if ($sql_check->numrows > 0) {
                    //print_r($this->workflow); die();
                    $sql_query = "select PROFILE from {$this->workflow->prefix}_ASSIGN_PROFILI where USERID=:userid AND PREDEF_ID='Yes'";
                    $sql_att = new query($this->conn);
                    $sql_att->set_sql($sql_query);
                    unset($bind_userid);
                    $bind_userid['USERID'] = $this->user->userid;
                    $sql_att->exec($sql_query, $bind_userid);//binded
                    $sql_att->get_row();

                    //lettura del predefinito
                    $this->profile_id = $sql_att->row['PROFILE'];
                    //					echo "profilo_id: ".$this->profile_id;
//					$cookie_name="MultiProfilo_".$this->workflow->prefix."_".$this->user->userid;

                    if (array_key_exists($this->profile_id, $this->workflow->profile_list) && preg_match("/[0-9]+/", $this->profile_id)) {
                        setcookie($cookie_name, $this->profile_id, time() + 3600);
                    }
                    //setcookie($cookie_name, ,time()+3600);

                }
                //FINE CAMBIO DEL PROFILO DA GET/COOKIE

                if (isset($_GET['ADMIN_PROFILI']) && $_GET['ADMIN_PROFILI'] != "") {
                    $this->admin_profili_html = $this->admin_profili_tb();
                    $this->body = $this->admin_profili_html;
                }

            }//chiuso if abilitato multiprof

        }

//		$test_date=date("H:i:s.u");

//		if (isset($_GET['eCRF_PDF'])){
//			$this->eCRF(true);
//		}
//		if (isset($_GET['eCRF'])){
//			$this->eCRF(false);
//		}
//

        if (isset ($_GET ['CRF'])) {
            if (isset($this->config_service['LANDSCAPE_MODE']) && $this->config_service['LANDSCAPE_MODE'] == true) $this->body = $this->crf(true);
            else    $this->body = $this->crf();
        }

        //Luigi: assegna automaticamente il prossimo progr senza ricavarlo manualmente
        if (isset($_GET['AUTOPROGR'])) {
            $sql_query = "select max(progr) as maxprogr from {$this->service}_coordinate where {$this->config_service['PK_SERVICE']}=:ID_SPER and esam=:ESAM and visitnum=:VISITNUM and visitnum_progr=:VISITNUM_PROGR";
            $array_bind['ID_SPER'] = $this->pk_service;
            $array_bind['ESAM'] = $_GET['ESAM'];
            $array_bind['VISITNUM'] = $_GET['VISITNUM'];
            $array_bind['VISITNUM_PROGR'] = $_GET['VISITNUM_PROGR'] ? $_GET['VISITNUM_PROGR'] : 0;


            $query = new query($this->conn);
            $query->exec($sql_query, $array_bind);
            $query->get_row();
            if ($query->row['MAXPROGR'] == '') {
                $query->row['MAXPROGR'] += 1;
            }
///			print ($query->row['MAXPROGR']);

            $sql_query2 = "select inizio from {$this->service}_coordinate where {$this->config_service['PK_SERVICE']}=:ID_SPER and esam=:ESAM and visitnum=:VISITNUM and progr={$query->row['MAXPROGR']}";
            $query2 = new query($this->conn);
            $query2->exec($sql_query2, $array_bind);
            $query2->get_row();

            if ($query2->row['INIZIO'] == 1) {
                $nextprogr = $query->row['MAXPROGR'] + 1;
            } else {
                $nextprogr = $query->row['MAXPROGR'];
            }

            $param = "";
            foreach ($_GET as $indice => $valore) {
                if ($indice != "AUTOPROGR") {
                    $param .= $indice;
                    $param .= "=";
                    $param .= $valore;
                    $param .= "&";
                }
            }
            $param .= "PROGR=$nextprogr";
            header("location: index.php?$param");
            die ();
        }

        //Luigi: assegna automaticamente il prossimo visitnum_progr senza ricavarlo manualmente
        if (isset($_GET['AUTOVPROGR'])) {
            $sql_query = "select max(visitnum_progr) as maxvprogr from ossc3_coordinate where {$this->config_service['PK_SERVICE']}=:ID_SPER and visitnum=:VISITNUM";
            $array_bind['ID_SPER'] = $_GET['ID_SPER'];
            $array_bind['VISITNUM'] = $_GET['VISITNUM'];

            $query = new query($this->conn);
            $query->exec($sql_query, $array_bind);
            $query->get_row();

            if ($query->row['MAXVPROGR'] != '') {
                $nextprogr = $query->row['MAXVPROGR'] + 1;
            } else {
                $nextprogr = 0;
            }

            $param = "";
            foreach ($_GET as $indice => $valore) {
                if ($indice != "AUTOVPROGR") {
                    $param .= $indice;
                    $param .= "=";
                    $param .= $valore;
                    $param .= "&";
                }
            }
            $param .= "VISITNUM_PROGR=$nextprogr";
            header("location: index.php?$param");
            die ();
        }

        //			}
        if (isset($_GET['field_file_doc'])) {
            if (file_exists("fields/field_file_doc.inc")) include_once "fields/field_file_doc.inc";
            else include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/field_file_doc.inc";
            if (class_exists("field_file_doc_gest")) {
                $field_file_doc_ajax_gest = new  field_file_doc_gest();
                $field_file_doc_ajax_gest->Controller();
                die();
            }
        }
        if (isset($_GET['field_file_cme'])) {
            if (file_exists($this->config_service['field_lib'] . "/field_file_cme.inc")) include_once $this->config_service['field_lib'] . "/field_file_cme.inc";
            else include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/field_file_cme.inc";
            if (class_exists("field_file_cme_gest")) {
                $field_file_cme_ajax_gest = new  field_file_cme_gest();
                $field_file_cme_ajax_gest->Controller();
                die();
            }
        }
        if (isset($_GET['getFP'])) {
            echo "<table cellpadding=0 cellspacing=0 border=1>";
            foreach ($this->vlist->esams as $k => $v) {
                foreach ($v as $e => $es) {

                    $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                    $xml_form->xml_form_by_file($this->xml_dir . '/' . $es['XML']);
                    $count_campi = 0;
                    $tb_ = '';
                    $tb_ext = '';
                    $tbf_ = '';
                    foreach ($xml_form->fields as $key => $val) {
                        if ($val['VAR'] != '' && $val['TB'] != 'no')
                            $count_campi++;
                        if ($val['BYTB'] != '') {
                            $tb_ext[$val['BYTB']] = true;
                        }
                    }
                    foreach ($tb_ext as $key => $val) {
                        $tb_ .= "$key<br/>";
                        $tbf_ .= "2<br/>";
                    }
                    if (isset($xml_form->form['F_TO_CALL'])) {
                        $f_ext = "Controllare la funzione:{$xml_form->form['F_TO_CALL']}";
                    }
                    $tb_ = rtrim($tb_, "<br/>");
                    $tbf_ = rtrim($tbf_, "<br/>");
                    echo "
					<tr>
						<td>{$xml_form->form['TITOLO']}</td>
						<td>{$xml_form->form['TABLE']}</td>
						<td>$count_campi</td>
						<td>$tb_</td>
						<td>$tbf_</td>
						<td>{$xml_form->form['TABLE']}</td>
						<td>$count_campi</td>
						<td>$f_ext</td>
						<td>$f_ext</td>
					</tr>";
                }
            }
            echo "</table>";
            die();
        }


        if (isset ($_POST ['eQuery_Integrazione_Send_']) || isset ($_POST ['eQuery_Integrazione_Send'])) {
            print_r($_POST);
            die ();
        }
        if (isset ($_GET ['CLOSE_VISIT'])) {

            $this->body = $this->close_all($_GET ['CLOSE_VISIT']);
            return;
        }
        if (isset($_POST['EQUERY_OBJ'])) {
            $curr_equery_obj = $this->equery_objs[$_POST['EQUERY_OBJ']];
            $curr_equery_obj->save();
        }
        if (isset($_POST['ID_QUERY']) && !isset($_POST['eform']) && !isset($_POST['EQUERY_OBJ'])) {
            $this->eQuerySave();
        }
        if (isset($_GET['CREATE_VPROGR']) && $_GET['CREATE_VPROGR'] == 'yes') {
            //LUIGI: controllo sui diritti di creazione
            $visitnum = $_GET ['VISITNUM'];
            if (!isset ($this->vlist->visitnums[$visitnum]['BUTTONS_DISABLED']) && $this->session_vars['USER_TIP'] == 'DE') {
                $this->addVProgr($_GET['VISITNUM']);
                die();
            } else {
                error_page($this->user->userid, $this->testo("NOTCREABLE"), "");
            }
        }
        if (isset($_GET['DelVisitProgr']) && $_GET['DelVisitProgr'] == 'yes') {
            //LUIGI: controllo sui diritti di cancellazione
            $visitnum = $_GET ['VISITNUM'];
            if (!isset($this->config_service['deletableVisits']) || $this->config_service['deletableVisits'][$this->user->profilo][$visitnum] == true) {
                $this->DelVisitProgr($_GET['VISITNUM'], $_GET['VISITNUM_PROGR']);
                die();
            } else {
                error_page($this->user->userid, $this->testo("NOTDELETABLE"), "");
            }
        }

        if ($_GET ['ELIMINA_LA_SCHEDA'] == 'yes') {
            $this->pk_service = $_GET [$this->config_service ['PK_SERVICE']];
            $esam = $_GET ['ESAM'];
            $visitnum = $_GET ['VISITNUM'];
            $visitnum_progr = $_GET ['VISITNUM_PROGR'];
            $progr = $_GET ['PROGR'];
            //TODO: Roba vecchia?? LUIGI: controllo sui diritti di cancellazione
            //if ($this->config_service['deletableExams'][$this->user->profilo][$visitnum][$esam]==true){
            $this->DeleteProgrEsam("", $visitnum, $visitnum_progr, $esam, $progr);
            $param = '';
            foreach ($_GET as $key => $val) {
                if ($key != 'ELIMINA_LA_SCHEDA' && $key != 'PROGR') {
                    $param .= "$key={$val}&"; //&amp;-->??
                }
            }
            $param .= "NoQuickAccess=yes";
            $param = rtrim($param, "&");
            $url = "index.php?$param";
// 			die("<html><head><meta http-equiv=\"refresh\" content=\"0;url=$url\"></head></html>");
            ob_clean();
            header('location:' . $url);
            $this->conn->commit();
            die();
            //} else {
            //	error_page ( $this->user->userid, "Scheda non eliminabile", "" );
            //}
        }

        if (((isset ($_POST ['invia']) && $_POST ['invia'] != '')) || $_POST ['INVIOCO'] == '1') {

            $this->SendForm($_POST ['form']);

        }
        if (((isset ($_GET ['invia']) && $_GET ['invia'] != '')) || $_GET ['INVIOCO'] == '1') {
            $this->SendForm($_GET ['form'], true);

        }

        if ((isset ($_GET ['salva']) && $_GET ['salva'] != '') || $_GET ['INVIOCO'] == '0') {

            $this->SaveForm($_GET ['form'], true);
        }
        if ((isset ($_POST ['salva']) && $_POST ['salva'] != '') || $_POST ['INVIOCO'] == '0') {

            $this->SaveForm($_POST ['form']);
        }

        if (count($_GET) == 0 && count($_POST) == 0) {
            $this->area = "Home";
            $this->HomePage();
        }

        if (isset ($_GET ['list']) && !isset($_GET['SDV_LIST'])) {
            $this->area = "ListPage";
            //echo "GET_LIST: {$_GET ['list']}";
            $this->ListPage();
        }


        if (isset ($_GET ['exams'])) {
            $this->area = "ExamsLists";
            $this->ExamsLists();
        }

        if (isset ($_GET ['getFormData'])) {

            if (isset ($this->config_service ['patients_list_substudy']) && $this->config_service ['patients_list_substudy'] != "") {
                $destination_url = "../index.php";
            } else {
                $destination_url = "index.php";
            }
            $type = "form";
            if (!isset ($_GET ['form'])) {
                $xml = $this->es_form [$_GET ['VISITNUM']] [$_GET ['ESAM']];
            } else {
                $xml = $_GET ['form'];
            }
            $this->formJsonData($xml);
            die();
        }

        if ((isset ($_GET ['form']) || isset ($_GET ['ESAM'])) && !isset($_GET['EQUERY_OBJ']) && !isset($_GET['eQuery'])) {
            $this->area = "EsamPage";
            $this->EsamPage();
        }

        if ((isset ($_GET ['form']) || isset ($_GET ['ESAM'])) && isset($_GET['EQUERY_OBJ'])) {

            $xml = $this->es_form [$_GET ['VISITNUM']] [$_GET ['ESAM']];
            if ($this->pk_service != '' && $this->pk_service != 'next') {
                $this->make_patient_table();
                $body = $this->patient_table;
                $body .= "<div class=\"br_separator\"></div>" . $this->tb_riassuntiva();
            }
            $curr_equery_obj = $this->equery_objs[$_GET['EQUERY_OBJ']];
            $this->body = $body . $curr_equery_obj->form($xml);
            $this->script = $curr_equery_obj->script;
            $this->onload = $curr_equery_obj->onload;
        }

        if (isset ($_GET ['SEARCH']) || isset ($_POST ['SEARCH'])) {
            $this->SearchPage();
        }

        if (isset ($_GET ['eQuery']) || isset ($_POST ['eQuery'])) {
            $this->onload = "";
            $this->body = $this->Equery();
        }
        /*if($this->session_vars['rep_link']=='true'){
			include_once("report_linker.php");
			$module=new linkModule($this->conn,$this->xmr);
			$module->controller($this->session_vars);
			$this->body.=$module->getResult();
		}*/
        if (isset($_GET['inbox'])) {
            include_once "inbox.php";
            if (class_exists("inbox")) {
                $inbox = new inbox($this->conn, $this->lang);
                $this->testi['inbox'] = $inbox->get_titolo();
                if (isset($_GET['ajax']) && $_GET['ajax'] == 'yes') {
                    die($inbox->req($_GET));
                }
                $this->body = $this->breadcrumb('inbox');
                $this->onload = $inbox->get_onload();
                $this->body .= $inbox->get_home();
            }
        }


//		if (isset ( $_GET ['INREV'] ) || $_GET ['INREV']==1 ) {
//		    //insert in EQ con nuovo stato = 5
//			$sql=new query($this->conn);
//			$sql_seq="select {$this->service}_eqseq.nextval as eq_int from dual";
//			$sql->exec($sql_seq);//commentata
//			$sql->get_row();
//			$values['ID_PRAT']=$this->pk_service;
//			$values['EQUERY_INT']=$sql->row['EQ_INT'];
//			$values['USERID_INS']=$this->user->userid;
//			$values['INS_DT']="sysdate";
//			//stato 5 in revisione all'azienda
//			$values['STATO']="5";
//
//			if($this->config_service['eQuerySpec']['txt_eq_inrev'][$this->service]!="")
//			$values['RICH_DM']=$this->config_service['eQuerySpec']['txt_eq_inrev'][$this->service];
//			else if($this->config_service['eQuerySpec']['txt_eq_inrev']!="")
//			$values['RICH_DM']=$this->config_service['eQuerySpec']['txt_eq_inrev'];
//			else
//			$values['RICH_DM']="Richiesta revisione al DE";
//
//			$sql_wfstato="select * from {$this->service}WF_STATO where PK_SERVICE={$this->pk_service}";
//			$sql_wf=new query($this->conn);
//			$sql_wf->get_row($sql_wfstato);
//			$values['WF_STATO']=$sql_wf->row['ID_STATO'];
////			if($sql_wf->row['ID_STATO']!=5) die("STATO SBAGLIATO");
//			$sql_2=new query($this->conn);
//			$sql_2->insert($values,$this->service."_EQ");
//
//			//mail e visitclose gestirli dal controller del servizio
//			$this->conn->commit();
//			die("gestire il controler di study_prototype");
//		}

        //echo $this->body;
        $this->gestEditLabelInLine();

    }

    function gestEditLabelInLine()
    {
        if (isset($_SESSION['editLabelInLine'])) {
            $this->body .= "<script>
				$(document).ready(function() {
					$('.editlabel').click(function(){
						console.log('sono in edit label');
						dataId=$(this).attr('data-id');
						labelId=$(this).attr('label-id');
						bootbox.prompt({
							title: dataId,
							value: $('[label-id-selector=\"'+labelId+'\"]').html(),
							callback: function(result) {                
							  	if (result === null) {                                             
							  		
								} else {
									var param='label='+dataId;
									param+='&value='+result;
									var textValue=result;
							    	$.ajax({
										type: 'GET',
										url: 'index.php?setLabel&'+param,
										contentType: 'application/json; charset=utf-8',
										success: function(data){
											if (data=='ok') {
												console.log('Vittoria!!!!!'+textValue);
												$('[label-id-selector=\"'+labelId+'\"]').html(textValue);
											}else {
												alert('Errore impostazione etichetta');
											}
										},
										failure: function(errMsg) {
											alert('Errore impostazione etichetta');
										}
									});	
						  		}
						  	}
						});
						return false;
					});
					/*
					
					*/
				});
			</script>";
        }
    }

    /**
     * Gestisce la pagina di ricerca
     *
     */
    function SearchPage()
    {
        $dir = $_SERVER['PATH_TRANSLATED'];

        $file_form = $this->xml_dir . "/search_paziente.xml";
        $xml_form = new xml_form();
        $xml_form->xml_form_by_file($file_form);
        $xml_form->open_form();
        $body = $xml_form->body;
        //          print_r($this->session_vars);
        ///16/03/2009 Giorgio Delsignore : Bisogna togliere la globale!!!!
        if (isset($_POST['TSEARCH'])) {
            global $in;
            $in = $this->session_vars;
            $in['list'] = $list = "patients_list_search.xml";
            $list_o = new xml_list($this->xml_dir . "/" . $list);
            $body .= $list_o->list_html();

        }
        $script = "
        <script type=\"text/javascript\">
          
          $(document).ready(function(){
            $('#esamForm').append('<input type=\"hidden\" name=\"TSEARCH\"/>'); 
            $('#esamForm').append('<input type=\"hidden\" name=\"SEARCH\" value=\"1\"/>'); 
          });
          
          function cf(){
          }
          
          function invia_f()
            {
                f=document.forms[0];
                el=f.elements;
                document.forms[0].TSEARCH.value='1';
                document.forms[0].action='index.php';
                document.forms[0].submit();
            }
        </script>
          ";

        $this->percorso = $this->breadcrumb("search");
        $body = $this->percorso . $body;

        $this->body = $body;
        $this->script = $script;
    }

    /**
     * Gestisce la pagina di sfoglia
     *
     */
    function SfogliaPage()
    {
        $filetxt = null;
        $remote_userid = null;
        $nome_user = null;
        $body = null;
        $this->session_vars['source'] = str_replace('|', ',', $this->session_vars['source']);
        $this->session_vars['dest'] = str_replace('|', ',', $this->session_vars['dest']);

        $dir = $_SERVER['PATH_TRANSLATED'];

        $dir = preg_replace("/\/index.php/", "", $dir);
        //$filetxt = file_get_contents($dir.'/template.htm');
        if ($this->session_vars['FORM'] != '') {
            $file_form = $this->xml_dir . "/sfoglia_form_{$this -> session_vars['FORM']}.xml";

            $xml_form = new xml_form($this->conn, $this->service, $this->config_service, $this->session_vars, $this->xml_dir);

            $xml_form->xml_form_by_file($file_form);
            $xml_form->open_form();
            $body .= $xml_form->body;
        }

        global $in;
        $in = $this->session_vars;
        if (isset($this->session_vars['TSEARCH'])) {
            $in['list'] = $list = "sfoglia_list_{$this -> session_vars['SFOGLIA']}.xml";
            $list_o = new xml_list($this->xml_dir . "/" . $list);

            $body .= $list_o->list_html();
        }
        $filetxt = preg_replace("/<!--body-->/", $body, $filetxt);
        $script = "<script type=\"text/javascript\">
          function invia_f()
          {
          
         
           
           f=document.forms[0];
           el=f.elements;
          
           document.forms[0].TSEARCH.value='1';
           document.forms[0].action='index.php';
           document.forms[0].submit();
           }
           function cf(){}
         </script>
          ";
        $script .= $xml_form->script_js;
        $codice_sis = $remote_userid - 0;
        $user_name = "<p align=right>
    <div class=\"br_separator\"></div>";
        //echo "<hr>$nome_user";
        $nome_user = str_replace("\\'", "'", $nome_user);

        $this->body = $body;
        $this->script = $script;
    }

    /**
     * Gestione della pagina della scheda
     *
     * @param boolean $no_link_back
     */
    function EsamPage($no_link_back = false)
    {
        $this->patient_table = "";

        if (isset ($this->config_service ['patients_list_substudy']) && $this->config_service ['patients_list_substudy'] != "") {
            $destination_url = "../index.php";
        } else {
            $destination_url = "index.php";
        }

        /*if (preg_match ( "!,!", $this->centers) && (!isset($this->config_service['NO_LISTA_CENTRI'])))
		 {	$percorso = "
		 <a href=\"{$destination_url}\">Home Page</a>&gt;&gt;
		 <a href=\"{$destination_url}?list=patients_list.xml\">Lista centri</a>&gt;&gt;
		 <a href=\"{$destination_url}?list=patients_list.xml&CENTER={$_GET['CENTER']}\">{$this->config_service['Patients_list']}</a>&gt;&gt;


		 ";
		 }
		 else {

		 $percorso = "
		 <a href=\"{$destination_url}\">Home Page</a>&gt;&gt;
		 <a href=\"{$destination_url}?list=patients_list.xml\">{$this->config_service['Patients_list']}</a>&gt;&gt;

		 ";
		 }
		 if (isset($this->pk_service)) $percorso.="<a href=\"{$destination_url}?&exams=visite_exam.xml&{$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}\">{$this->config_service['Lista_schede']}</a>&gt;&gt;";
		 $percorso.="<b>{$this->vlist->esams[$_GET['VISITNUM']][$_GET['ESAM']]['TESTO']}</b>";
		 */
        $type = "form";
        $percorso = $this->breadcrumb("form", $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['TESTO']);
        if (!isset ($_GET ['form'])) {
            $xml = $this->es_form [$_GET ['VISITNUM']] [$_GET ['ESAM']];
        } else {
            $xml = $_GET ['form'];
        }
        //echo("chiamoform!");
        $this->form($xml, true, $no_link_back);

        //		die($this->vlist->make_patient_table());


        $this->body = $percorso . $this->body;


        /**
         * merge cro inserisco link view all records/reopen main per gestione main/sub
         * 07.02.2014 merge cro vmazzeo
         */
        if (isset($_GET ['PROGR']) && isset($_GET ['ESAM']) && isset($_GET ['VISITNUM']) && isset($_GET ['VISITNUM_PROGR'])) {
            $in = $this->session_vars;
            $this->pk_service = $_GET [$this->config_service ['PK_SERVICE']];
            $esam = $_GET ['ESAM'];
            $visitnum = $_GET ['VISITNUM'];
            $visitnum_progr = $_GET ['VISITNUM_PROGR'];
            $progr = $_GET ['PROGR'];
// 			if(strtolower($this->config_service['lang'])=='en'){
// 				$link_txt="Back to records list";
// 			}
// 			else{
// 				$link_txt="Torna alla lista dei record";
// 			}

            $link_txt = mlOut("System.MainSub.back_record_list", "Back to records list");
            if ($this->vlist->esams[$visitnum][$esam]['SUB'] == "yes") {
                $link = "index.php?CENTER=" . $in['CENTER'] . "&{$this->config_service['PK_SERVICE']}=" . $in[$this->config_service['PK_SERVICE']] . "&VISITNUM=" . $in['VISITNUM'] . "&ESAM=" . $esam . "&form=" . $this->vlist->esams[$visitnum][$esam]['XML'] . "";
                $this->body .= '
						<p align=left><a href="' . $link . '" >&lt;&lt;' . $link_txt . '</a></p>';
            } elseif ($this->vlist->esams[$visitnum][$esam]['MAIN'] == "yes") {
                $str = $this->MainSentLink($in);
                //var_dump($str);

                $this->body .= $this->MainSentLink($in);
            }
        }
    }

    /**
     * Costruisce un XML con i dati dell'oggetto di studio differenziando i file per visitnum_progr
     *
     * @param String $xsl
     * @param String $file_output
     * @param String $visitnum - il visitnum che ha visitnum_progr diversi
     *
     */
    /*	function xmlData_multi($xsl, $file_output = false, $visitnum = null) {

		$sql_alter = "alter session set nls_date_format = 'DD/MM/YYYY'";
		$sql = new query ( $this->conn );
		$sql->set_sql ( $sql_alter );
		$sql->ins_upd ();//commentata


		$sql_query="select distinct visitnum_progr from {$this->service}_coordinate where id_prat={$this->pk_service} and visitnum=$visitnum order by visitnum_progr";
		$sql_=new query($this->conn);
		$sql_->exec($sql_query);//commentata
		while ($sql_->get_row()){


		$sql_query = "
			select * from {$this->service}_coordinate
			where {$this->config_service['PK_SERVICE']}={$this->pk_service}
			and abilitato=1 and eq_action is null and visitnum <>$visitnum
			union
			select * from {$this->service}_coordinate
			where {$this->config_service['PK_SERVICE']}={$this->pk_service}
			and abilitato=1 and eq_action is null and visitnum =$visitnum and visitnum_progr={$sql_->row['VISITNUM_PROGR']}
			";
		if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
			$sql_query="select * from {$this->service}_coordinate
			where {$this->config_service['PK_SERVICE']}={$this->pk_service}
			and abilitato=1 and (eq_action is null or (eq_action=1 and inv_query={$this->integrazione->eq_int}))
			and visitnum <>$visitnum
			union
			select * from {$this->service}_coordinate
			where {$this->config_service['PK_SERVICE']}={$this->pk_service}
			and abilitato=1 and eq_action is null and visitnum=$visitnum and visitnum_progr={$sql_->row['VISITNUM_PROGR']}
			";
		}


		//		print_r($this->vlist->esams);
		$sql = new query ( $this->conn );
		$sql->exec ( $sql_query );//commentata
//		$scheda=array();
		while ( $sql->get_row () ) {
			$scheda [$sql->row ['VISITNUM']] [$sql->row ['VISITNUM_PROGR']] [$sql->row ['ESAM']] [$sql->row ['PROGR']] = true;
		}
//		echo "<pre>";
//		print_r($scheda); echo "<hr>";
		if (! $file_output)
		header ( "content-type: text/xml" );

		$output = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
		<?xml-stylesheet type=\"text/xsl\" href=\"$xsl\" ?>
	<Object>
		<PK_SERVICE id=\"{$this->pk_service}\"/>";
		foreach ( $this->vlist->visitnums as $vis => $vis_val ) {
			if (isset ( $scheda [$vis] )) {

				$visit_tag = strtoupper ( $vis_val ['SHORT_TXT'] );
				$visit_tag = str_replace ( " ", "_", $visit_tag );
				$output .= "
		<VISITNUM_{$vis} id=\"{$vis}\">";
				for($i = 0; $i < count ( $scheda [$vis] ); $i ++) {
					if ($vis_val ['PROGR'] == 'yes')
					$output .= "
			<VISITNUM_PROGR id=\"$i\">";
					foreach ( $this->vlist->esams [$vis] as $esam => $esam_val ) {
						if (isset ( $scheda [$vis] [$i] [$esam] )) {
							$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $session_vars, $this->uploaded_file_dir );
							if (file_exists ( $this->xml_dir . '/' . $esam_val ['XML'] ))
							$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $esam_val ['XML'] );
							$table = $xml_form->form ['TABLE'];
							if ($table != '') {
								$output .= "
					<ESAM_{$esam} id=\"$esam\" table=\"$table\">";
								for($p = 1; $p <= count ( $scheda [$vis] [$i] [$esam] ); $p ++) {
									if ($esam_val ['PROGR'] == 'yes')
									$output .= "
						<PROGR id=\"$p\">";

									$sql_query = "select * from $table
									where {$this->config_service['PK_SERVICE']}={$this->pk_service}
									and visitnum=$vis
									and visitnum_progr=$i
									and esam=$esam
									and progr=$p
									";
									$sql = new query ( $this->conn );
									$sql->get_row ( $sql_query );
									foreach ( $sql->row as $key => $val ) {
										if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='') {
											$sql_query_eq_field = "select VALORE from {$this->service}_EQFIELD
											where {$this->config_service['PK_SERVICE']}={$this->pk_service}
											and visitnum=$vis
											and visitnum_progr=$i
											and esam=$esam
											and progr=$p
											and field = '$key'
											and eq_int =  {$this->integrazione->eq_int}
											";
											$sql_field = new query ( $this->conn );
											if($sql_field->get_row ( $sql_query_eq_field  )) {
												if($sql->type[$key]=="DATE")
												$val=substr($sql_field->row['VALORE'],0,2)."/".substr($sql_field->row['VALORE'],2,2)."/".substr($sql_field->row['VALORE'],4);
												else
												$val=$sql_field->row['VALORE'];
											}
										}
										if ($val != '')
										$output .= "
											<$key><![CDATA[$val]]></$key>";
									}
									if ($esam_val ['PROGR'] == 'yes')
									$output .= "
						</PROGR>";
								}
								$output .= "
					</ESAM_{$esam}>";
							}
						}

					}
					if ($vis_val ['PROGR'] == 'yes')
					$output .= "
				</VISITNUM_PROGR>";
				}
				$output .= "
			</VISITNUM_{$vis}>";

			}
		}
		$output .= "
	</Object>";



			if ($file_output) {
				$file_dest = "tmp/{$this->config_service['PK_SERVICE']}_{$_GET[$this->config_service['PK_SERVICE']]}_VPROGR_{$sql->row ['VISITNUM_PROGR']}.xml";

				//die($file_dest);
				$fp = fopen ( $file_dest, 'w' );
				fwrite ( $fp, $output );
				fclose ( $fp );
			} else {
				die ( "Passare il nome del file di output per il multi-VPROGR" );
			}

		}

	}*/

    /**
     * Costruisce un XML con i dati dell'oggetto di studio
     *
     * @param String $xsl
     * @param String $file_output
     */
    function xmlData($xsl, $file_output = false)
    {

        $sql_alter = "alter session set nls_date_format = 'DD/MM/YYYY'";
        $sql = new query ($this->conn);
        $sql->set_sql($sql_alter);
        $sql->ins_upd();//non richiede binding

        $sql_query = "
			select * from {$this->service}_coordinate
			where {$this->config_service['PK_SERVICE']}=:pk_service
			and abilitato=1 and eq_action is null
			";
        if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '') {
            $sql_query = "select * from {$this->service}_coordinate
			where {$this->config_service['PK_SERVICE']}=:pk_service
			and abilitato=1 and (eq_action is null or (eq_action=1 and inv_query=:eq_id))";
        }

        //		print_r($this->vlist->esams);
        $sql = new query ($this->conn);
        unset($bind);
        $bind['EQ_ID'] = $this->integrazione->eq_int;
        $bind['PK_SERVICE'] = $this->pk_service;
        $sql->exec($sql_query, $bind);//binded
        while ($sql->get_row()) {
            $scheda [$sql->row ['VISITNUM']] [$sql->row ['VISITNUM_PROGR']] [$sql->row ['ESAM']] [$sql->row ['PROGR']] = true;
        }
        if (!$file_output)
            header("content-type: text/xml");

        $output = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
		<?xml-stylesheet type=\"text/xsl\" href=\"$xsl\" ?>
	<Object>
		<PK_SERVICE id=\"{$this->pk_service}\"/>";
        foreach ($this->vlist->visitnums as $vis => $vis_val) {
            if (isset ($scheda [$vis])) {

                $visit_tag = strtoupper($vis_val ['SHORT_TXT']);
                $visit_tag = str_replace(" ", "_", $visit_tag);
                $output .= "
		<VISITNUM_{$vis} id=\"{$vis}\">";
                for ($i = 0; $i < count($scheda [$vis]); $i++) {
                    if ($vis_val ['PROGR'] == 'yes')
                        $output .= "
			<VISITNUM_PROGR id=\"$i\">";
                    foreach ($this->vlist->esams [$vis] as $esam => $esam_val) {
                        if (isset ($scheda [$vis] [$i] [$esam])) {

                            $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                            if (file_exists($this->xml_dir . '/' . $esam_val ['XML']))
                                $xml_form->xml_form_by_file($this->xml_dir . '/' . $esam_val ['XML']);
                            $table = $xml_form->form ['TABLE'];
                            if ($table != '') {
                                $output .= "
					<ESAM_{$esam} id=\"$esam\" table=\"$table\">";
                                for ($p = 1; $p <= count($scheda [$vis] [$i] [$esam]); $p++) {
                                    if ($esam_val ['PROGR'] == 'yes')
                                        $output .= "
						<PROGR id=\"$p\">";

                                    $sql_query = "select * from $table
									where {$this->config_service['PK_SERVICE']}={$this->pk_service}
									and visitnum=$vis
									and visitnum_progr=$i
									and esam=$esam
									and progr=$p
									";
                                    $sql = new query ($this->conn);
                                    $sql->get_row($sql_query);
                                    foreach ($sql->row as $key => $val) {
                                        if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '') {
                                            $sql_query_eq_field = "select VALORE from {$this->service}_EQFIELD
											where {$this->config_service['PK_SERVICE']}={$this->pk_service}
											and visitnum=$vis
											and visitnum_progr=$i
											and esam=$esam
											and progr=$p
											and field = '$key'
											and eq_int =  {$this->integrazione->eq_int}
											";
                                            $sql_field = new query ($this->conn);
                                            if ($sql_field->get_row($sql_query_eq_field)) {
                                                if ($sql->type[$key] == "DATE")
                                                    $val = substr($sql_field->row['VALORE'], 0, 2) . "/" . substr($sql_field->row['VALORE'], 2, 2) . "/" . substr($sql_field->row['VALORE'], 4);
                                                else
                                                    $val = $sql_field->row['VALORE'];
                                            }
                                        }
                                        if ($val != '')
                                            $output .= "
											<$key><![CDATA[$val]]></$key>";
                                    }
                                    if ($esam_val ['PROGR'] == 'yes')
                                        $output .= "
						</PROGR>";
                                }
                                $output .= "
					</ESAM_{$esam}>";
                            }
                        }

                    }
                    if ($vis_val ['PROGR'] == 'yes')
                        $output .= "
				</VISITNUM_PROGR>";
                }
                $output .= "
			</VISITNUM_{$vis}>";

            }
        }
        $output .= "
	</Object>";
        if ($file_output) {
            $file_dest = "tmp/{$this->config_service['PK_SERVICE']}_{$_GET[$this->config_service['PK_SERVICE']]}.xml";
            //die($file_dest);
            $fp = fopen($file_dest, 'w');
            fwrite($fp, $output);
            fclose($fp);
        } else
            die ($output);

    }

    /**
     * Controlla la chiusura della scheda
     *
     * @param number $visitnum
     * @param number $esam
     * @param number $visitnum_progr
     * @param String $testo_waiting
     * @return String
     */
    function CheckClosure($visitnum = null, $esam = null, $visitnum_progr = null, $testo_waiting = null)
    {
        $ins = '';
        $where = '';
        unset($bind);
        if (isset ($visitnum))
            if (is_array($visitnum)) {
                foreach ($visitnum as $key => $val) {
                    $ins .= "$val,";
                }
                $ins = rtrim($ins, ",");
                $where .= "and visitnum in ($ins)";
            } else {
                $where .= "and visitnum=:visitnum";
                $bind['VISITNUM'] = $visitnum;
            }
        if (isset ($esam)) {
            $where .= "and esam=:esam";
            $bind['ESAM'] = $esam;
        }
        if (isset ($visitnum_progr)) {
            $where .= "and visitnum_progr=$visitnum_progr";
            $bind['VISITNUM_PROGR'] = $visitnum_progr;
        }
        $where_agg = '';
        if ($this->integrazione->eq_enabled && $this->integrazione->eq_int) $where_agg = " and nvl(eq_action,1)!=2";
        $sql_query = "
			select esam, progr,visitnum, visitnum_progr, inizio, {$this->config_service['PK_SERVICE']} from {$this->service}_coordinate
			where {$this->config_service['PK_SERVICE']}=:pk_service
			and nvl(fine,0)<>1 $where_agg
			$where
		";

        $bind['PK_SERVICE'] = $this->pk_service;
        $sql = new query ($this->conn);
        $sql->exec($sql_query, $bind);//binded
        $message = "";
        $completed = true;
        while ($sql->get_row()) {
            if (!isset($this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])) continue;
            if ($sql->row ['INIZIO'] == '') {

                if ($this->vlist->esams [$sql->row ['VISITNUM']] [$sql->row ['ESAM']] ['OPTIONAL'] == '') {
                    $returns [] ['TEXT'] = $this->testo('The form') . " {$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO']} " . $this->testo('is incomplete');
                    if ($this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['SFOGLIA_CALL'] == "yes")
                        $returns [count($returns) - 1] ['href'] = "index.php?VISITNUM={$sql->row['VISITNUM']}&ESAM={$sql->row['ESAM']}&VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}&{$this->config_service['PK_SERVICE']}={$sql->row[$this->config_service['PK_SERVICE']]}";
                    else
                        $returns [count($returns) - 1] ['href'] = "index.php?VISITNUM={$sql->row['VISITNUM']}&ESAM={$sql->row['ESAM']}&PROGR={$sql->row['PROGR']}&VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}&{$this->config_service['PK_SERVICE']}={$sql->row[$this->config_service['PK_SERVICE']]}";
                    $completed = false;
                }
            } else {
                if (!($this->closeable_esam($sql->row ['VISITNUM'], $sql->row ['ESAM'], $sql->row ['VISITNUM_PROGR'], $sql->row ['PROGR']))) {
                    $returns [] ['TEXT'] = $this->testo('The form') . " {$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO']} " . $this->testo('is incomplete');
                    $returns [count($returns) - 1] ['href'] = "index.php?VISITNUM={$sql->row['VISITNUM']}&ESAM={$sql->row['ESAM']}&PROGR={$sql->row['PROGR']}&VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}&{$this->config_service['PK_SERVICE']}={$sql->row[$this->config_service['PK_SERVICE']]}";
                    $completed = false;
                }
            }
        }
        $ret ['Check'] = $completed;
        $ret ['AggInfo'] = $returns;
        return $ret;
    }

    /**
     * Chiude tutte le schede
     *
     * @param number $visitnum
     * @param number $esam
     * @param number $visitnum_progr
     * @param String $redir_url
     * @param String $testo_waiting
     * @return String
     */
    function close_all($visitnum = null, $esam = null, $visitnum_progr = null, $redir_url = null, $testo_waiting = null)
    {
        $str_incompleted = null;
        $where = null;
        unset($bind);
        if (isset ($visitnum)) {
            $where .= "and visitnum=:visitnum";
            $bind['VISITNUM'] = $visitnum;
        }
        if (isset ($esam)) {
            $where .= "and esam=$esam";
            $bind['ESAM'] = $esam;
        }
        if (isset ($visitnum_progr))
            $where .= "and visitnum_progr=$visitnum_progr";
        $sql_query = "
			select esam, progr,visitnum, visitnum_progr, inizio from {$this->service}_coordinate
			where {$this->config_service['PK_SERVICE']}=:pk_service
			and nvl(fine,0)<>1
			$where
		";
        $sql = new query ($this->conn);

        $bind['PK_SERVICE'] = $this->pk_service;
        $sql->exec($sql_query, $bind); //binded
        $message = "";
        $completed = true;
        while ($sql->get_row()) {
            if ($sql->row ['INIZIO'] == '') {
                if ($this->vlist->esams [$sql->row ['VISITNUM']] [$sql->row ['ESAM']] ['OPTIONAL'] == '') {
                    $str_incompleted .= "<li>La scheda {$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO']} &egrave; incompleta</li>";
                    $completed = false;
                }
            } /* XXX non togliere - lorenzo 7/7/2010
				 else if ($this->vlist->esams[$sql->row['VISITNUM']][$sql->row ['ESAM']]['CONDITIONAL'] != ''){
				 error_log("----------- conditional");
				 $cond_var = $this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['CONDITION_VAR'];
				 $cond_val = $this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['CONDITION_VALUE'];
				 $cond_tb = $this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['CONDITION_TABLE'];

				 // TODO riguardare
				 $query = "SELECT {$cond_var} FROM {$cond_tb} where {$this->config_service['PK_SERVICE']} = {$in['{$this->config_service['PK_SERVICE']}']} AND VISITNUM_PROGR = {$in['VISITNUM_PROGR']}";
				 $sql = new query($this->conn);
				 $sql->exec($query);
				 $sql->get_row();

				 if ($sql->row[$cond_var] == $cond_val) {
					// condition true
					} else { // condition false
					$completed = false;
					// TODO cambiare messaggio
					$str_incompleted .= "<li>La scheda {$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO']} &egrave; incompleta</li>";
					}
					}
					*/
            else {
                if (!($this->closeable_esam($sql->row ['VISITNUM'], $sql->row ['ESAM'], $sql->row ['VISITNUM_PROGR'], $sql->row ['PROGR']))) {
                    $str_incompleted .= "<li>La scheda {$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO']} &egrave; incompleta</li>";
                    $completed = false;
                }
            }
        }
        if ($completed) {
            $sql_update = "
				update {$this->service}_coordinate set FINE=1, MODDT=sysdate
				where {$this->config_service['PK_SERVICE']}=:pk_service
				and fine<>1
				$where
			";
            $this->session_vars ['VISITNUM'] = $visitnum;
            $sql = new query ($this->conn);
            $sql->ins_upd($sql_update, $bind);//binded
            $sql_update = "
				update {$this->service}_coordinate set VISITCLOSE=1
				where {$this->config_service['PK_SERVICE']}=:pk_service
				$where
			";
            $sql->ins_upd($sql_update, $bind);//binded
            if (isset ($_GET ['NOTE_CHIUSURA_SPEC'])) {
                $tb = $this->vlist->visitnums [$visitnum] ['CLOSE_VISIT_NOTE_ATTR'] ['TB'];
                $note = $this->vlist->visitnums [$visitnum] ['CLOSE_VISIT_NOTE_ATTR'] ['FIELD'];
                $tb = "{$this->service}_$tb";
                $values = '';
                $values [$note] = $_GET ['NOTE_CHIUSURA_SPEC'];
                $pk [$this->config_service ['PK_SERVICE']] = $this->pk_service;
                $sql->update($values, $tb, $pk);
            }
            $this->conn->commit();
            if ($testo_waiting == null)
                $testo_waiting = "Save data...<br>Waiting";
            if (isset ($redir_url)) {
                ob_clean();
                header('location:' . $redir_url);
                $this->conn->commit();
                die();
                die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=$redir_url\"></head><body>$testo_waiting</body></html>");
            } else {
                ob_clean();
                header('location:' . "index.php?&exams=visite_exam.xml&{$this->config_service['PK_SERVICE']}={$this->pk_service}&CENTER={$this->session_vars['CENTER']}");
                $this->conn->commit();
                die();
                die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=index.php?&exams=visite_exam.xml&{$this->config_service['PK_SERVICE']}={$this->pk_service}&CENTER={$this->session_vars['CENTER']}\"></head><body>$testo_waiting</body></html>");
            }
        }
        if ($this->config_service ['testo_chiusura_non_possibile'] != '')
            $testo_incompleted = $this->config_service ['testo_chiusura_non_possibile'];
        else
            $testo_incompleted = "Attenzione non &ograve; possibile chiudere la/e schede in quanto";
        $str_incompleted = "
			<p class=titolo>$testo_incompleted:</p>
				<div style=\"color:red;font-weight:bold\">" . $str_incompleted . "</div><br>
			<a href=\"index.php?&exams=visite_exam.xml&{$this->config_service['PK_SERVICE']}={$this->pk_service}&CENTER={$this->session_vars['CENTER']}\">&lt;&lt; indietro</a>
				";
        return $str_incompleted;
    }

    /**
     * Controlla se una schede rispetta i requisiti per essere chiusa
     *
     * @param number $visitnum
     * @param number $esam
     * @param number $visitnum_progr
     * @param number $progr
     * @return String
     */
    function closeable_esam($visitnum, $esam, $visitnum_progr, $progr)
    {
        $sql_query = "
			select fine from {$this->service}_coordinate
				where {$this->config_service['PK_SERVICE']}={$this->pk_service}
				and visitnum=$visitnum
				and visitnum_progr=$visitnum_progr
				and esam=$esam
				and progr=$progr
				";
        $sql = new query ($this->conn);
        $sql->get_row($sql_query);
        if ($sql->row ['FINE'] == 1)
            return true;
        $xml_file = $this->vlist->esams [$visitnum] [$esam] ['XML'];
        $session_vars = $this->session_vars;
        $session_vars ['VISITNUM'] = $visitnum;
        $session_vars ['VISITNUM_PROGR'] = $visitnum_progr;
        $session_vars ['PROGR'] = $progr;
        $session_vars ['ESAM'] = $esam;
        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $xml_file);
        $xml_form->closed_form();
        foreach ($xml_form->tb_vals as $key => $val) {
            $session_vars [$key] = $val;
        }
        $session_vars ['INVIOCO'] = 1;
        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $xml_file);
        if ($xml_form->valida()) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Modalit di visualizzazione ALL_IN delle schede progressive
     *
     * @param String $xml_form
     * @return String
     */

    function all_in_form_view($xml_form)
    {
        $onload = null;
        $xml = null;
        $testo_rev = null;
        $select_field = null;
        $type_fields_agg = null;
        $field_agg_txt = null;
        $equery = null;
        $note_eq = null;
        $confs = null;
        $c1_agg = null;
        $alert_delete_eqpending = null;

        $remote_userid = $_SERVER['REMOTE_USERID'];
        //$exclude_visit si riferisce anche ad exclude_esam si consiglia di rinominare la variabile appena possibile
        //al momento non si considera per l'exclude esam la visitnum verificare che impatto ci sarebbe a modificare e correggere

        if ($this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$this->config_service['service']][$_GET['VISITNUM']] != "")
            $exclude_visit = $this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$this->config_service['service']][$_GET['VISITNUM']];
        else
            $exclude_visit = $this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$_GET['VISITNUM']];
        if (!$exclude_visit) {
            if ($this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_ESAM'][$this->config_service['service']][$_GET['ESAM']] != "")
                $exclude_visit = $this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$this->config_service['service']][$_GET['VISITNUM']];
            else
                $exclude_visit = $this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_ESAM'][$_GET['ESAM']];
        }

        $this->session_vars ['form'] = $xml;
        $vlist = $this->vlist;
        $in = $this->session_vars;
        $conn = $this->conn;
        $service = $this->service;
        if (!isset($_GET['CRF'])) {
            $this->make_patient_table();
            $body = $this->patient_table;
        }
        $sql_query = "select max(progr) as max_p from {$service}_coordinate where {$this->config_service['PK_SERVICE']}=:pk_service and esam=:esam and visitnum=:visitnum and VISITNUM_PROGR=:visitnum_progr and inizio is not null";
//		echo $sql_query;
        unset($bind);
        $bind['PK_SERVICE'] = $in[$this->config_service['PK_SERVICE']];
        $bind['ESAM'] = $in['ESAM'];
        $bind['VISITNUM'] = $in['VISITNUM'];
        $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
        $sql = new query ($conn);
        $sql->exec($sql_query, $bind); //binded
        $sql->get_row();
//
//
        $sql->row['MAX_P'] -= 0;
        if ($this->session_vars['USER_TIP'] == 'DE' && $sql->row['MAX_P'] < 1 && $this->vlist->esams[$_GET['VISITNUM']][$_GET ['ESAM']]['QUICKACCESS'] == 'yes' && !isset($_GET['NoQuickAccess'])) {
            $linkff = "{$_SERVER['REQUEST_URI']}&PROGR=1";

            header("Location: $linkff");
            die();
        }
        $m_p = $sql->row ['MAX_P'];
        $max = $m_p - 0;
        if ($m_p == '' || $m_p == 0)
            $m_p++;
        $real_progr = $_GET ['PROGR'];
        $next = $m_p + 1;
//
        if (isset ($_GET ['PROGR'])) {
            $in['PROGR'] = $_GET ['PROGR'];
            /*Controllo di visibilita*/
            if (isset ($this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE']) && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE'] != '') {
                if ($_GET ['VISITNUM_PROGR'] == '')
                    $_GET ['VISITNUM_PROGR'] = 0;
                $sql_query = "
								select
									fine,
									userid
								from {$service}_coordinate
								where visitnum=:visitnum
								and visitnum_progr=:visitnum_progr
								and esam=:esam
								and progr=:progr
								and {$this->config_service['PK_SERVICE']}=:pk_service
								";

                unset($bind);
                $bind['PK_SERVICE'] = $in[$this->config_service['PK_SERVICE']];
                $bind['ESAM'] = $in['ESAM'];
                $bind['PROGR'] = $in['PROGR'];
                $bind['VISITNUM'] = $in['VISITNUM'];
                $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
                $sql_abil = new query ($conn);
                $sql_abil->exec($sql_query, $bind); //binded
                $sql_abil->get_row();
                if ($sql_abil->row ['FINE'] != 1 && ($sql_abil->row ['USERID'] != $this->user->userid && $in ['USER_TIP'] != 'DE')) {
                    error_page($this->user->userid, $this->testo("userNotCenter"), "");
                }
            }
            $xml_form->make_html();
            $script = "
				<script type=\"text/javascript\">
				" . $xml_form->salva_js . "
				" . $xml_form->invia_js . "
				" . $xml_form->check_js . "
				" . $xml_form->inrevisione_js . "
				</script>
				";
            $onload .= $xml_form->onload . ";";
            if ($this->pk_service != '' && $this->pk_service != 'next' && !isset($_GET['CRF'])) {
                $this->make_patient_table();
                $body = $this->patient_table;
                $body .= "<div class=\"br_separator\"></div>" . $this->tb_riassuntiva();
            } else
                $body = '';
            $body .= $xml_form->body;
        } else {
            $colspan = 4;
            if (isset ($xml_form->form ['FIELD_AGG'])) {
                /*Modalità  con modifica diretta dei valori in schema riassuntivo*/
                $tr_agg = "<tr>";
                $fields_agg = explode("|", $xml_form->form ['FIELD_AGG']);
                $fields_agg_txt = explode("|", $xml_form->form ['FIELD_AGG_TXT']);
                if (isset ($_GET ['ADDBLANK'])) {/*Aggiunta di scheda vuota*/

                    $this->AllInAddBlank($sql, $xml_form);

                }

                if (isset ($_POST ['ApplMod'])) {/*Applico le modifiche*/
                    $this->AllInApplMod($fields_agg, $fields_agg_txt, $xml_form);

                }
                /*Aggiunta di scehda vuota*/
                if ($sql->row['MAX_P'] != "") {
                    if ($sql->row['MAX_P'] >= $_GET ['ADDBLANK'] || $sql->row['MAX_P'] + 1 < $_GET ['ADDBLANK']) {
                        error_page($remote_userid, "La scheda numero {$_GET ['ADDBLANK']}  gi stata inserita. Non utilizzare il tasto back del browser o ritornare alla lista schede aggiornata.", "La scheda numero {$_GET ['ADDBLANK']}  gi stata inserita. Non utilizzare il tasto back del browser o ritornare alla lista schede aggiornata.");
                    }
                }


                /*Header della tabella*/
                foreach ($fields_agg_txt as $key => $val) {
                    $field_agg_txt .= "<th>$val</th>";
                }
                foreach ($fields_agg as $fk => $field) {
                    $colspan++;
                    foreach ($xml_form->fields as $key => $val) {
                        if ($val ['VAR'] == $field) {
                            $nextrow = count($type_fields_agg);
                            foreach ($val as $k => $v) {
                                $type_fields_agg [$nextrow] [$k] = $v;
                            }
                            $field_tot = '';
                            $field_type = "field_" . $val['TYPE'];

                            if ($val['TYPE'] != 'file_doc')
                                $select_field .= "$field,";
                            if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                                include_once $this->config_service['field_lib'] . $field_type . ".inc";
                            } else {
                                include_once "{$field_type}.inc";
                            }
                            //include_once $_SERVER['DOCUMENT_ROOT']."/../libs/xCRF/$field_type.inc";
                            $tr_agg .= call_user_func(array($field_type, "S_all_in"), $field, $m_p, $xml_form);
                        }
                    }
                }

                $rowspan = " rowspan='2'";
                $tr_agg .= "</tr>";
            }
            $sql = new query ($this->conn);
            if ($_GET ['VISITNUM_PROGR'] == '') {
                $visitnum_progr = 0;
            } else {
                $visitnum_progr = $_GET ['VISITNUM_PROGR'];
            }
            $where_agg_eq = '';
            if ($this->config_service['eQuerySpec']['Integrazione']['ON'] && (!$this->integrazione->eq_enabled || $this->integrazione->eq_int == '')) {
                $where_agg_eq = "and (INV_QUERY is null or EQ_ACTION=2)";
            }
            $sql_query = "select min(fine) as fine from {$this->service}_coordinate where
			VISITNUM={$_GET['VISITNUM']}
			and esam={$_GET['ESAM']}
			and {$this->config_service['PK_SERVICE']}={$this->pk_service}
			and visitnum_progr=$visitnum_progr
			$where_agg_eq
			";
            $sql->get_row($sql_query);
            if (($sql->row ['FINE'] == 1 || $this->session_vars ['USER_TIP'] != 'DE') && !($this->integrazione->eq_enabled && $this->integrazione->role == $this->user->profilo && !$exclude_visit)) {
                $closed_all = true;
                $rowspan = "";
                $tr_agg = "";
                $colspan--;
                $elimina_col = "";
            } else {
                $closed_all = false;
                if ($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TRASH'] != '' && ($this->session_vars ['USER_TIP'] == 'DE' || $this->integrazione->eq_enabled))
                    $elimina_col = "<td class='int' width='40' align='center' $rowspan>" . mlOut("System.all_in_view.delete_col", "Delete") . "</td>";
            }
            $body .= $this->tb_riassuntiva();
            /*Gestione main
			 * Solo se specificato mainsub="yes" nel visite_exams.xml , gli esami progressivi normali non ne hanno bisogno.
			*/
            $main = "";
            if ($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['MAINSUB'] == 'yes') {
                $main_txt = "";
            }
            $main .= '<table border=0 width=100%><tr><td align="center">
					<table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr><b>' . $main_txt . '</b>
							<!-- CAMPI -->' . $testo_rev;
            //		$colonne = $xml_form ['COLS'];
            $colonne = 4;
            $width = 100 / ($colonne * 2);
            for ($i = 0; $i < $colonne; $i++) {
                $main .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
            }
            $main .= "</tr>";
            $main .= "<tr><td colspan=\"" . ($colonne * 2) . "\" align=\"center\">$note_eq</td>";
            $main .= "</tr>";

            $c = 0;
            foreach ($xml_form->fields as $i => $val) {
                if ($val['MAIN'] == 'yes') {
                    if (isset ($val ['TYPE']) && $val ['TYPE'] != '') {
                        $field_type = "field_{$val['TYPE']}";
                    } else {
                        $field_type = "field";
                    }
                    // 					if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
                    // 						include_once $this->config_service['field_lib'] . $field_type . ".inc";
                    // 					} else
                    // 					include_once "{$field_type}.inc";
                    /**
                     *  Modifica 08/09/2011
                     * Carico prima i campi modificati per servizio se esistono
                     * M. Verrocchio
                     **/
                    if (!class_exists($field_type)) {
                        if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                            include_once $this->config_service['field_lib'] . $field_type . ".inc";
                        } elseif (file_exists($_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc")) {
                            include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc";
                        } else {
                            include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/fields/{$field_type}.inc";
                        }
                    }
                    $field_obj = new $field_type ($xml_form, $i, $this->conn, $xml_form->tb_vals, $this->session_vars, $this->service, $this->errors);
                    //					$field_obj->make_open_html ($equery);
                    //				if ($field_obj->attributes ['TYPE'] != 'hidden' && ($field_obj->attributes ['HIDE'] != 'yes' || $field_obj->condition_passed || $field_obj->attributes ['SHOW_VIS'] == 'yes')) {
                    $field_obj->make_open_html($equery);
                    if ($colonne <= $c) {
                        $main .= "</tr><tr>";
                        $c = 0;
                    }
                    if ($field_obj->attributes ['COLS'] == '')
                        $c++;
                    else {
                        $c += $field_obj->attributes ['COLS'];
                    }
                    $main .= $field_obj->html;
                    //				}
                }
            }
            $main .= "</table>
						<!--FINE CAMPI-->
						";


            $body .= "$main
				<p align=center><b>{$vlist->esams[$in['VISITNUM']][$in['ESAM']]['TESTO']}</b></p>
				<form method=\"POST\" name=\"ALL_IN_FORMS\" action=\"index.php?VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&{$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}&ESAM={$_GET['ESAM']}&VISITNUM={$_GET['VISITNUM']}\">
				<table class='table table-striped table-bordered table-hover'>";
            $col_modifica = true;
            if ($xml_form->form ['NO_MOD_COL'] != '')
                $col_modifica = false;
            if ($col_modifica) {
                $col_modifica_header = "<th class=int width=40 align=center $rowspan>" . mlOut("System.all_in_view.view_update_col", "View/Update") . " </th>";
                $elimina_col = "<th class=int width=40 align=center $rowspan>" . mlOut("System.all_in_view.delete_col", "Delete") . "</th>";
                $col_num_txt = mlOut("System.all_in_view.number_col", "Number");
            }
            if ($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TRASH'] == '') {
                $elimina_col = "";
            }

            if ($max > 0) {
                if ($xml_form->form ['TB_HEADER'] != '') {
                    $tb_header = "<th $rowspan>{$xml_form->form['TB_HEADER']}</th>";
                } else {
                    $tb_header = "";
                }

                if (isset($xml_form->form['FIELD_TB_PLUS'])) {
                    $tb_header_split = explode('|', $xml_form->form['FIELD_TB_PLUS_DECODE']);
// 					print_r($tb_header_split);
                    $tb_plus_header = "";
                    foreach ($tb_header_split as $key => $val) {
                        $val = str_replace("'", "", $val);
                        $tb_plus_header .= "<th class=int nowrap>$val</th>";
                    }
                }

                $body .= "
						<tr>
							<th class=int $rowspan>$col_num_txt</th>
							$tb_header
							$field_agg_txt
								$tb_plus_header
							$col_modifica_header
							$elimina_col
						</tr>
						$tr_agg
						";
            }
            if ($in ['PROGR'] > $m_p) {
                $m_p = $in ['PROGR'];
            }
            if ($max > 0) {
                $all_closed = true;
            }
            $counter = 0;
            $sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW
				from {$xml_form->form['TABLE']} 
				where {$this->config_service['PK_SERVICE']}='{$in[$this->config_service['PK_SERVICE']]}' and visitnum={$in['VISITNUM']}
				and visitnum_progr={$in['VISITNUM_PROGR']}
				and esam={$in['ESAM']}
				--and progr=$i
				";

            $sql = new query ($conn);
            $sql->set_sql($sql_query);

            $sql->exec();

            /** Field progressivi (in futuro)*/
            $pending = $this->AllInFieldPendig();

            if ((isset($_GET['ABILITA_EQ_DE']) || isset($_GET['ABILITA_EQ_DM'])) && $this->config_service['eQuery'] == 1) {
                $body .= '<input type="hidden" name="' . $this->config_service['PK_SERVICE'] . '" value="' . $_GET[$this->config_service['PK_SERVICE']] . '"   />
							<input type="hidden" name="ESAM" value="' . $_GET['ESAM'] . '"   />
									<input type="hidden" name="VISITNUM" value="' . $_GET['VISITNUM'] . '"   />
											<input type="hidden" name="VISITNUM_PROGR" value="' . $_GET['VISITNUM_PROGR'] . '"   />
													<input type="hidden" name="PROGR"    />
													<input type="hidden" name="USERID_INS" value="' . $this->session_vars['remote_userid'] . '"   />
															<input type="hidden" name="TABLE" value="' . $xml_form->form['TABLE'] . '"   />
																	';
            }
            $send_all_disabled = false;
            $send_all_deleted = true;
            for ($i = 1; $i <= $max; $i++) {

                if ($_GET ['VISITNUM_PROGR'] == '')
                    $_GET ['VISITNUM_PROGR'] = 0;

                $where_agg = "";
                if ($this->config_service['eQuerySpec']['Integrazione']['ROLE'][$this->config_service['service']] != $this->session_vars['USER_PROFILE'] && $confs != "") {
                    $where_agg = " and EQ_ACTION is null";
                }
                $sql_query = "
								select
								*
								from {$service}_coordinate
								where visitnum={$_GET['VISITNUM']}
								and visitnum_progr={$_GET['VISITNUM_PROGR']}
								and esam={$_GET['ESAM']}
								and progr=$i
								and {$this->config_service['PK_SERVICE']}={$this->pk_service}
								$where_agg
								";
                $sql_abil = new query ($this->conn);
                if (!$sql_abil->get_row($sql_query)) continue;
                if ($sql_abil->row['ABILITATO'] != 1 && $sql_abil->row['ABILITATO'] != 2) continue;
                if ($sql_abil->row['INIZIO'] != 1 && $sql_abil->row['VISITCLOSE'] == 1) continue;
                if ($sql_abil->row['FINE'] == '' || $sql_abil->row['FINE'] == '0') {
                    $send_all_disabled = true;
                }
                if ($sql_abil->row['ABILITATO'] != 2) {
                    $send_all_deleted = false;
                }
                $eq_new = false;


                if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '') {
                    if ($sql_abil->row['EQ_ACTION'] == 1) {
                        $eq_new = true;
                    }
                    //if ($sql_abil->row['EQ_ACTION']==2) continue;
                } else {
                    if ($sql_abil->row['EQ_ACTION'] == 1) continue;
                }

                if (isset ($this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE']) && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE'] != '') {
                    if ($_GET ['VISITNUM_PROGR'] == '')
                        $_GET ['VISITNUM_PROGR'] = 0;

                    $sql_query = "
								select
									fine,
									userid,
						            abilitato,
						            inv_query
								from {$service}_coordinate
								where visitnum={$_GET['VISITNUM']}
                                    and visitnum_progr={$_GET['VISITNUM_PROGR']}
                                    and esam={$_GET['ESAM']}
                                    and progr=$i
                                    and {$this->config_service['PK_SERVICE']}={$this->pk_service}
								";
                    $sql_abil = new query ($this->conn);
                    $sql_abil->get_row($sql_query);
                    if ($sql_abil->row ['FINE'] != 1 && $sql_abil->row ['USERID'] != $this->user->userid)
                        continue;
                }
                if ($sql_abil->row['FINE'] == 1) {
                    $this_close = true;
                } else {
                    $this_close = false;
                }
                $body .= "<tr>";
                $counter++;
                if ($i != $real_progr) {
                    $in ['PROGR'] = $i;
                    $table = $xml_form->form['TABLE'];
                    if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '' && $sql_abil->row['EQ_ACTION'] == '') {

                        $sql_query_eq = "select FIELD, VALORE
											from {$this->service}_EQFIELD
											where eq_int=:eq_int
											and action=0
											and esam=:esam
											and visitnum=:visitnum
											and visitnum_progr=:visitnum_progr
											and progr=:progr
											and {$this->config_service['PK_SERVICE']}=:pk_service";

                        $bind_eq["eq_int"] = $this->integrazione->eq_int;
                        $bind_eq['esam'] = $_GET['ESAM'];
                        $bind_eq['visitnum'] = $_GET['VISITNUM'];
                        $bind_eq['visitnum_progr'] = $_GET['VISITNUM_PROGR'] - 0;
                        $bind_eq['progr'] = $i;
                        $bind_eq['pk_service'] = $_GET[$this->config_service['PK_SERVICE']];

                        $sql2 = new query($this->conn);
                        $sql2->exec($sql_query_eq, $bind_eq);
                        while ($sql2->get_row()) {
                            $eqValues[$i][$sql2->row['FIELD']] = $sql2->row['VALORE'];
                        }
                        if (count($eqValues[$i]) > 0) {
                            $sql_query_tb_descr = "select column_name from user_tab_columns where TABLE_NAME=upper('$table')";
                            $fromTBeq = "select ";
                            $sql2->exec($sql_query_tb_descr);
                            $bind2 = '';
                            while ($sql2->get_row()) {
                                if (isset($eqValues[$i][$sql2->row['COLUMN_NAME']])) {
                                    $fromTBeq .= ":{$sql2->row['COLUMN_NAME']}_EQ as {$sql2->row['COLUMN_NAME']},";
                                    $bind2[$sql2->row['COLUMN_NAME'] . "_EQ"] = $eqValues[$i][$sql2->row['COLUMN_NAME']];
                                } else {
                                    $fromTBeq .= "{$sql2->row['COLUMN_NAME']},";
                                }
                            }
                            $fromTBeq = rtrim($fromTBeq, ",");
                            $fromTBeq .= " from $table where {$this->config_service['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr";
                            $bind2['esam'] = $_GET['ESAM'];
                            $bind2['visitnum'] = $_GET['VISITNUM'];
                            $bind2['visitnum_progr'] = $_GET['VISITNUM_PROGR'] - 0;
                            $bind2['progr'] = $i;
                            $bind2['pk_service'] = $_GET[$this->config_service['PK_SERVICE']];
                            $sql = new query ($conn);
                            $sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW from ($fromTBeq)";
                            //$sql->set_sql ($sql_query , $bind2);
//
//
                            $sql->exec($sql_query, $bind2);


                        } else {
                            $sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW from $table where {$this->config_service['PK_SERVICE']}=:pk_service and esam=:esam and visitnum=:visitnum and visitnum_progr=:visitnum_progr and progr=:progr";
                            $bind3['esam'] = $in['ESAM'];
                            $bind3['visitnum'] = $in['VISITNUM'];
                            $bind3['visitnum_progr'] = $in['VISITNUM_PROGR'] - 0;
                            $bind3['progr'] = $i;
                            $bind3['pk_service'] = $in[$this->config_service['PK_SERVICE']];
                            $sql = new query ($conn);
//
                            $sql->exec($sql_query, $bind3);
                        }
                    } else {
                        $sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW from $table where {$this->config_service['PK_SERVICE']}=:pk_service and esam=:esam and visitnum=:visitnum and visitnum_progr=:visitnum_progr and progr=:progr";
                        $bind3['esam'] = $in['ESAM'];
                        $bind3['visitnum'] = $in['VISITNUM'];
                        $bind3['visitnum_progr'] = $in['VISITNUM_PROGR'] - 0;
                        $bind3['progr'] = $i;
                        $bind3['pk_service'] = $in[$this->config_service['PK_SERVICE']];
                        $sql = new query ($conn);
//
                        $sql->exec($sql_query, $bind3);
                    }

                    $sql->get_row();
                    $TXT = $sql->row ['FIELD_TB_SHOW'];
                    $TXT = preg_replace("!#(.*?)#!m", "<$1>", $TXT);

                    foreach ($xml_form->fields as $k => $v) {
                        if ($v['TYPE'] == 'date_cal' && $v['VAR'] == $xml_form->form['FIELD_TB_SHOW']) {//Gestire il date_cal , con NA NK
                            if (!preg_match("/[0-9]{1,2}\/[0-9]{1,2}\/[0-9]{4}/", $TXT)) {
                                $dd = substr($TXT, 0, 2);
                                $mm = substr($TXT, 2, 2);
                                $yyyy = substr($TXT, 4, 4);
                                $TXT = $dd . '/' . $mm . '/' . $yyyy;
                            }
                        }
                    }

                    $rowdeleted = false;
                    if ($sql_abil->row['ABILITATO'] == 2) {
                        $css_class = "deleted";
                        $css_style = "style=background-color:darkgrey";
                        $rowdeleted = true;
                    } else {
                        $css_class = "sc4bis";
                        $css_style = "";
                    }
                    if ($TXT != '') {
                        $tb_content = "<td class={$css_class} {$css_style}> $TXT</td>";
                    } elseif (!isset ($this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['ADD_BLANK'])) {
                        $tb_content = "<td class={$css_class} $css_style> &nbsp; </td>";
                    } else {
                        $tb_content = "";
                    }

                    if (isset($xml_form->form['FIELD_TB_PLUS'])) {

                        $where_plus = $xml_form->form['FIELD_TB_PLUS_WHERE'];
                        $where_tb_field = preg_replace("/(.*)\[(.*?)\](.*)/", '$2', $where_plus);

                        $sql_query_field = "select $where_tb_field
											from {$xml_form->form['TABLE']}
											where {$this->config_service['PK_SERVICE']}=:pk_service
											and visitnum=:visitnum
											and visitnum_progr=:visitnum_progr
											and progr=:progr";
                        $bind4 = array();
                        $bind4['ESAM'] = $in['ESAM'];
                        $bind4['VISITNUM'] = $in['VISITNUM'];
                        $bind4['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'] - 0;
                        $bind4['PROGR'] = $i;
                        $bind4['PK_SERVICE'] = $in[$this->config_service['PK_SERVICE']];
                        $sql_f = new query ($conn);
                        //
                        $sql_f->exec($sql_query_field, $bind4);
                        $sql_f->get_row();
                        $where_original_cond = $sql_f->row[$where_tb_field];
                        $where_plus = str_replace("[$where_tb_field]", "'" . $where_original_cond . "'", $where_plus);
                        $field_plus = str_replace("|", ",", $xml_form->form['FIELD_TB_PLUS']);
                        $sql_query = "select $field_plus from {$xml_form->form['FIELD_TB_PLUS_VIEW']} where $where_plus";
                        $sql = new query ($conn);
                        $sql->set_sql($sql_query);
                        $sql->exec();
                        $sql->get_row();
                        $td_plus = "";
                        foreach ($sql->row as $key => $val) {
                            $td_plus .= "<td class=sc4bis $css_style>$val</td>";
                        }
                    }
                    $add_txt = '';
                    if (!$exclude_visit) {
                        if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '' && $sql_abil->row['EQ_ACTION'] == '2') {
                            $add_txt = "<img src=\"images/iphone_delete_icon.png\">";
                        }
                        if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '' && $sql_abil->row['EQ_ACTION'] == '1') {
                            $add_txt = "<img src=\"images/plus-icon.png\" width=15px>";
                        }
                        if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '' && count($eqValues[$i]) > o) {
                            $add_txt = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";
                        }

                        /*if( $this->session_vars['USER_PROFILE']!=$this->config_service['eQuerySpec']['Integrazione']['ROLE'][$this->config_service['service']]){
                        $add_txt="";
                    }*/
                    }

                    $body .= "<td class={$css_class} $css_style><b>$add_txt $counter</b></td>
							$tb_content
							$td_plus
							";
                    //$progr = $in ['PROGR'];
                    //if (($xml_form->closed_form ( $progr ) || $this->session_vars ['USER_TIP'] != 'DE') && !($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo)) {
                    //	$this_closed = true;
                    //} else
                    //	$this_closed = false;

                    $progr = $in ['PROGR'];
                    if (!$xml_form->closed_form($progr) || ($this->integrazione->eq_enabled && $this->integrazione->role == $this->user->profilo && !$exclude_visit)) {
                        //se questo if lo mettiamo dentro al prossimo if e anche dentro al prossimo else valorizza le var anche alla progr = 1
                        //modifica edo e giorgio per far valorizzare la $in anche alla prima progressiva dell'all_in_form_view
                        if (isset ($type_fields_agg)) {
                            foreach ($type_fields_agg as $key => $val) {
                                $var = $val ['VAR'];
                                $field_type = "field_{$val['TYPE']}";
                                if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                                    include_once $this->config_service['field_lib'] . $field_type . ".inc";
                                } else {
                                    include_once "{$field_type}.inc";
                                }
                                //include_once $_SERVER['DOCUMENT_ROOT']."/../libs/xCRF/$field_type.inc";
                                $field_obj = new $field_type ($xml_form, $xml_form->vars [$var], $xml_form->conn, $xml_form->tb_vals, $xml_form->session_vars, $xml_form->service, $xml_form->errors);
                                $ret = "";
                                if ($this_close == false && (isset($_GET['ABILITA_EQ_DE']) || isset($_GET['ABILITA_EQ_DM']))) {
                                    $ret = "";
                                } else {
                                    $ret = $field_obj->all_in($var, $i, $sql->row, $this_close);
                                }
                                if ($sql_abil->row['EQ_ACTION'] == '') {
                                    $ret = $field_obj->all_in($var, $i, $sql->row, $this_close);
                                }
                                if ($sql_abil->row['EQ_ACTION'] == '2') {
                                    $ret = $field_obj->all_in($var, $i, $sql->row, true);
                                }
                                $body .= $ret ['body'];
                                $c1_agg .= $ret ['c1_agg'];
                                if ($ret['last_call_sfoglia'] != '') {
                                    $last_call_sfoglia = $ret['last_call_sfoglia'];
                                }
                            }
                        }

                        $all_closed = false;
                        if ($col_modifica) {
                            if ($xml_form->closed_form($progr)) {
                                $col_modifica_td = "<td class=sc4bis align=center><a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}&form={$_GET['form']}\"><i class=\"fa fa-share-square-o\"></i><!-- img src=\"images/pen.png\" border=0 --></a></td>";
                            } else {
                                //fa-share-square-o
                                $col_modifica_td = "<td class=sc4bis align=center><a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}&form={$_GET['form']}\"><i class=\"fa fa-pencil-square-o\"></i><!-- img src=\"images/pen.png\" border=0 --></a></td>";
                            }
                        }
                        $body .= $col_modifica_td;

                    } else {
                        //modifica edo e giorgio per far valorizzare la $in anche alla prima progressiva dell'all_in_form_view
                        if (isset ($type_fields_agg)) {
                            foreach ($type_fields_agg as $key => $val) {
                                $var = $val ['VAR'];
                                $field_type = "field_{$val['TYPE']}";
                                include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc";
                                $field_obj = new $field_type ($xml_form, $xml_form->vars [$var], $xml_form->conn, $xml_form->tb_vals, $xml_form->session_vars, $xml_form->service, $xml_form->errors);
                                $ret = $field_obj->all_in($var, $i, $sql->row, $this_close);

                                if ($sql_abil->row['EQ_ACTION'] == '') {
                                    $ret = $field_obj->all_in($var, $i, $sql->row, $this_close);
                                }
                                if ($sql_abil->row['EQ_ACTION'] == '2') {
                                    $ret = $field_obj->all_in($var, $i, $sql->row, true);
                                }
                                $body .= $ret ['body'];
                                $c1_agg .= $ret ['c1_agg'];
                                if ($ret['last_call_sfoglia'] != '') {
                                    $last_call_sfoglia = $ret['last_call_sfoglia'];
                                }
                            }
                        }
                        /*Field progressivi (in futuro)
                         foreach($pending as $k=>$v){
                            if($v['PROGR']==$progr){
                                $img_eq="<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";
                            }else{
                                $img_eq="";
                             }
                         }*/
                        if ($this->MainSubEqPending($progr)) {
                            $img_eq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";
                        } else {
                            $img_eq = "";
                        }
//						print_r($pending);
                        if (class_exists('SDV_module')) {
                            $param['PK_SERVICE'] = $in[$this->config_service['PK_SERVICE']];
                            $param['VISITNUM'] = $in['VISITNUM'];
                            $param['ESAM'] = $in['ESAM'];
                            $param['FINE'] = $sql_abil->row['FINE'];
                            if (!is_object($this->sdv_module)) {
                                //echo "CREA<hr/>";
                                $this->sdv_module = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], $this);
                            }
                            $add_module = $this->sdv_module->before_print_esams($param, $i, $in['VISITNUM_PROGR']);
                        }
                        if ($col_modifica) {
                            //$col_modifica_td = "<td class={$css_class} align=center><a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}&form={$vlist->esams[$in['VISITNUM']][$in['ESAM']]['XML']}\"><img src=\"images/lente.gif\" border=0>{$add_module}</a>$img_eq</td>";
                            $col_modifica_td = "<td class=sc4bis align=center><a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}&form={$vlist->esams[$in['VISITNUM']][$in['ESAM']]['XML']}\"><i class=\"fa fa-share-square-o\"></i>{$add_module}</a>{$img_eq}</td>";

                        }
                        $body .= "$col_modifica_td";
                        //								if (! $closed_all)
                        //								$body .= "<!--td class=sc4bis>&nbsp;</td-->";
                    }
                    /**
                     *   La cancellazione di una sub è possibile solo se non è stato già cancellato (ABILITATO=2) , altrimenti solo il DE cmq può cancellare.
                     */
                    if ($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TRASH'] != '') {
                        if (!(isset($_GET['ABILITA_EQ_DE']) || isset($_GET['ABILITA_EQ_DM']))) {
// 							if($sql_abil->row['ABILITATO']==2){
// 								$body .= "<td class=deleted  align=center>
// 											<i class=\"fa fa-trash-o grey\"></i> <!-- img src=\"/images/delete.png\" border=0 -->
// 										  </td>";
// 							}
// 							else
                            if (($this->session_vars ['USER_TIP'] == 'DE' || $sql_abil->row['USERID'] == $this->user->userid) && $sql_abil->row['INV_QUERY'] != "MAINSUBSENT" && $xml_form->closed_form($progr)) {
                                if ($this->MainSubEqPending($progr, true)) {
                                    /**
                                     * Il secondo parametro true sta per dire di cercare qualinque eQ , sia pending che risolta
                                     *
                                     */
                                    $body .= "
											<td class=sc4bis align=center>
											<a onclick=\"alert('{$alert_delete_eqpending}'); return false;\" >
											<i class=\"fa fa-trash-o grey\"> <!-- img src=\"/images/trash.png\" border=0 -->
											</a></td>";
                                } else {
                                    //Icona diversa se form cancellata
                                    if ($rowdeleted) {
                                        $body .= "
											<td class=sc4bis align=center>
											<i class=\"fa fa-trash-o red\" title=\"" . mlOut("System.all_in_view.deleted_row", "Row alredy deleted.") . "\"> <!-- img src=\"/images/trash.png\" border=0 -->
											</td>";
                                    } else {
                                        $body .= "
											<td class=sc4bis align=center>
											<a onclick=\"if (!confirm('" . mlOut("System.all_in_view.delete_confirm", "Are you sure to delete the record ") . ": {$this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TESTO']} num. $i?')) {return false;}else{window.location.href='index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$_GET['form']}&PROGR={$i}&CANCELLA_LA_SCHEDA=yes'}\" href=\"#\">
											<i class=\"fa fa-trash-o blue\"> <!-- img src=\"/images/trash.png\" border=0 -->
											</a></td>";
                                    }
                                }
                            } else {
                                $body .= "<td class={$css_class}  >
										</td>";
                            }
                        }
                    }
                    $body .= "</tr>";
                }
            }

            if ($max == 0) {
                $next = 1;
            }
            if (isset ($xml_form->form ['FIELD_AGG']) && ($this->session_vars ['USER_TIP'] == 'DE' || $this->integrazione->eq_enabled)) {
                if (isset ($_GET ['CALL_Sfoglia']) && $last_call_sfoglia != '') {
                    $body .= "
							<script>
							apri_window('/$last_call_sfoglia');
							</script>";
                }
                if (isset ($_GET ['JUST_DELETE'])) {
                    $body .= "
							<script>
							document.forms['ALL_IN_FORMS'].submit();
							</script>";
                }
                if (!$all_closed && $this->integrazione->stato != 2 && !(isset($_GET['ABILITA_EQ_DE']) || isset($_GET['ABILITA_EQ_DM'])) || $exclude_visit) {
                    $body .= "
							<tr>
								<td colspan=$colspan align=center>
								<font color=red><b>" . mlOut("System.eQuery.send_alert", "Attenzione &egrave; necessario applicare le modifiche con il pulsante apposito") . "</b></font><br>
									<input type='hidden' name='ApplMod' value='Salva le modifiche'>
									<input type='submit' name='ApplMod_button' value='" . mlOut("System.eQuery.send", "Applica modifiche") . "' onclick=\"
										f=document.forms[0];
										el=f.elements;
										specifiche='A=ON&L=0&F=0';
								  		c1='';
								  		$c1_agg;
										rc=contr(c1,specifiche);
								  		if (rc) return false;
									\">
						<input type='hidden' name='FreezeMod' value='Congela le modifiche'>
						<input type='submit' style=\"cursor: pointer;\" name='FreezeMod_button' value='" . mlOut("System.eQuery.freeze", "Freeze Modifiche") . "' onclick=\"
						f=document.forms[0];
						el=f.elements;
						specifiche='A=ON&L=0&F=0';
						c1='';
						$c1_agg;
						rc=contr(c1,specifiche);
						if (rc) return false;
						\">
								</td>
							</tr>";
                }
            }

            $add_progr = $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['ADD_PROGR'];
            if (!isset ($this->config_service ['Aggiungi_nuova_scheda'])) {
                $this->config_service ['Aggiungi_nuova_scheda'] = mlOut("System.all_in_view.add_new_record", "Add new record");
            }
            $where_agg_eq = '';
            if ($this->config_service['eQuerySpec']['Integrazione']['ON'] && (!$this->integrazione->eq_enabled || $this->integrazione->eq_int == '')) {
                $where_agg_eq = "and (INV_QUERY is null or EQ_ACTION=2)";
            }
            $sql_visitclose = "select min(visitclose) as closed
								from {$service}_coordinate where visitnum={$_GET['VISITNUM']}
								and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
								$where_agg_eq
							  ";
            $sql_c = new query ($this->conn);
            $sql_c->get_row($sql_visitclose);
            if ($sql_c->row ['CLOSED'] == 1) {
                $visit_closed = true;
            } else {
                $visit_closed = false;
            }
            if (
                (
                    (!$visit_closed && $in ['USER_TIP'] == 'DE')
                    || ($this->integrazione->eq_enabled && $this->integrazione->stato != 2 && $this->integrazione->role == $this->user->profilo && !$exclude_visit)
                )
                && $add_progr != 'no' && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['NEXT_ENABLED'] != 'no' && !isset($_GET['CRF']) && !isset($_GET['ABILITA_EQ_DE'])) {

                if (isset ($this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['ADD_BLANK'])) {
                    //echo "<li>{$_SERVER['REQUEST_URI']}&ADDBLANK=$next</li>";
                    $button = "<input type=\"button\"
								onclick=\"window.location.href='{$_SERVER['REQUEST_URI']}&ADDBLANK=$next'\"
							value=\"{$this->config_service['Aggiungi_nuova_scheda']}\">";
                } elseif ((isset($this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['MAX_ALL_IN']) && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['MAX_ALL_IN'] == $progr)
                    || $sql_abil->row['INV_QUERY'] == "MAINSUBSENT") {
                    /**
                     * Caso di limite massimo per le form progressive. Oppure MainSub inviate , in coordinate INV_QUERY=MAINSUBSENT
                     */
                    $button = "";
                } else {
                    $button = "<input type=\"button\" onclick=\"window.location.href='index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$next}'\" value=\"{$this->config_service['Aggiungi_nuova_scheda']}\">";
                }
                if ($in ['PROGR'] != 0 && $this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['MAINSUB'] == 'yes' && $sql_abil->row['INV_QUERY'] != "MAINSUBSENT") {
                    if ($send_all_disabled == true) {

                        $alert_not_send_all = mlOut("System.MainSub.alert_not_send_all", "Attention please, not all records have been sent. Please open the records (by clicking on the pencil) and send them.");
                        $block_send_all = "alert('$alert_not_send_all');return false;";
                    } elseif ($send_all_deleted == true) {
                        $alert_not_send_all_deleted = mlOut("System.MainSub.alert_not_send_all_deleted", "Attention please, all records are deleted. Please insert a new record or change the answer for the previous question from \'Yes\' to \'No\'.");
                        $block_send_all = "alert('$alert_not_send_all_deleted');return false;";
                    }
                    $send_alert = mlOut("System.MainSub.send_alert", "Attention please, this exam will be closed. Are you sure??");
                    $send = mlOut("System.MainSub.send", "Send");
                    $send_message = mlOut("System.MainSub.send_message", "By clicking on Send button this form will be closed, all data cannot be changed anymore");
                    $button_send = "
						<input type=\"button\" style=\"cursor: pointer;\"
						onclick=\"{$block_send_all}if (!confirm('$send_alert')) return false;window.location.href='{$_SERVER['REQUEST_URI']}&SEND_MAINSUB=yes'\"
						value=\"{$send}\">
						<p>{$send_message}</p>";
                }
                $body .= "
						<tr>
							<td colspan=$colspan align=center>
							$button
							</td>
					</tr>

					<tr>
					<td colspan=$colspan align=center>
					$button_send
					</td>
					</tr>
					";
            }

            if (isset ($this->config_service ['Note'] [$_GET ['VISITNUM']] [$_GET ['ESAM']])) {
                $body .= "<tr><td colspan=$colspan align=center style=\"color:red\">{$this->config_service['Note'][$_GET['VISITNUM']][$_GET['ESAM']]}</td></tr>";
            }
            $body .= "</table></form>";
            if (!isset($_GET['CRF'])) {
                $body .= "<div class=\"br_separator\"></div><div class=\"hide\"><a href=\"index.php?VISITNUM={$_GET['VISITNUM']}&CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&exams=visite_exams.xml\">&lt;&lt; {$this->config_service ['Torna_lista_schede']}</a></div>";
            }
        }
        $ret ['body'] = $body;
        return $ret;
    }


    function CancelProgrEsam($visitnum, $visitnum_progr, $esam, $progr, $center)
    {
        //estrazione tabella dell'esame
        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['XML']);
        $table = $xml_form->form ['TABLE'];

        //Record DELETED nella tabella Audit Trail
        $sql_query = "select var , VALUE_NEW , D_VALUE_NEW from S_X_{$this->service} where {$this->config_service ['PK_SERVICE']}={$this->pk_service} and esam={$esam} and visitnum={$visitnum} and visitnum_progr={$visitnum_progr} and progr={$progr} group by VAR , VALUE_NEW , D_VALUE_NEW";
        $sql = new query($this->conn);
        $sql->exec($sql_query);
        $pk2 = array();
        while ($sql->get_row()) {
            //				echo $sql->row['VAR'];
            $value2 [$this->config_service ['PK_SERVICE']] = $this->pk_service;
            $value2 ['VISITNUM'] = $visitnum;
            $value2 ['VISITNUM_PROGR'] = $visitnum_progr;
            $value2 ['ESAM'] = $esam;
            $value2 ['PROGR'] = $progr;
            $value2['ACTION'] = "DELETED";
            $value2['VAR'] = $sql->row['VAR'];
            $value2['VALUE_OLD'] = $sql->row['VALUE_NEW'];
            $value2['D_VALUE_OLD'] = $sql->row['D_VALUE_NEW'];
            $value2['MODDT'] = sysdate;
            $value2['NOMETAB'] = $table;
            $value2['USERID'] = $this->session_vars['remote_userid'];
            $table_AT = "S_X_" . $this->service;
            $sql2 = new query ($this->conn);
            $sql2->insert($value2, $table_AT, $pk2);
            $this->conn->commit();
        }

        //LO STORICO!!!
        $sql = new query($this->conn);
        $sql_storico = "insert into S_{$table} select '{$this->user->userid}', sysdate, storico_id.nextval, 'E', null, {$table}.*  from $table where {$this->config_service['PK_SERVICE']}='{$_GET[$this->config_service['PK_SERVICE']]}' and VISITNUM={$_GET['VISITNUM']} and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']} and ESAM={$_GET['ESAM']} and PROGR={$_GET['PROGR']}";
        $sql->set_sql($sql_storico);
        $sql->ins_upd();

        // Svuotare il record corrisp al progr in tabella , settare deleted=1
        //Prima lo cancello
        $sql_delete = "
		delete from {$table}
		where esam=$esam
		and visitnum=$visitnum
		and visitnum_progr=$visitnum_progr
		and {$this->config_service['PK_SERVICE']}={$this->pk_service}
		and progr=$progr
		";
        $sql->set_sql($sql_delete);
        $sql->ins_upd();
        $this->conn->commit();

        //Poi lo inserisco solo con pk e deleted=1
        $pk3 = array();
        $value = array();
        $value [$this->config_service ['PK_SERVICE']] = $this->pk_service;
        $value ['VISITNUM'] = $visitnum;
        $value ['VISITNUM_PROGR'] = $visitnum_progr;
        $value ['ESAM'] = $esam;
        $value ['PROGR'] = $progr;
        $value['DELETED'] = 1;
        $sql3 = new query ($this->conn);
        $sql3->insert($value, $table, $pk3);
        $this->conn->commit();

        // Update di coordinate settare abilitato=2
        $pk4 = array();
        $pk4 [$this->config_service ['PK_SERVICE']] = $this->pk_service;
        $pk4 ['VISITNUM'] = $visitnum;
        $pk4 ['VISITNUM_PROGR'] = $visitnum_progr;
        $pk4 ['ESAM'] = $esam;
        $pk4 ['PROGR'] = $progr;
        $value_coord['ABILITATO'] = 2;
        $value_coord['FINE'] = 1;
        $table_coord = $this->service . "_COORDINATE";
        $sql4 = new query ($this->conn);
        $sql4->update($value_coord, $table_coord, $pk4);
        $this->conn->commit();

        if (class_exists('SDV_module')) {
            $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], $this->vlist, $this->xml_dir);
            $sdv->after_cancella_la_scheda($this->pk_service, $visitnum, $visitnum_progr, $esam, $progr, $center);
        }

        die ("<html><head><meta http-equiv=\"refresh\" content=\"0; url=index.php?CENTER=$center&VISITNUM_PROGR=$visitnum_progr&{$this->config_service['PK_SERVICE']}={$this->pk_service}&ESAM=$esam&VISITNUM=$visitnum&form={$this->vlist->esams [$visitnum] [$esam] ['XML']}&JUST_DELETE=yes\"></head></html>");
    }

    function AllInAddBlank($sql, $xml_form)
    {
        $pt_to_verify = null;
        if (!isset ($_GET ['VISITNUM_PROGR']) || $_GET ['VISITNUM_PROGR'] == '')
            $_GET ['VISITNUM_PROGR'] = 0;
        $redirect = $_SERVER ['REQUEST_URI'];
        $redirect = str_replace("&ADDBLANK={$_GET['ADDBLANK']}", "", $redirect);
        $values ['INIZIO'] = 1;
        $values ['ABILITATO'] = 1;
        $values ['USERID'] = $this->user->userid;
        $values ['INSERTDT'] = sysdate;
        $values [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
        $tb_prefix = "{$this->service}";
        $sql_query = "
					select count(*) as conto from {$tb_prefix}_coordinate
					where
						VISITNUM={$_GET['VISITNUM']}
						and
						VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}
						and
						ESAM={$_GET['ESAM']}
						and
						PROGR={$_GET['ADDBLANK']}
						and
						{$this->config['PK_SERVICE']}={$_GET[$this->config['PK_SERVICE']]}
				";
        $sql->get_row($sql_query);

        if ($this->integrazione->eq_enabled && $this->integrazione->role == $this->user->profilo) {
            if ($this->integrazione->eq_int == '') $this->integrazione->CreateEq();
            $values['INV_QUERY'] = $this->integrazione->eq_int;
            $values['EQ_ACTION'] = 1;
        }
        if ($sql->row ['CONTO'] == 0) {
            $values ['VISITNUM'] = $_GET ['VISITNUM'];
            $values ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
            $values ['ESAM'] = $_GET ['ESAM'];
            $values ['PROGR'] = $_GET ['ADDBLANK'];
            $values [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
            $tb_coord = $tb_prefix . "_coordinate";
            $pk = '';
            $sql->insert($values, $tb_coord, $pk);
        } else {

            $tb_coord = $tb_prefix . "_coordinate";
            $pk ['VISITNUM'] = $_GET ['VISITNUM'];
            $pk ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
            $pk ['ESAM'] = $_GET ['ESAM'];
            $pk ['PROGR'] = $_GET ['ADDBLANK'];

            $pk [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
            $sql->update($values, $tb_coord, $pk);
        }
        $pk = '';
        $values = '';
        $values ['VISITNUM'] = $_GET ['VISITNUM'];
        $values ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
        $values ['ESAM'] = $_GET ['ESAM'];
        $values ['PROGR'] = $_GET ['ADDBLANK'];
        $values [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
        $tb_ = $xml_form->form ['TABLE'];

        $sql->insert($values, $tb_, $pk);

        if ((isset ($this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['SFOGLIA_CALL'])) && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['SFOGLIA_CALL'] == 'yes') {
            $redirect .= "&CALL_Sfoglia";
        }

        $this->conn->commit();
        header("location:$redirect");
        die ();
    }

    function AllInApplMod($fields_agg, $fields_agg_txt, $xml_form)
    {
        $redirect = $_SERVER ['REQUEST_URI'];
        $param = '';
        foreach ($_GET as $key => $val) {
            if ($key != 'CALL_Sfoglia')
                $param .= "$key=$val&";
        }
        $param = rtrim($param, "&");
        $redirect = "index.php?{$param}";
        $table = $xml_form->form ['TABLE'];

        $visitnum = $_GET ['VISITNUM'];
        $esam = $_GET ['ESAM'];
        if ($_GET ['VISITNUM_PROGR'] != '')
            $visitnum_progr = $_GET ['VISITNUM_PROGR'];
        else
            $visitnum_progr = 0;
        foreach ($fields_agg as $fk => $field) {
            foreach ($xml_form->fields as $key => $val) {
                if ($val ['VAR'] == $field) {

                    foreach ($_POST as $pkey => $pval) {
                        $field = new field ($xml_form, $key);

                        if (preg_match("!^{$val ['VAR']}_PROGR_!", $pkey) && !preg_match("!D$!", $pkey) && !preg_match("!M$!", $pkey) && !preg_match("!Y$!", $pkey) && !preg_match("!RC$!", $pkey)) {
                            $progr = str_replace("{$val ['VAR']}_PROGR_", "", $pkey);
                            if ($val ['TYPE'] == 'radio') {
                                $values [$progr] ["D_" . $val ['VAR']] = $field->values [$_POST [$val ['VAR'] . "_PROGR_" . $progr]];
                            }
                            if ($val ['TYPE'] == 'select') {
                                $values [$progr] ["D_" . $val ['VAR']] = $field->values [$_POST [$val ['VAR'] . "_PROGR_" . $progr]];

                            }
                            $values [$progr] [$val ['VAR']] = $pval;
                            if ($val ['TYPE'] == 'data') {
                                if ($pval != '') {
                                    $values [$progr] [$val ['VAR']] = "to_date('{$pval}','DDMMYYYY')";
                                    $values [$progr] [$val ['VAR'] . "RC"] = "OKOKOK";
                                } else
                                    unset ($values [$progr] [$val ['VAR']]);
                            }
                        }
                    }
                }
            }
        }
        foreach ($values as $progr => $values_) {
            $audit_trail = new audit_trail($this->service, $this->conn, $this->config_service, $this->vlist);
            $audit_trail->audit_trail_diff_all_in($xml_form, null, $this->session_vars, $progr);
            $pk = array();
            $pk [$this->config_service ['PK_SERVICE']] = $this->pk_service;
            $pk ['VISITNUM'] = $visitnum;
            $pk ['VISITNUM_PROGR'] = $visitnum_progr;
            $pk ['ESAM'] = $esam;
            $pk ['PROGR'] = $progr;
            if (count($values_) > 0) {
                //echo "<hr>$progr";
                $sql = new query ($this->conn);
                $sql->update($values_, $table, $pk);
                //ufficio prova 1
                //							$sql_uff = new query ( $this->conn );
                //							$sql_uff->update ( $values_, "CP_VI_CONFEZIONI_UFF", $pk );

            }
            if (isset($this->integrazione) && $this->integrazione->eq_int != '') {
                $sql_query_coord = "select eq_action from {$this->service}_COORDINATE
								where 
								visitnum=:visitnum
								and visitnum_progr=:visitnum_progr
								and progr=:progr
								and esam=:esam 
								and {$this->config_service ['PK_SERVICE']}=:pk_service
								";
                $bind_['visitnum'] = $visitnum;
                $bind_['visitnum_progr'] = $visitnum_progr;
                $bind_['progr'] = $progr;
                $bind_['pk_service'] = $this->pk_service;
                $bind_['esam'] = $esam;
                $sql->get_row($sql_query_coord, $bind_);
                $action = $sql->row['EQ_ACTION'] - 0;
                foreach ($values_ as $field => $val) {
                    $bind1 = '';
                    $sql_query = "select count(*) as C from {$this->service}_EQFIELD 
									where eq_int=:eq_int
									and visitnum=:visitnum
									and visitnum_progr=:visitnum_progr
									and progr=:progr
									and esam=:esam
									and field=:field
									and {$this->config_service ['PK_SERVICE']}=:pk_service";
                    $bind1['eq_int'] = $this->integrazione->eq_int;
                    $bind1['visitnum'] = $visitnum;
                    $bind1['visitnum_progr'] = $visitnum_progr;
                    $bind1['progr'] = $progr;
                    $bind1['pk_service'] = $this->pk_service;
                    $bind1['esam'] = $esam;
                    $bind1['field'] = $field;
                    $sql->get_row($sql_query, $bind1);
//
                    $eqPkAssoc['EQ_INT'] = $this->integrazione->eq_int;
                    $eqPkAssoc['VISITNUM'] = $visitnum;
                    $eqPkAssoc['VISITNUM_PROGR'] = $visitnum_progr;
                    $eqPkAssoc['PROGR'] = $progr;
                    $eqPkAssoc[$this->config_service ['PK_SERVICE']] = $this->pk_service;
                    $eqPkAssoc['ESAM'] = $esam;
                    $eqPkAssoc['FIELD'] = $field;
                    if ($sql->row['C'] > 0) {
                        $eqValues = '';
                        $eqValues['VALORE'] = $val;
                        $eqValues['ACTION'] = $action;
                        $sql->update($eqValues, $this->service . "_EQFIELD", $eqPkAssoc);
                    } else {
                        $eqValues = '';
                        $eqpk = '';
                        $eqValues['VALORE'] = $val;
                        $eqValues['ACTION'] = $action;
                        foreach ($eqPkAssoc as $bk => $bv) {
                            $eqValues[$bk] = $bv;
                        }
                        $sql->insert($eqValues, $this->service . "_EQFIELD", $eqpk);
                    }
                }

            }

        }
        if ($xml_form->form ['F_TO_CALL'] != '') {
            $f_to_call = $xml_form->form ['F_TO_CALL'];
            $f_to_call ($xml_form);
        }
        $this->conn->commit();
        header("location:$redirect");
        die ();
    }

    /**
     * Genera il codice HTML della scheda
     *
     * @param String $xml
     * @param boolean $col_modifica
     * @param boolean $no_link_back
     */
    function formJsonData($xml)
    {
        $pt_info = $this->evaluate_pt($xml);
        $xml = $pt_info['XML'];

        $this->session_vars ['form'] = $xml;
        $vlist = $this->vlist;
        $in = $this->session_vars;
        $conn = $this->conn;
        $service = $this->service;
        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);

        $xml_form->xml_form_by_file($this->xml_dir . '/' . $xml);

        if (isset ($this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE']) && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE'] != '') {

            if ($_GET ['VISITNUM_PROGR'] == '')
                $_GET ['VISITNUM_PROGR'] = 0;
            $sql_query = "
                                select
                                    fine,
                                    userid
                                from {$service}_coordinate
                                where visitnum={$_GET['VISITNUM']}
                                and visitnum_progr={$_GET['VISITNUM_PROGR']}
                                and esam={$_GET['ESAM']}
                                and progr={$_GET ['PROGR']}
                                and {$this->config_service['PK_SERVICE']}={$this->pk_service}
                                ";
            $sql_abil = new query ($this->conn);
            $sql_abil->get_row($sql_query);
            if ($sql_abil->row ['FINE'] != 1 && $sql_abil->row ['USERID'] != $this->user->userid) {
                $data = [];
                $data['status'] = 'ERROR';
                $data['msg'] = $this->testo("userNotCenter");
                header('Content-Type: application/json');
                echo json_encode($data);
                die();
            }
        }
        if (!($this->pk_service != '' && $this->pk_service != 'next') && $_GET['CENTER'] == '') {
            $sql_query = "select c.* from {$service}_UTENTI_CENTRI uc, {$service}_CENTRI c where uc.center=c.center and uc.userid=:userid";
            $bind['USERID'] = $this->session_vars['remote_userid'];
            $sql = new query($this->conn);
            $sql->exec($sql_query, $bind);
            if ($sql->numrows > 1) {
                $data = [];
                $data['status'] = 'ERROR';
                $data['msg'] = "NO_SITE_SELECTED";
                header('Content-Type: application/json');
                echo json_encode($data);
                die();
            } else {
                $sql->get_row();
                $this->session_vars['CENTER'] = $sql->row['CENTER'];
            }
        }
        $xml_form->make_html();
        $data = [];
        $data['status'] = 'OK';
        $data['data'] = $xml_form->tb_vals;
        header('Content-Type: application/json');
        echo json_encode($data);
        die();


    }

    /**
     * Genera il codice HTML della scheda
     *
     * @param String $xml
     * @param boolean $col_modifica
     * @param boolean $no_link_back
     */
    function form($xml, $col_modifica = true, $no_link_back = false)
    {
        $onload = null;
        $pt_to_verify = null;
        $pt_field = null;
        $pt_info = $this->evaluate_pt($xml);
        $xml = $pt_info['XML'];
        $body = null;
        $this->session_vars ['form'] = $xml;
        $vlist = $this->vlist;
        $in = $this->session_vars;
        $conn = $this->conn;
        $service = $this->service;
        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);

        $xml_form->xml_form_by_file($this->xml_dir . '/' . $xml);

        $dbaligned = true;
        if ($this->config_service['production'] != 1) {
            $dbaligned = $xml_form->allinea_db();
        }
        if (!$dbaligned) {
            //$body .= "<p align=center>";
            $body = $xml_form->body;
            $body .= "<form method=post align=center>";

            foreach ($in as $key => $val)
                $body .= "<input type=\"hidden\" name=\"$key\" value=\"$val\">";
            $body .= "<input type=\"submit\" name=\"CREATE\" value=\"Update DB\"></form></p>";
        } else {

            if ($vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN'] != '' && !isset($in['PROGR'])) {
                $ret = $this->all_in_form_view($xml_form);
                $body .= $ret ['body'];
            } else {

                if (isset ($this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE']) && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE'] != '') {

                    if ($_GET ['VISITNUM_PROGR'] == '')
                        $_GET ['VISITNUM_PROGR'] = 0;
                    $sql_query = "
                                select
                                    fine,
                                    userid
                                from {$service}_coordinate
                                where visitnum={$_GET['VISITNUM']}
                                and visitnum_progr={$_GET['VISITNUM_PROGR']}
                                and esam={$_GET['ESAM']}
                                and progr={$_GET ['PROGR']}
                                and {$this->config_service['PK_SERVICE']}={$this->pk_service}
                                ";
                    $sql_abil = new query ($this->conn);
                    $sql_abil->get_row($sql_query);
                    if ($sql_abil->row ['FINE'] != 1 && $sql_abil->row ['USERID'] != $this->user->userid) {
                        error_page($this->user->userid, $this->testo("userNotCenter"), "");
                    }
                }
                if (!($this->pk_service != '' && $this->pk_service != 'next') && $_GET['CENTER'] == '') {
                    $sql_query = "select c.* from {$service}_UTENTI_CENTRI uc, {$service}_CENTRI c, SITES S where uc.center=c.center and uc.userid=:userid and s.id = c.center order by s.code";
                    $bind['USERID'] = $this->session_vars['remote_userid'];
                    $sql = new query($this->conn);
                    $sql->exec($sql_query, $bind);
                    if ($sql->numrows > 1) {
                        while ($sql->get_row()) {

                            $this->page_title = "Site Selection";
                            $this->body .= "</br><a href=\"{$_SERVER['SCRIPT_NAME']}?{$_SERVER['QUERY_STRING']}&CENTER={$sql->row['CENTER']}\"><i class=\"fa fa-hospital-o\"></i> Site: {$sql->row['DENOM']}</a>";
                        }
                        return;
                    } else {
                        $sql->get_row();
                        $this->session_vars['CENTER'] = $sql->row['CENTER'];
                    }
                }
                $xml_form->make_html($no_link_back);
                //TODO: $pt_to_verify da dove viene?
                if ($pt_to_verify && $xml_form->tb_vals[$pt_field] != '') {

                    $str = "select PT_VALUTAZIONE from {$this->service}_{$this->config_service['PT_TABLE']} where PT_CODE=:pt_code";
                    $bind['PT_CODE'] = $xml_form->tb_vals[$pt_field];
                    $query = new query($this->conn);
                    $query->get_row($str, $bind);
                    unset($bind);
                    $newXml = str_replace('.xml', '_' . $query->row['PT_VALUTAZIONE'] . '.xml', $xml);
                    if (file_exists($this->xml_dir . '/' . $newXml)) {
                        $xml = $newXml;
                        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                        $xml_form->xml_form_by_file($this->xml_dir . '/' . $xml);
                        $dbaligned = true;
                        if ($this->config_service['production'] != 1) {
                            $dbaligned = $xml_form->allinea_db();
                        }
                        if (!$dbaligned) {

                            $xml_form->body = '';
                            //$body .= "<p align=center>";
                            $body = $xml_form->body;
                            $body .= "<form method=post align=center>";

                            foreach ($in as $key => $val)
                                $body .= "<input type=\"hidden\" name=\"$key\" value=\"$val\">";
                            $body .= "<input type=\"submit\" name=\"CREATE\" value=\"Update DB\"></form></p>";
                            $this->body = $body;
                            return;
                        } else {
                            $xml_form->make_html($no_link_back);
                        }
                    }
                }
                if ($this->pk_service != '' && $this->pk_service != 'next') {
                    $this->make_patient_table();
                    $body = $this->patient_table;
                    $body .= "<div class=\"br_separator\"></div>" . $this->tb_riassuntiva();
                } else
                    $body = '';

                $body .= $xml_form->body;

                $script = "
                <script type=\"text/javascript\">
                " . $xml_form->salva_js . "
                " . $xml_form->invia_js . "
                " . $xml_form->check_js . "
                " . $xml_form->inrevisione_js . "
                </script>
                " . $xml_form->script_js . "
                ";
                $onload .= $xml_form->onload . ";";

            }
            if ($this->config_service ['lang'] == "en") {
                $link_equery = "Send eQuery on this form";
            } else {
                $link_equery = "Invia eQuery su questa scheda";
            }
            if ($xml_form->closed && $this->config_service ['equery'] == 'yes') {
                //modifica G.Tufano 05/07/2010
                //controllo se sono in un sottostudio o no
                $profond = $this->xmr->depth;
                $lvl_up = "";
                //depth >0 sono in un sottostudio
                if ($profond > 0) {
                    do {
                        $lvl_up .= "../";
                        $profond--;
                    } while ($profond > 0);
                }

                $body .= "
                    <br>
                    <p align=right>
                        <a href=\"{$lvl_up}index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&REGISTRY={$this->xmr->prefix}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&eQuery&eform\">
                        $link_equery
                        </a>
                    </p>
                ";
            }
        }
        if ($xml_form->closed && $this->config_service['equery_objs'] == 'yes') {
            //global $config_service;
            $index = "index.php";
            foreach ($this->equery_objs as $curr_equery_obj) {
                $body .= "<br>
                    <p align=right>" . $curr_equery_obj->link('nuovo') . "</p>";
            }
        }
        $this->body = $this->audit_trail_form_body($xml_form) . $body;
        $this->onload = $onload;
        $this->script = $script . $this->audit_trail_form_js($xml_form);

    }

    function addSendCoordInfo($xml_form, $in)
    {
        if (!isset($_POST['ajax_call']) || $_POST['ajax_call'] == '') {
            $bind['PK_SERVICE'] = $xml_form->session_vars[$this->config_service['PK_SERVICE']];
            $bind['VISITNUM'] = $in['VISITNUM'];
            if ($in['VISITNUM_PROGR'] == '') $in['VISITNUM_PROGR'] = 0;
            if ($in['PROGR'] == '') $in['PROGR'] = 1;
            $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
            $bind['PROGR'] = $in['PROGR'];
            $bind['ESAM'] = $in['ESAM'];
            $bind['USER_'] = $this->user->userid;
            $sql = new query($this->conn);
            $sql_check = "select CREATE_USER from {$this->service}_COORDINATE where {$this->config_service['PK_SERVICE']}=:PK_SERVICE and VISITNUM=:VISITNUM and ESAM=:ESAM and PROGR=:PROGR and VISITNUM_PROGR=:VISITNUM_PROGR";
            $sql->get_row($sql_check, $bind);
            if ($sql->row['CREATE_USER'] != '') $updateField = "LAST_MOD_USER=:USER_";
            else $updateField = "SEND_DT=sysdate, CREATE_USER=:USER_";
            $sql_update = "update {$this->service}_COORDINATE set $updateField where {$this->config_service['PK_SERVICE']}=:PK_SERVICE and VISITNUM=:VISITNUM and ESAM=:ESAM and PROGR=:PROGR and VISITNUM_PROGR=:VISITNUM_PROGR";
            $sql = new query($this->conn);
            $sql->ins_upd($sql_update, $bind);
        }
    }

    /**
     * Gestisce il salvataggio dei dati all'invio
     *
     * @param String $xml_form
     * @param String $debug
     */
    function invia_db_dm($xml_form, $debug = null)
    {
        global $filetxt;
        global $body;
        $filetxt = preg_replace("/<!--user_name-->/", "Loading...", $filetxt);
        //		print($body);
        $conn = $this->conn;
        $in = $this->session_vars;
        $service = $this->service;
        //		foreach ( $in as $key => $val )
        //		$in [$key] = ora_escape ( $in [$key] );
        $this->invia_form($xml_form, $in);
        if ($in ['ID_QUERY'] > 0) {
            $query = new query ($this->conn);
            $sql_equery = "update " . $this->config_service['service_root'] . "_equery set validata=1, val_userid=:userid, val_dt=sysdate, chiusa='1', chiusa_dt=sysdate where id=:id_query";
            unset($bindUpdate);
            $bindUpdate['USERID'] = $in ['remote_userid'];
            $bindUpdate['ID_QUERY'] = $in ['ID_QUERY'];
            $query->ins_upd($sql_equery, $bindUpdate);//binded
        }
        $this->addSendCoordInfo($xml_form, $in);
        //controllo se sono in un sottostudio o no
        $profond = $this->xmr->depth;
        $lvl_up = "";
        //depth >0 sono in un sottostudio
        if ($profond > 0) {
            do {
                $lvl_up .= "../";
                $profond--;
            } while ($profond > 0);
        }

        if ($in ['ID_QUERY'] > 0) {
            $link = "{$lvl_up}index.php?eQuery";
        } else {
            $link = "{$lvl_up}index.php?exams=visite_exams.xml&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&CENTER={$in['CENTER']}&VISITNUM={$in['VISITNUM']}";
        }
        if (isset ($in ['ajax_call'])) {
            die ("link_to:" . $link);
        } else {
            $this->check_visit_closure();
            if (!($debug == 1)) {
                ob_clean();
                header('location:' . $link);
                $this->conn->commit();
                die();
                $filetxt = preg_replace("/<!--meta refresh-->/", "<meta http-equiv=\"refresh\" content=\"1;url=$link\">", $filetxt);
            }
        }

        $this->conn->commit();
        $in ['invia'] = '';
        $in ['INVIOCO'] = '';
        $in ['ESAM'] = '';
        $form = '';
        $in ['form'] = '';
        if ($debug != 1) {
            ob_clean();
            header('location:' . $link);
            $this->conn->commit();
            die();
            $filetxt = preg_replace("/<!--meta refresh-->/", "<meta http-equiv=\"refresh\" content=\"1;url=$link\">", $filetxt);
        }
        $script = "";
        $onload = '';
        $body = ' &nbsp; SAVING...';
    }

    /**
     * Gestisce il salvataggio dei dati al salvataggio della scheda
     *
     * @param String $xml_form
     * @param String $debug
     * @return String
     */
    function salva_db($xml_form, $debug = null, $force_save = false)
    {
        $get_variables = null;
        $old_in = null;
        $prev_idx = null;
        $conn = $this->conn;
        $filetxt = $this->config_service ['filetxt'];
        $filetxt = preg_replace("/<!--user_name-->/", "Loading...", $filetxt);
        $in = $this->session_vars;
        $service = $this->service;
        $query = new query ($conn);
        if ($xml_form->closed_form() && !$force_save) {
            /*$debug_values.="SALVA DB LINEA 2594";
			foreach($in as $key=>$val) {
				$debug_values.="\n- Nome variabile: ".$key." -> Valore variabile: ".$val;
			}
			foreach($xml_form as $key=>$val) {
				$debug_values.="\n- Nome variabile: ".$key." -> Valore variabile: ".$val;
			}*/
            $txt_error = $this->testo("schedaInviata");
            error_page($in ['remote_userid'], $txt_error, "");
        }
        $this->salva_form($xml_form, $in, $force_save);
        $new_xml_form = new xml_form ();
        foreach ($old_in as $key => $val)
            $in [$key] = $val;
        $in ['invia'] = '';
        $in ['INVIOCO'] = '';
        $form = '';
        $in ['form'] = '';
        $link = $xml_form->form ['LINK_TO'];
        // GESTIONE LINK_TO |ME| E |NEXT|
        if ($link == '')
            $link = "index.php";
        elseif (preg_match("/^\|ME\|/i", $link)) {
            $service = $this->service;
            $session_vars = $this->session_vars;
            unset($session_vars['VISITNUM']);
            $vlist = new xml_esams_list ($this->xml_dir . "/" . $this->visit_structure_xml, $this->config_service, $session_vars, $this->conn, $this->xml_dir);
            $form = $vlist->esams[$in['VISITNUM']][$in['ESAM']]['XML'];
            if (!isset($in['PROGR']) || $in['PROGR'] == "") {
                /**
                 *  Il link per cambiare paziente, lascio l'add_progr vuoto , se sto ad esempio in una sub arriverï¿½ in una sub.
                 *  Il link per cambiare form , metto di default il PROGR=1 , se passo da una sub ad una form normale
                 */
                $add_progr = "";
                $add_progr_form = "&PROGR=1";
            } else {
                $add_progr_form = $add_progr = "&PROGR={$in['PROGR']}";
            }
            if ($get_variables != "") {
                $get_variables = str_replace("?", "", $get_variables);
                $get_variables = str_replace("|and|", "&", $get_variables);
                $get_variables = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $get_variables);
            }
            $link = "index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}{$add_progr_form}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$form}&{$get_variables}";

            // 			 			var_dump($link);
            // 			 			echo "<hr/>";
            // 			 			//var_dump($vlist);
            // 			 			die();
        } elseif (preg_match("/^\|NEXT\|/i", $link)) {
            $service = $this->service;
            $session_vars = $this->session_vars;
            unset($session_vars['VISITNUM']);
            $vlist = new xml_esams_list ($this->xml_dir . "/" . $this->visit_structure_xml, $this->config_service, $session_vars, $this->conn, $this->xml_dir);
            $i = 0;
            $j = 0;
            //		print_r($this->vlist->esams);
            foreach ($this->vlist->visitnums as $key => $val) {

                foreach ($this->vlist->esams[$key] as $k => $v) {
                    //				print_r($this->vlist->visitnums[$key]['NUMBER']);
                    $esams[$i] = $this->vlist->esams[$key][$k]['NUMBER'];
                    $visitnums[$i] = $this->vlist->visitnums[$key]['NUMBER'];
                    if ($this->vlist->esams[$key][$k]['NUMBER'] == $in['ESAM'] && $this->vlist->visitnums[$key]['NUMBER'] == $in['VISITNUM']) {
                        //						print_r($i);
                        $next_idx = $i + 1;
                        //						echo $next_idx;


                    }
                    $i++;
                }
            }
            if ($this->vlist->esams[$visitnums[$next_idx]][$esams[$next_idx]]['SUB'] == "yes") {
                $next_idx++;
            }
            if ($this->vlist->esams[$visitnums[$prev_idx]][$esams[$prev_idx]]['SUB'] == "yes") {
                $prev_idx--;
            }

            $next_esam = $esams[$next_idx];
            $next_visit = $visitnums[$next_idx];
            $next_form = $this->vlist->esams[$next_visit][$next_esam]['XML'];
            $form = $vlist->esams[$in['VISITNUM']][$in['ESAM']]['XML'];
            if (!isset($in['PROGR']) || $in['PROGR'] == "") {
                /**
                 *  Il link per cambiare paziente, lascio l'add_progr vuoto , se sto ad esempio in una sub arriverï¿½ in una sub.
                 *  Il link per cambiare form , metto di default il PROGR=1 , se passo da una sub ad una form normale
                 */
                $add_progr = "";
                $add_progr_form = "&PROGR=1";
            } else {
                $add_progr_form = $add_progr = "&PROGR={$in['PROGR']}";
            }
            if ($next_esam != '') {
                if ($get_variables != "") {
                    $get_variables = str_replace("?", "", $get_variables);
                    $get_variables = str_replace("|and|", "&", $get_variables);
                    $get_variables = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $get_variables);
                }
                $link = "index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&VISITNUM={$next_visit}&ESAM={$next_esam}{$add_progr_form}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$next_form}&{$get_variables}";
            }
            // 			var_dump($link);
            // 			echo "<hr/>";
            // 			//var_dump($vlist);
            // 			die();
        } else {
            $link = str_replace("|and|", "&", $link);
            $link = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $link);
        }
        $insert_errors = $this->errors;
        if (count($insert_errors) > 0)
            return false;
        if (isset ($in ['ajax_call']))
            die ("link_to:" . $link);
        else {
            ob_clean();
            header('location:' . $link);
            $this->conn->commit();
            die();
            $filetxt = preg_replace("/<!--meta refresh-->/", "<meta http-equiv=\"refresh\" content=\"1;url=$link\">", $filetxt);
        }
        global $link_to;
        $link_to = $link;
        $conn->commit();
        $this->body = ' &nbsp; Saving...';
        $filetxt = preg_replace("/<!--body-->/", $this->body, $filetxt);
        die ($filetxt);
    }

    /**
     * Salva i dati in DB (gestione salva)
     *
     * @param String $xml_form
     * @param array $in_s
     */
    function salva_form($xml_form, $in_s, $forceSave = false)
    {
        $conn = $this->conn;
        $in = $this->session_vars;
        $in = $in_s;
        $debug = 1;

        //Controllo che l'utente loggato possa fare DE
        if ($in['USER_TIP'] != "DE" && !isset($in['ID_QUERY'])) {
            $message = "Current profile does not allow Data Entry.";
            if ($in['ajax_call'] != '') {
                echo "Error:#error#";
                die($message);
            } else {
                error_page($this->user->userid, $message, array());
            }
        }

        $f_to_call_pre = $xml_form->form ['F_TO_CALL_PRE'];
        if ($f_to_call_pre != "") {
            $this->conn->commit();
            $this->conn->close();
            if ($xml_form->session_vars['PROGR'] == '') $xml_form->session_vars['PROGR'] = 1;
            if ($xml_form->session_vars['VISITNUM_PROGR'] == '') $xml_form->session_vars['VISITNUM_PROGR'] = 0;
            foreach ($xml_form->session_vars as $key => $val) {
                $vars[$key] = $val;
            }
            include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/activitiClient.inc";
            $service = new ActivitiService("admin", "xxx");
            $vars['connectId'] = $this->config_service['AWFConnectionId'];
            $vars['studyPrefix'] = $this->config_service['service'];
            $vars['pkService'] = $this->config_service['PK_SERVICE'];
            if (!isset($xml_form->session_vars['ajax_call'])) $vars['ajax_call'] = '';
            $this->LaunchActivitiProcess($service, $f_to_call_pre, $vars);
            $this->reopenConn();
            $conn = $this->conn;
        }
        $this->audit_trail($xml_form);
        /*Chiamata dell'oggetto audit trail per salvare i dati nella tabella relativa, storico per singolo campo valente per ogni tabella dello studio*/
        $audit_trail = new audit_trail($this->service, $this->conn, $this->config_service, $this->vlist);
        $audit_trail->audit_trail_difference($xml_form);
        $query = new query ($conn);
        $xml_form->query_builder($forceSave);
        $this->errors = $xml_form->getErrors();
        //		global $config_service;


        $f_to_call = $xml_form->form ['F_TO_CALL'];
        if (function_exists($f_to_call)) {
            $f_to_call ($xml_form);
        } elseif ($f_to_call != "") {
            $this->conn->commit();
            $this->conn->closeConnection();
            if ($xml_form->session_vars['PROGR'] == '') $xml_form->session_vars['PROGR'] = 1;
            if ($xml_form->session_vars['VISITNUM_PROGR'] == '') $xml_form->session_vars['VISITNUM_PROGR'] = 0;
            foreach ($xml_form->session_vars as $key => $val) {
                $vars[$key] = $val;
            }
            include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/activitiClient.inc";
            $service = new ActivitiService($this->config_service['AWFBaseURL'], $this->config_service['AWFUsername'], $this->config_service['AWFPassword']);
            $vars['connectId'] = $this->config_service['AWFConnectionId'];
            $vars['studyPrefix'] = $this->config_service['service'];
            $vars['pkService'] = $this->config_service['PK_SERVICE'];
            if (!isset($xml_form->session_vars['ajax_call'])) $vars['ajax_call'] = '';
            $this->LaunchActivitiProcess($service, $f_to_call, $vars);
            $this->reopenConn();
            $conn = $this->conn;
        }
        for ($i = 0; $i < count($xml_form->query_enable); $i++) {
            $query = new query ($conn);
            $query->set_sql($xml_form->query_enable [$i]);
            $query->ins_upd();//non richiede binding
        }
        foreach ($in as $key => $val) {
            $old_in [$key] = $val;
            if (preg_match("/TB_COLL/", $key)) {
                $numero_record = preg_replace("/TB_COLL_/", "", $key);
                $numero_record = preg_replace("/(.*?)_(.*)/", "$1", $numero_record);
                if (!isset ($forms_coll [$numero_record]))
                    $forms_coll [$numero_record] = true;
            }

        }

        //Invio mail generico
        if (!$in['ajax_call']) {
            $this->sendGenericMail($in['VISITNUM'], $in['ESAM'], "SAVE", false, false, $in, false);
        }

    }

    /**
     * Salva i dati in DB (gestione invio)
     */
    function invia_db($xml_form, $debug = null)
    {
        $old_in = null;
        $prev_idx = null;
        $conn = $this->conn;

        $filetxt = $this->config_service ['filetxt'];
        $in = $this->session_vars;
        $service = $this->service;
        if (($this->session_vars['USER_TIP'] == "DM" || $this->config_service['eQuerySpec']['Integrazione']['VALIDATOR'] == $this->session_vars['USER_PROFILE']) && isset($_POST['eQueryApproval'])) {
            $this->eQueryApproval($xml_form);
        } else {

            $query = new query ($conn);
            if ($xml_form->closed_form())
                error_page($in ['remote_userid'], $this->testo("schedaInviata"), "");

            $this->invia_form($xml_form, $in);
        }
        $new_xml_form = new xml_form ();
        foreach ($old_in as $key => $val)
            $in [$key] = $val;
        $in ['invia'] = '';
        $in ['INVIOCO'] = '';
        $form = '';
        $in ['form'] = '';
        $link = $in ['link_to_send'] != '' ? $in ['link_to_send'] : $in ['link_to']; //vmazzeo 24.20.2015 bugfix non veniva considerato il link_to_send all'invio della scheda
        // GESTIONE LINK_TO |ME| E |NEXT|
        if (strtolower($in[$this->config_service['PK_SERVICE']]) == 'next') {
            $in[$this->config_service['PK_SERVICE']] = var_glob($this->config_service['PK_SERVICE']);
        }
        if ($link == '')
            $link = "index.php";
        elseif (preg_match("/^\|ME\|/i", $link)) {
            $service = $this->service;
            $session_vars = $this->session_vars;
            unset($session_vars['VISITNUM']);
            $vlist = new xml_esams_list ($this->xml_dir . "/" . $this->visit_structure_xml, $this->config_service, $session_vars, $this->conn, $this->xml_dir);
            $form = $vlist->esams[$in['VISITNUM']][$in['ESAM']]['XML'];
            if (!isset($in['PROGR']) || $in['PROGR'] == "") {
                /**
                 *  Il link per cambiare paziente, lascio l'add_progr vuoto , se sto ad esempio in una sub arriverï¿½ in una sub.
                 *  Il link per cambiare form , metto di default il PROGR=1 , se passo da una sub ad una form normale
                 */
                $add_progr = "";
                $add_progr_form = "&PROGR=1";
            } else {
                $add_progr_form = $add_progr = "&PROGR={$in['PROGR']}";
            }
            $get_variables = strrchr($link, '?'); //vmazzeo 24.20.2015 aggiungo possibilità di inserire variabili get in link_to e link_to_send |ME|?variabile1=valore1|and|variabile2=valore2
            if ($get_variables != "") {
                $get_variables = str_replace("?", "", $get_variables);
                $get_variables = str_replace("|and|", "&", $get_variables);
                $get_variables = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $get_variables);
            }
            $link = "index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&VISITNUM={$in['VISITNUM']}&ESAM={$in['ESAM']}{$add_progr_form}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$form}&{$get_variables}";

            // 			 			var_dump($link);
            // 			 			echo "<hr/>";
            // 			 			//var_dump($vlist);
            // 			 			die();
        } elseif (preg_match("/^\|NEXT\|/i", $link)) {
            $service = $this->service;
            $session_vars = $this->session_vars;
            unset($session_vars['VISITNUM']);
            $vlist = new xml_esams_list ($this->xml_dir . "/" . $this->visit_structure_xml, $this->config_service, $session_vars, $this->conn, $this->xml_dir);
            $i = 0;
            $j = 0;
            //		print_r($this->vlist->esams);
            foreach ($this->vlist->visitnums as $key => $val) {

                foreach ($this->vlist->esams[$key] as $k => $v) {
                    //				print_r($this->vlist->visitnums[$key]['NUMBER']);
                    $esams[$i] = $this->vlist->esams[$key][$k]['NUMBER'];
                    $visitnums[$i] = $this->vlist->visitnums[$key]['NUMBER'];
                    if ($this->vlist->esams[$key][$k]['NUMBER'] == $in['ESAM'] && $this->vlist->visitnums[$key]['NUMBER'] == $in['VISITNUM']) {
                        //						print_r($i);
                        $next_idx = $i + 1;
                        //						echo $next_idx;


                    }
                    $i++;
                }
            }
            if ($this->vlist->esams[$visitnums[$next_idx]][$esams[$next_idx]]['SUB'] == "yes") {
                $next_idx++;
            }
            if ($this->vlist->esams[$visitnums[$prev_idx]][$esams[$prev_idx]]['SUB'] == "yes") {
                $prev_idx--;
            }

            $next_esam = $esams[$next_idx];
            $next_visit = $visitnums[$next_idx];
            $next_form = $this->vlist->esams[$next_visit][$next_esam]['XML'];
            $form = $vlist->esams[$in['VISITNUM']][$in['ESAM']]['XML'];
            if (!isset($in['PROGR']) || $in['PROGR'] == "") {
                /**
                 *  Il link per cambiare paziente, lascio l'add_progr vuoto , se sto ad esempio in una sub arriverï¿½ in una sub.
                 *  Il link per cambiare form , metto di default il PROGR=1 , se passo da una sub ad una form normale
                 */
                $add_progr = "";
                $add_progr_form = "&PROGR=1";
            } else {
                $add_progr_form = $add_progr = "&PROGR={$in['PROGR']}";
            }
            if ($next_esam != '') {
                $get_variables = strrchr($link, '?'); //vmazzeo 24.20.2015 aggiungo possibilità di inserire variabili get in link_to e link_to_send |ME|?variabile1=valore1|and|variabile2=valore2
                if ($get_variables != "") {
                    $get_variables = str_replace("?", "", $get_variables);
                    $get_variables = str_replace("|and|", "&", $get_variables);
                    $get_variables = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $get_variables);
                }
                $link = "index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&VISITNUM={$next_visit}&ESAM={$next_esam}{$add_progr_form}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$next_form}&{$get_variables}";
            }
            // 			var_dump($link);
            // 			echo "<hr/>";
            // 			//var_dump($vlist);
            // 			die();
        } else {
            $link = str_replace("|and|", "&", $link);
            $link = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $link);
        }

        if (count($this->errors) > 0)
            return false;
        if (isset ($in ['ajax_call']))
            die ("link_to:" . $link);
        else {
            $this->check_enable_visit();
            if (!($debug == 1)) {
                ob_clean();
                header('location:' . $link);
                $this->conn->commit();
                die();
                $filetxt = preg_replace("/<!--meta refresh-->/", "<meta http-equiv=\"refresh\" content=\"1;url=$link\">", $filetxt);
            }
        }
        global $link_to;
        $link_to = $link;
        $conn->commit();
        $this->body = ' &nbsp; Sending...';
        $this->body = "<table align=\"center\">
				<tr><td><div  style=\"text-align:center;width:220px;padding:30px;border:1px solid gray;margin:20px;\"><b>Sending ...</b> <br /><br /> <img  src=\"images/loading_bar.gif\" /></div></td></tr>
				<tr><td></td></tr>
				</table>";
        $filetxt = preg_replace("/<!--body-->/", $this->body, $filetxt);
        die ($filetxt);
    }

    /**
     * Operazioni da effettuare al cambio di stato
     *
     * @param number $dest
     */
    function StatusChangePostOperation($dest)
    {
        return;
    }

    /**
     * Gestisce le operazioni da effettuare all'"invio" della form
     *
     * @param String $xml_form_file
     * @param String $ajax_call
     */
    function SendForm($xml_form_file, $ajax_call = false)
    {
        $body = null;
        $filetxt = null;
        $link_to = null;

        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $xml_form_file);
        $this->session_vars ['INVIOCO'] = '1';
        $validata = false;
        $validata = $xml_form->valida();
        if ($validata) {
            //echo "sono qui";
            if ($this->invia_db($xml_form)) {

                $filetxt = preg_replace("/<!--body-->/", $body, $filetxt);
                if ($this->session_vars ['ajax_call'] != '')
                    die ("link_to:$link_to");
                echo $filetxt;
                die ();
            } else {
                if ($this->session_vars ['ajax_call'] != '') {
                    echo "Error:";
                    foreach ($xml_form->errors as $key => $val) {
                        die ($key . "#error#" . $val);
                    }
                }
            }
        } else {
            if ($this->session_vars ['ajax_call'] != '') {
                echo "Error:";
                foreach ($xml_form->errors as $key => $val) {
                    die ($key . "#error#" . $val);
                }
            } else
                foreach ($xml_form->errors as $key => $val) {
                    die ($key . "#error#" . $val);
                }
        }
    }

    /**
     * Gestisce le operazioni da effettuare al'"salva" della form
     *
     *
     *
     */
    function SaveForm($xml_form_file, $ajax_call = false, $forceSave = false)
    {
        $body = null;
        $filetxt = null;
        $link_to = null;

        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $xml_form_file);
        $this->session_vars ['INVIOCO'] = '1';
        $validata = false;
        $validata = $xml_form->valida();
        if ($validata) {
            if ($this->salva_db($xml_form, null, $forceSave)) {
                //TODO: codice morto
                $filetxt = preg_replace("/<!--body-->/", $body, $filetxt);
                if ($this->session_vars ['ajax_call'] != '')
                    die ("link_to:$link_to");
                echo $filetxt;
                die ();
            } else { //Questo else mi sembra completamente inutile
                if ($this->session_vars ['ajax_call'] != '') {
                    echo "Error:";
                    foreach ($xml_form->errors as $key => $val) {
                        die ($key . "#error#" . $val);
                    }
                }
            }
        } else {
//
//
//
//
            if ($this->session_vars ['ajax_call'] != '') {
                if ($xml_form->errors) {
                    foreach ($xml_form->errors as $key => $val) die ("Error:" . $key . "#error#" . $val);
                }
            }
            //print_r ( $this->errors );
        }
    }


    function doOmoCheck($xml_form)
    {
        $omoCheckFields = [];
        foreach ($xml_form->fields as $field) {
            if (isset($field['OMO_CHECK']) && $field['OMO_CHECK'] != '') {
                if ($field['TYPE'] == 'date_cal' || $field['TYPE'] == 'data') {
                    $omoCheckFields[$field['VAR']] = "to_char({$field['VAR']},'DDMMYYYY')";
                } else $omoCheckFields[$field['VAR']] = "upper({$field['VAR']})";
            }
        }

        if (count($omoCheckFields) > 0) {
            $where = "";
            foreach ($omoCheckFields as $var => $f) {
                if ($where != "") $where .= " and ";
                $where .= " $f = :{$var}";
                $bind["{$var}"] = $_POST[$var];
            }
            $sql_check_query = "select * from {$xml_form->form['TABLE']} where {$where}";

            $q = new query($this->conn);
            if ($q->get_row($sql_check_query, $bind)) {
                $msg = mlOut("System.form.checkOmo", "E' gia' presente un paziente con gli stessi dati anagrafici. Continuare con la registrazione?");
                echo "Confirm:omocheck:" . $msg;
                die();
            }
        }
        return true;
    }

    function doUniqueCheck($xml_form)
    {
        $uniqueCheckFields = [];
        foreach ($xml_form->fields as $field) {
            if (isset($field['UNIQUE_CHECK']) && $field['UNIQUE_CHECK'] != '') {
                if ($field['TYPE'] == 'date_cal' || $field['TYPE'] == 'data') {
                    $uniqueCheckFields[$field['VAR']] = "to_char({$field['VAR']},'DDMMYYYY')";
                } else $uniqueCheckFields[$field['VAR']] = "upper({$field['VAR']})";
            }
        }

        if (count($uniqueCheckFields) > 0) {
            $where = "";
            foreach ($uniqueCheckFields as $var => $f) {
                if ($where != "") $where .= " and ";
                $where .= " $f = :{$var}";
                $bind["{$var}"] = $_POST[$var];
            }
            $sql_check_query = "select * from {$xml_form->form['TABLE']} where {$where}";

            $q = new query($this->conn);
            if ($q->get_row($sql_check_query, $bind)) {
                $msg = mlOut("System.form.univoco", "Non e' possibile proseguire in quanto il controllo di univocita' ha dato esito negativo");
                echo "Error:" . $msg;
                die();
            }
        }
        return true;

    }


    /**
     * Effettua il salvataggio in DB (gestione invio)
     */
    function invia_form($xml_form, $in_s)
    {
        $config = null;
        $session_vars = null;

        $conn = $this->conn;
        //$in = $this->in;
        //		global $config_service;
        $in = $in_s;
        $debug = 1;

        //Controllo che l'utente loggato possa fare DE
        if ($in['USER_TIP'] != "DE" && !isset($in['ID_QUERY'])) {
            $message = "Current profile does not allow Data Entry.";
            if ($in['ajax_call'] != '') {
                echo "Error:#error#";
                die($message);
            } else {
                error_page($this->user->userid, $message, array());
            }
        }

        /*Chiamata dell'oggetto audit trail per salvare i dati nella tabella relativa, storico per singolo campo valente per ogni tabella dello studio*/
        $needATRegistration = false;
        $audit_trail = new audit_trail($this->service, $this->conn, $this->config_service, $this->vlist);
        if ($_POST[$xml_form->PK_SERVICE] != 'next') {
            $audit_trail->audit_trail_difference($xml_form);
        } else {
            //Registration form -> call postponed when I've a PKEY value!
            $needATRegistration = true;
        }

        if ($in['ajax_call']) {
            if (!$in['omocheck'] || $in['omocheck'] != 'skip') $this->doOmoCheck($xml_form);
            $this->doUniqueCheck($xml_form);
        }

        $f_to_call_pre = $xml_form->form ['F_TO_CALL_PRE'];
        if ($f_to_call_pre != "") {
            $this->conn->commit();
            $this->conn->close();
            if ($xml_form->session_vars['PROGR'] == '') $xml_form->session_vars['PROGR'] = 1;
            if ($xml_form->session_vars['VISITNUM_PROGR'] == '') $xml_form->session_vars['VISITNUM_PROGR'] = 0;
            foreach ($xml_form->session_vars as $key => $val) {
                $vars[$key] = $val;
            }
            include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/activitiClient.inc";
            $service = new ActivitiService("admin", "xxx");
            $vars['connectId'] = 'devService';
            $vars['studyPrefix'] = $this->service;
            $vars['pkService'] = $this->config_service['PK_SERVICE'];
            if (!isset($xml_form->session_vars['ajax_call'])) $vars['ajax_call'] = '';
            $this->LaunchActivitiProcess($service, $f_to_call_pre, $vars);
            $this->reopenConn();
            $conn = $this->conn;
        }

        /*
         * Riapertura della firma elettronica
        *
        * Verrocchio 05/07/2011 Verri 05/07/2013
        */
        if (isset ($in[$this->config_service['PK_SERVICE']]) && $in[$this->config_service['PK_SERVICE']] != 'next') {
            $electronic_signature_esam = array();
            $visite_exams_path = str_replace("index.php", "", $_SERVER['SCRIPT_FILENAME']) . "xml/visite_exams.xml";
            $vlist = new xml_esams_list ($visite_exams_path, $config, $session_vars, $conn);
            /*Numero dell'esame skip_visit della visita*/
            $visit_num = array();
            foreach ($vlist->esams as $key => $val) {
                foreach ($val as $k => $v) {
                    if ($v['XML'] == 'esign.xml') {
                        $electronic_signature_esam[$key] = $v['NUMBER'];
                    }
                }
            }
            // Per tutte le signature
            foreach ($electronic_signature_esam as $visit_num => $esam_num) {
                $query = new query ($this->conn);
                unset($vals);
                $vals['PK_SERVICE'] = $in[$this->config_service['PK_SERVICE']];
                $vals['VISITNUM'] = $visit_num;
                $vals['ESAM'] = $esam_num;
                //$vals['PROGR'] = $this->session_vars['PROGR'];
                //$vals['VISITNUM_PROGR'] = $this->session_vars['VISITNUM_PROGR'];
                $sql_query = "SELECT * FROM {$this->config_service['service']}_COORDINATE WHERE {$this->config_service['PK_SERVICE']}=:PK_SERVICE AND ESAM=:ESAM and VISITNUM=:VISITNUM";
                $query->exec($sql_query, $vals);
                $query->get_row();
                if ($query->row['FINE'] == 1) {
                    // Riapro la Electronic Signature
                    $query = new query ($this->conn);
                    unset($vals);
                    $vals['CENTER'] = $this->session_vars['CENTER'];
                    $vals[$this->config_service['PK_SERVICE']] = $this->session_vars[$this->config_service['PK_SERVICE']];
                    $vals['VISITNUM'] = $visit_num;
                    $vals['ESAM'] = $esam_num;
                    $sql_query = "UPDATE {$this->service}_COORDINATE SET FINE='' WHERE SUBSTR(USERID, 0, 3)=:CENTER AND {$this->config_service['PK_SERVICE']}=:{$this->config_service['PK_SERVICE']} AND VISITNUM=:VISITNUM AND ESAM=:ESAM";
                    $query->exec($sql_query, $vals);

                    $query = new query ($this->conn);
                    unset($vals);
                    $vals['CENTER'] = $this->session_vars['CENTER'];
                    $vals[$this->config_service['PK_SERVICE']] = $this->session_vars[$this->config_service['PK_SERVICE']];
                    $vals['VISITNUM'] = $visit_num;
                    $sql_query = "UPDATE {$this->service}_COORDINATE SET VISITCLOSE='0' WHERE SUBSTR(USERID, 0, 3)=:CENTER AND {$this->config_service['PK_SERVICE']}=:{$this->config_service['PK_SERVICE']} AND VISITNUM=:VISITNUM";
                    $query->exec($sql_query, $vals);
                }
            }
        }
        $this->audit_trail($xml_form);
        $query = new query ($conn);
        if ($this->config_service['de_modify_form_allowed'] == true && $in['USER_TIP'] == 'DE' && isset($in['ID_QUERY']) && $in['ID_QUERY'] != '') {
            $xml_form->query_builder(true);
        } else {
            $xml_form->query_builder();
        }
        $audit_trail->CheckVisitIsClose($in, $xml_form);
        $this->errors = $xml_form->getErrors();
        //		global $config_service;
        $this->addSendCoordInfo($xml_form, $in);

        if ($needATRegistration && !$in['ajax_call']) {
            //Recupero l'ultimo valore della sequence
            //select seq_test.currval from dual
            $sql_query = "SELECT {$this->service}_PK_SEQ.currval AS CVAL from dual";
            $query->exec($sql_query, array());
            $query->get_row();
            $cval = $query->row['CVAL'];

            $_POST[$xml_form->PK_SERVICE] = $cval;
            $in[$xml_form->PK_SERVICE] = $cval;
            $query = new query ($conn);

        }
        /*
		if (!isset($_POST['ajax_call']) || $_POST['ajax_call']==''){
			$sql_update="update {$this->service}_COORDINATE set SEND_DT=sysdate, CREATE_USER=:USER_ where {$this->config_service['PK_SERVICE']}=:PK_SERVICE and VISITNUM=:VISITNUM and ESAM=:ESAM and PROGR=:PROGR and VISITNUM_PROGR=:VISITNUM_PROGR";
			$bind['PK_SERVICE']=$xml_form->session_vars[$this->config_service['PK_SERVICE']];
			$bind['VISITNUM']=$in['VISITNUM'];
			if ($in['VISITNUM_PROGR']=='') $in['VISITNUM_PROGR']=0;
			if ($in['PROGR']=='') $in['PROGR']=1;
			$bind['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
			$bind['PROGR']=$in['PROGR'];
			$bind['ESAM']=$in['ESAM'];
			$bind['USER_']=$this->user->userid;
			$sql=new query($this->conn);
			$sql->ins_upd($sql_update, $bind);
		}
		*/


        $f_to_call = $xml_form->form ['F_TO_CALL'];

        if (function_exists($f_to_call)) {
            $f_to_call ($xml_form);
        } elseif ($f_to_call != "") {
            $this->conn->commit();
            $this->conn->closeConnection();
            if ($xml_form->session_vars['PROGR'] == '') $xml_form->session_vars['PROGR'] = 1;
            if ($xml_form->session_vars['VISITNUM_PROGR'] == '') $xml_form->session_vars['VISITNUM_PROGR'] = 0;
            foreach ($xml_form->session_vars as $key => $val) {
                $vars[$key] = $val;
            }
            include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/activitiClient.inc";
            $service = new ActivitiService($this->config_service['AWFBaseURL'], $this->config_service['AWFUsername'], $this->config_service['AWFPassword']);
            $vars['connectId'] = $this->config_service['AWFConnectionId'];
            $vars['studyPrefix'] = $this->config_service['service'];
            $vars['pkService'] = $this->config_service['PK_SERVICE'];
            if (!isset($xml_form->session_vars['ajax_call'])) $vars['ajax_call'] = '';
            $this->LaunchActivitiProcess($service, $f_to_call, $vars);
            $this->reopenConn();
            $conn = $this->conn;
            $audit_trail = new audit_trail($this->service, $this->conn, $this->config_service, $this->vlist);
        }

        /*Chiamata dell'oggetto audit trail per salvare i dati nella tabella relativa, storico per singolo campo valente per ogni tabella dello studio*/
        if ($needATRegistration && !$in['ajax_call']) {
            //print_r($_POST);
            //print_r($in);
            //die();
            $audit_trail->audit_trail_difference($xml_form);
        }
        for ($i = 0; $i < count($xml_form->query_enable); $i++) {
            $query = new query ($conn);
            $query->set_sql($xml_form->query_enable [$i]);
            $query->ins_upd();//non richiede binding
        }

        //Invio mail generico
        if (!$in['ajax_call']) {
            $this->sendGenericMail($in['VISITNUM'], $in['ESAM'], "SEND", false, false, $in, false);
        }

    }

    /**
     * Controlla la chiusura delle visite (obsoleta)
     *
     */
    function check_visit_closure()
    {
        $this->check_enable_visit();
    }

    /**
     * Controlla l'abilitazione delle visite
     *
     */
    function check_enable_visit()
    {
        $exams = null;

        if ($this->session_vars [$this->config_service ['PK_SERVICE']] == 'next')
            return;
        $conn = $this->conn;
        $filetxt = $this->config_service ['filetxt'];
        $in = $this->session_vars;
        $service = $this->service;
        $xml_dir = $this->xml_dir;
        $config_service = $this->config_service;
        $mand_exams = array();
        foreach ($this->vlist->esams [$in ['VISITNUM']] as $key => $val) {
            if (isset ($val ['MANDATORY']) && $val ['MANDATORY'] == 'yes')
                $mand_exams [$key] = "yes";
        }
        foreach ($mand_exams as $key => $val) {
            $exams .= "$key,";
        }
        $exams = rtrim($exams, ",");
        if ($exams != '') {
            $sql = "select min(nvl(fine,0)) as fine from {$service}_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service and VISITNUM=:visitnum and esam in ($exams)";
            $query = new query ($conn);
            unset($bind);
            $bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
            $bind['VISITNUM'] = $in['VISITNUM'];

            //$query->set_sql ( $sql );
            $query->exec($sql, $bind);//binded
            $query->get_row();
            $fine = $query->row ['FINE'];
            //echo "<li>$sql</li>";
            //echo $query->tb_res();
            if ($fine == 1) {
                foreach ($this->vlist->enable_visit [$in ['VISITNUM']] as $key => $val) {
                    $number_visit = $val ['NUMBER'];
                    $progr_visit = $val ['PROGR'];
                    $abilita = false;
                    //print_r($val);
                    if ($val ['CONDITION_VALUE'] != '') {
                        $condition_value = $val ['CONDITION_VALUE'];

                        $condition_value = str_replace(",", "','", $condition_value);

                        $condition_value = "'$condition_value'";

                        $conditions = explode(".", $val ['CONDITION']);
                        //print_r($conditions);
                        $condition_var = $conditions [1];
                        $condition_table = $conditions [0];
                        $sql_query = "
						select
							count(*) as conto
						from {$service}_{$condition_table}
						where
						{$config_service['PK_SERVICE']}=:pk_service
							and {$service}_{$condition_table}.{$condition_var} in ($condition_value)
							";
                        unset($bind);
                        $bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];

                        $sql = new query ($conn);
                        //$sql->set_sql ( $sql_query );
                        $sql->exec($sql_query, $bind);//binded

                        //echo "<li>$sql_query</li>";
                        //echo $sql->tb_res();
                        $sql->get_row();
                        if ($sql->row ['CONTO'] > 0)
                            $abilita = true;
                    } else {
                        $abilita = true;
                    }
                    if ($abilita && ($val ['AUTO'] == 'yes' || (isset ($in ['CLOSE_VISIT']) && $in ['CLOSE_VISIT'] == $in ['VISITNUM']))) {
                        foreach ($this->vlist->esams [$number_visit] as $key_e => $val_e) {
                            if ($val_e ['DEFAULT'] == "yes") {
                                $sql_controllo = "
									select
										count(*) as conto
									from {$service}_coordinate where
									{$config_service['PK_SERVICE']}=:pk_service
									   and visitnum=:visitnum
									   and visitnum_progr=:visitnum_progr
									   and esam=:esam
									   and progr=1
								";
                                unset($bind);
                                $bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                                $bind['VISITNUM'] = $number_visit;
                                $bind['VISITNUM_PROGR'] = $progr_visit;
                                $bind['ESAM'] = $val_e['NUMBER'];
                                $query = new query ($conn);
                                $query->set_sql($sql_controllo);
                                $query->exec($sql_controllo, $bind); //binded
                                //echo "<li>$sql_controllo</li>";
                                //echo $query->tb_res();
                                $query->get_row();
                                if ($query->row ['CONTO'] == 0) {
                                    $sql_update = "
										insert into {$service}_coordinate
											(VISITNUM, VISITNUM_PROGR, ESAM, PROGR, {$config_service['PK_SERVICE']}, ABILITATO)
										values
											(:visitnum, :visitnum_progr, :esam, 1, :pk_service,1)
									";
                                    //echo "<li>$sql_update</li>";
                                    $query = new query ($conn);
                                    $query->ins_upd($sql_update, $bind);//binded
                                }
                            }
                        }
                    }
                }
                /*
				 $sql="select * from {$service}_COORDINATE where {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}'";
				 $query=new query($conn);
				 $query->set_sql($sql);
				 $query->exec();//commentata
				 echo $query->tb_res();
				 */
                //TODO: Qui ci va una parte del drug-registry!
            }
        }
    }

    /**
     * Restituisce il codice html della form in visualizzazione
     *
     * @param number $esam
     * @param number $visitnum
     * @param number $visitnum_progr
     * @param number $progr
     * @return String
     */
    function printable_form($esam, $visitnum, $visitnum_progr, $progr, $footer_header = false)
    {
        $_GET ['ESAM'] = $this->session_vars ['ESAM'] = $esam;
        $_GET ['VISITNUM'] = $this->session_vars ['VISITNUM'] = $visitnum;
        $_GET ['VISITNUM_PROGR'] = $this->session_vars ['VISITNUM_PROGR'] = $visitnum_progr;
        $_GET ['PROGR'] = $this->session_vars ['PROGR'] = $progr;
        $form = $this->vlist->esams [$visitnum] [$esam] ['XML'];
        if (is_array($this->vlist->esams [$visitnum][0][$esam])) {

            $form = $this->vlist->esams [$visitnum][0][$esam]['XML'];
        };
        $pt_info = $this->evaluate_pt($form);
        $form = $pt_info['XML'];
        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $form);
        if ($xml_form->form['PDF_PREPARE']) {
            $func = $xml_form->form['PDF_PREPARE'];
            if (method_exists($this, $func)) {
                $xml_form = $this->$func($xml_form);
            }
        }
        $xml_form->make_html(true, true);
        if ($footer_header) {
            $prepend = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $xml_form->header);
            $append = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $xml_form->footer);
        }
        if ($xml_form->form['PDF_TEMPLATE'] != '') {
            $template = $xml_form->form['PDF_TEMPLATE'];
            $pt_template = $template . $pt_info['SUFFIX'];
            if (file_exists($pt_template . '.html')) $template = $pt_template;

            $template = file_get_contents($template . '.html');
            $xml_form->body = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $template);
        }

        unset ($_GET ['ESAM']);
        unset ($_GET ['VISITNUM']);
        unset ($_GET ['VISITNUM_PROGR']);
        unset ($_GET ['PROGR']);
        return $prepend . $xml_form->body . $append;
    }


    function printable_form_esam($esam, $visitnum, $visitnum_progr, $progr)
    {
        Logger::info($this->session_vars);
        $_GET['ESAM'] = $this->session_vars['ESAM'] = $esam;
        $_GET['VISITNUM'] = $this->session_vars['VISITNUM'] = $visitnum;
        $_GET['VISITNUM_PROGR'] = $this->session_vars['VISITNUM_PROGR'] = $visitnum_progr;
        $_GET['PROGR'] = $this->session_vars['PROGR'] = $progr;
        $form = $this->vlist->esams[$visitnum][$esam]['XML'];
        //Logger::info($this->session_vars);
        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $form);

        if (isset($this->vlist->esams[$visitnum][$esam]['ALL_IN']) && $this->vlist->esams[$visitnum][$esam]['ALL_IN'] != "") {
            $xml_form->body = $this->AllInPrintableForm($xml_form, $esam, $visitnum, $visitnum_progr, $progr);

            $xml_form->body = "<table style='width:100% ;' align=center ><tr><td>" . $xml_form->body . "</td></tr></table>";
        } else {
            $xml_form->make_html(true, true);
            unset($_GET['ESAM']);
            unset($_GET['VISITNUM']);
            unset($_GET['VISITNUM_PROGR']);
            unset($_GET['PROGR']);
            $xml_form->body = "<table style='width:100% ;' align=center ><tr><td>" . $xml_form->body . "</td></tr></table>";

        }
        return $xml_form->body;
    }


    /**
     * Genera il codice html di tutte le schede compilate in visualizzazione
     *
     * @param String $service
     * @return String
     */
    function view_all($service = null, $vlist = null)
    {
        $ret = null;
        if ($service == '')
            $service = $this->config_service ['service'];
        $sql_query = "select visitnum, esam, visitnum_progr, progr from {$service}_coordinate where fine=1 and {$this->config_service['PK_SERVICE']}=:pk_service order by progr asc";
        $sql = new query ($this->conn);
        unset($bind_pk);
        $bind_pk['PK_SERVICE'] = $this->pk_service;
        $sql->exec($sql_query, $bind_pk);//binded
        while ($sql->get_row()) {
            $res [$sql->row ['VISITNUM']] [$sql->row ['VISITNUM_PROGR']] [$sql->row ['ESAM']] [$sql->row ['PROGR']] = true;
        }
        if (!isset($vlist)) $vlist = $this->vlist;
        foreach ($vlist->visitnums as $visitnum => $visitnum_val) {
            if (isset($res[$visitnum])) {
                foreach ($res[$visitnum] as $visitnum_progr => $vprogr_val) {
                    foreach ($vlist->esams[$visitnum] as $esam => $es_val) {
                        if (isset($res[$visitnum][$visitnum_progr][$esam])) {
                            if (count($res[$visitnum][$visitnum_progr][$esam]) > 1) $multiple = true;
                            else $multiple = false;
                            foreach ($res[$visitnum][$visitnum_progr][$esam] as $progr => $progr_val) {
                                if ($multiple) $ret .= "<li><b>Scheda n.ro $progr</b></li>";
                                $ret .= $this->printable_form($esam, $visitnum, $visitnum_progr, $progr, $service, $vlist);
                            }
                        }
                    }
                }
            }
        }
        return $ret;

    }

    /**
     * Genera il codice html di tutte le schede compilate in visualizzazione
     * COMPRESI I SOTTOSTUDI
     *
     * @param String $service
     * @return String
     */
    function view_all_services($services)
    {
        $config = null;
        $ret = null;
        foreach ($services as $key => $val) {
            if ($val == $this->xmr_root->prefix) {
                $vlist = new xml_esams_list ($this->xml_dir . '/' . $this->visit_structure_xml, $config, $this->session_vars, $this->conn);
            } else {
                $vlist = new xml_esams_list ($this->xml_dir . '/' . $val . '/' . $this->visit_structure_xml, $config, $this->session_vars, $this->conn);
            }
            $ret .= $this->view_all($val, $vlist);
        }
        return $ret;
    }


    function crf($landscape = null)
    {
        if ($_GET['CRF'] == 1) {
            //Luigi: CRF globale
            if (isset($_GET['PATID'])) {
                //Il PATID è utilizzato per le creazioni multiple (di più pazienti)
                $table_exist = "select {$this->config_service['PK_SERVICE']} as SUBJID,CENTER from {$this->service}_REGISTRAZIONE where CODPAT=:CODPAT";
                $sql_exist = new query($this->conn);
                $bind[$this->config_service ['PK_SERVICE']] = $this->pk_service;
                $sql_exist->exec($table_exist, $bind);
                $sql_exist->get_row();
                $return = "<!-- HEADER RIGHT \"Patient Code: {$sql_exist->row['SUBJID']} Center: {$sql_exist->row['CENTER']}\" -->";
            }
            if (isset($this->config_service['HEADER_DATE']) && $this->config_service['HEADER_DATE'] == true) $return .= "<!-- HEADER LEFT \"Date: " . date("d/m/Y G:i") . "\" -->";
            $service = $this->service;
            $sql_query = "select visitnum, esam, visitnum_progr, progr from {$service}_coordinate where fine=1 and {$this->config_service['PK_SERVICE']}={$this->pk_service} order by progr asc";
            $sql = new query ($this->conn);
            $sql->exec($sql_query);
            while ($sql->get_row()) {
                $res [$sql->row ['VISITNUM']] [$sql->row ['VISITNUM_PROGR']] [$sql->row ['ESAM']] [$sql->row ['PROGR']] = true;
            }
            $html = "";
            $header = "";
            foreach ($this->vlist->visitnums as $visitnum => $visitnum_val) {

                if (isset ($res [$visitnum])) {
                    $html .= "<page backtop=\"35mm\" backbottom=\"10mm\">$header";
                    $html .= "<bookmark title=\"{$this->vlist->visitnums[$visitnum]['TEXT']}\" level=\"0\" ></bookmark>";

                    foreach ($res [$visitnum] as $visitnum_progr => $vprogr_val) {

                        foreach ($this->vlist->esams [$visitnum] as $esam => $es_val) {

                            if (isset ($res [$visitnum] [$visitnum_progr] [$esam])) {

                                if (count($res [$visitnum] [$visitnum_progr] [$esam]) > 1)
                                    $multiple = true;
                                else
                                    $multiple = false;
                                foreach ($res [$visitnum] [$visitnum_progr] [$esam] as $progr => $progr_val) {

                                    #GENHD-374 - 13/10/2017 magnifynig glass near to Patient View does not produce Patient report
                                    global $in;
                                    $in['ESAM'] = $esam;
                                    $in['VISITNUM'] = $visitnum;
                                    $in['VISITNUM_PROGR'] = $visitnum_progr;
                                    $in['PROGR'] = $progr;
                                    #END

                                    $nomeEsame = $this->vlist->esams[$visitnum][$esam]['TESTO'];
                                    $nomeEsame = rtrim($nomeEsame, "\n");
                                    $nomeEsame = rtrim($nomeEsame, "\r");

                                    $nomeEsame = rtrim($nomeEsame, "\s");
                                    $nomeEsame = ltrim($nomeEsame, "\n");

                                    $testoForm = "<b>{$this->vlist->visitnums[$visitnum]['TEXT']} - <i>{$nomeEsame}</i></b>";
                                    if ($multiple) {
                                        $html .= "<bookmark title=\"$nomeEsame $progr\" level=\"1\" ></bookmark>";
                                        $testoForm .= " {$progr}";
                                    } else {
                                        $html .= "<bookmark title=\"$nomeEsame\" level=\"1\" ></bookmark>";
                                    }

                                    $form = $this->printable_form($esam, $visitnum, $visitnum_progr, $progr, $service);
                                    $form = str_replace('<table border=0 width=100%><tr><td align="center">', "", $form);
                                    $form = str_replace("<table style='width:100% ;' align=center ><tr><td><form method=\"post\">", "", $form);
                                    $form = str_replace("class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\"", "", $form);
                                    $html .= "<div class=\"form-title\">{$testoForm}</div><div class=\"form-content\">{$form}</div>";

                                    //AUDITRAIL (COMPATIBILE SOLO CON WKHTML2PDF)
                                    if (isset($this->config_service['CRF_AUDIT_TRAIL']) && $this->config_service['CRF_AUDIT_TRAIL'] == true) {
                                        $examfile = (string)$this->vlist->esams[$visitnum][$esam]['XML'];
                                        $examfilexml = simplexml_load_file("xml/{$examfile}") or die("visite_exams.xml not loading");
                                        //print_r($examfilexml);
                                        $nometab = $examfilexml['table'];
                                        foreach ($examfilexml->field as $field_key => $field) {
                                            //echo $field['var']." ".$field["type"]."</br>";
                                            //echo $progr."</br>";
                                            $html .= audit_trail_popup($field, "{$this->service}_" . $nometab, $_GET[$this->config_service ['PK_SERVICE']], $visitnum, $visitnum_progr, $esam, $progr);
                                        }
                                    }

                                    $html .= '<div style="width:100%;page-break-after:always" align="center"></div>';
                                }
                            }

                        }
                        //$html.="</page>";
                    }
                    $html .= "</page>";
                    $last_visitnum = $visitnum;
                }
            }

            $return .= $html;
//		echo $return;
//		die();
        } else if ($_GET['CRF'] == 2 && isset($_GET['ESAM']) && isset($_GET['VISITNUM']) && isset($_GET['PROGR'])) {
            if ($_GET['VISITNUM_PROGR'] == '') $_GET['VISITNUM_PROGR'] = 0;
            $return = $this->printable_form_esam($_GET['ESAM'], $_GET['VISITNUM'], $_GET['VISITNUM_PROGR'], $_GET['PROGR']);
        }
        //$doc_template = file_get_contents('./doc_template.htm');
        $doc_template = "<!--style-->
<!--body-->";
        $return = preg_replace("/<!--body-->/", $return, $doc_template);
//		echo $return;
//		die();
        if (isset($_GET['PDF'])) {

            $this->embedAndCreatePDF($return, $this->config_service ['PK_SERVICE'] . "_" . $this->pk_service);

        } else {
            return $return;
        }

    }


    function crf_blank()
    {
        $return = "<div id='crf_blank'>";
        foreach ($this->vlist->esams as $k => $v) {
            $visitnum = $this->vlist->visitnums[$k]['NUMBER'];
//						echo '<br>'.$visitnum.'<br>';
//						print_r($this->vlist->visitnums[$k]['TEXT'] );
            $visitname = $this->vlist->visitnums[$k]['TEXT'];
            /*$return.="<p style=\"page-break-before:always\"></p>";
				$return.="<table align=\"center\" width=\"100%\"><tr><td><div  style='width:520px;
						padding:50px;
						border:1px solid gray;
						margin:250px;margin-top:500px;text-align:center;font-size: xx-large;'> $visitname </div></td></tr>
						<tr><td></td></tr>
						<table>";
				$return.="<p style=\"page-break-before:always\"></p>";


				*/

            $return .= "<div class='page-header left'> <h1>$visitname</h1> </div>";

            foreach ($v as $ke => $va) {
                $esam = $this->vlist->esams[$k][$ke]['NUMBER'];
                $form = $this->vlist->esams[$k][$ke]['XML'];
//							echo $esam;
                $return .= $this->printable_form_blank($esam, $visitnum, 1, 1, $form);

                $return .= "<p style=\"page-break-before:always;\"></p>";
            }

            //$return.="<p style=\"page-break-before:always\"></p>";
        }
        $return .= "</div>";
        $return .= "<script type=\"text/javascript\">";
        $return .= "$('#sidebar').hide();";
        $return .= "$('.main-content').addClass('main-content-nomarginleft');";
        $return .= "$('.main-content').css('margin-left','0');";
        $return .= '</script>';

        if ($_GET['PDF']) {
            $this->embedAndCreatePDF($return, "BLANK");
        }

        return $return;
    }

    function printable_form_blank($esam, $visitnum, $visitnum_progr, $progr, $form)
    {
        $return = "<div class='page-header center' style='margin-top:10px'> <h1>{$this->vlist->esams[$visitnum][$esam]['TESTO']}</h1> </div>";
        $_GET['ESAM'] = $this->session_vars['ESAM'] = $esam;
        $_GET['VISITNUM'] = $this->session_vars['VISITNUM'] = $visitnum;
        $_GET['VISITNUM_PROGR'] = $this->session_vars['VISITNUM_PROGR'] = $visitnum_progr;
        $_GET['PROGR'] = $this->session_vars['PROGR'] = $progr;

        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $form);

        $xml_form->make_html(true, true);
        unset($_GET['ESAM']);
        unset($_GET['VISITNUM']);
        unset($_GET['VISITNUM_PROGR']);
        unset($_GET['PROGR']);
        $form = "<div>" . $xml_form->body . "</div>";
        $form = str_replace('</div></p>', "", $form);
        //$xml_form->body = "".$xml_form->body."";
        $return .= $form;
        return $return;
    }

    function embedAndCreatePDF($content, $title)
    {
        $prefix = $this->service;
        $html = '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
                <html>
                <head><TITLE>' . $prefix . '</TITLE></head>
                ';
        $html .= '
        <!--<link href="../../../assets/css/bootstrap-responsive.css" rel="stylesheet">-->
        <link href="../../../assets/css/bootstrap.min.css" rel="stylesheet">
            <style>
                body {
                    padding-right: 0px;
                    padding-left: 0px;
                }
                #form_a_t{display:none;}
                #baseAuditRecordLog{display:none;}
            </style>
            <!-- basic styles -->
            <!--link href="../../../assets/css/bootstrap.min.css" rel="stylesheet" /-->
            <link href="../../../assets/css/font-awesome-4.0.3.css" rel="stylesheet">
            <link rel="stylesheet" href="../../../assets/css/font-awesome.min.css" />
            <!--[if IE 7]>
            <link rel="stylesheet" href="../../../assets/css/font-awesome-ie7.min.css" />
            <![endif]-->
            <!-- page specific plugin styles -->
            <!-- fonts -->
            <link rel="stylesheet" href="../../../assets/css/openFont.css" />
            <!-- ace styles -->
            <link rel="stylesheet" href="../../../assets/css/ace.min.css" />
            <!--<link rel="stylesheet" href="../../../assets/css/ace-rtl.min.css" />-->
            <link rel="stylesheet" href="../../../assets/css/ace-skins.min.css" />
            <!-- forms additional css -->
            <link rel="stylesheet" href="../../../assets/css/jquery-ui-1.10.3.custom.min.css" />
            <link rel="stylesheet" href="../../../assets/css/chosen.css" />
            <link rel="stylesheet" href="../../../assets/css/datepicker.css" />
            <link rel="stylesheet" href="../../../assets/css/bootstrap-timepicker.css" />
            <link rel="stylesheet" href="../../../assets/css/daterangepicker.css" />
            <link rel="stylesheet" href="../../../assets/css/colorpicker.css" />
            <link rel="stylesheet" href="../../../assets/css/flag-icon.min.css" />
            <link rel="stylesheet" href="../../../assets/css/select2.css" />
            <link rel="stylesheet" href="libs/css/std.css" />
            <style>
                body {
                    font-size: 14px;
                    width:1280px;
                }
                .col-sm-1,.col-sm-2,.col-sm-3,.col-sm-4,.col-sm-5,.col-sm-6,.col-sm-7,.col-sm-8,.col-sm-9,.col-sm-10,.col-sm-11,.col-sm-12{
                    /* min-height: 26px; */
                    margin-bottom: 4px;
                    margin-top: 4px;
                }
                .form-horizontal .control-label{
                    padding: 0px;
                    padding-right: 4px;
                }
                label{
                    font-size: 14px;
                    /* max-width: 50%; */
                }
                .block_reopen_form{display:none;}
                .block_eq_panel{display:none;}
                form{
                    width: 100%; /* 600px; */
                }
                div[id^=tr_]{
                    clear:both;
                }
                #main-container{
                    width:100%;
                }
                .main-container-inner, .page-content, .row{
                    width:100%;
                }
                .textfield{
                    font-weight: bold;
                }
                .selectedOption{
                    font-weight: bold;
                }
            </style>
            ';
        $html .= '<body><div style="width:100%;">';
        $html .= '<div class="main-container" id="main-container" >';
        $html .= '<div class="main-container-inner" >';
        $html .= '<div class="page-content" >';
        $html .= '<div class="row" >';

        $html .= $content;

        //echo "<pre>{$siteid} - {$subjid}</pre>";die();
        $html .= '</div>';
        $html .= '</div>';
        $html .= '</div>';
        $html .= '</div>';

        $html .= "</div></body>";

        $tmpCartella = "{$_SERVER['DOCUMENT_ROOT']}/wkpdftmp/{$prefix}/";
        if (!file_exists($tmpCartella . "templates")) {
            mkdir($tmpCartella . "templates", 0775, true);
            exec("chgrp -R devj {$tmpCartella}", $retval);
            exec("chgrp -R devj {$tmpCartella}templates", $retval);
            exec("chmod -R ug+w {$tmpCartella}", $retval);
            exec("chmod -R ug+w {$tmpCartella}templates", $retval);
        }
        //$attachName = str_replace(" ", "_", str_replace("'", "", str_replace("/", "", $nomeEsame)));
        $tmph = "PDF_{$title}.html";
        $tmp = "PDF_{$title}.pdf";
        $filenamehtml = "{$tmpCartella}{$tmph}";
        $headerhtmlSTD = "{$tmpCartella}templates/pdf_header_FORM.html";
        //echo "<pre>";print_r($filenamehtml);echo "<hr/>";print_r($headerhtmlSTD);echo "</hr>";die();
        $footerhtml = "{$tmpCartella}templates/pdf_footer_FORM.html";
        $filename = "{$tmpCartella}{$tmp}";
        $headerTxt = file_get_contents($headerhtmlSTD);
        //$headerTxt = str_replace("[SITEID]",$siteid,$headerTxt);
        //$headerTxt = str_replace("[SUBJID]",$subjid,$headerTxt);
        //$headerTxt = str_replace("[VISIT_NAME]",$nomeVisita,$headerTxt);
        $headerTxt = str_replace("[CODPAT]", $_GET[$this->config_service ['PK_SERVICE']], $headerTxt);
        $headerTxt = str_replace("[PREFIX]", $prefix, $headerTxt);
        $headerhtml = "{$tmpCartella}pdf_header_{$title}_" . date("Y-m-d-h-i-s") . ".html";
        //die($headerTxt);
        file_put_contents("{$headerhtml}", $headerTxt);

        file_put_contents("{$filenamehtml}", $html);
        //--disable-external-links --outline --toc
        $command = $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/wkhtmltopdf --page-size A4 --viewport-size 1280x1024 -O portrait  --disable-javascript --header-html {$headerhtml}  --encoding UTF8 -q --margin-top 25mm --margin-bottom 15mm --margin-left 15 --margin-right 15 --footer-font-size 8 --footer-left \"{$title} - {$prefix}\" --footer-right \"CINECA - [page]/[topage]\"  {$filenamehtml} {$filename}";
        //die($command);
        $last_line = system($command, $retval);
        exec("chgrp -R devj {$filenamehtml}", $retval);
        exec("chgrp -R devj {$filename}", $retval);
        exec("chmod -R ug+w {$filenamehtml}", $retval);
        exec("chmod -R ug+w {$filename}", $retval);
        //exec("rm {$filenamehtml}", $retval);
        system("pdfopt {$tmpCartella}_TEMP_{$tmp} {$tmpCartella}{$tmp}");


        if ($filename) {
            $ext = strrchr($filename, ".");
            switch ($ext) {
                case "pdf":
                    $ctype = "application/pdf";
                    break;
                case "exe":
                    $ctype = "application/octet-stream";
                    break;
                case "zip":
                    $ctype = "application/zip";
                    break;
                case "doc":
                case "docx":
                    $ctype = "application/msword";
                    break;
                case "xls":
                case "xlsx":
                    $ctype = "application/vnd.ms-excel";
                    break;
                case "ppt":
                    $ctype = "application/vnd.ms-powerpoint";
                    break;
                case "gif":
                    $ctype = "image/gif";
                    break;
                case "png":
                    $ctype = "image/png";
                    break;
                case "jpeg":
                case "jpg":
                    $ctype = "image/jpg";
                    break;
                default:
                    $ctype = "application/force-download";
            }

            $data = file_get_contents($filename);
            ob_clean();
            header("Pragma: public");
            header("Expires: 0");
            header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
            header("Content-Type: $ctype");
            header("Content-Description: File Transfer");
            header("Content-Disposition: attachment; filename=\"$tmp\"");
            header("Accept-Ranges: bytes");
            header("Content-Length: " . strlen($data));
            header("Content-Transfer-Encoding: binary");

            die($data);
        }

    }


    /**
     * Gestione equery
     *
     * @return String
     */
    function Equery()
    {
        $html = '';
        $in = $this->session_vars;
        $service = $this->service;
        $percorso = $this->breadcrumb("equery");
        $remote_userid = $in ['remote_userid'];
        if (!isset ($in ['eform'])) {
            if (isset ($in ['closed'])) {
                $open = false;
                $sql_rec = "
				select e.ID,
					e.REGISTRY,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.{$this->config_service['PK_SERVICE']},
			       e.CENTER,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.QUEST_DT,
			       E.ANS_DT,
			       E.CHIUSA_DT
			  from {$this->xmr_root->prefix}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			 where e.q_userid <> :userid
			   and e.chiusa=1
			   and c.center = e.center
			   and uc.center = c.center
			   and uc.userid = :userid
					order by e.ID";
                $sql_sent = "
				select e.ID,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.{$this->config_service['PK_SERVICE']},
			       e.CENTER,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.QUEST_DT,
			       E.ANS_DT,
			       E.CHIUSA_DT
			  from {$this->xmr_root->prefix}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			 where e.q_userid = :userid
			   and e.chiusa=1
			   and c.center = e.center
			   and uc.center = c.center
			   and uc.userid = :userid
					order by e.ID";
                $this->page_title = $this->testo("closedEqL");
                $html .= "
					<button class=\"btn btn-info\" style=\"float:right\" onclick=\"window.location.href='index.php?eQuery';\"><i class=\"fa fa-unlock\"></i> " . $this->testo("openedEqS") . " <i class=\"fa fa-arrow-right\"></i></button>
				";
                unset($bind_userid);
                $bind_userid['USERID'] = $in['remote_userid'];
            } else {
                $open = true;
                $sql_rec = "
				select e.ID,
				   e.REGISTRY,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.{$this->config_service['PK_SERVICE']},
			       e.CENTER,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.QUEST_DT,
			       E.ANS_DT
			  from {$this->xmr_root->prefix}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			 where e.q_userid <> :userid
			   and e.chiusa is null
			   and c.center = e.center
			   and uc.center = c.center
			   and uc.userid = :userid
					order by e.ID";
                $sql_sent = "
				select e.ID,
				   e.REGISTRY,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.{$this->config_service['PK_SERVICE']},
			       e.CENTER,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.QUEST_DT,
			       E.ANS_DT
			  from {$this->xmr_root->prefix}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			 where e.q_userid = :userid
			   and e.chiusa is null
			   and c.center = e.center
			   and uc.center = c.center
			   and uc.userid = :userid
					order by e.ID";
                $this->page_title = $this->testo("openedEq");
                $html .= "
					<button class=\"btn btn-info\" style=\"float:right\" onclick=\"window.location.href='index.php?eQuery&closed';\"><i class=\"fa fa-lock\"></i> " . $this->testo("closedEq") . " <i class=\"fa fa-arrow-right\"></i></button>
				";
                unset($bind_userid);
                $bind_userid['USERID'] = $in['remote_userid'];
            }

            //eQuery ricevute
            $sql = new query ($this->conn);
            //$sql->set_sql ( $sql_rec );
            $sql->exec($sql_rec, $bind_userid);//binded
            $rec_list = $this->eList($sql, $open);
            $sql = new query ($this->conn);
            //$sql->set_sql ( $sql_sent );
            $sql->exec($sql_sent, $bind_userid);//binded
            $sent_list = $this->eList($sql, $open);
            //TODO: da controllare
            if (!preg_match("/^995/", $remote_userid))
                $html .= "<button class=\"btn btn-success\"  onclick=\"window.location.href='index.php?eQuery&eform'\"><i class=\"fa fa-plus\"></i> " . $this->testo("newEq") . "</button>";
            $html .= "<br/>

				<div class=\"widget-box\">
					<div class=\"widget-header\">
					<h5 class=\"bigger lighter\"><i class=\"fa fa-inbox\"></i> " . $this->testo("receivedEq") . "</h5>
					</div>
					<div class=\"widget-body\">
						<div class=\"widget-main no-padding\">
							$rec_list
						</div>
					</div>
				</div>
				<div class=\"br_separator\"></div>
				<div class=\"widget-box\">
					<div class=\"widget-header\">
					<h5 class=\"bigger lighter\"><i class=\"fa fa-upload\"></i> " . $this->testo("sendedEq") . "</h5>
					</div>
					<div class=\"widget-body\">
						<div class=\"widget-main no-padding\">
							$sent_list
						</div>
					</div>
				</div>
				<div class=\"br_separator\"></div>

				";
            if (!preg_match("/^995/", $remote_userid))
                $html .= "<a href=\"index.php?eQuery&eform\">" . $this->testo("newEq") . "</a>";
        } else {
            if (!isset ($in ['ID'])) {
                $dati_equery = null;
            } else {
                $sql_dati_query = "select * from {$service}_equery where id=:eq_id";
                $sql = new query ($this->conn);
                $sql->set_sql($sql_dati_query);
                unset($bind);
                $bind['EQ_ID'] = $in['ID'];
                $sql->exec($sql_dati_query, $bind);//binded
                $sql->get_row();
                $dati_equery = $sql->row;
            }
            $html .= $this->eForm($dati_equery);
        }
        //Nuovo modo di generare il menu briciola di pane
        //

        return $percorso . $html;
    }

    /**
     * Lista delle equery
     *
     * @param String $sql
     * @param dbconn $open
     * @return String
     */
    function eList($sql, $open)
    {
        $config = null;
        $in = $this->session_vars;
        $config_service = $this->config_service;
        if (!$this->config_service['eQueryXmlConfigurations']['SingleRegistry']) {
            $th_registry = "<th class=int>" . $this->testo("Registry") . "</th>";

        }
        if ($open)
            $html = "
			<table class=\"table table-striped table-bordered table-hover\">
			<thead  class=\"thin-border-bottom\">
				<tr>
					<th class=int>ID</th>
					{$th_registry}
					<th class=int>" . $this->testo("Center") . "</th>
					<th class=int>" . $this->testo("Visit") . "</th>
					<th class=int>" . $this->testo("Esam") . "</th>
					<th class=int>" . $this->testo("eQueryDate") . "</th>
					<th class=int>" . $this->testo("Dateofanswer") . "</th>
					<th class=int>" . $this->testo("Modify") . "</th>
				</tr>
							</thead>
		";
        if (!$open) {
            $html = "
			<table class=\"table table-striped table-bordered table-hover\">
			<thead class=\"thin-border-bottom\">
				<tr>
					<th class=int>ID</th>
					{$th_registry}
					<th class=int>" . $this->testo("Center") . "</th>
					<th class=int>" . $this->testo("Visit") . "</th>
					<th class=int>" . $this->testo("Esam") . "</th>
					<th class=int>" . $this->testo("eQueryDate") . "</th>
					<th class=int>" . $this->testo("Dateofanswer") . "</th>
					<th class=int>" . $this->testo("closeDate") . "</th>
					<th class=int>" . $this->testo("Modify") . "</th>
				</tr>
							</thead>
		";
        }


        foreach ($this->xmr->substudies as $substd) {
            $vlists[$substd->prefix] = new xml_esams_list ($this->xml_dir . '/' . $substd->prefix . '/' . $this->visit_structure_xml, $config, $this->session_vars, $this->conn);
            $descrs[$substd->prefix] = $substd->workflow['DESCR'];
            $dirs[$substd->prefix] = $substd->prefix . "/";
        }

        $vlists[$this->service] = $this->vlist;
        $descrs[$this->service] = $this->xmr->workflow['DESCR'];
        $dirs[$this->service] = "";

        while ($sql->get_row()) {
            if (!$this->config_service['eQueryXmlConfigurations']['SingleRegistry']) {
                $td_registry = "<td class=sc4bis align=center>{$descrs[$sql->row ['REGISTRY']]}</td>";
            }
            $visita = $vlists[$sql->row ['REGISTRY']]->visitnums [$sql->row ['VISITNUM']] ['TEXT'];
            $esame = $vlists[$sql->row ['REGISTRY']]->esams [$sql->row ['VISITNUM']] [$sql->row ['ESAM']] ['TESTO'];
            $link_ = "<a href=\"index.php?eQuery&eform&ID={$sql->row['ID']}\">{$sql->row['ID']}</a>";
            if ($sql->row ['TO_BE_VALIDATE'] == '1' && $in ['USER_TIP'] == 'DM' && $sql->row ['VAL_DT'] == '') {
                //percorso al file xml
                //	$subdir = '';
                $form = "&amp;form={$vlists[$sql->row ['REGISTRY']]->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML']}";

                $link_validazione = "
					<a href=\"{$dirs[$sql->row ['REGISTRY']]}index.php?CENTER={$sql->row['CENTER']}&amp;{$config_service['PK_SERVICE']}={$sql->row[$config_service['PK_SERVICE']]}&amp;ESAM={$sql->row['ESAM']}&amp;PROGR={$sql->row['PROGR']}&amp;VISITNUM={$sql->row['VISITNUM']}&amp;VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}{$form}&ABILITA_MOD_DM=1&ID_QUERY={$sql->row['ID']}\">" . $this->testo("ModifyForm") . "</a>
					";
            }
            if ($sql->row ['TO_BE_VALIDATE'] == '1' && $sql->row ['VAL_DT'] == '' && $in ['USER_TIP'] != 'DM') {
                $link_validazione = $this->testo("ChangeNecessary");
            }
            if ($sql->row ['TO_BE_VALIDATE'] == '0') {
                $link_validazione = $this->testo("ChangeNotNecessary");
            }
            if ($sql->row ['TO_BE_VALIDATE'] == '') {
                $link_validazione = '---';
            }
            if ($sql->row ['TO_BE_VALIDATE'] == '1' && $sql->row ['VAL_DT'] != '') {
                $link_validazione = $this->testo("ChangeMadeAt") . " " . $sql->row ['VAL_DT'];
            }

            if ($open) {

                $html .= "
				<tr>
					<td class=sc4bis align=center>$link_</td>
					{$td_registry}
					<td class=sc4bis>{$sql->row['DENOM']}</td>
					<td class=sc4bis>$visita</td>
					<td class=sc4bis>$esame</td>
					<td class=sc4bis>{$sql->row['QUEST_DT']}</td>
					<td class=sc4bis>{$sql->row['ANS_DT']}</td>
					<td class=sc4bis align=center>$link_validazione</td>
				</tr>
					";
            } else
                $html .= "
				<tr>
					<td class=sc4bis align=center>$link_</td>
					{$td_registry}
					<td class=sc4bis>{$sql->row['DENOM']}</td>
					<td class=sc4bis>$visita</td>
					<td class=sc4bis>$esame</td>
					<td class=sc4bis>{$sql->row['QUEST_DT']}</td>
					<td class=sc4bis>{$sql->row['ANS_DT']}</td>
					<td class=sc4bis>{$sql->row['CHIUSA_DT']}</td>
					<td class=sc4bis align=center>$link_validazione</td>
				</tr>
					";
        }
        $html .= "</table>";

        return $html;
    }

    /**
     * Form in modalit equery
     *
     * @param array $dati_equery
     * @return String
     */
    function eForm($dati_equery = null)
    {
        $in = $this->session_vars;
        $this->eRegistryList();
        if (!isset ($in ['ID']) || ($dati_equery ['ANSWER'] == '' && $dati_equery ['Q_USERID'] == $in ['remote_userid']))
            return $this->eFormStep1($dati_equery);
        else {
            $first_step = $this->eFormStep1($dati_equery);
            $second_step = $this->eFormStep2($dati_equery);
            return $first_step . $second_step;
        }
    }

    /**
     * Step 2 delle equery
     *
     * @param array $dati_equery
     * @return String
     */
    function eFormStep2($dati_equery)
    {
        $html = '';
        $form = "
		<div class=\"form-group\">
			<label class=\"col-sm-3 control-label no-padding-right\" for=\"ANSWER_FIELD\">" . mlOut("System.eQuery.Answer_form.Answer", "Answer:") . "</label>
			<div class=\"col-sm-7\" id=\"ANSWER_FIELD\">
				<!--answer-->
			</div>
		</div>";
        $service = $this->service;
        $in = $this->session_vars;
        //echo "<hr>step2<hr>";
        //echo $in['USER_TIP']."<hr>";
        if (isset ($in ['ANSWER']) && $in ['ANSWER'] != '') {
            $values ['A_USERID'] = $in ['remote_userid'];
            $values ['ANSWER'] = $in ['ANSWER'];
            $values ['ANS_DT'] = "sysdate";
            if (isset ($in ['TO_BE_VALIDATE'])) {
                if ($in ['TO_BE_VALIDATE'] == '0') {
                    $values ['CHIUSA'] = '1';
                    $values ['CHIUSA_DT'] = 'sysdate';
                }
                $values ['TO_BE_VALIDATE'] = $in ['TO_BE_VALIDATE'];
            }

            $pk ['ID'] = $in ['ID'];
            $table = $service . "_equery";
            $sql = new query ($this->conn);
            $sql->update($values, $table, $pk);
            $this->conn->commit();

            // Notifiche mail, nuova equery
            if ($this->notifica)
                $this->notifica_equery(2, $in ['ID']);
            ob_clean();
            header('location: index.php?eQuery');
            $this->conn->commit();
            die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=index.php?eQuery\"></head></html>");
        }
        if (isset ($in ['TO_BE_VALIDATE'])) {
            if ($in ['TO_BE_VALIDATE'] == '0') {
                $values ['CHIUSA'] = '1';
                $values ['CHIUSA_DT'] = 'sysdate';
            }
            $values ['TO_BE_VALIDATE'] = $in ['TO_BE_VALIDATE'];
            $pk ['ID'] = $in ['ID'];
            $table = $service . "_equery";
            $sql = new query ($this->conn);
            $sql->update($values, $table, $pk);
            $this->conn->commit();
            ob_clean();
            header('location: index.php?eQuery');
            $this->conn->commit();

            die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=index.php?eQuery\"></head></html>");
        }
        if ($dati_equery ['ANSWER'] == '') {
            if ($in ['remote_userid'] != $dati_equery ['Q_USERID']) {
                $answer = "<textarea name=\"ANSWER\" cols=\"80\" ROWS=\"10\"></textarea>";
                if ($in ['USER_TIP'] == 'DM')
                    $answer .= "
					</div>
				</div>
				<div class=\"form-group\">
					<label class=\"col-sm-3 control-label no-padding-right\" for=\"MODIFY_FIELD\">" . mlOut("System.eQuery.Answer_form.Modify", "Modify Form") . "</label>
					<div class=\"col-sm-7\" id=\"MODIFY_FIELD\">
						<input type='radio' name='TO_BE_VALIDATE' value='0'>" . $this->testo('notNecessary') . "<br>
						<input type='radio' name='TO_BE_VALIDATE' value='1'>" . $this->testo('necessary') . "
				";
                $form = str_replace("<!--answer-->", $answer, $form);
                $html .= "<form class=\"form-horizontal\" method=post action=\"\">
				$form
				<p align=center>
						<button type='submit' class=\"btn btn-success\" value='" . $this->testo('sendAnswer') . "'>  <i class=\"icon-ok\"></i>" . $this->testo('sendAnswer') . "</button>
						<button type='reset' class=\"btn\" value='" . $this->testo('cancel') . "'> <i class=\"icon-undo bigger-110\"></i>" . $this->testo('cancel') . "</button>
					</p>
				</form>	";

            } else
                error_page($in ['remote_userid'], $this->testo('userNotCenter'), $this->testo('userNotCenter'));
        } else {

            if ($dati_equery ['TO_BE_VALIDATE'] == '') {
                if ($in ['USER_TIP'] == 'DM') {

                    $answer = "<b >{$dati_equery['ANSWER']}</b>";
                    $answer .= "</div></div>
					
				<div class=\"form-group\">
					<label class=\"col-sm-3 control-label no-padding-right\" for=\"MODIFY_FIELD\">" . mlOut("System.eQuery.Answer_form.Modify", "Modify Form") . "</label>
					<div class=\"col-sm-7\" id=\"MODIFY_FIELD\">
						<input type='radio' name='TO_BE_VALIDATE' value='0'>" . $this->testo('notNecessary') . "<br>
						<input type='radio' name='TO_BE_VALIDATE' value='1'>" . $this->testo('necessary') . "
					</div>
				</div>
								";
                    $form = str_replace("<!--answer-->", $answer, $form);
                    $html .= "
				<form method=post action=\"\" class=\"form-horizontal\">
				$form
				<p align=center>
						<button type='submit' class=\"btn btn-success\" value='" . $this->testo('sendAnswer') . "'>  <i class=\"icon-ok\"></i>" . $this->testo('sendAnswer') . "</button>
						<button type='reset' class=\"btn\" value='" . $this->testo('cancel') . "'> <i class=\"icon-undo bigger-110\"></i>" . $this->testo('cancel') . "</button>
					</p>
				</form>
				";
                } else {
                    $form = str_replace("<!--answer-->", "<b>{$dati_equery['ANSWER']}</b>", $form);
                    $html .= "
					$form
						";
                }
            } else {
                $answer = "<b >{$dati_equery['ANSWER']}</b>";
                $answer .= "</div></div>";
                $img_not_nec = $img_nec = "<img src=\"images/uncheckedradio.gif\">";
                if ($dati_equery ['TO_BE_VALIDATE'] == '0')
                    $img_not_nec = "<img src=\"images/checkedradio.gif\">";
                if ($dati_equery ['TO_BE_VALIDATE'] == '1')
                    $img_nec = "<img src=\"images/checkedradio.gif\">";
                $answer .= "
				
				<div class=\"form-group\">
					<label class=\"col-sm-3 control-label no-padding-right\" for=\"MODIFY_FIELD\">" . mlOut("System.eQuery.Answer_form.Modify", "Modify Form") . ":</label>
					<div class=\"col-sm-7\" id=\"MODIFY_FIELD\">
						$img_not_nec " . $this->testo('notNecessary') . "<br>
						$img_nec " . $this->testo('necessary') . "
				";
                $form = str_replace("<!--answer-->", $answer, $form);
                $html .= "<form method=post action=\"\" class=\"form-horizontal\">
				$form</form>
				";
            }
        }
        return $html;
    }

    /**
     * Step 1 delle equery
     *
     * @param array $dati_equery
     * @return String
     */
    function eFormStep1($dati_equery = null)
    {
        $html = null;
        $config = null;
        $in = $this->session_vars;
        $config_service = $this->config_service;
        $xml_dir = $this->xml_dir;
        $service = $this->xmr->prefix;
        if (!is_null($dati_equery)) {
            /*parte per la visualizzazione del progressivo in visualizzazione delle equery /**Giorgio DELSIGNORE**/
            $sql_query = "
					select
						distinct progr
					from {$service}_coordinate
					where
					{$config_service['PK_SERVICE']}=:pk_service
					and abilitato=1
					and visitnum=:visitnum
					and visitnum_progr=:visitnum_progr
					and esam=:esam
					";
            unset($bind);
            $bind['PK_SERVICE'] = $dati_equery[$config_service['PK_SERVICE']];
            $bind['VISITNUM'] = $dati_equery['VISITNUM'];
            $bind['VISITNUM_PROGR'] = $dati_equery['VISITNUM_PROGR'];
            $bind['ESAM'] = $dati_equery['ESAM'];
            $sql = new query($this->conn);
            //$sql->set_sql($sql_query);
            $sql->exec($sql_query, $bind);//binded

            //					print_R($in);
            if ($sql->numrows > 1) {

                $progressivo = "
								<b>n. {$dati_equery['PROGR']}</b>
				";
            }
            $sql_query = "
					select
						distinct visitnum_progr
					from {$service}_coordinate
					where
					{$config_service['PK_SERVICE']}=:pk_service
					and abilitato=1
					and visitnum=:visitnum
					and esam=:esam
					";
            unset($bind);
            $bind['PK_SERVICE'] = $dati_equery[$config_service['PK_SERVICE']];
            $bind['VISITNUM'] = $dati_equery['VISITNUM'];
            $bind['ESAM'] = $dati_equery['ESAM'];
            $sql = new query($this->conn);
            //$sql->set_sql($sql_query);
            $sql->exec($sql_query, $bind);//binded

            //					print_R($in);
            if ($sql->numrows > 1) {
                $vprogr = $dati_equery['VISITNUM_PROGR'] + 1;
                $visit_progr = "
								<b>n. {$vprogr}</b>
				";
            }
            /*fine parte per la visualizzazione del progressivo*/
            $sql_query = "
				select c.*
				from {$service}_centri c,
				{$service}_utenti_centri uc
				where
					uc.userid=:userid
					and uc.center=c.center
					and uc.center=:center
					";
            $sql_query = "select c.DENOM, c.CENTER from {$service}_UTENTI_CENTRI uc, {$service}_CENTRI c where c.center=uc.center and uc.userid=:userid and c.center=:center";

            unset($bind);
            $bind['CENTER'] = $dati_equery['CENTER'];
            $bind['USERID'] = $in['remote_userid'];

            $bind['PREFIX'] = $service;
            $sql = new query ($this->conn);
            //$sql->set_sql ( $sql_query );
            $sql->exec($sql_query, $bind);//binded
            $sql->get_row();

            //NON COMMENTARE LA PARTE SEGUENTE: per problemi rivolgersi a Giorgio Delsignore o Lorenzo Manacorda (17/06/2010)
            $prefix = $dati_equery ['REGISTRY'];
            if ($prefix == $this->xmr->prefix) {
                $vlist = $this->vlist;
            } else {
                $vlist = new xml_esams_list ($this->xml_dir . '/' . $prefix . '/' . $this->visit_structure_xml, $config, $this->session_vars, $this->conn);
            }

            $centro = "<b>{$sql->row['DENOM']}</b><input type=\"hidden\" name=\"CENTER\" value=\"{$dati_equery['CENTER']}\">";
            $paziente = "<b>{$dati_equery[$config_service['PK_SERVICE']]}</b><input type=\"hidden\" name=\"{$config_service['PK_SERVICE']}\" value=\"{$dati_equery[$config_service['PK_SERVICE']]}\">";
            $visita = "<b>{$vlist->visitnums[$dati_equery['VISITNUM']]['TEXT']}</b><input type=\"hidden\" name=\"VISITNUM\" value=\"{$dati_equery['VISITNUM']}\">";
            $visit_progr .= "<input type=\"hidden\" name=\"VISITNUM_PROGR\" value=\"{$dati_equery['VISITNUM_PROGR']}\">";
            $esame = "<b>{$vlist->esams[$dati_equery['VISITNUM']][$dati_equery['ESAM']]['TESTO']}</b>
						<input type=\"hidden\" name=\"ESAM\" value=\"{$dati_equery['ESAM']}\">
						";
            $progressivo .= "
						<input type=\"hidden\" name=\"PROGR\" value=\"{$dati_equery['PROGR']}\">
						";

            $question = "<b>{$dati_equery['QUESTION']}</b>";
            $form = "
			 		<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"CENTER_FIELD\">" . mlOut("System.eQuery.Question_form.Center", "Center:") . "</label>
						<div class=\"col-sm-7\" id=\"CENTER_FIELD\">
									<!--centro-->
						</div>
					</div>
					
					<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"PT_FIELD\">" . mlOut("System.eQuery.Question_form.TPcode", "Therapeutic plan code:") . "</label>
						<div class=\"col-sm-7\" id=\"PT_FIELD\">
										<!--paziente-->
								<!--registry-->
						</div>
					</div>
								
					<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"VISITA_FIELD\">" . mlOut("System.eQuery.Question_form.Block", "Block:") . "</label>
						<div class=\"col-sm-7\" id=\"VISITA_FIELD\">
										<!--visita-->
						</div>
					</div>	
					
					<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"ESAM_FIELD\">" . mlOut("System.eQuery.Question_form.Esam", "Esam:") . "</label>
						<div class=\"col-sm-7\" id=\"ESAM_FIELD\">
										<!--esame-->
						</div>
					</div>	
					
					<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"QUESTION_FIELD\">" . mlOut("System.eQuery.Question_form.Question", "Question:") . "</label>
						<div class=\"col-sm-7\" id=\"QUESTION_FIELD\">
										<!--question-->
						</div>
					</div>";
            $form = str_replace("<!--centro-->", $centro, $form);
            $form = str_replace("<!--paziente-->", $paziente, $form);
            $form = str_replace("<!--registry-->", $this->eRegistryList(), $form);
            $form = str_replace("<!--visita-->", $visita . $visit_progr, $form);
            $form = str_replace("<!--esame-->", $esame . $progressivo, $form);
            error_log("---- q " . $question . " visita" . $visita);
            $form = str_replace("<!--question-->", $question, $form);
            $this->page_title = "eQuery n. {$in['ID']}";
            $html .= "
			 	<form method=post action=\"index.php\" class=\"form-horizontal\">
				$form
				</form>


			";
        } else {
            if (isset ($in ['CENTER']) && $in ['CENTER'] != '' && isset ($in [$config_service ['PK_SERVICE']]) && $in [$config_service ['PK_SERVICE']] != '' && isset ($in ['VISITNUM']) && $in ['VISITNUM'] != '' && isset ($in ['VISITNUM_PROGR']) && $in ['VISITNUM_PROGR'] != '' && isset ($in ['ESAM']) && $in ['ESAM'] != '' && isset ($in ['PROGR']) && $in ['PROGR'] != '' && isset ($in ['REGISTRY']) && $in ['REGISTRY'] != '' && isset ($in ['SALVA_EQUERY']) && $in ['SALVA_EQUERY'] != '' && isset ($in ['QUESTION']) && $in ['QUESTION'] != '') {

                $sql_query = "select max(ID) as maxid from {$this->config['service']}_equery";
                $sql = new query ($this->conn);
                $sql->set_sql($sql_query);
                $sql->exec();//non richiede binding
                $sql->get_row();
                $maxid = $sql->row ['MAXID'] - 0;
                $maxid++;
                $values ['ID'] = $maxid;
                $values ['QUEST_DT'] = "sysdate";
                $values ['Q_USERID'] = $in ['remote_userid'];
                $values ['CENTER'] = $in ['CENTER'];
                $values ['CODPAT'] = $in ['CODPAT'];
                $values ['VISITNUM'] = $in ['VISITNUM'];
                $values ['ESAM'] = $in ['ESAM'];
                $values ['PROGR'] = $in ['PROGR'];
                $values ['QUESTION'] = $in ['QUESTION'];
                $values ['VISITNUM_PROGR'] = $in ['VISITNUM_PROGR'];
                $values ['REGISTRY'] = $in ['REGISTRY'];

                $table = "{$this->config['service']}_equery";
                $pk ['ID'] = '';
                $sql = new query ($this->conn);
                $sql->insert($values, $table, $pk, true);
                $this->conn->commit();

                // Notifiche mail, nuova equery
                if ($this->notifica)
                    $this->notifica_equery(1, $maxid);
                ob_clean();
                header('location: index.php?eQuery');
                $this->conn->commit();
                die();
                die ("<html><head><meta http-equiv=\"refresh\" content=\"0;url=index.php?eQuery\"></head></html>");
            }
            //$sql_query = "select  wf.* from workflow wf where prefix='{$this->service}WF'";
            //			echo $sql_query;
            //$sql_wf = new query ( $this->conn );
            //$sql_wf->get_row ( $sql_query );
            $question = "<textarea name=\"QUESTION\" cols=\"80\" ROWS=\"10\"></textarea>";
            $form = "
					<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"CENTER_FIELD\">" . mlOut("System.eQuery.Question_form.Center", "Center:") . "</label>
						<div class=\"col-sm-7\" id=\"CENTER_FIELD\">
									<!--centro-->
						</div>
					</div>
					
					<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"PT_FIELD\">" . mlOut("System.eQuery.Question_form.TPcode", "Therapeutic plan code:") . "</label>
						<div class=\"col-sm-7\" id=\"PT_FIELD\">
										<!--paziente-->
								<!--registry-->
						</div>
					</div>
								
					<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"VISITA_FIELD\">" . mlOut("System.eQuery.Question_form.Block", "Block:") . "</label>
						<div class=\"col-sm-7\" id=\"VISITA_FIELD\">
										<!--visita-->
						</div>
					</div>	
					
					<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"ESAM_FIELD\">" . mlOut("System.eQuery.Question_form.Esam", "Esam:") . "</label>
						<div class=\"col-sm-7\" id=\"ESAM_FIELD\">
										<!--esame-->
						</div>
					</div>	
					
					<div class=\"form-group\">
						<label class=\"col-sm-3 control-label no-padding-right\" for=\"QUESTION_FIELD\">" . mlOut("System.eQuery.Question_form.Question", "Question:") . "</label>
						<div class=\"col-sm-7\" id=\"QUESTION_FIELD\">
										<!--question-->
						</div>
					</div>";
            $form = str_replace("<!--centro-->", $this->eCenterList(), $form);
            //$form = str_replace ( "<!--study-->", "<input type=\"hidden\" value='{$sql_wf->row['ID']}'>", $form );
            $form = str_replace("<!--paziente-->", $this->ePatientList(), $form);
            $form = str_replace("<!--registry-->", $this->eRegistryList(), $form);
            $form = str_replace("<!--visita-->", $this->eVisitList(), $form);
            //error_log("---- visita " . $this->eVisitList() );
            $form = str_replace("<!--esame-->", $this->eEsamList(), $form);
            $form = str_replace("<!--question-->", $question, $form);

            $this->page_title = "New eQuery";
            $html .= "
				<div class=\"widget-box\">
					<div class=\"widget-header\">
						<h5><i class=\"fa fa-question-circle\"></i> Question</h5>
					</div>
					<div class=\"widget-body\">
					<br/>
					<form method=post action=\"index.php\" class=\"form-horizontal\">
				$form
				<p align=center>
						<button type='submit' class=\"btn btn-success\" name='SALVA_EQUERY' onclick=\"
							if (document.forms[0].CENTER.value=='') {
								alert('" . mlOut("System.eQuery.Alert-SelectCenter") . "');
								return false;
							}
							if (document.forms[0].{$config_service['PK_SERVICE']}.value=='') {
								alert('" . mlOutJs("Alert-SelectPatient") . "');
								return false;
							}
							if (document.forms[0].VISITNUM.value=='') {
								alert('" . mlOutJs("Alert-SelectVisit") . "');
								return false;
							}
							if (document.forms[0].ESAM.value=='') {
								alert('" . mlOutJs("Alert-SelectExam") . "');
								return false;
							}
							if (document.forms[0].QUESTION.value=='') {
								alert('" . mlOutJs("Insert the question") . "');
								return false;
							}
						\" value='Send eQuery'><i class=\"icon-ok\"></i>Send eQuery</button>
						<button class=\"btn\" type=\"reset\" >
								<i class=\"icon-undo bigger-110\"></i>
								" . mlOut("Cancel") . "
								</button>
					</p>
				</form>
				</div>
				</div>
			";
            /*
			}
			else {
				$html .= "
				<p class=titolo>Nuova eQuery</p>
				<form method=post action=\"index.php\">
				$form
				<p align=center>
						<input type='submit' name='SALVA_EQUERY' onclick=\"
							if (document.forms[0].CENTER.value=='') {
								alert('E\\' necessario selezionare un centro');
								return false;
							}
							if (document.forms[0].{$config_service['PK_SERVICE']}.value=='') {
								alert('E\\' necessario selezionare un paziente');
								return false;
							}
							if (document.forms[0].VISITNUM.value=='') {
								alert('E\\' necessario selezionare una visita');
								return false;
							}
							if (document.forms[0].ESAM.value=='') {
								alert('E\\' necessario selezionare un esame');
								return false;
							}
							if (document.forms[0].QUESTION.value=='') {
								alert('Inserire la domanda');
								return false;
							}
						\" value='Invia eQuery'> &nbsp;
						<input type='reset' value='Annulla'>
					</p>
				</form>
			";
			}
			*/
        }

        return $html;
    }

    /**
     * Lista delle schede dell'oggetto di studio (equery)
     *
     * @return array
     */
    function eEsamList()
    {
        $config = null;
        $xml_dir = $this->xml_dir;
        $in = $this->session_vars;
        $config_service = $this->config_service;

        if (!isset ($in [$config_service ['PK_SERVICE']]) || $in [$config_service ['PK_SERVICE']] == '') {
            return "";
        }
        if (isset ($in ['VISITNUM']) && $in ['VISITNUM'] != '') {
            /*$str="select prefix from workflow where id={$in['STUDY']}";
			 $sql_study=new query($this->conn);
			 $sql_study->get_row($str);
			 $prefix=substr($sql_study->row['PREFIX'],0,strlen($sql_study->row['PREFIX'])-2);

			 */
            //$vlist = $this->vlist;
            //NON COMMENTARE LA PARTE SEGUENTE: per problemi rivolgersi a Giorgio Delsignore o Giacomo Tufano (05/07/2010)
            $prefix = $in ['REGISTRY'];

            if ($prefix == $this->xmr->prefix) {
                $vlist = $this->vlist;
                $service = $this->service;
            } else {
                $vlist = new xml_esams_list ($this->xml_dir . '/' . $prefix . '/' . $this->visit_structure_xml, $config, $this->session_vars, $this->conn);;
                $service = $in['REGISTRY'];
            }

            if ($service == '')
                $service = $this->service;
            //FINE PARTE DA NON COMMENTARE (05/07/2010)
            //Esame
            $sql_query = "
					select
						distinct esam
					from {$service}_coordinate
					where {$config_service['PK_SERVICE']}=:pk_service
					and abilitato=1
					and fine=1
					and visitnum=:visitnum
					and visitnum_progr=:visitnum_progr
					order by esam asc";
            $sql = new query ($this->conn);
            //$sql->set_sql ( $sql_query );
            unset($bind);
            $bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
            $bind['VISITNUM'] = $in['VISITNUM'];
            $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
            $sql->exec($sql_query, $bind);//binded
            $options = "";

            if ($sql->numrows > 0) {
                while ($sql->get_row()) {
                    if (isset ($in ['ESAM']) && $in ['ESAM'] == $sql->row ['ESAM'])
                        $selected = "selected";
                    else
                        $selected = '';
                    $options .= "
						<option value=\"{$sql->row['ESAM']}\" $selected>{$vlist->esams[$in['VISITNUM']][$sql->row['ESAM']]['TESTO']}</option>";
                }
                $esame = "
					<select name=\"ESAM\" onchange=\"document.forms[0].submit();\">
						<option value=\"\"></option>
						$options
					</select>
				";
            } else {
                $sql->get_row();
                $in ['ESAM'] = $sql->row ['ESAM'];
                $esame = "
						<b>{$vlist->esams[$in['VISITNUM']][$sql->row['ESAM']]['TESTO']}</b>
						<input type=\"hidden\" name=\"ESAM\" value=\"{$in['ESAM']}\">
						";
            }
        }

        if (isset ($in ['VISITNUM']) && $in ['VISITNUM'] != '' && isset ($in ['ESAM']) && $in ['ESAM'] != '') {
            $sql_query = "
					select
						distinct progr
					from {$service}_coordinate
					where
					{$config_service['PK_SERVICE']}=:pk_service
					and abilitato=1
					and visitnum=:visitnum
					and visitnum_progr=:visitnum_progr
					and esam=:esam
					order by progr asc";
            $sql = new query ($this->conn);
            //$sql->set_sql ( $sql_query );
            unset($bind);
            $bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
            $bind['VISITNUM'] = $in['VISITNUM'];
            $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
            $bind['ESAM'] = $in['ESAM'];
            $sql->exec($sql_query, $bind);//binded
            $options = "";
            //print_R($in);
            if ($sql->numrows > 1) {
                while ($sql->get_row()) {
                    if (isset ($in ['PROGR']) && $in ['PROGR'] == $sql->row ['PROGR'])
                        $selected = "selected";
                    else
                        $selected = '';
                    $options .= "
						<option value=\"{$sql->row['PROGR']}\" $selected>{$sql->row['PROGR']}</option>";
                }
                $progressivo = "
							</td>
						</tr>
						<tr>
							<td class=destra>
								<b>Esame n.ro</b>
							</td>
							<td class=input>
								<select name=\"PROGR\" onchange=\"document.forms[0].submit();\">
									<option value=\"\"></option>
									$options
								</select>
				";
            } else {
                $sql->get_row();
                $in ['PROGR'] = $sql->row ['PROGR'];
                $progressivo = "
						<input type=\"hidden\" name=\"PROGR\" value=\"{$in['PROGR']}\">
						";
            }
        }
        return $esame . $progressivo;
    }

    /**
     * Lista Visite (equery)
     *
     * @return String
     */
    function eVisitList()
    {
        $config = null;
        //		global $xml_dir;
        //		global $in;
        //		global $service;
        //		global $config_service;
        $xml_dir = $this->xml_dir;
        $in = $this->session_vars;
        $service = $this->service;
        $config_service = $this->config_service;
        if (!isset ($in ['REGISTRY']) || $in ['REGISTRY'] == '' || $this->session_vars [$this->config_service ['PK_SERVICE']] == '') {
            return "";
        }
        //Visita
        if (isset ($in ['REGISTRY']) && $in ['REGISTRY'] != '') {
            //NON COMMENTARE LA PARTE SEGUENTE: per problemi rivolgersi a Giorgio Delsignore o Lorenzo Manacorda (17/06/2010)
            $prefix = $in ['REGISTRY'];
            if ($prefix == $this->xmr->prefix) {
                $vlist = $this->vlist;
            } else {
                $vlist = new xml_esams_list ($this->xml_dir . '/' . $prefix . '/' . $this->visit_structure_xml, $config, $this->session_vars, $this->conn);;
            }
            //FINE PARTE DA NON COMMENTARE (17/06/2010)
            //$vlist = $this->vlist;

            $sql_query = "
					select
						distinct visitnum
					from {$this->service}_coordinate
					where {$config_service['PK_SERVICE']}=:pk_service
					and abilitato=1
					and fine=1
					order by visitnum asc";
            unset($bind_pk);
            $bind_pk['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
            $sql = new query ($this->conn);
            //$sql->set_sql ( $sql_query );
            $sql->exec($sql_query, $bind_pk);//binded
            $options = "";
            if ($sql->numrows > 0) {
                while ($sql->get_row()) {
                    if (isset ($in ['VISITNUM']) && $in ['VISITNUM'] == $sql->row ['VISITNUM'])
                        $selected = "selected";
                    else
                        $selected = '';
                    $options .= "
						<option value=\"{$sql->row['VISITNUM']}\" $selected>{$vlist->visitnums[$sql->row['VISITNUM']]['TEXT']}</option>";
                }
                $visita = "
					<select name=\"VISITNUM\" onchange=\"document.forms[0].submit();\">
						<option value=\"\"></option>
						$options
					</select>
				";
            } else {
                $sql->get_row();
                $in ['VISITNUM'] = $sql->row ['VISITNUM'];
                $visita = "
						<b>{$vlist->visitnums[$sql->row['VISITNUM']]['TEXT']}</b>
						<input type=\"hidden\" name=\"VISITNUM\" value=\"{$in['VISITNUM']}\">
						";

            }
        }
        if (isset ($in ['VISITNUM']) && $in ['VISITNUM'] != '') {
            //visita progressiva
            $sql_query = "
					select
						distinct visitnum_progr
					from {$service}_coordinate
					where {$config_service['PK_SERVICE']}=:pk_service
					and abilitato=1 and visitnum=:visitnum
					order by visitnum_progr asc";
            $sql = new query ($this->conn);
            //$sql->set_sql ( $sql_query );
            unset($bind);
            $bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
            $bind['VISITNUM'] = $in['VISITNUM'];
            $sql->exec($sql_query, $bind);//binded
            $options = "";
            if ($sql->numrows > 0) {
                while ($sql->get_row()) {
                    if (isset ($in ['VISITNUM_PROGR']) && $in ['VISITNUM_PROGR'] == $sql->row ['VISITNUM_PROGR'])
                        $selected = "selected";
                    else
                        $selected = '';
                    $n_visit = $sql->row ['VISITNUM_PROGR'] + 1;
                    $options .= "
						<option value=\"{$sql->row['VISITNUM_PROGR']}\" $selected>{$n_visit}</option>";
                }
                $visit_progr = "
							</td>
						</tr>
						<tr>
							<td class=destra>
								<b>" . $this->testo("Visit") . " n.ro</b>
							</td>
							<td class=input>
								<select name=\"VISITNUM_PROGR\" onchange=\"document.forms[0].submit();\">
									<option value=\"\"></option>
									$options
								</select>
				";
            } else {
                $sql->get_row();
                $in ['VISITNUM_PROGR'] = $sql->row ['VISITNUM_PROGR'];
                $visit_progr = "
						<input type=\"hidden\" name=\"VISITNUM_PROGR\" value=\"{$in['VISITNUM_PROGR']}\">
						";
            }
        }
        return $visita . $visit_progr;
    }

    /**
     * Lista pazienti (equery)
     *
     * @return String
     */
    function ePatientList()
    {

        $this->page_title = "Patient's List";
        //		global $xml_dir;
        //		global $in;
        //		global $service;
        //		global $config_service;
        $xml_dir = $this->xml_dir;
        $in = $this->session_vars;
        $service = $this->service;
        $config_service = $this->config_service;

        $in = $this->session_vars;

        if ($this->session_vars ['CENTER'] != '') {
            $reg_form = new xml_form ($this->conn, $this->xmr_root->prefix);

            $reg_form->xml_form_by_file($xml_dir . "/" . $this->vlist_root->esams [0] [0] ['XML']);
            $table_ana = $reg_form->form ['TABLE'];

            $sql_query = "
					select
						a.{$config_service['PK_SERVICE']}
					from $table_ana a , {$this->service}_coordinate coor
					where a.center=:center and a.{$config_service['PK_SERVICE']}=coor.{$config_service['PK_SERVICE']} and coor.esam=0
					order by {$config_service['PK_SERVICE']} asc";
            unset($bind_center);
            $bind_center['CENTER'] = $in['CENTER'];
            $sql = new query ($this->conn);
            $sql->exec($sql_query, $bind_center);//binded

            $options = '';
            if ($sql->numrows >= 1) {
                while ($sql->get_row()) {
                    //					print_r($sql->row);
                    if (isset ($in [$config_service ['PK_SERVICE']]) && $in [$config_service ['PK_SERVICE']] == $sql->row [$config_service ['PK_SERVICE']])
                        $selected = "selected";
                    else
                        $selected = '';
                    $options .= "
						<option value=\"{$sql->row[$config_service['PK_SERVICE']]}\" $selected>{$sql->row[$config_service['PK_SERVICE']]}</option>
						";
                }
                $paziente = "
					<select name=\"{$config_service['PK_SERVICE']}\" onchange=\"document.forms[0].submit();\">
						<option value=''></option>
						" . $options . "
						</select>";
            } else {
                if ($sql->numrows > 0) {
                    $sql->get_row();
                    $in ['CENTER'] = $sql->row ['CENTER'];
                    $paziente = "<b>{$sql->row[$config_service['PK_SERVICE']]}</b><input type=\"hidden\" name=\"{$config_service['PK_SERVICE']}\" value=\"{$in[$config_service['PK_SERVICE']]}\">";
                } else {
                    $in [$config_service ['PK_SERVICE']] = '';
                    $no_pat = "<b>" . $this->testo("noPatient") . "</b>";
                    $paziente = $no_pat;
                }

            }
        }
        return $paziente;
    }

    /**
     * Lista Registri (equery)
     *
     * @return String
     */
    function eRegistryList()
    {
        $options = null;
        //		global $xml_dir;
        //		global $in;
        //		global $config_service;
        //		global $service;
        $xml_dir = $this->xml_dir;
        $in = $this->session_vars;
        $service = $this->service;
        $config_service = $this->config_service;
        if ($this->config_service['eQueryXmlConfigurations']['SingleRegistry']) {
            $return = "<input type='hidden' name='REGISTRY' value='{$this->service}' />";
            $in['REGISTRY'] = $_POST['REGISTRY'] = $this->session_vars['REGISTRY'] = $this->service;
            return $return;
        }
        if ($this->session_vars [$this->config_service ['PK_SERVICE']] != '') {
            if (isset ($in ['REGISTRY']) && $in ['REGISTRY'] == $this->xmr->prefix)
                $selected = "selected";
            else
                $selected = '';
            $options .= "<option value='{$this->xmr->prefix}' $selected>{$this->xmr->workflow['DESCR']}</option>";
            foreach ($this->xmr->substudies as $val) {
                #echo $val;
                if (isset ($in ['REGISTRY']) && $in ['REGISTRY'] == $val->prefix)
                    $selected = "selected";
                else
                    $selected = '';
                $sql_query_2 = "select count(*) conto from {$val->prefix}_coordinate where {$this->config_service['PK_SERVICE']}='{$this->session_vars[$this->config_service['PK_SERVICE']]}'";
                $sql = new query ($this->conn);
                //$sql->set_sql ( $sql_query_2 );
                unset($bind_pk);
                $bind_pk['PK_SERVICE'] = $this->session_vars[$this->config_service['PK_SERVICE']];
                $sql->exec($sql_query_2, $bind_pk);//binded
                $sql->get_row();
                if ($sql->row ['CONTO'] > 0) {
                    $options .= "
						<option value=\"{$val->prefix}\" $selected>{$val->workflow['DESCR']}</option>
						";
                }

            }
            $registry_select = "
					<select name=\"REGISTRY\" onchange=\"document.forms[0].submit();\">
						<option></option>
						" . $options . "
						</select>";

        } else {
            $sql_query_2 = "select registry from {$this->xmr_root->prefix}_equery where ID=:eq_id";
            $sql = new query ($this->conn);
            //$sql->set_sql ( $sql_query_2 );
            unset($bind);
            $bind['EQ_ID'] = $this->session_vars['ID'];
            $sql->exec($sql_query_2, $bind); //binded
            $sql->get_row();
            $registry = $sql->row ['REGISTRY'];
            $registry_select = "<b>" . $registry . "</b>";
        }

        return $registry_select;

        //		$sql_query="select distinct c.* from {$service}_centri c, {$service}_utenti_centri uc where uc.userid='{$in['remote_userid']}' and uc.center=c.center ";
        //		$sql=new query($this->conn);
        //		$sql->set_sql($sql_query);
        //		$sql->exec();//commentata


    }

    /**
     * Lista dei centri su cui ha visibilit l'utente (equery)
     *
     * @return array
     */
    function eCenterList()
    {
        //		global $xml_dir;
        //		global $in;
        //		global $config_service;
        //		global $service;
        $xml_dir = $this->xml_dir;
        $in = $this->session_vars;
        $service = $this->service;
        $config_service = $this->config_service;

        //da filtrare con solo centri che hanno pazienti
        //$sql_query = "select  distinct c.* from {$service}_centri c, {$service}_utenti_centri uc where uc.userid='{$in['remote_userid']}' and uc.center=c.center ";
        $sql_query = "select c.DENOM, c.CENTER from {$service}_UTENTI_CENTRI uc, {$service}_CENTRI c where c.center=uc.center and uc.userid=:userid";
        $sql = new query ($this->conn);
        //$sql->set_sql ( $sql_query );
        unset($bind);
        $bind['USERID'] = $in['remote_userid'];
        $bind['PREFIX'] = $service;
        $sql->exec($sql_query, $bind);//binded
        $options = '';
        if ($sql->numrows > 1) {

            while ($sql->get_row()) {
                if (isset ($in ['CENTER']) && $in ['CENTER'] == $sql->row ['CENTER'])
                    $selected = "selected";
                else
                    $selected = '';
                $options .= "
						<option value=\"{$sql->row['CENTER']}\" $selected>{$sql->row['DENOM']} {$sql->row['CITTA']}</option>
						";
            }
            $centro = "
					<select name=\"CENTER\" onchange=\"document.forms[0].submit();\">
						<option value=''></option>
						" . $options . "
						</select>";
        } else {
            $sql->get_row();
            $centro = "<b>{$sql->row['DENOM']}</b><input type=\"hidden\" name=\"CENTER\" value=\"{$in['CENTER']}\">";

        }
//
        return $centro;
    }

    //	function eStudytList(){
    //		global $xml_dir;
    //		global $in;
    //		global $config_service;
    //		global $service;
    //		$in=$this->session_vars;
    //		$sql_query="select  wf.* from workflow wf";
    //		$sql=new query($this->conn);
    //		$sql->set_sql($sql_query);
    //		$sql->exec();//commentata
    //
    //		$options='';
    //		if (isset($in[$config_service['PK_SERVICE']]) && $in[$config_service['PK_SERVICE']]!=''){
    //			if ($sql->numrows>1){
    //
    //				while ($sql->get_row()){
    //					$prefix=substr($sql->row['PREFIX'],0,strlen($sql->row['PREFIX'])-2);
    //					$sql_query_2="select  count(*) conto from {$prefix}_coordinate where {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}'";
    //					$sql_2=new query($this->conn);
    //					$sql_2->set_sql($sql_query_2);
    //					$sql_2->exec();//commentata
    //					$sql_2->get_row();
    //					if($sql_2->row['CONTO']>0){
    //						if($in['STUDY']==$sql->row['ID'])$selected='selected="selected"';
    //						else $selected="";
    //						$options.="
    //						<option value=\"{$sql->row['ID']}\" $selected>{$sql->row['DESCR']}</option>
    //						";
    //					}
    //				}
    //				$study="
    //					<select name=\"STUDY\" onchange=\"document.forms[0].submit();\">
    //						<option value=''></option>
    //						".$options."
    //						</select>";
    //			}
    //			else {
    //				$sql->get_row();
    //				$study="<b>{$sql->row['DENOM']}</b><input type=\"hidden\" name=\"STUDY\" value=\"{$in['CENTER']}\">";
    //
    //			}
    //		}
    //		return $study;
    //	}


    /**
     * Salvataggio equery
     *
     */
    function eQuerySave()
    {
        //		global $in;
        global $filetxt;
        global $body;
        //		global $service;
        //		global $config_service;
        global $from_service_email;

        $in = $this->session_vars;
        $service = $this->service;
        $config_service = $this->config_service;

        $xml_dir = $this->xml_dir;
        $form = $in ['form'];
        $in ['INVIOCO'] = '1';
        $xml_form = new xml_form ();
        $xml_form->xml_form_by_file($xml_dir . '/' . $form);
        $xml_form->valida();
        if ($xml_form->validata) {
            $this->invia_db_dm($xml_form);
            $filetxt = preg_replace("/<!--body-->/", $body, $filetxt);
            echo $filetxt;
            die ();

        }

    }

    /**
     * Costruisce l'href
     *
     * @param String $testo_link
     * @param number $profondita
     * @return String
     */
    function href($testo_link, $profondita = 0)
    {
        $back_href = "";
        if (!isset ($this->hrefs [$testo_link])) {
            $this->hrefs ['Home'] = "index.php";
            $this->hrefs ['Registro Lista Pazienti'] = "index.php?list=patients_list.xml&CENTER={$this->session_vars['CENTER']}";
            $this->hrefs ['Registro Lista Centri'] = "index.php?list=patients_list.xml";
            $this->hrefs ['Vista Paziente'] = "index.php?exams=visite_exam.xml&{$this->config_service ['PK_SERVICE']}=$this->pk_service&CENTER={$this->session_vars['CENTER']}";
            $this->hrefs ['eQuery List'] = "index.php?eQuery&";
        }
        for ($i = 1; $i <= $profondita; $i++) {
            $back_href .= "../";
        }
        return $back_href . $this->hrefs [$testo_link];
    }

    /**
     * Tabella paziente (obsoleta)
     *
     */
    function make_patient_table()
    {
        return;
    }

    /**
     * Menu a briciola di pane
     *
     * @param String $type
     * @param array $dynamic_link_text
     * @return String
     */
    function breadcrumb($type, $dynamic_link_text = '')
    {
        /*
		 * Il termine inglese 'breadcrumb'
		 * (letteralmente 'briciola di pane')
		 * fa riferimento alla favola di Grimm, Hansel e Gretel,
		 * che racconta la storia di due bambini perduti nel bosco che ...
		 * ...
		 * ...
		 * e poi sono morti tutti.
		 *
		 */
        $in = $this->session_vars;
        $percorso [0] ['TESTO'] = $this->testo('Home');
        $percorso [0] ['HREF'] = $this->href('Home', $this->xmr->depth);
        switch ($type) {
            case 'form' :
                if (isset ($this->session_vars ['CENTER'])) {
                    if ($this->xmr->depth > 0) {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti', $this->xmr->depth);
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti') . "($this->service)";
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti');
                    } else {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti');
                    }
                } else if (isset ($this->centers)) {
                    if ($this->xmr->depth > 0) {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Centri');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Centri', $this->xmr->depth);
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Centri') . " ($this->service)";
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Centri');

                    } else {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Centri');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Centri');
                    }
                }

                if ($this->pk_service != '' && $this->pk_service != "next") {
                    if ($this->xmr->depth > 0)
                        $percorso [] ['TESTO'] = $this->testo('Vista Paziente') . " ($this->service)";
                    else
                        $percorso [] ['TESTO'] = $this->testo('Vista Paziente');
                    $percorso [count($percorso) - 1] ['HREF'] = $this->href('Vista Paziente');

                }
                $percorso [] ['TESTO'] = mlOut("Form.Title.{$dynamic_link_text}", "{$dynamic_link_text}");
                break;
            case 'patients_list' :
                //nuovo modo, solo lista centri valorizzato
                if ((isset ($this->session_vars ['list']) && $this->session_vars ['list'] == 'patients_list.xml') || isset ($_GET ['lista'])) {
                    if (isset ($this->session_vars ['CENTER'])) {
                        if ($this->xmr->depth > 0) {
                            $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti');
                            $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti', $this->xmr->depth);
                            $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti') . " ($this->service)";
                            $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti');

                        } else {
                            $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti');
                            $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti');
                        }
                    } else if (isset ($this->centers)) {
                        if ($this->xmr->depth > 0) {
                            $percorso [] ['TESTO'] = $this->testo('Registro Lista Centri');
                            $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Centri', $this->xmr->depth);
                            $percorso [] ['TESTO'] = $this->testo('Registro Lista Centri') . " ($this->service)";
                            $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Centri');

                        } else {
                            $percorso [] ['TESTO'] = $this->testo('Registro Lista Centri');
                            $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Centri');
                        }
                    }
                } else {
                    if ($this->xmr->depth > 0) {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti', $this->xmr->depth);
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti') . " ($this->service)";
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti');

                    } else {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti');
                    }
                }

                //type=exam_list
                break;
            case 'altra_list' :
                //tutto uguale a patients_list, ma prendo un altro titolo (dalla scheda stessa)
                //nuovo modo, solo lista centri valorizzato
                $percorso [] ['TESTO'] = mlOut("List.Title.{$dynamic_link_text}", "{$dynamic_link_text}");
                $percorso [count($percorso) - 1] ['HREF'] = mlOut("List.Title.{$dynamic_link_text}", "{$dynamic_link_text}");

                //type=exam_list
                break;
            case 'exam_list' :
                if (isset ($this->session_vars ['CENTER'])) {
                    if ($this->xmr->depth > 0) {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti', $this->xmr->depth);
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti') . " ($this->service)";
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti');
                    } else {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Pazienti');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Pazienti');
                    }
                } else if (isset ($this->centers)) {
                    if ($this->xmr->depth > 0) {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Centri');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Centri', $this->xmr->depth);
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Centri') . " ($this->service)";
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Centri');

                    } else {
                        $percorso [] ['TESTO'] = $this->testo('Registro Lista Centri');
                        $percorso [count($percorso) - 1] ['HREF'] = $this->href('Registro Lista Centri');
                    }
                }
                if (isset ($this->session_vars ['exams']) && isset ($this->session_vars ['CENTER'])) {

                    $percorso [] ['TESTO'] = $this->testo('Vista Paziente');

                }
                break;
            case 'search' :
                $percorso [] ['TESTO'] = $this->testo('Search');
                break;
            case 'equery' :
                //				print_r($in);
                //				$percorso[]['TESTO']=$this->testo('Equery');
                if (!isset ($in ['eform'])) {
                    $percorso [] ['TESTO'] = "<b>" . $this->testo('eQueryList') . "</b>";
                } else {
                    $percorso [] ['TESTO'] = $this->testo('eQueryList');
                    $percorso [count($percorso) - 1] ['HREF'] = $this->href('eQuery List');
                    if (!isset ($in ['ID'])) {
                        $percorso [] ['TESTO'] = '<b>' . $this->testo('newEquery') . '</b>';
                    } else {
                        $sql_dati_query = "select * from {$this->xmr_root->prefix}_equery where id=:eq_id";
                        $sql = new query ($this->conn);
                        //$sql->set_sql ( $sql_dati_query );
                        unset($bind);
                        $bind['EQ_ID'] = $in['ID'];
                        $sql->exec($sql_dati_query, $bind);//binded
                        $sql->get_row();
                        $dati_equery = $sql->row;
                        $percorso [] ['TESTO'] = "<b>eQuery n.ro {$sql->row['ID']}</b>";
                    }
                }
                break;
            case 'inbox' :
                $percorso [] ['TESTO'] = $this->testo('Inbox');
                break;
            case 'gest_profili' :
                $percorso [] ['TESTO'] = "<b>" . $this->testo('gest_prof') . "</b>";
                break;

        }

        $percorso_html = "";
        $n_links = count($percorso);
        foreach ($percorso as $key => $link) {
            if ($key != $n_links - 1)
                $percorso_html .= "<a href=\"{$link['HREF']}\" >{$link['TESTO']}</a> &gt;&gt; ";
            else
                $percorso_html .= $link ['TESTO'];
        }

        $percorso_html = "<p>$percorso_html</p>";

        foreach ($percorso as $key => $val) {
            $paths[] = array("", $val['TESTO'], $val['HREF']);

            $this->page_title = $val['TESTO'];
        }
        $this->breadcrumb = new BreadCrumb($paths);
        return "";
    }

    /**
     * Notifica eQuery
     *
     * @param String $switch_notifica
     * @param number $id
     * @return String
     */
    function notifica_equery($switch_notifica, $id)
    {

        $in = $this->session_vars;
//echo "Notifica:<hr>";
//print_r($in);
        $service = $this->service;
        $config_service = $this->config_service;
        $conn = $this->conn;

        $sql = new query ($conn);
        $sql->set_sql("select max(id) as maxid from " . $service . "_equery");
        $sql->exec();
        $sql->get_row();

        $query = "select nome||' '||cognome||' - '||azienda_ente as mitt from ana_utenti where userid='{$in['remote_userid']}'";
        $sql->set_sql($query);
        $sql->exec();
        $sql->get_row();
        //		echo $query;

        if ($_SERVER ['HTTPS'])
            $s = 's';
        $link = "http$s://" . $_SERVER ['HTTP_HOST'] . $_SERVER ['PHP_SELF'] . "?eQuery";

        switch ($switch_notifica) {
            case "1" :
                $where = "where a.userid=uc.userid and uc.center='{$in['CENTER']}' and ";
                $testo_mail = mlOut("System.eQuery.mail.request.sent_from", "New equery sent from") . " {$sql->row['MITT']} query n. $id
					<br /><br />
					" . mlOut("System.eQuery.mail.request.equeries_list", "Equeries list") . ":<br />
					<a href='$link'>$link</a>
					";
                break;
            case "2" :
                $where = ", {$service}_equery eq where eq.id='{$in['ID']}' and eq.center=uc.center and a.userid=uc.userid and ";
                $testo_mail = mlOut("System.eQuery.mail.answer.equery_answer", "Equery answer") . " n. $id
					<br /><br />
					" . mlOut("System.eQuery.mail.answer.equeries_list", "Equeries list") . ":<br />
					<a href='$link'>$link</a>
					";
                break;
            default :
                $where = " where ";
                return '';
        }

        //G.Tufano 27/07/2011
        //modifica: inserita la clausola per evitare di includere le farma territoriali tra i mittenti (lunghezza 9 e penultimo carattere = '0')

        if ($in ['USER_TIP'] == 'DE') {
            $query = "select email from ana_utenti a, {$service}_utenti_centri uc $where uc.tipologia like '%manager%' and a.userid not like '______00_' and a.userid not like '_______0_'";
            $sql->set_sql($query);
            $sql->exec();
            $to = '';
//			echo "if ".$query;die();
            while ($sql->get_row()) {
                if ($to != '')
                    $to .= ",";
                $to .= $sql->row ['EMAIL'];
            }

        } else {
            $query = "select email from ana_utenti a,{$service}_utenti_centri uc $where  uc.tipologia like '%Entry%' and a.userid not like '______00_' and a.userid not like '______0_'";
//			echo "else ".$query;die();
            $sql->set_sql($query);
            $sql->exec();

            $to = '';
            while ($sql->get_row()) {
                if ($to != '')
                    $to .= ",";
                $to .= $sql->row ['EMAIL'];
            }
//		echo $to."<hr>";
        }

        //**** INVIO MAIL
        include_once "send_email_common.inc";

        //differenzio se sono in test o no
        if ((preg_match("/sissdev/i", $_SERVER['SERVER_NAME'])) || (preg_match("/sissprep/i", $_SERVER['SERVER_NAME']))) {
            $test = '***TEST***';
        } else {
            $test = '';
        }

        //IMPOSTARE NEL CONFIG QUESTI PARAMETRI
        $from_service_email = $config_service ['from_service_email'];
        $from_service_name = $config_service ['from_service_name'];

        $reply_to = ($config_service['from_service_name'] == '') ? 'noreply@cineca.it' : $config_service ['from_service_name'];

        if ($config_service ['oggetto_notifiche'] != "")
            $oggetto = $test . $config_service ['oggetto_notifiche'] . "- query n. '.$id";
        else
            $oggetto = $test . $_SERVER ['SERVER_NAME'] . ' - query n. ' . $id;


//		echo "tutto ok";die($from_service_email.' '.$from_service_name);
        if ($testo_mail != '')
            send_email(null, $from_service_email, $from_service_name, $oggetto, $testo_mail, $reply_to, false, null, $to);
    }


    function getAdminProfili()
    {
        //estraggo i gestori dei profili
        $sql_query = "select * from user_views where view_name = '{$this->workflow->prefix}_ANA_ADMIN_PROFILI'";
        $sql_check = new query($this->conn);
        $sql_check->set_sql($sql_query);
        $sql_check->exec();//non richiede binding
        if ($sql_check->numrows > 0) {
            $sql_query = "select * from {$this->workflow->prefix}_ANA_ADMIN_PROFILI";
//			echo $sql_query;
            $sql = new query($this->conn);
            $sql->set_sql($sql_query);
            $sql->exec();//non richiede binding
            while ($sql->get_row()) {
                $this->admin_profili[] = $sql->row['USERID'];
            }

            //			} else {
            //				echo("Creare la vista {$this->workflow->prefix}_ANA_ADMIN_PROFILI con almeno il campo USERID contenente le user dei gestori dei profili");
            //			}
        }
    }

    /*
	 * admin_profili:
	 * Interfaccia di gestione del multiprofilo da parte degli utenti presenti nella vista [prefix]_gest_profili
	 *
	 * Tb dove salva le assegnazioni: [prefix]_admin_profili
	 *
	 * */
    function admin_profili_tb()
    {
        $invia_button = null;
        $colspan = null;
        $html = null;
        $table = null;
        $this->body .= $this->breadcrumb("gest_prof");
        $prefix = $this->workflow->prefix;

        $sql_query = "select * from user_all_tables where table_name='{$prefix}_ASSIGN_PROFILI'";
        $sql_check = new query($this->conn);
        $sql_check->get_row($sql_query);
        if ($sql_check->numrows == 0) {
            $create_sql = "
			CREATE TABLE {$prefix}_ASSIGN_PROFILI(
				USERID VARCHAR2(200 CHAR),
				PROFILE VARCHAR2(400 CHAR),
				PREDEF_ID VARCHAR2(400 CHAR),
				constraint pk_{$prefix}_userid primary key (userid,PROFILE)
			)";
            $sql_create = new query($this->conn);
            $sql_create->set_sql($create_sql);
            $sql_create->ins_upd();//non richiede binding

//			$values['USERID']=$this->user->userid;
//			$values['PROFILE']=$first_id;
//			$values['PREDEF_ID']='Yes';
//			$sql=new query($this->conn);
//			$sql->insert($values,"{$prefix}_ASSIGN_PROFILI");

            die("CREATA TABELLA $table ; inserire almeno un utente  a mano nella tabella creata.<br /> <a href=\"#\" onclick=\"window.location.href=window.location.href;\">Ricarica</a>");
        }

        if (in_array($this->user->userid, $this->admin_profili)) {

            //estraggo gli user dei profili
            $sql_query = "select * from user_views where view_name = '{$prefix}_ANA_USER_PROFILI'";
            $sql_check = new query($this->conn);
            //$sql_check->set_sql($sql_query);
            unset($bind_table);
            $bind_table['TABLE_NAME'] = "{$prefix}_ANA_USER_PROFILI";
            $sql_check->exec($sql_query, $bind_table);//binded
            if ($sql_check->numrows > 0) {
                $sql_query = "select * from {$prefix}_ANA_USER_PROFILI";
                $sql = new query($this->conn);
                $sql->set_sql($sql_query);
                $sql->exec();//non richiede binding
                while ($sql->get_row()) {
                    $this->user_profili[] = $sql->row['USERID'];
                }
            } else {
                die("Creare la vista {$prefix}_ANA_USER_PROFILI con almeno il campo USERID contenente le user dei gestori dei profili");
            }

            if (!in_array($this->user->userid, $this->admin_profili)) {
                die("L'utente {$this->user->userid} non  abilitato alla gestione dei multi-profili nella tabella [prefix]_ANA_ADMIN_PROFILI");
            }

            $sql_query = "select ID,DECODE from {$prefix}_attori_multi order by POS";
            $sql_check = new query($this->conn);
            $sql_check->exec($sql_query);//non richiede binding
            $all_profiles = array();
            while ($sql_check->get_row()) {
                $all_profiles[$sql_check->row['ID']] = $sql_check->row['DECODE'];
            }

            //salvo le impostazioni utenti-profili
            if (isset($_POST['salva_admin_profili']) && $_POST['salva_admin_profili'] != "") {
                foreach ($_POST as $key => $val) {
                    if (preg_match("/^checkbox_/", $key)) {
                        if ($val == "on")
                            $checkbox_array[] = str_replace("checkbox_", "", $key);
                    }

                    if (preg_match("/^sel_/", $key)) {
                        if ($val != "")
                            $sel_array[] = str_replace("sel_", "", $key) . "_$val";
                    }
                }
                $table = $prefix . "_ASSIGN_PROFILI";
                $query = "delete from $table";
                $sql_delall = new query($this->conn);
                $sql_delall->set_sql($query);
                $sql_delall->ins_upd();//non richiede binding
                $this->conn->commit();
                foreach ($checkbox_array as $key => $val) {
                    $checkbox_arr = explode("_", $val);
                    if (!in_array($checkbox_arr[0], $this->user_profili)) {
                        die("L'utente {$checkbox_arr[0]} non  abilitato alla gestione dei multi-profili nella tabella [prefix]_ANA_ADMIN_PROFILI");
                    }
                    $values['USERID'] = $checkbox_arr[0];
                    $values['PROFILE'] = $checkbox_arr[1];
                    $query = "select * from $table where USERID='{$checkbox_arr[0]}' and PROFILE='{$checkbox_arr[1]}'";
                    $sql_integrity = new query($this->conn);
                    $sql_integrity->get_row($query);
                    $sql = new query($this->conn);
                    $sql->insert($values, $table);
                    $this->conn->commit();

                }

                foreach ($sel_array as $key => $val) {
                    $sel_arr = explode("_", $val);
                    $table = $prefix . "_ASSIGN_PROFILI";
                    $values = array();
                    $pk = array();
                    $pk['USERID'] = $sel_arr[0];
                    $values['PREDEF_ID'] = "";
                    $sql_clean = new query($this->conn);
                    $sql_clean->update($values, $table, $pk);
                    $this->conn->commit();

                    $values = array();
                    $pk = array();
                    $pk['USERID'] = $sel_arr[0];
                    $pk['PROFILE'] = $sel_arr[1];
                    $values['PREDEF_ID'] = "Yes";
                    $sql_yes = new query($this->conn);
                    $sql_yes->update($values, $table, $pk);

                    $this->conn->commit();

                }

                header("Location: {$_SERVER['REQUEST_URI']}");


            }

            $html .= "
				<style>
				#admin_profili {
				margin:5px auto;
				border: 1px solid #1b358a;
				border-collapse: collapse
				}
				#admin_profili td {
				border: 1px solid #1b358a;
				padding:5px;
				}
				#admin_profili td.center {
				margin:auto;
				text-align:center;
				}
				</style>
				";
            $html .= "<a href=\"index.php\">Home</a>
			<p><h2 style=\"text-align:center;text-decoration:underline;font-weight:bold;\">Utilizzare questa tabella per abilitare alle utenze i profili del sistema</h2></p>";
            $html .= "<form method=\"POST\" id=\"profile_admin\"><table id=\"admin_profili\">";
            $html .= "<tr><td class=\"int\">Username</td>";

            foreach ($all_profiles as $id => $profile) {
                $html .= "<td class=\"int\"><b>" . $profile . "</b></td>";
            }
            $html .= "<td class=\"int\"> <b>Profilo predefinito</b> </td>";
            $html .= "</tr>";

            $html .= "<tr><td  class=\"int\">&nbsp;</td>";
            foreach ($all_profiles as $id => $profile) {
                $html .= "<td style=\"text-align:center;\" class=\"int\"><b>seleziona tutti</b><br /><input type=\"checkbox\" name=\"sel_all_$id\" onclick=\"if(this.checked) selall('$id','1'); else selall('$id','2');\" /></td>";
            }
            $html .= "<td class=\"int\">&nbsp;</td>";
            $html .= "</tr>";

            $table = $prefix . "_ASSIGN_PROFILI";
            $query = "select * from $table";
            $sql_ = new query($this->conn);
            $sql_->exec($query);//non richiede binding
            while ($sql_->get_row()) {
                $dump_arr[] = $sql_->row['USERID'] . "_" . $sql_->row['PROFILE'];
                $selected_arr[$sql_->row['USERID'] . "_" . $sql_->row['PROFILE']] = $sql_->row['PREDEF_ID'];
            }

            foreach ($this->user_profili as $id => $user) {
                $html .= "<tr>";
                $html .= "<td class=\"int\"> <b>" . $this->useridNome($user) . " ($user)</b> </td>";
                foreach ($all_profiles as $id => $profile) {
                    $colspan++;
                    $checked = $class = "";
                    if (in_array($user . "_" . $id, $dump_arr)) {
                        $checked = "checked=\"checked\"";
                        $class = "class=\"sc4bis\"";
                    }
                    $checkbox = "<input type=\"checkbox\" name=\"checkbox_{$user}_{$id}\" $checked 
					onclick=\"if(!this.checked && document.forms[0].sel_$user.value==$id) {
						document.forms[0].sel_$user.value='';
					} else if(this.checked && document.forms[0].sel_$user.value==$id) {
						document.forms[0].sel_$user.value='';	
					} else if(this.checked && document.forms[0].sel_$user.value=='') {
						document.forms[0].sel_$user.value=$id;			
					} 
					\" />";
                    $html .= "<td style=\"text-align:center;\" $class onclick=\"
					if(this.className=='sc4bis') {
						this.className='';
					} else {
						this.className='sc4bis';
					} \"> $checkbox </td>";

                }


                $option_predef = "<option value=\"\"></option>";
                $class_color = "";
                foreach ($all_profiles as $id => $profile) {
                    $selected = "";
                    if ($selected_arr[$user . "_" . $id] == "Yes") {
                        $selected = "selected=\"selected\"";
                    }
                    $option_predef .= "<option value=\"$id\" $selected>$profile</option>";
                    if ($selected != "") $class_color = "class=\"sc4bis\"";
                }

                $select_predef = "<select name=\"sel_{$user}\" onchange=\"check_predef('$user',this.value);
				\" />$option_predef</select>";
                $html .= "<td $class_color> $select_predef </td>";
                $html .= "</tr>";
            }
            $html .= "<tr>";

            $colspan_all = $colspan + count($this->user->profile_list);
            $invia_button .= "<td colspan=\"{$colspan_all}\" class=\"int\" style=\"text-align:center;\">
			<input type=\"submit\" value=\"Salva\" name=\"salva_admin_profili\" /></td></tr>";

            $html .= $invia_button;
            $html .= "</table></form>";
            $html .= "<p><a href=\"javascript:document.location.href=document.location.href;\"><h2 style=\"text-align:center;text-decoration:underline;font-weight:bold;\">Per ricaricare le impostazioni salvate aggiornare la pagina cliccando qui</h2></a></p>";

        } else {
            $html = "<h2 style=\"color:red;\">Utenza non abilitata alla gestione dei profili. Contattare l'assistenza tecnica.</h2>";
        }

        return $html;

    }

    function useridNome($userid)
    {
        $sql_str = "select nvl(nome||' ' ||cognome,'-') as nome from ana_utenti where userid = :userid";
        //		echo $sql_str;
        $sql = new query($this->conn);
        $bind['USERID'] = $userid;
        $sql->exec($sql_str, $bind);//binded
        $sql->get_row();
        return $sql->row['NOME'];
    }


    /**
     * Funzioni di libreria AIFA per gestire cancella/inserisci schede
     * G.Tufano 12/12/2011
     *
     */

    /**
     *
     * Funzione per cancellare un esame non progressivo
     * OVVIAMENTE con BINDING e senza toccare i costraints
     */
    function DeleteEsam($nome_tabella, $visitnum, $visitnum_progr, $esam, $progr = 1)
    {
        $in = $this->session_vars;
        global $conn;

        if ($in['ajax_call'] == '') {
            $sql = new query($this->conn);
            //0.0 estrazione tabella dell'esame
            if ($nome_tabella != '') {
                $table = $nome_tabella;
            } else {
                $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                $xml_form->xml_form_by_file($this->xml_dir . '/' . $this->vlist->esams [$visitnum] [$esam] ['XML']);
                $table = $xml_form->form ['TABLE'];
            }
            //echo $table;

            //preparo il binding
            $bind = array();
            $bind['userid'] = $this->user->userid;
            $bind['pk_service'] = $_GET[$this->config_service['PK_SERVICE']];
            $bind['visitnum'] = $visitnum;
            $bind['visitnum_progr'] = $visitnum_progr;
            $bind['esam'] = $esam;
            $bind['progr'] = $progr;


            //			0.1 LOCK sulle tabelle
            $sql_lock = "LOCK TABLE $table,{$this->service}_coordinate in EXCLUSIVE MODE";
            // 						echo "--REM 0.1) LOCK: <br />$sql_lock <hr />";
            $sql->exec($sql_lock);

            // 			0.2 Salvo la tabella nello storico
            $sql_storico = "insert into S_{$table}
						select :userid, 
						sysdate, 
						storico_id.nextval, 
						'V', 
						null, 
						{$table}.*
						from $table 
						where {$this->config_service['PK_SERVICE']}=:pk_service and 
						VISITNUM=:visitnum and 
						VISITNUM_PROGR=:visitnum_progr and 
						ESAM=:esam and
						progr = :progr
						";

            // 						echo "--REM 0.2)  storico: <br />$sql_storico <br />--" .print_r($bind,true)."<hr />";
            // 			die();
            $sql->ins_upd($sql_storico, $bind);

            //1. cancello dalla tabella la riga corrispondente
            $sql_del_row_coo = "DELETE {$table}
										WHERE
										esam=:esam
									and visitnum=:visitnum
									and visitnum_progr=:visitnum_progr
									and {$this->config_service['PK_SERVICE']}= :pk_service
									and progr = :progr
									";
            // 			 			echo "--REM 1)  cancello la riga da coord: <br />$sql_del_row_coo <br />--" . print_r($bind,true)."<hr />";
            //  			die();
            $sql->ins_upd($sql_del_row_coo, $bind);

            //2. riapro la scheda
            $sql_open_visit = "UPDATE {$this->service}_coordinate
												SET inizio = NULL,
													fine = NULL,
													--insertdt = NULL,
													--MODDT = NULL,
													--USERID = NULL,
													abilitato = 1
													--eq_action = NULL
												
												WHERE visitnum=:visitnum
												and visitnum_progr=:visitnum_progr
												and esam = :esam
												and {$this->config_service['PK_SERVICE']}= :pk_service
												and progr = :progr
								";
            // 						echo "--REM 2) Riapro la visita con inizio e fine: <br /> $sql_open_visit<br />--" . print_r($bind,true)."<hr />";

            $sql->ins_upd($sql_open_visit, $bind);


            //2.1. infine controllo che la visita venga riaperta: visitclose =0
            $sql_open_visit = "UPDATE {$this->service}_coordinate
									SET visitclose = 0
									WHERE visitnum=:visitnum
									and visitnum_progr=:visitnum_progr
									and {$this->config_service['PK_SERVICE']}= :pk_service
									and progr = :progr
					";
            // 						echo "--REM 2.1) Riapro la visita con visitclose: <br /> $sql_open_visit<br />--" . print_r($bind,true)."<hr />";
            // 			die();

            $sql->ins_upd($sql_open_visit, $bind);
            // 				die();
            $this->conn->commit();
        }

    }


    /**
     * Cancella un esame progressivo tra altri 2 in una tabella, e
     * si preoccupa automagicamente di sistemare anche le tabelle correlate
     *
     * in modalit "Don't Touch Costraints!!!" (Edo copyright)
     * __creata da Giacomo Tufano 12/11/2010__
     *
     * @param number $visitnum
     * @param number $visitnum_progr
     * @param number $esam
     * @param number $progr
     */
    function DeleteProgrEsamConCorrelate($nome_tabella, $visitnum, $visitnum_progr, $esam, $progr)
    {
        $sql = new query($this->conn);

        // 	 	echo $this->vlist->esams[$visitnum][$esam]['CORR'];die();
        //se sono il correlativo di qualcuno, non devo cancellare tutti i progr a catena, ma solo me stesso!
        if ($this->vlist->esams[$visitnum][$esam]['CORR'] != '') {
            $this->DeleteEsam($nome_tabella, $visitnum, $visitnum_progr, $esam, $progr);
        } else {
            $this->DeleteProgrEsam($nome_tabella, $visitnum, $visitnum_progr, $esam, $progr);
        }


        $sql_count = "select max(esam) as MAXE,min(esam) as MINE
		 	from {$this->service}_coordinate  
		 	where
		 	visitnum={$visitnum} 
		 	and {$this->config_service['PK_SERVICE']}='{$this->pk_service}'";
        // echo $sql_count."<hr>";
        $sql->set_sql($sql_count);
        $sql->exec();
        $sql->get_row();

        $maxe = $sql->row['MAXE'];
        $mine = $sql->row['MINE'];
        $ncorr = -1;
        for ($nes = $mine; $nes <= $maxe; $nes++) {
            //    echo $nes."<hr>";
            if ($this->vlist->esams[$visitnum][$nes]['CORR'] == $esam)
                $ncorr = $nes;
        }
        //	  	   echo $ncorr."<hr>";
        if ($ncorr != -1) {
            $xml_form_corr = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
            $xml_form_corr->xml_form_by_file($this->xml_dir . '/' . $this->vlist->esams [$visitnum] [$ncorr] ['XML']);
            $table_corr = $xml_form_corr->form ['TABLE'];
            //print_r($xml_form_corr);die();
            $this->DeleteProgrEsam($table_corr, $visitnum, $visitnum_progr, $ncorr, $progr);
        }
    }

    static function SDeleteProgrEsam($conn, $config_service, $session_vars, $xmldir, $xml, $userid, $pk_service, $esam, $progr, $visitnum, $visitnum_progr)
    {
        $errors = null;
        $sql = new query($conn);
        $xml_form = new xml_form ($conn, $config_service['service'], $config_service, $session_vars, $xmldir);
        $xml_form->xml_form_by_file($xmldir . '/' . $xml);
        $table = $xml_form->form ['TABLE'];
        $bind = array();
        $bind['userid'] = $userid;
        $bind['pk_service'] = $pk_service;
        $bind['visitnum'] = $visitnum;
        $bind['visitnum_progr'] = $visitnum_progr;
        $bind['esam'] = $esam;
        $bind['progr'] = $progr;
        //Controllo la foreign key verso coordinate
        $sql_query_fk = "
			select 
			c.CONSTRAINT_NAME, c.DELETE_RULE, c.STATUS, c.DEFERRABLE,c.DEFERRED, c.VALIDATED 
			from user_constraints c, user_constraints c1  where c.CONSTRAINT_TYPE='R' and c.TABLE_NAME=upper('{$table}') and c1.CONSTRAINT_NAME=c.R_CONSTRAINT_NAME
			and c1.TABLE_NAME='{$config_service['service']}_COORDINATE'";
        if ($sql->get_row($sql_query_fk)) {
            //Se presente controllo che sia DEFERRABLE e DEFERRED altrimenti la droppo e la ricreo DEFERRABLE e DEFERRED
            if ($sql->row['DEFERRABLE'] != 'DEFERRABLE' || $sql->row['DEFERRED'] != 'DEFERRED') {
                $alter1 = "ALTER TABLE $table drop constraint {$sql->row['CONSTRAINT_NAME']}";
                $alter2 = "ALTER TABLE $table ADD CONSTRAINT {$sql->row['CONSTRAINT_NAME']} 
			FOREIGN KEY({$config_service['PK_SERVICE']}, ESAM, VISITNUM, VISITNUM_PROGR, PROGR) 
			REFERENCES {$config_service['service']}_COORDINATE({$config_service['PK_SERVICE']}, ESAM, VISITNUM, VISITNUM_PROGR, PROGR) ";
                if ($sql->row['DELETE_RULE'] == 'CASCADE') $alter2 .= " ON DELETE CASCADE ";
                $alter2 .= "DEFERRABLE INITIALLY DEFERRED";
                if ($sql->row['STATUS'] == 'ENABLED') $alter2 .= " ENABLE";
                if ($sql->row['VALIDATED'] == 'VALIDATED') $alter2 .= " VALIDATE";
                $sql->ins_upd($alter1);
                $sql->ins_upd($alter2);

            }
        }
        //Locko la tabella
        $sql_lock = "LOCK TABLE $table in EXCLUSIVE MODE";
        $sql->set_sql($sql_lock);
        $sql->ins_upd();

        //Inserimento in storico:
        $sql_storico = "insert into S_{$table}
				select :userid,
				sysdate,
				storico_id.nextval,
				'E',
				(select inv_query from {$config_service['service']}_COORDINATE where  {$config_service['PK_SERVICE']}=:pk_service and VISITNUM=:visitnum and VISITNUM_PROGR=:visitnum_progr and ESAM=:esam and PROGR=:progr),
				{$table}.*
				from $table
				where {$config_service['PK_SERVICE']}=:pk_service and
				VISITNUM=:visitnum and
							VISITNUM_PROGR=:visitnum_progr and 
							ESAM=:esam and 
							PROGR=:progr
							";
//
//
        $sql->ins_upd($sql_storico, $bind);
        unset($bind['userid']);
        $sql_query = "select * from $table where ESAM=:esam and VISITNUM=:visitnum and VISITNUM_PROGR=:visitnum_progr and PROGR=:progr and {$config_service['PK_SERVICE']}=:pk_service";
        $sql = new query($conn);
        $sql->get_row($sql_query, $bind);
        $db_vals = $sql->row;
        foreach ($xml_form->fields as $key => $val) {
            if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                $field_type = "field_{$val['TYPE']}";
            else
                $field_type = "field";

            if ($config_service['field_lib'] != '' && file_exists($config_service['field_lib'] . $field_type . ".inc")) {
                include_once $config_service['field_lib'] . $field_type . ".inc";
            } else
                include_once "{$field_type}.inc";
            $field_obj = new $field_type ($xml_form, $key, $conn, $db_vals, $session_vars, $config_service['service'], $errors);
            //Funzione per la gestione avanzata della delete (fondamentalmente nei field legati alla WCA per impostare a Trash il documento
            if (method_exists($field_obj, "gestDelete")) {
                $field_obj->gestDelete($conn);
            }
        }
        $check_visitclose = "select visitclose from {$config_service['service']}_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service and
				VISITNUM=:visitnum and
							VISITNUM_PROGR=:visitnum_progr and 
							ESAM=:esam  and 
							PROGR=:progr
							";
        $sql->get_row($check_visitclose, $bind);
        $visitclose = $sql->row['VISITCLOSE'];
        $delete_coord = "delete from {$config_service['service']}_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service and
				VISITNUM=:visitnum and
							VISITNUM_PROGR=:visitnum_progr and 
							ESAM=:esam and 
							PROGR=:progr";
        //verifico che ci sia almeno una progr dopo il delete se no reinserisco la prima
        $check_n_progr = "select count(progr) conto from {$config_service['service']}_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service and
				VISITNUM=:visitnum and
							VISITNUM_PROGR=:visitnum_progr and 
							ESAM=:esam  
							";
        $values_one_progr[$config_service['PK_SERVICE']] = $pk_service;
        $values_one_progr['VISITNUM'] = $visitnum;
        $values_one_progr['VISITNUM_PROGR'] = $visitnum_progr;
        $values_one_progr['ESAM'] = $esam;
        $values_one_progr['PROGR'] = 1;
        $values_one_progr['ABILITATO'] = 1;
        $values_one_progr['VISITCLOSE'] = $visitclose;
        $values_one_progr['INSERTDT'] = 'sysdate';

        if ($config_service['ALLOW_BLANK_PROGR'] != 1) {
            $update_coordinate = "update {$config_service['service']}_COORDINATE set progr=progr-1 where {$config_service['PK_SERVICE']}=:pk_service and
				VISITNUM=:visitnum and
							VISITNUM_PROGR=:visitnum_progr and 
							ESAM=:esam and 
							PROGR>:progr";
            $update_table = "update {$table} set progr=progr-1 where {$config_service['PK_SERVICE']}=:pk_service and
				VISITNUM=:visitnum and
							VISITNUM_PROGR=:visitnum_progr and 
							ESAM=:esam and 
							PROGR>:progr";
            foreach ($xml_form->fields as $key => $val) {
                if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                    $field_type = "field_{$val['TYPE']}";
                else
                    $field_type = "field";

                if ($config_service['field_lib'] != '' && file_exists($config_service['field_lib'] . $field_type . ".inc")) {
                    include_once $config_service['field_lib'] . $field_type . ".inc";
                } else
                    include_once "{$field_type}.inc";
                $field_obj = new $field_type ($xml_form, $key, $conn, $db_vals, $session_vars, $config_service['service'], $errors);
                //Funzione per la gestione avanzata della update (fondamentalmente nei field legati alla WCA per impostare correttamente le keywords
                if (method_exists($field_obj, "gestDelete")) {
                    $field_obj->gestChangeProgr($conn, $progr);
                }
            }
        }
//
//
        $sql->ins_upd($delete_coord, $bind);
        $sql->get_row($check_n_progr, $bind);
        if ($sql->row['CONTO'] == '0') {
            $sql->insert($values_one_progr, $config_service['service'] . '_COORDINATE');
        }
        if ($config_service['ALLOW_BLANK_PROGR'] != 1) {
//
//
//
//
            $sql->ins_upd($update_coordinate, $bind);
            $sql->ins_upd($update_table, $bind);
        }
//
    }

    /**
     * Cancella un esame progressivo
     * in modalit "Don't Touch Costraints!!!" (Edo copyright)
     * __creata da Giacomo Tufano 12/11/2010__
     *
     * UPDATE 16/11/2011 --> ORA CON BINDING!
     *
     * @param number $visitnum
     * @param number $visitnum_progr
     * @param number $esam
     * @param number $progr
     */
    function DeleteProgrEsam($nome_tabella, $visitnum, $visitnum_progr, $esam, $progr)
    {
        $in = $this->session_vars;

        global $conn;
        //
        if (isset($this->integrazione) && !$this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_ESAM'][$esam] && !$this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$visitnum] && $this->integrazione->profilo == $this->integrazione->role && $this->session_vars['per_integrazione'] == 'true') {

            if ($this->integrazione->eq_int == '') {

                $valuesEq['EQUERY_INT'] = "{$this->service}_EQSEQ.nextval";
                $valuesEq[$this->config_service['PK_SERVICE']] = $_GET[$this->config_service['PK_SERVICE']];
                $valuesEq['INS_DT'] = "sysdate";
                $valuesEq['STATO'] = 0;
                $valuesEQ['USERID_INS'] = $this->user->userid;
                $sql = new query($this->conn);
                $sql->insert($valuesEq, $this->service . "_EQ");
                $sql_query = "select {$this->service}_EQSEQ.currval as eq_int from dual";
                $sql->get_row($sql_query);
                $this->integrazione->eq_int = $sql->row['EQ_INT'];

            }
            $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
            $xml_form->xml_form_by_file($this->xml_dir . '/' . $this->vlist->esams [$visitnum] [$esam] ['XML']);
            $table = $xml_form->form ['TABLE'];

            $pk[$this->config_service['PK_SERVICE']] = $_GET[$this->config_service['PK_SERVICE']];
            $pk['ESAM'] = $_GET['ESAM'];
            $pk['VISITNUM'] = $_GET['VISITNUM'];
            $pk['VISITNUM_PROGR'] = $_GET['VISITNUM_PROGR'];
            $pk['PROGR'] = $_GET['PROGR'];
            $sql_query = "select * from $table where ESAM={$pk['ESAM']} and VISITNUM={$pk['VISITNUM']} and VISITNUM_PROGR={$pk['VISITNUM_PROGR']} and PROGR={$pk['PROGR']} and {$this->config_service['PK_SERVICE']}={$pk[$this->config_service['PK_SERVICE']]}";
            $sql = new query($this->conn);
//
            $sql->get_row($sql_query);
            $db_vals = $sql->row;
            foreach ($xml_form->fields as $key => $val) {
                if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                    $field_type = "field_{$val['TYPE']}";
                else
                    $field_type = "field";

                if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                    include_once $this->config_service['field_lib'] . $field_type . ".inc";
                } else
                    include_once "{$field_type}.inc";
                $field_obj = new $field_type ($xml_form, $key, $this->conn, $db_vals, $this->session_vars, $this->service, $this->errors);
                $field_obj->insert_stmt();
                foreach ($field_obj->field_stmt as $k1 => $field) {
                    if (!isset($pk[$field])) {
                        $valuesEqField = '';
                        foreach ($pk as $k2 => $v2) {
                            $valuesEqField[$k2] = $v2;
                        }
                        $valuesEqField['VALORE'] = $db_vals[$field];
                        $valuesEqField['FIELD'] = $field;
                        $valuesEqField['ACTION'] = 2;
                        $valuesEqField['EQ_INT'] = $this->integrazione->eq_int;
                        $pk1 = '';
                        $sql->insert($valuesEqField, $this->service . "_EQFIELD", $pk1);
                    }
                }
            }
            $coordUpdateValues['EQ_ACTION'] = 2;
            $coordUpdateValues['INV_QUERY'] = $this->integrazione->eq_int;
            $sql->update($coordUpdateValues, $this->service . "_COORDINATE", $pk);

            //effettuo inserimenti in eqfield con action=2
            $this->conn->commit();
            return;

        }
        if ($in['ajax_call'] == '') {
            $sql = new query($this->conn);
            call_user_func(__CLASS__ . "::SDeleteProgrEsam", $this->conn, $this->config_service, $this->session_vars, $this->xml_dir, $this->vlist->esams [$visitnum] [$esam] ['XML'], $this->session_vars['remote_userid'], $_GET[$this->config_service['PK_SERVICE']], $esam, $progr, $visitnum, $visitnum_progr);
            $this->conn->commit();
            return;
            /*MODIFICA  Carlo Contino 30/01/2012 Questa parte viene gestita dalla statica SDeleteProgrEsam


	// 			0.2 Salvo la tabella nello storico
	$sql_storico = "insert into S_{$table}
	select :userid,
	sysdate,
	storico_id.nextval,
	'V',
	null,
	{$table}.*
	from $table
	where {$this->config_service['PK_SERVICE']}=:pk_service and
	VISITNUM=:visitnum and
				VISITNUM_PROGR=:visitnum_progr and
				ESAM=:esam and
				PROGR=:progr
				";

	// 			echo "--REM 0.2)  storico: <br />$sql_storico <br />--" .print_r($bind,true)."<hr />";
	// 			die();
				$sql->ins_upd ($sql_storico,$bind);


				//1.1 controllo quanti progr sono
				$sql_maxq = "
								select
					nvl(max(progr),0) as conto
					from {$this->service}_coordinate
					where esam= :esam
					and visitnum=:visitnum
					and visitnum_progr=:visitnum_progr
					and {$this->config_service['PK_SERVICE']}=:pk_service";

// 					echo "--REM 2.1)  TROVA MAX:<br /> $sql_maxq <br />--" . print_r($bind,true)."<hr />";
				// 			die();
				$sql->exec ($sql_maxq,$bind);
				$sql->get_row ();



				$bind['max_progr'] = $sql->row ['CONTO'];
				// 			echo "<hr />TOTALE:". $bind['max_progr']." <hr />";die();

				//1.2 cancello da coordinate la riga corrispondente
	$sql_del_row_coo = "DELETE {$this->service}_coordinate
	WHERE
	esam=:esam
	and visitnum=:visitnum
	and visitnum_progr=:visitnum_progr
	and {$this->config_service['PK_SERVICE']}= :pk_service
	and progr = :progr";
// 	 			echo "--REM 1)  cancello la riga da coord: <br />$sql_del_row_coo <br />--" . print_r($bind,true)."<hr />";
// 	 			die();

				$sql->ins_upd ($sql_del_row_coo,$bind);


				//2. aggiungo un rigo in COORDINATE
	$sql_add_coo = "insert into {$this->service}_coordinate
	(VISITNUM, VISITNUM_PROGR, PROGR, ESAM, VISITCLOSE, {$this->config_service['PK_SERVICE']}, ABILITATO)
	VALUES
	(:visitnum, :visitnum_progr, :max_progr + 1 , :esam, 0, :pk_service, 1)";
	// 			echo "--REM 2.2) aggiungo una riga in COORDINATE:  <br />$sql_add_coo <br />--" . print_r($bind,true)."<hr />";
	// 			die();
				$sql->ins_upd ($sql_add_coo,$bind);

				//3. in COORDINATE tutte le righe da ultima fino a progr attuale shiftano: PROGR = PROGR-1
				$sql_update_coo = "UPDATE {$this->service}_coordinate
	SET progr = progr - 1
	WHERE
	esam=:esam
	and visitnum=:visitnum
	and visitnum_progr=:visitnum_progr
	and {$this->config_service['PK_SERVICE']}= :pk_service
	and progr > :progr
	";

	// 			echo "--REM 3)  Shift in coordinate: <br />$sql_update_coo<br />--" . print_r($bind,true)."<hr />";
	// 			die();
				$sql->ins_upd ($sql_update_coo,$bind);

				//4. in TABLE shifto i progr: PROGR = PROGR -1 da ultima fino a progr
				$sql_update_tab = "UPDATE $table
								SET progr = progr - 1
								WHERE
								esam=:esam
	and visitnum=:visitnum
	and visitnum_progr=:visitnum_progr
	and {$this->config_service['PK_SERVICE']}= :pk_service
	and progr >= :progr
	";
// 				echo "--REM 4) Shift in TABLE:  <br />$sql_update_tab<br />--" . print_r($bind,true)."<hr />";
	// 			die();
	$sql->ins_upd ($sql_update_tab,$bind);


				//5. cancello la riga MAX_PROGR in coordinate
				$sql_del_last_riga_coo = "delete {$this->service}_coordinate
	WHERE
	esam=:esam
	and visitnum=:visitnum
								and visitnum_progr=:visitnum_progr
								and {$this->config_service['PK_SERVICE']}= :pk_service
								and progr = :max_progr";
// 				echo "--REM 5) cancello max_progr in coordinate: <br /> $sql_del_last_riga_coo<br />--" . print_r($bind,true)."<hr />";
// 	 			die();
	$sql->ins_upd ($sql_del_last_riga_coo,$bind);

				//6. infine controllo che la visita venga riaperta: visitclose =0
				$sql_open_visit = "UPDATE {$this->service}_coordinate
								SET visitclose = 0
								WHERE visitnum=:visitnum
								and visitnum_progr=:visitnum_progr
								and {$this->config_service['PK_SERVICE']}= :pk_service
								";
// 											echo "--REM 6) Riapro la visita: <br /> $sql_open_visit<br />--" . print_r($bind,true)."<hr />";

								$sql->ins_upd ($sql_open_visit,$bind);

	$this->conn->commit();
*/
        }

    }


    /**
     * Inserisce un esame progressivo tra altri 2
     * in modalit "Don't Touch Costraints!!!" (Edo copyright)
     * __creata da Giacomo Tufano 11/11/2010__
     *
     * @param number $visitnum
     * @param number $visitnum_progr
     * @param number $esam
     * @param number $progr
     */
    function InsertProgrEsam($nome_tabella, $visitnum, $visitnum_progr, $esam, $progr)
    {
        $in = $this->session_vars;
        global $conn;
        //global $visit_exam;
        //$vlist= new xml_esams_list($xml_dir.'/'.$visit_exam);

        if ($in['ajax_call'] == '') {
            $sql = new query($this->conn);
            //0.0 estrazione tabella dell'esame
            if ($nome_tabella != '') {
                $table = $nome_tabella;
            } else {
                $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                $xml_form->xml_form_by_file($this->xml_dir . '/' . $this->vlist->esams [$visitnum] [$esam] ['XML']);
                $table = $xml_form->form ['TABLE'];
            }
            //echo $table;

            //preparo il binding
            $bind = array();
            $bind['userid'] = $this->user->userid;
            $bind['pk_service'] = $_GET[$this->config_service['PK_SERVICE']];
            $bind['visitnum'] = $visitnum;
            $bind['visitnum_progr'] = $visitnum_progr;
            $bind['esam'] = $esam;
            $bind['PROGR'] = $progr;

            //			0.1 LOCK sulle tabelle
            $sql_lock = "LOCK TABLE $table,{$this->service}_coordinate in EXCLUSIVE MODE";
            // 			echo "--REM 0.1) LOCK: <br />$sql_lock <hr />";
            $sql->set_sql($sql_lock);
            $sql->ins_upd();

            //0.2 Salvo la tabella nello storico
            $sql_storico = "insert into S_{$table}
				select 
					:userid, 
					sysdate, 
					storico_id.nextval, 
					'V', 
					null, 
					{$table}.*  
				from $table 
				where 
					{$this->config_service['PK_SERVICE']}= :pk_service and 
					VISITNUM= :visitnum and 
					VISITNUM_PROGR= :visitnum_progr and 
					ESAM= :esam and 
					PROGR >= :progr
				
				";
            // 			echo "--REM 0.2) storico:  <br />$sql_storico<br />".print_r($bind,true)."<hr />";
            // 			die();
            $sql->ins_upd($sql_storico, $bind);

            //1.1 controllo quanti progr sono
            $sql_maxq = "
				select
					max(progr) as conto
				from {$this->service}_coordinate
				where 
					esam= :esam
					and visitnum= :visitnum
					and visitnum_progr=$visitnum_progr
					and {$this->config_service['PK_SERVICE']}= :pk_service
				";
            // 			echo "--REM 1.1a) controllo il nume di progr:  <br />$sql_maxq<br />".print_r($bind,true);
            $sql->exec($sql_maxq, $bind);
            $sql->get_row();
            $max_progr = $sql->row ['CONTO'];
            // 			echo "<br /> VALORE TROVATO: $max_progr<hr />";
            // 			die();


            $bind['max_progr'] = $sql->row ['CONTO'];
            //1.2 aggiungo un rigo in COORDINATE
            $sql_add_coo = "
								insert into {$this->service}_coordinate 
								(VISITNUM, VISITNUM_PROGR, PROGR, ESAM, VISITCLOSE, {$this->config_service['PK_SERVICE']}, ABILITATO)
									VALUES 
								(:visitnum, :visitnum_progr, :max_progr + 1 ,:esam, 0, :pk_service, 1)";
            // 			echo "--REM 1.2) aggiungo una riga in COORDINATE:  <br />$sql_add_coo<br />".print_r($bind,true)."<hr />";
            // 			die();
            $sql->ins_upd($sql_add_coo, $bind);

            //2. in TABLE tutte le righe da ultima fino a progr attuale shiftano: PROGR = PROGR+1
            $sql_update_table = "UPDATE $table
								SET progr = progr +1
								WHERE 
								esam= :esam
								and visitnum= :visitnum
								and visitnum_progr= :visitnum_progr
								and {$this->config_service['PK_SERVICE']}= :pk_service
								and progr >= :progr
				";

            // 			echo "--REM 2) Shift in table:  <br />$sql_update_table<br />".print_r($bind,true)."<hr />";
            // 			die();
            $sql->ins_upd($sql_update_table, $bind);

            //3. in COORDINATE shifto TUTTI I CAMPI tranne le coordinate da PROGR a PROGR +1
            /*			for ($i= $max_progr; $i >= $progr; $i--){
			$sql_update_coo = "UPDATE {$this->service}_coordinate
			SET
			(INIZIO, FINE, INSERTDT, MODDT, USERID, VISITCLOSE, INV_QUERY, {$this->config_service['PK_SERVICE']}, ABILITATO)
			=
			(SELECT INIZIO, FINE, INSERTDT, MODDT, USERID, VISITCLOSE, INV_QUERY, {$this->config_service['PK_SERVICE']}, ABILITATO
			from {$this->service}_coordinate where
			esam=$esam
			and visitnum=$visitnum
			and visitnum_progr=$visitnum_progr
			and {$this->config_service['PK_SERVICE']}= '{$this->pk_service}'
			and progr = $i )
			WHERE
			esam=$esam
			and visitnum=$visitnum
			and visitnum_progr=$visitnum_progr
			and {$this->config_service['PK_SERVICE']}= '{$this->pk_service}'
			and progr = $i+1 ";
			//				echo "3) Shift in COORDINATE: ".$sql_update_coo;echo "<hr />";
			$sql->set_sql ( $sql_update_coo );
			$sql->ins_upd ();
			}
			*/
            $sql_update_coo = "UPDATE {$this->service}_coordinate
			SET progr = progr +1
			WHERE
			esam= :esam
			and visitnum= :visitnum
			and visitnum_progr= :visitnum_progr
								and {$this->config_service['PK_SERVICE']}= :pk_service
								and progr >= :progr
				";
            // 			echo "--REM 3) Shift in COORDINATE:  <br />$sql_update_coo<br />".print_r($bind,true)."<hr />";
            // 			die();
            $sql->ins_upd($sql_update_coo, $bind);


            //4. infine inserisco la riga PROGR mancante
            $sql_ins_missing_riga_coo = "insert into {$this->service}_coordinate
			(VISITNUM, VISITNUM_PROGR, PROGR, ESAM, VISITCLOSE, {$this->config_service['PK_SERVICE']}, ABILITATO)
									VALUES 
			(:visitnum, :visitnum_progr, :progr , :esam, 0, :pk_service, 1)
				";
            // 			echo "--REM 4) inserisco un'altra riga in coordinate:  <br />$sql_ins_missing_riga_coo<br />".print_r($bind,true)."<hr />";
            // 			die();
            $sql->ins_upd($sql_ins_missing_riga_coo, $bind);

            //5. cancello infine il campo in pi
            $sql_del_row_coo = "DELETE {$this->service}_coordinate
			WHERE
			esam= :esam
			and visitnum= :visitnum
			and visitnum_progr= :visitnum_progr
			and {$this->config_service['PK_SERVICE']}= :pk_service
								and progr = :max_progr + 2";
            // 			echo "--REM 5) cancello la riga in eccesso:  <br />$sql_del_row_coo<br />".print_r($bind,true)."<hr />";
            // 			die();
            $sql->ins_upd($sql_del_row_coo, $bind);

            // 			die();

            $this->conn->commit();
        }

    }


    /**
     * Inserisce un esame progressivo tra altri 2 in una tabella, e
     * si preoccupa automagicamente di sistemare anche le tabelle correlate
     *
     * in modalit "Don't Touch Costraints!!!" (Edo copyright)
     * __creata da Giacomo Tufano 11/11/2010__
     *
     * @param number $visitnum
     * @param number $visitnum_progr
     * @param number $esam
     * @param number $progr
     */
    function InsertProgrEsamConCorrelate($nome_tabella, $visitnum, $visitnum_progr, $esam, $progr)
    {
        $sql = new query($this->conn);
        $this->InsertProgrEsam($nome_tabella, $visitnum, $visitnum_progr, $esam, $progr);

        //preparo il binding
        $bind = array();
        $bind['userid'] = $this->user->userid;
        $bind['pk_service'] = $this->pk_service;
        $bind['visitnum'] = $visitnum;
        $bind['visitnum_progr'] = $visitnum_progr;
        $bind['esam'] = $esam;
        $bind['PROGR'] = $progr;

        $sql_count = "select max(esam) as MAXE,min(esam) as MINE  
		 from {$this->service}_coordinate
		 where
		 visitnum= :visitnum
		 	and {$this->config_service['PK_SERVICE']}= :pk_service
		 	";
        // echo $sql_count."<br />".print_r($bind,true)."<hr>";

        $sql->exec($sql_count, $bind);
        $sql->get_row();

        $maxe = $sql->row[MAXE];
        $mine = $sql->row[MINE];

        $esami_corr = array();
        for ($nes = $mine; $nes <= $maxe; $nes++) {
            //    echo $nes."<hr>";
            if ($this->vlist->esams[$visitnum][$nes]['CORR'] == $esam)
                $esami_corr[] = $nes;
        }
        // 	 	 echo print_r($esami_corr,true).'<hr>';die();

        foreach ($esami_corr as $ncorr) {
            // 	  	   	echo $ncorr;die();
            $xml_form_corr = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
            $xml_form_corr->xml_form_by_file($this->xml_dir . '/' . $this->vlist->esams [$visitnum] [$ncorr] ['XML']);
            // 		  	print_r($xml_form_corr);die();
            $table_corr = $xml_form_corr->form ['TABLE'];

            $this->InsertProgrEsam($table_corr, $visitnum, $visitnum_progr, $ncorr, $progr);
        }
    }


    function trasferisci_paziente($codice_pat, $centro_OLD, $CENTRO_new)
    {
        echo "vaiiiii";
        die();
    }

    /**
     *
     * Metodo utilizzato per sapere la tipologia di un utente
     *
     * @param $userid
     * @param $center
     */
    protected function getTipologia($userid, $center)
    {
        //echo "<hr>".$userid;
        global $conn;
        $query = new query($conn);
        $sql = "select tipologia from {$this->service}_utenti_centri where userid= :userid and center = :center";
        // 		$query->set_sql($sql);
        $bind = array();
        $bind['USERID'] = $userid;
        $bind['CENTER'] = $center;
        $query->exec($sql, $bind);
        $query->get_row();
        $perfil = $query->row['TIPOLOGIA'];
        return $perfil;
    }


    //restituisce il percorso dell'xmr, al livello che mi interessa
    //G.Tufano 20/03/2012
    function getXMRPath($tipo, $filename = null)
    {
        $ret = '';
        switch ($tipo) {
            //restituisce il percorso completo, a parte il nome dello script
            case 'full':
                $dirs = explode("/", $_SERVER['PATH_TRANSLATED']);
                for ($i = 0; $i < count($dirs) - 1; $i++) {
                    $ret .= $dirs[$i] . "/";
                }
                break;

            //restituisce la dir della libreria o quella locale a seconda di dove trova il file xml
            case 'xml_dir':            /*$dirs=explode("/",__FILE__);
									for ($i=0;$i<count($dirs)-1;$i++){
										$dir_lib.=$dirs[$i]."/";
									}*/
                $dir_lib = $this->config_service['dir_lib'];
                //specifico questo controllo in ordine a seconda di dove voglio controllare.
                //1) dentro la cartella ARMONIA
                $dir_lib .= '/xml/';
                if ($filename != '' && file_exists($dir_lib . $filename)) {
                    $ret = $dir_lib;
                } else {
                    $ret = $this->xml_dir;
                }
                break;

            //restituisce la dir della libreria o quella locale a seconda di dove trova il file xml
            case 'templates_dir':
                $dir_lib = $this->config_service['dir_lib'];
                //specifico questo controllo in ordine a seconda di dove voglio controllare.
                //1) dentro la cartella ARMONIA
                $dir_lib .= '/templates/';
                if ($filename != '' && file_exists($dir_lib . $filename)) {
                    $ret = $dir_lib;
                } else {
                    $ret = '.';
                }
                break;

            //restituisce la root del registro
            case 'dir_registro':
                $ret = $_SERVER['DOCUMENT_ROOT'];
                break;

            //restituisce la root del servizio (se  srevizio root corrisponde a dir_registro, altrimenti  il registro padre
            case 'dir_servizio':
            default:
                $dirs = explode("/", $_SERVER['PATH_TRANSLATED']);
                for ($i = 0; $i < count($dirs) - (1 * $this->xmr->depth + 1); $i++) {
                    $ret .= $dirs[$i] . "/";
                }
        }

        $ret = rtrim($ret, "/");
        // 		print_r($_SERVER);die();
        return $ret;

    }


    /*******************************************************************************************************
     * Funzioni private e statiche
     * G.Tufano
     *
     *******************************************************************************************************/
    private function _print_table_res_query($sql)
    {
// 		print_r($sql);die();
        $body = '<table border="1px"><tr><th>ID</th>';

        foreach ($sql->keys as $chiave) {
            $body .= '<th>' . $chiave . '</th>';
        }
        $body .= '</tr>';


// 		echo "keys = {$sql->keys[2]} val = {$sql->res[$sql->keys[2]][5]}";die();
        for ($i = 0; $i < $sql->numrows; $i++) {
            $body .= '<tr><td>' . $i . '</td>';
            for ($j = 0; $j < $sql->numcols; $j++) {
                $body .= '<td>' . $sql->res[$sql->keys[$j]][$i] . '</td>';
            }
            $body .= '</tr>';
        }

        $body .= '</tr></table>';
        return $body;
    }


    public static function _elimina_files_e_dirs($dirname)
    {
//
        if (file_exists($dirname) && is_file($dirname)) {
            unlink($dirname);
        } elseif (is_dir($dirname)) {
            $handle = opendir($dirname);
            while (false !== ($file = readdir($handle))) {
                if (is_file($dirname . $file)) {
                    unlink($dirname . $file);
                }
            }
            closedir($handle);
            rmdir($dirname);
        }
    }

    function audit_trail($xml_form)
    {
        if (class_exists("audit_trail_core")) {
            $audit_trail = new audit_trail_core($this->service, $this->conn, $this->config_service, $this->vlist);
            $audit_trail->audit_trail_difference($xml_form);
            return true;
        } else {
            return false;
        }
    }

    function audit_trail_form_js($xml_form)
    {
        if (class_exists("audit_trail_core")) {
            $audit_trail = new audit_trail_core($this->service, $this->conn, $this->config_service, $this->vlist);
            return $audit_trail->audit_trail_form_js($xml_form);

        } else {
            return '';
        }
    }

    function audit_trail_form_body($xml_form)
    {
        if (class_exists("audit_trail_core")) {
            $audit_trail = new audit_trail_core($this->service, $this->conn, $this->config_service, $this->vlist);
            return $audit_trail->audit_trail_form_body($xml_form);

        } else {
            return '';
        }
    }

    function pdf_esame($esam, $visitnum, $visitnum_progr, $progr, $filename_suffix = null, $download = true, $anonymous = false)
    {
        $prepend = null;
        $append = null;
        $dir = str_replace('html', '', $_SERVER['DOCUMENT_ROOT']);
        $folder = "{$dir}pdf_esami/tmpCRF/";
        $folder_base = "{$dir}pdf_esami/";
        $folder_pdf = "{$dir}pdf_esami/pdfCRF/";
        $old = umask(0);
        mkdir($folder, 0770, true);
        mkdir($folder_base, 0770, true);
        mkdir($folder_pdf, 0770, true);
        chgrp($folder, "devj");
        chgrp($folder_base, "devj");
        chgrp($folder_pdf, "devj");
        $form = $this->printable_form($esam, $visitnum, $visitnum_progr, $progr, $this->service, $this->vlist, true);
        $fp = fopen("{$folder}{$this->session_vars['remote_userid']}_esam_pdf_{$this->pk_service}_{$esam}_{$visitnum}_{$visitnum_progr}_{$progr}{$filename_suffix}.html", "w");

        $search = array('@<a[^>]*?>.*?</a>@siU', '@<span[^>]*?display:none[^>]*?>.*?</span>@siU');
        $form = str_replace(' src="/', " src=\"{$dir}html/", $form);
        $form = str_replace(" src='/", " src='{$dir}html/", $form);
        $form = preg_replace($search, '', $form);
        $form = $prepend . $form . $append;
        if ($anonymous) {
            $form = preg_replace("!Record created on(.*)!", "", $form);
            $form = preg_replace("!\n!", "", $form);
            $form = preg_replace("!\r!", "", $form);
            $form = preg_replace("!<div id=\"tr_EVENT\"(.*?)<\!--</tr><tr>-->!", "", $form);
        }
        fwrite($fp, $form);
        fclose($fp);
        //system("htmldoc_rw -t pdf14 --no-title --footer . --size A4 --fontsize 14 --browserwidth 1024 --landscape long --charset iso-8859-15 --headfootsize 8 --headfootfont Times-Italic --bottom 5mm --top 5mm --left 5mm --right 5mm --path /amministrazione/schede_utente --webpage --no-numbered {$folder}{$this->session_vars['remote_userid']}_esam_pdf_{$this->pk_service}_{$esam}_{$visitnum}_{$visitnum_progr}_{$progr}{$filename_suffix}.html > {$folder_pdf}{$this->session_vars['remote_userid']}_esam_pdf_{$this->pk_service}_{$esam}_{$visitnum}_{$visitnum_progr}_{$progr}{$filename_suffix}.pdf");
        system("/http/local/bin/htmldoc_rw -t pdf14 --no-title --footer . --size A4 --fontsize 14 --browserwidth 1024 --landscape long --charset iso-8859-15 --headfootsize 8 --headfootfont Times-Italic --bottom 5mm --top 5mm --left 5mm --right 5mm --path /amministrazione/schede_utente --webpage --no-numbered {$folder}{$this->session_vars['remote_userid']}_esam_pdf_{$this->pk_service}_{$esam}_{$visitnum}_{$visitnum_progr}_{$progr}{$filename_suffix}.html > {$folder_pdf}{$this->session_vars['remote_userid']}_esam_pdf_{$this->pk_service}_{$esam}_{$visitnum}_{$visitnum_progr}_{$progr}{$filename_suffix}.pdf");
        umask($old);
        if ($download) {
            ob_clean();
            $search[] = ' ';
            $search[] = '*';
            $replace[] = '_';
            $replace[] = '';
            $nome_file = $this->vlist->esams[$visitnum][$esam]['TESTO'] . $filename_suffix . ".pdf";
            $nome_file = trim($nome_file, ' ');
            $nome_file = str_replace($search, $replace, $nome_file);
            header("Content-type: *");
            header("Content-Disposition: attachment; filename={$nome_file}");
            readfile("{$folder_pdf}{$this->session_vars['remote_userid']}_esam_pdf_{$this->pk_service}_{$esam}_{$visitnum}_{$visitnum_progr}_{$progr}{$filename_suffix}.pdf");
            die();
        }
    }


    function sideBar()
    {
        $this->sidebar = new SideBar();
    }

    function evaluate_pt($form)
    {
        $retval = array();
        $retval['XML'] = $form;
        return $retval;
    }

    function getStudyTitle()
    {
        return "[Insert title here!]";
    }

    /**************************/
    /**  FIELD PROGRESSIVI   **/
    /**************************/

    function AllInFieldPendig($progr = false)
    {
        if (!$progr) {
            $progr = 1;
        }
        if ($this->config_service['eQuery'] == '1') {
            $sql_check = "select * from {$this->service}_eqfield eqfield, {$this->service}_eq eq
			where eq.equery_int=eqfield.eq_int
			and statofield in (0,2)
			and eqfield.{$this->config_service['PK_SERVICE']}={$this->pk_service}
			and eqfield.esam={$this->session_vars['ESAM']}
			and eqfield.progr={$progr}
			and eqfield.VISITNUM={$this->session_vars['VISITNUM']}
			and eqfield.VISITNUM_PROGR={$this->session_vars['VISITNUM_PROGR']}
			";

            $sql = new query ($this->conn);
            $sql->exec($sql_check);

            /**
             * Se eQ pending su un campo , valorizzo l'array:
             */
            while ($sql->get_row()) {
                $pending[$sql->row['FIELD']] = $sql->row;
            }
            //Debug:
            //			echo "FIELD PENDING:";echo "<br>";
            //			print_r($pending);echo "<br>";
            //			echo "Query in DB:";echo "<br>"; echo $sql_check;echo "<br>";
            //		die();

            return $pending;
        }
    }

    /**************************/
    /**    FORM MAIN SUB     **/
    /**************************/
    function MainSubEqPending($progr = false, $any_equery = false)
    {
        if ($this->config_service['eQuery'] == '1') {
            /**
             * $any_equery è true nel caso del pulsante cancella record, infatti se c'è mai stat un eQ su quella sub non potrà  più essere cancellata
             */
            if ($any_equery == true) {
                $and_any_equery = "";
            } else {
                $and_any_equery = "and statofield in (0,2) ";
            }
            if (!$progr) {
                $progr = 1;
            }
            $bind = array();
            $bind['PKSERVICE'] = $this->pk_service;
            $bind['ESAM'] = $this->session_vars['ESAM'];
            $bind['VISITNUM'] = $this->session_vars['VISITNUM'];
            $bind['VISITNUM_PROGR'] = $this->session_vars['VISITNUM_PROGR'];
            $bind['PROGR'] = $progr;
            $sql_check = "select * from {$this->service}_eqfield eqfield, {$this->service}_eq eq
			where eq.equery_int=eqfield.eq_int
			{$and_any_equery}
			and eqfield.{$this->config_service['PK_SERVICE']}=:PKSERVICE
			and eqfield.esam=:ESAM
			and eqfield.VISITNUM=:VISITNUM
			and eqfield.VISITNUM_PROGR=:VISITNUM_PROGR
			and eqfield.PROGR=:PROGR
			";

            $sql = new query ($this->conn);
            $sql->exec($sql_check, $bind);

            /**
             * Se eQ pending su un campo , valorizzo l'array:
             */
            while ($sql->get_row()) {
                $pending[$sql->row['FIELD']] = $sql->row;
            }
            //Debug:
            //			echo "FIELD PENDING:";echo "<br>";
            //			print_r($pending);echo "<br>";
            //			echo "Query in DB:";echo "<br>"; echo $sql_check;echo "<br>";
            //		die();

            return $pending;
        }
    }

    function SendMainSub()
    {
        $tb_prefix = "{$this->service}";
        $conn = $this->conn;
        $sql = new query ($conn);
        $pk ['VISITNUM'] = $_GET ['VISITNUM'];
        $pk ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
        $pk ['ESAM'] = $_GET ['ESAM'];
        $values ['FINE'] = 1;
        $values ['INV_QUERY'] = "MAINSUBSENT";
        $pk [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
        $tb_coord = $tb_prefix . "_coordinate";
        /*Sub*/
        $sql->update($values, $tb_coord, $pk);

        /*Main*/
        $pk ['ESAM'] = $_GET ['ESAM'] - 1;
        $sql->update($values, $tb_coord, $pk);
        if (class_exists('SDV_module')) {
            $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], $this->vlist, $this->xml_dir);
            $result = $sdv->after_SendMainSub($_GET [$this->config ['PK_SERVICE']], $_GET ['VISITNUM'], $pk ['ESAM']);
        }
        $this->conn->commit();
        $redirect = "index.php?CENTER={$_GET ['CENTER']}&{$this->config ['PK_SERVICE']}={$_GET [$this->config ['PK_SERVICE']]}&exams=visite_exams.xml";
        header("location:$redirect");
        die ();
    }

    function MainSentLink($in)
    {

        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['XML']);
        $table = $xml_form->form ['TABLE'];


        $view_lab = mlOut("System.MainSub.view_record_list", "View records details");
        $reopen_lab = mlOut("System.MainSub.reopen_records", "Click to re-open records details");

        $sql_maintb_exist = "
		select count(*) as CONTO from user_objects where object_name='{$table}' ";
        //			 echo $sql_maintb_exist;
        $sql2 = new query($this->conn);
        $sql2->set_sql($sql_maintb_exist);
        $sql2->exec();
        $sql2->get_row();
        //			echo $sql2->row['CONTO'];

        if ($sql2->row['CONTO'] == 1) {

            $sql_query = "
			select coord.fine , maintb.{$xml_form->form ['MAIN_FIELD']} from {$this->service}_coordinate coord, {$table} maintb where maintb.{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} and maintb.visitnum={$in['VISITNUM']}
			and maintb.{$this->config_service['PK_SERVICE']}=coord.{$this->config_service['PK_SERVICE']} and maintb.esam=coord.esam and maintb.visitnum=coord.visitnum and maintb.esam={$in['ESAM']}";
            //			 echo $sql_query;
            $sql = new query($this->conn);
            $sql->set_sql($sql_query);
            $sql->exec();
            $sql->get_row();
            //			echo $sql->row['FINE'];
            $main_link = "";
            if ($sql->row['FINE'] == 1 || $in['USER_TIP'] == 'DM' || $in['USER_TIP'] == 'RO') {
                //Domanda principale della Main form , con conseguente valore da rispettare.
                if ($sql->row[$xml_form->form ['MAIN_FIELD']] == $xml_form->form ['MAIN_FIELD_VALUE']) {
                    $sub_esam = $in['ESAM'] + 1;
                    $sub_form = $this->vlist->esams[$in['VISITNUM']][$sub_esam]['XML'];
                    $link = "index.php?CENTER=" . $in['CENTER'] . "&{$this->config_service['PK_SERVICE']}=" . $in[$this->config_service['PK_SERVICE']] . "&VISITNUM=" . $in['VISITNUM'] . "&ESAM={$sub_esam}&form={$sub_form}";
                    $main_link .= "<table style='width:95% ;' align=left ><tr><td class='sc4bis' width='10%' align=\"left\"><a href=\"$link\">{$view_lab}</a></td></tr></table>";

                }
                //else
                if ($in['USER_TIP'] == 'DE') {
                    // Vuole cambiare da No a Yes , quindi ha la possibilità  di aprire le sub.
                    $main_form = $this->vlist->esams[$in['VISITNUM']][$in['ESAM']]['XML'];
                    $link = "index.php?CENTER=" . $in['CENTER'] . "&{$this->config_service['PK_SERVICE']}=" . $in[$this->config_service['PK_SERVICE']] . "&VISITNUM=" . $in['VISITNUM'] . "&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}&form={$main_form}&REOPEN_MAINSUB=yes";
                    $main_link .= "<table style='width:95% ;' align=left ><tr><td class='sc4bis' width='10%' align=\"left\"><a  href=\"$link\">{$reopen_lab}</a></td></tr></table>";
                }
            }

        }

        return $main_link;
    }

    function MainSubReOpen($visitnum, $visitnum_progr, $esam, $progr, $codpat, $center)
    {
        //die("TEST");
        $xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
        $xml_form->xml_form_by_file($this->xml_dir . '/' . $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['XML']);
        $table = $xml_form->form ['TABLE'];

        $_POST['ESAM'] = $esam;
        $_POST['PROGR'] = $progr;
        $_POST['VISITNUM'] = $visitnum;
        $_POST['VISITNUM_PROGR'] = $visitnum_progr;
        $_POST[$this->config_service['PK_SERVICE']] = $codpat;
        $_POST['CENTER'] = $center;
        $_POST[$xml_form->form ['MAIN_FIELD']] = 1;
        $_POST['D_' . $xml_form->form ['MAIN_FIELD']] = "Yes";
        $_POST['EQAREADE_' . $xml_form->form ['MAIN_FIELD']] = "Main Form, Obvious correction by Investigator ";
        $this->session_vars[$xml_form->form ['MAIN_FIELD']] = 1;

        $this->integrazione->SaveEqDE($xml_form);

        $sql_eqfield = "select note_de, eq_int, statofield from {$this->service}_eqfield eqfield, {$this->service}_eq eq where
		eqfield.{$xml_form->config_service['PK_SERVICE']}={$_GET [$xml_form->config_service['PK_SERVICE']]}
		and eqfield.esam={$_GET ['ESAM']}
		and eqfield.visitnum={$_GET ['VISITNUM']}
		and eqfield.visitnum_progr={$_GET ['VISITNUM_PROGR']}
		and eqfield.progr={$_GET ['PROGR']}
		and eqfield.FIELD='{$xml_form->form ['MAIN_FIELD']}'
		and eq.equery_int=eqfield.eq_int
		and eq.stato=2
		";


        $sql2 = new query ($this->conn);
        $sql2->set_sql($sql_eqfield);
        $sql2->exec();
        $sql2->get_row();
        $nota_de = $sql2->row['NOTE_DE'];
        $eq_int = $sql2->row['EQ_INT'];
        $d_eqfield = "";


        // Update del valore 1 e Yes nella EQFIELD
        $sql4 = new query($this->conn);
        $vals4['VALORE'] = $xml_form->form ['MAIN_FIELD_VALUE'];
        $pk4['ESAM'] = $esam;
        $pk4['VISITNUM'] = $visitnum;
        $pk4['VISITNUM_PROGR'] = $visitnum_progr;
        $pk4['PROGR'] = $progr;
        $pk4[$this->config_service['PK_SERVICE']] = $codpat;
        $pk4['EQ_INT'] = $eq_int;
        $pk4['FIELD'] = $xml_form->form ['MAIN_FIELD'];
        $sql4->update($vals4, $this->service . "_EQFIELD", $pk4);

        $pk4['FIELD'] = 'D_' . $xml_form->form ['MAIN_FIELD'];
        $vals4['VALORE'] = "Yes";
        $sql4->update($vals4, $this->service . "_EQFIELD", $pk4);
        $this->conn->commit();

        $to_approve = "&EQ_INT_FIELD={$eq_int}&EQFIELD={$xml_form->form ['MAIN_FIELD']}&D_EQFIELD={$d_eqfield}&APPROVA_EQFIELD=1";

        $redirect = "index.php?CENTER=" . $center . "&{$this->config_service['PK_SERVICE']}=" . $codpat . "&VISITNUM=" . $visitnum . "&ESAM={$esam}&PROGR={$progr}&form={$_GET['form']}{$to_approve}";

        if ($eq_int) {
            $redirect .= "{$to_approve}";
        }
        //			echo $redirect;

        // Riapro la main dal FINE=1:
        $sql3 = new query($this->conn);
        $pk = '';
        $vals['FINE'] = '';
        $pk['ESAM'] = $esam;
        $pk['VISITNUM'] = $visitnum;
        $pk['VISITNUM_PROGR'] = $visitnum_progr;
        $pk['PROGR'] = $progr;
        $pk[$this->config_service['PK_SERVICE']] = $codpat;
        $sql3->update($vals, $this->service . "_COORDINATE", $pk);

        // Riapro le sub dal INV_QUERY=MAINSUBSENT
        $vals3['INV_QUERY'] = '';
        $pk3['VISITNUM'] = $visitnum;
        $pk3[$this->config_service['PK_SERVICE']] = $codpat;
        $pk3['ESAM'] = $esam + 1;
        $pk3['VISITNUM_PROGR'] = $visitnum_progr;
        $sql3->update($vals3, $this->service . "_COORDINATE", $pk3);


        //Poi metto fine null  se hanno inizio null (caso di primo inserimento)
        $sql_update = "update {$this->service}_coordinate set fine='' where
		visitnum={$pk3['VISITNUM']} and esam={$pk3['ESAM']} and visitnum_progr={$pk3['VISITNUM_PROGR']}
		and {$this->config_service['PK_SERVICE']}={$codpat} and inizio is null
		";
        //		echo $sql_update;
        $sql3->set_sql($sql_update);
        $sql3->ins_upd();
        $this->conn->commit();

        //Poi metto VISITCLOSE=0 per la visita corrente
        //visitnum_progr={$pk3['VISITNUM_PROGR']}
        $sql_update = "update {$this->service}_coordinate set VISITCLOSE='0' where
		visitnum={$pk3['VISITNUM']}
		and {$this->config_service['PK_SERVICE']}={$codpat}
		";
        //		echo $sql_update;
        $sql3->set_sql($sql_update);
        $sql3->ins_upd();
        $this->conn->commit();

        //Poi riapro la firma se presente!
        $electronic_signature_esam = array();
        $visite_exams_path = str_replace("index.php", "", $_SERVER ['SCRIPT_FILENAME']) . "xml/visite_exams.xml";
        $vlist = new xml_esams_list ($visite_exams_path, $this->config_service, $this->session_vars, $this->conn);
        /* Numero dell'esame skip_visit della visita */
        $visit_num = array();
        foreach ($vlist->esams as $key => $val) {
            foreach ($val as $k => $v) {
                if ($v ['XML'] == 'esign.xml') {
                    $electronic_signature_esam [$key] = $v ['NUMBER'];
                }
            }
        }
        // Per tutte le signature
        foreach ($electronic_signature_esam as $visit_num => $esam_num) {
            $query = new query ($this->conn);
            unset ($vals);
            $vals ['PK_SERVICE'] = $codpat;
            $vals ['VISITNUM'] = $visit_num;
            $vals ['ESAM'] = $esam_num;
            $vals ['PROGR'] = "1"; //-> Esame di firma mai progressivo (Se progressivo utilizzare il MAX(PROGR) //$this->session_vars ['PROGR'];
            $vals ['VISITNUM_PROGR'] = ($visitnum_progr ? $visitnum_progr : 0);
            $sql_query = "SELECT * FROM {$this->config_service['service']}_COORDINATE WHERE {$this->config_service['PK_SERVICE']}=:PK_SERVICE AND ESAM=:ESAM and VISITNUM=:VISITNUM AND PROGR=:PROGR AND VISITNUM_PROGR=:VISITNUM_PROGR";
            $query->exec($sql_query, $vals);
            $query->get_row();
            if ($query->row ['FINE'] == 1) {
                // Riapro la Electronic Signature
                $query = new query ($this->conn);
                unset ($vals);
                $vals [$this->config_service['PK_SERVICE']] = $codpat;
                $vals ['VISITNUM'] = $visit_num;
                $vals ['ESAM'] = $esam_num;
                $sql_query = "UPDATE {$this->service}_COORDINATE SET FINE='0' WHERE {$this->config_service['PK_SERVICE']}=:{$this->config_service['PK_SERVICE']} AND VISITNUM=:VISITNUM AND ESAM=:ESAM";
                $query->exec($sql_query, $vals);

                $query = new query ($this->conn);
                unset ($vals);
                $vals [$this->config_service['PK_SERVICE']] = $codpat;
                $vals ['VISITNUM'] = $visit_num;
                $sql_query = "UPDATE {$this->service}_COORDINATE SET VISITCLOSE='0' WHERE {$this->config_service['PK_SERVICE']}=:{$this->config_service['PK_SERVICE']} AND VISITNUM=:VISITNUM";
                $query->exec($sql_query, $vals);
            }
        }
        $this->conn->commit();

        header("location:$redirect");
        die ();

    }

    //ALL-IN VIEW Helper functions and progr handling

    /**
     * Prende come parametri ESAM,VISITNUM,VISITNUM_PROGR,CODPAT restituendo
     * l'html di tutte le progressive presenti in db per quella scheda per quel paziente (e visita e visitnum_progr).
     *
     * @param array $xml_form
     * @param number $esam
     * @param number $visitnum
     * @param number $visitnum_progr
     * @return $body
     *
     */
    function AllInPrintableForm($xml_form, $esam, $visitnum, $visitnum_progr)
    {
        $body = null;
        if ($_GET[$this->config_service['PK_SERVICE']] != '' && isset($_GET['CRF'])) {
            $sql_query = "
			select progr  from {$this->service}_coordinate
			where {$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}
			and visitnum={$visitnum} and esam={$esam} and visitnum_progr={$visitnum_progr}
			order by progr
			";
            $sql = new query ($this->conn);
            $sql->exec($sql_query);
            while ($sql->get_row()) {
                if ($sql->row['PROGR'] != '') {
                    /**Esplosione delle progressive nel Patient Dossier:*/
                    $_GET['PROGR'] = $this->session_vars['PROGR'] = $sql->row['PROGR'];
                    $xml_form->make_html(true, true);
                    $body .= $xml_form->body;
                }
            }
        }
        return $body;
    }


    function AllInEqButton($xml_form, $progr)
    {
        $eq_button = null;
        if (strtolower($this->config_service['lang']) == 'en') {
            $integra_button_text = "Integrate Record";
            $eq_note_msg = "eQuery general comment:";
            $msg_generale_obbl = "General comment is necessary for eQuery";
            $msg_field_obbl = "Field comment is necessary for eQuery";
        } else {
            $integra_button_text = "Integra Record";
            $eq_note_msg = "eQuery, commento generale:";
            $msg_generale_obbl = "Commento generale obbligatorio per le eQuery";
            $msg_field_obbl = "Commento al campo obbligatorio per le eQuery";
        }
        $sql_query = "select equery_int from {$this->service}_eq where stato in (0,2) and {$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}";
        $sql = new query($this->conn);
        if ($sql->get_row($sql_query)) $equery_int = $sql->row['EQUERY_INT'];
        else $equery_int = 0;

        // Textarea per il DE, nel caso voglia fare un eQ:
        if (isset($_GET['ABILITA_EQ_DE'])) {
            // Nella check_eqfield controllo prima che almeno una textarea per campo sia stata aperta, altrimenti messaggio di alert
            // Successivamente controllo che tali textarea sia compilate altrimenti messaggi odi alert.

            $eq_button .= '<script>
					function check_eqfield_de(){
					var el;
					var f;
					var result;
					var check;
					var espressione = /EQAREADE_/;
					f=document.forms[0];
					el=f.elements;
					result = true;
					check = false;
					for (i=0;i<el.length;i++) {
					if(	espressione.test(el[i].name) && el[i].style.display!=\'none\'){
					check = true;
		}
		}
					if(check==false){
					alert(\'' . $msg_field_obbl . '\');
							return false;
		}
							for (i=0;i<el.length;i++) {
							if(el[i].style.display!=\'none\' && el[i].value==\'\' && espressione.test(el[i].name) ){
							alert(\'' . $msg_field_obbl . '\');
									return false;
		}
		}
				   		return true;
		}
									</script>';
            $eq_button .= '
					<input type="hidden" value="' . $equery_int . '" name="EQUERY_INT">
							<input type="submit" style="width:150px; height:50px; cursor:pointer; border:1px outset #0000FF" value="' . $integra_button_text . '" name="salva" onclick="if(!check_eqfield_de()){return false; }else{document.forms[0].PROGR.value=' . $progr . ';invia_f();}"/>';

            return $eq_button;
        }
    }

    /**************************/
    /**  END FORM MAIN SUB   **/
    /**************************/


    function LaunchActivitiProcess($service, $f_to_call, $vars)
    {
        global $in;
        try {
            $processId = $service->startProcess($f_to_call, $vars);
            $timeoutCount = 0;
            $message = $service->hasProcessEnded($f_to_call, $processId);
            while ($message == $service->WAITMESSAGE && $timeoutCount < 50) {
                $timeoutCount++;
                usleep(200 * 1000);
                $message = $service->hasProcessEnded($f_to_call, $processId);
            }
            $this->reopenConn();
            //echo "ACT_RES: $message";
            if ($message == $service->RES_FAILURE) {
                //crf.getProcessMessage(processId)
                $sql = new query($this->conn);
                $bind = array();
                $sql_check = "select * from {$this->service}_ACTIVITI_MESSAGES where PROCESSID = '{$processId}'";
                $sql->get_row($sql_check, $bind);
                //var_dump($sql->row);
                if ($in['ajax_call'] != '') {
                    echo "Error:#error#";
                    //die("Activiti MSG\n ".$sql->row['MESSAGE']);
                    die($sql->row['MESSAGE']); //rimosso Activiti MSG\n vmazzeo 24.06.2015
                } else {
                    error_page($this->user->userid, $sql->row['MESSAGE'] . "<br/>" . $f_to_call . "<br/>", array());
                }
            } else {
                $sql = new query($this->conn);
                $bind = array();
                $sql_check = "select * from {$this->service}_ACTIVITI_MESSAGES where PROCESSID = '{$processId}'";
                $sql->get_row($sql_check, $bind);
                //var_dump($sql->row);
                if ($in['ajax_call'] != '') {
                    //Nulla
                } else {
                    $redirect = $sql->row['REDIRECT'];
                    if ($redirect) {
                        header("location: $redirect");
                        die();
                    }
                }
            }
        } catch (Exception $ex) {
            //var_dump($ex);
            //die();
            error_page($this->user->userid, $ex->getMessage() . "<br/>" . $f_to_call . "<br/>", $ex->getTrace());
        }
    }

    function reopenConn()
    {
        if ($this->conn->isClosed()) {
            $this->conn = new dbconn();
        }
    }

    /**
     *  vmazzeo 18.06.2015 la prendo dallo study.inc.php di lipigen_registry per renderla di libreria (ho eliminato la funzione sia da study_inc di lipigen_registry che di lipigen)
     */
    function eQBar($lock_query = 0, $lock_obvious = 0, $small = false)
    {
        //echo "eQBar (".$lock_query.",".$lock_obvious.")<br/>";
        global $in;
        global $remote_userid;
        global $service;
        $service = $this->service;
        $session_vars = $this->session_vars;

        // Se sono un DM e sono abilitato ad approvare faccio comparire casella in più nella barra degli strumenti

        $link_set_eq = mlOut("System.patient_table.link_set_eq", "Open eQ");
        $link_unset_eq = mlOut("System.patient_table.link_unset_eq", "Close eQ");
        $link_set_mod = mlOut("System.patient_table.link_set_mod", "Open");
        $link_unset_mod = mlOut("System.patient_table.link_unset_mod", "Close");
        $link_eq_on = mlOut("System.patient_table.link_eq_on", "Data Quality");
        $link_modify_form = mlOut("System.patient_table.link_modify_form", "Modify Form");
        $label_eq_not_available = "<i class=\"red fa fa-lock\"></i>"; //mlOut ( "System.patient_table.eq_not_available", "Not Available" );
        $link_reopen_form = mlOut("System.patient_table.link_reopen_form", "Re-open Form");

        $html_eq = "";
        //if (!$small) {
        $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;" . $link_eq_on . "</div>";
        //}
        $html_eq .= "<div style=\"float:right\">{$label_eq_not_available}</div><div style=\"clear:both\">&nbsp;</div>";
        //if (!$small) {
        $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-pencil-square\"></i>&nbsp;$link_modify_form</div>";
        //}
        $html_eq .= "<div style=\"float:right\">{$label_eq_not_available}</div>";

        $progr_link = "";
        if ($in ['PROGR'] != '') {
            $progr_link = "&PROGR={$in['PROGR']}";
        }

        $link_mod = "";
        $link_eq = "";
        $index = $_SERVER['SCRIPT_NAME'] . "";
        //die($index);

        if (($in ['USER_TIP'] == 'DM' || $in ['USER_TIP'] == 'RO' || ($in ['USER_TIP'] == 'DE' && ($this->config_service['de_modify_form_allowed'] == true))) && $this->config_service ['eQuery'] == '1') {
            //if (isset ( $_GET ['ESAM'] ) && isset ( $_GET ['exams'] ) || isset ( $_GET ['form'] )) {
            if (isset ($_GET ['ESAM'])) {
                // ABILITA_MOD_DM
                if (isset ($in ['ABILITA_MOD_DM']) && $in ['ABILITA_MOD_DM'] != '') {
                    $link_mod .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
					<i class=\"fa fa-circle\"></i>&nbsp;" . $link_unset_mod . "</a>";
                } else {
                    $link_mod .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&ABILITA_MOD_DM=1\">
					<i class=\"fa fa-circle-o\"></i>&nbsp;" . $link_set_mod . "</a>";
                }
                // ABILITA_EQ_DM
                if ($in ['USER_TIP'] == 'DM') {
                    if (isset ($in ['ABILITA_EQ_DM']) && $in ['ABILITA_EQ_DM'] != '') {
                        $link_eq .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
									 <i class=\"fa fa-circle\"></i>&nbsp;$link_unset_eq</a>";
                    } else {
                        $link_eq .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&ABILITA_EQ_DM=1\">
									 <i class=\"fa fa-circle-o\"></i>&nbsp;$link_set_eq</a>";
                    }
                }
                // INSERISCO CONTROLLI SE DBLOCK ESISTE PER EQUERY E OBVIOUS CORRECTION
                if (($lock_obvious != 1) || ($lock_query != 1)) {
                    $html_eq = "";  //Importante, sbianco il testo di default perchè ne inserisco interamente di nuovo!
                    if ($in ['USER_TIP'] == 'DM' || ($in ['USER_TIP'] == 'DE' && ($this->config_service['de_modify_form_allowed'] == true))) {
                        if ($in ['USER_TIP'] == 'DM') {
                            $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;$link_eq_on</div>";
                            if ($lock_query != 1) {
                                $html_eq .= "<div style=\"float:right\">" . $link_eq . "</div><div style=\"clear:both\">&nbsp;</div>";
                            } else {
                                $html_eq .= "<div style=\"float:right\">" . $label_eq_not_available . "</div><div style=\"clear:both\">&nbsp;</div>";
                            }
                        }
                        $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-pencil-square\"></i>&nbsp;$link_modify_form</div>";
                        if ($lock_obvious != 1) {
                            $html_eq .= "<div style=\"float:right\">" . $link_mod . "</div><div style=\"clear:both\">&nbsp;</div>";
                        } else {
                            $html_eq .= "<div style=\"float:right\">" . $label_eq_not_available . "</div><div style=\"clear:both\">&nbsp;</div>";
                        }
                        $html_eq .= "";
                    }                    // Caso del CRA
                    elseif ($in ['USER_TIP'] == 'RO') {
                        if ($lock_query != 1) {
                            $html_eq = "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;" . $link_eq_on . "</div><div style=\"float:right\">" . $link_eq . "</div><div style=\"clear:both\">&nbsp;</div>";
                        }
                    }
                    $html_eq .= "";
                }
            }
        }
        // Studio con Dm ma senza eQ, il Dm deve comunque poter modificare la form
        if (($in ['USER_TIP'] == 'DM' || ($in ['USER_TIP'] == 'DE' && ($this->config_service['de_modify_form_allowed'] == true))) && !isset ($this->config_service ['eQuery']) && isset ($this->session_vars ['ESAM'])) {

            if (isset ($in ['ABILITA_MOD_DM']) && $in ['ABILITA_MOD_DM'] != '') {
                $link_mod .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
							  <i class=\"fa fa-circle\"></i>&nbsp;" . $link_unset_mod . "</a>";
            } else {
                $link_mod .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&ABILITA_MOD_DM=1\">
							  <i class=\"fa fa-circle-o\"></i>&nbsp;" . $link_set_mod . "</a>";
            }
            if ($lock_obvious != 1) {
                $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;" . $link_modify_form . "</div>
				<div style=\"float:right\">{$link_mod}</div><div style=\"clear:both\">&nbsp;</div>";
            }
        }
        // Fine Studio con Dm ma senza eQ, il Dm deve comunque poter modificare la form

        // Se sono un DE e sono abilitato a fare eQ faccio comparire casella in più nella barra degli strumenti
        //	echo $in ['USER_TIP'] ."<br/>";
        //	echo $this->config_service ['eQuerySpec'] ['Integrazione'] ['ROLE'] ."<br/>";
        //	echo $this->config_service ['eQuery']."<br/>";
        if ($in ['USER_TIP'] == 'DE' && $this->config_service ['eQuery'] == '1') {
            /*echo "<pre>";
			var_dump($in ['USER_TIP']);
			var_dump($this->config_service['de_modify_form_allowed']);
			echo "</pre>";*/
            /**
             * STATI:
             * stato 0: eQ proposta dal DM al DE
             * stato 1: eQ fatta dal DE e approvata dal DM
             * stato 2: eQ fatta dal DE al DM
             * stato 3: eQ fatta dal DE e rifiutata dal DM
             */

            // ABILITA_EQ_DE
            if (isset ($_GET ['ESAM']) && isset ($_GET ['exams']) || isset ($_GET ['form'])) {
                if (isset ($in ['ABILITA_EQ_DE']) && $in ['ABILITA_EQ_DE'] != '') {
                    $link_eq .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
								<i class=\"fa fa-circle\"></i>&nbsp;$link_unset_eq
								</a>";
                } else { // &REGISTRY={$this->service} levato...
                    $link_eq .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&ABILITA_EQ_DE=1\">
							<i class=\"fa fa-circle-o\"></i>&nbsp;$link_set_eq
							</a>";
                }
            } else {
                $link_eq .= "&nbsp;";
            }
            if ($lock_query != 1) {
                if ($this->config_service['de_modify_form_allowed'] == false) {
                    $html_eq = "";//Importante, sbianco il testo di default perchè ne inserisco interamente di nuovo!
                }
                //if (!$small) {
                $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;" . $link_eq_on . "</div>";
                //}
                $html_eq .= "<div style=\"float:right\">{$link_eq}</div><div style=\"clear:both\">&nbsp;</div>";
            }
        }

        /*
        // Per tutte le form che iniziano per "Upload" o si chiamano "eSource.xml", faccio in modo per il DE di poter riaprire la form stessa
        if (( $in ['USER_TIP'] == 'DE' || $in ['USER_TIP'] == 'CO_PI' || $in ['USER_TIP'] == 'SUB_PI' || $in ['USER_TIP'] == 'ST') && isset ( $this->session_vars ['ESAM'] )) {//GENHD-364 il DE pu? riaprire le form di eSource.
            $form = $in['form'];
            if (!$form){
                $form = $in['FORM'];
            }
            //var_dump($form);
            if ($form=="eSource.xml" || (substr($form, 0, strlen("Upload")) === "Upload")) {
                $link_reop = "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&REOPEN_FORM=1\">
							  <i class=\"fa fa-circle-o\"></i>&nbsp;" . $link_set_mod . "</a>";

                if (true) {
                    $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;" . $link_reopen_form . "</div>
				<div style=\"float:right\">{$link_reop}</div><div style=\"clear:both\">&nbsp;</div>";
                }
            }
        }
        // Fine Studio con Dm ma senza eQ, il Dm deve comunque poter modificare la form
        */
        return $html_eq;
    }

    /**
     * Restituisce lo specchiatto relativo ad una eQ pendig sulla scheda.
     *
     * @return HTML
     *
     */
    function eQPendingBar()
    {
        // Gestione specchietto dove non c'è eQ pending
        $eq_approv = "";
        if (isset ($_GET ['ESAM']) && isset ($_GET ['exams']) || isset ($_GET ['form'])) {
            if ($this->config_service ['eQuery'] == 1) {
                if (isset ($_GET ['PROGR']) && $_GET ['PROGR'] != "") {
                    $and_progr = " and eqfield.progr={$_GET ['PROGR']} ";
                }
                if (isset ($_GET ['VISITNUM_PROGR']) && $_GET ['VISITNUM_PROGR'] != "") {
                    $and_progr .= " and eqfield.visitnum_progr={$_GET ['VISITNUM_PROGR']} ";
                }
                // non ho l'eq_int, da rivedere:
                $sql_eqint = "select  eqfield.eq_int,eq.stato,eq.rich_dm,eq.rich_de from {$this->service}_eqfield eqfield, {$this->service}_eq eq where
				eqfield.{$this->xmr->configurations['PK_SERVICE']}={$_GET [$this->xmr->configurations['PK_SERVICE']]}
				and eqfield.esam={$_GET ['ESAM']}
				and eqfield.visitnum={$_GET ['VISITNUM']}
				and eq.stato in (0,2)
				and eqfield.eq_int=eq.equery_int
				$and_progr
				";
                $sql2 = new query ($this->conn);
                $sql2->set_sql($sql_eqint);
                $sql2->exec();

                // echo $sql_eqint;

                /**
                 * STATI:
                 * stato 0: eQ proposta dal DM al DE
                 * stato 1: eQ fatta dal DE e approvata dal DM
                 * stato 2: eQ fatta dal DE al DM
                 * stato 3: eQ fatta dal DE e rifiutata dal DM
                 */
                while ($sql2->get_row()) {
                    $this->integrazione->eq_int = $sql2->row ['EQ_INT'];
                    $stato = $sql2->row ['STATO'];

                    if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '' && $stato == '2' && !isset ($_GET ['ABILITA_MOD_DM'])) {
                        $ret = $this->integrazione->getEqSpec($this->vlist);
                        $eq_approv = "<span style=\"color: orange;\"><i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>" . mlOut("MESSAGE_EQPENDING", "Equery pending") . "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i></span>";
                    } elseif ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '' && ($stato == '0' || $stato == '2')) {
                        $eq_approv = "<span style=\"color: orange;\"><i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>" . mlOut("MESSAGE_EQPENDING", "Equery pending") . "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i></span>";
                    }
                }
            }
        }
        return $eq_approv;
    }

    //Gestione invio mail generico (AUTOMAIL) -> richiamato ad ogni save/send delle form
    function sendGenericMail($visitnum, $esam, $email_id, $additional_to, $additional_subject, $additional_message, $attachments = false)
    {
        global $in;
        //global $lang;
        //var_dump($in);
        //die();

        $conn = $this->conn;
        $service = $this->service;


        //Check automail table
        $sql_create = "CREATE TABLE {$service}_AUTOMAIL (
	VISITNUM NUMBER NOT NULL ENABLE, 
	ESAM NUMBER NOT NULL ENABLE, 
	MAIL_ID VARCHAR2(200 CHAR) NOT NULL ENABLE, 
	MAIL_BODY CLOB, 
	MAIL_RECIPIENT_DEV VARCHAR2(2000 CHAR), 
	MAIL_RECIPIENT_TEST VARCHAR2(2000 CHAR), 
	MAIL_RECIPIENT_PROD VARCHAR2(2000 CHAR), 
    MAIL_SUBJECT VARCHAR2(2000 CHAR), 
    CONSTRAINT {$service}_AUTOMAIL_PK PRIMARY KEY (VISITNUM, ESAM, MAIL_ID) ENABLE )
            ";
        $sql_check = "SELECT count(*) as CONTA FROM user_objects where object_name = '{$service}_AUTOMAIL'";
        $sql = new query ($conn);
        $bind = array();
        $sql->exec($sql_check, $bind);
        $sql->get_row();
        if (!$sql->row['CONTA']) {
            $sql = new query ($conn);
            $sql->ins_upd($sql_create);
        }

        $sql_automail = "SELECT *
                       FROM {$service}_AUTOMAIL 
                       WHERE visitnum=:VISITNUM AND
                             ESAM=:ESAM
                             and MAIL_ID=:MAIL_ID";
        $sql = new query ($conn);
        $bind = array();
        $bind['VISITNUM'] = $visitnum;
        $bind['ESAM'] = $esam;
        $bind['MAIL_ID'] = $email_id;
        //var_dump($sql_automail);
        //var_dump($bind);
        $sql->exec($sql_automail, $bind);
        $sql->get_row();
        $row_automail = $sql->row;
        //var_dump($row_automail);
        //die();
        if (!empty($row_automail)) {
            //echo "<pre>";
            //print_r($row_automail);
            //echo "</pre>";

            $email_text = $row_automail['MAIL_BODY'];
            foreach ($additional_message as $key => $value) {
                $email_text = str_replace('[' . $key . ']', $value, $email_text);
            }
            $email_subject = $row_automail['MAIL_SUBJECT'];
            foreach ($additional_subject as $key => $value) {
                $email_subject = str_replace('[' . $key . ']', $value, $email_subject);
            }
            $test = "";
            $mailto = "";
            if (preg_match("/\.dev\./i", $_SERVER['HTTP_HOST']) || preg_match("/\.sissdev\./i", $_SERVER['HTTP_HOST'])) {
                // Dev
                $test = '<span style="color:red"><b>"DEV ENVIRONMENT"</b></span><br/><br/>';
                $mailto .= $row_automail['MAIL_RECIPIENT_DEV'];
            } elseif (preg_match("/\.test\./i", $_SERVER['HTTP_HOST']) || preg_match("/\.sissprep\./i", $_SERVER['HTTP_HOST'])) {
                // Test
                $test = '<span style="color:red"><b>"TEST ENVIRONMENT"</b></span><br/><br/>';
                $mailto .= $row_automail['MAIL_RECIPIENT_TEST'];
                //$mailto .= ",a.dalessandro@cineca.it";
            } else {
                // Prod
                $mailto .= $row_automail['MAIL_RECIPIENT_PROD'];
            }
            $email_text = $test . "" . $email_text;
            $mailto .= $additional_to;
            require_once("PHPMailerUtils.inc");
            $headers = "From: {$service}@{$_SERVER['SERVER_NAME']}\n";
            $headers .= "Content-type: text/html; charset=utf-8 \n";
            $reply_to = "noreply@cineca.it";

            //echo "<pre>";
            //print_r($email_subject);
            //print_r($email_text);
            //print_r($mailto);
            //echo "</pre>";


            //$email_text.="<b>has screened patient: {$subjid} </b><br/>";
            //echo "BEFORE SEND<br/>\n";
            if (!send_email($mailto, "{$service}@{$_SERVER['SERVER_NAME']}", "{$service}@{$_SERVER['SERVER_NAME']}", $email_subject, $email_text, "{$service}@{$_SERVER['SERVER_NAME']}", $attachments, null, null, "text/html", "utf-8")) {
                error_page($_SERVER['REMOTE_USERID'], "An error while sending Mail occurred!", array(), true);
                //require_once("send_email_common.inc");
                //if (!send_email_common($mailto, "{$service}@{$_SERVER['SERVER_NAME']}", "{$service}@{$_SERVER['SERVER_NAME']}", $email_subject, $email_text, $reply_to, $attachments, null, null, null, "utf-8")) {
                //    error_page($_SERVER['REMOTE_USERID'], "An error while sending  Mail occurred! via {$service}@{$_SERVER['SERVER_NAME']}", array(), true);
                //}

            }
            //echo "AFTER SEND<br/>\n";
            return true;
        }
        //die("NO AUTOMAIL ROW");
        return false;
    }


}

