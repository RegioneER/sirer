<?
include_once "AxmrML.class.inc";
/**
 * Classe prototipo per l'utente
 *
 * @package CORE
 */
class user_prototype{
	/**
	 * UserID dell'utente
	 *
	 * @var String
	 */
	var $userid;
	/**
	 * Azienda/Ente dell'utente
	 *
	 * @var String
	 */
	var $nome_azienda;
	/**
	 * Nome e cognome
	 *
	 * @var String
	 */
	var $nome_cognome;
	/**
	 * Email dell'utente
	 *
	 * @var String
	 */
	var $email;
	/**
	 * Profilo dell'utente
	 *
	 * @var String
	 */
	var $profilo;
	var $profilo_id;
	var $stato_id;
	/**
	 * Connessione DB
	 *
	 * @var dbconn
	 */
	var $conn;
	/**
	 * Id attore
	 *
	 * @var number
	 */
	var $actid;
	/**
	 * Profili
	 *
	 * @var Array
	 */
	var $profile_list;
	var $profile_code;
	var $sites;
	var $type;
	var $site_ids;
	var $profile_scope;
	var $usersProfiles;
	/**
	 * Costruttore
	 *
	 * @param dbconn $conn
	 * @param String $userid
	 * @param String $xmrwf
	 * @return user_prototype
	 */
	function user_prototype($conn, $userid, $xmrwf, $config_service=null){
		$this->conn=$conn;
		$this->userid=$userid;
		$this->config_service=$config_service;
		
		$sql_profile="select * from {$xmrwf->prefix}_USER_PROFILES where userid=:userid";
		$sql=new query($this->conn);
		$bind['userid']=$userid;
		$bind['prefix']=$xmrwf->prefix;
		$sql->exec($sql_profile, $bind);//binded
		while ($sql->get_row()){
			$this->usersProfiles[$sql->row['PROFILE_CODE']]=mlOut("Profile_".$sql->row['PROFILE_CODE'].".profileName",$sql->row['DESCRIZIONE']);
			if ($sql->row['ACTIVE']==1){
				$this->profile_code=$sql->row['PROFILE_CODE'];
				$this->profilo=$sql->row['DESCRIZIONE'];
				$this->policy=$sql->row['POLICY'];
				$this->profile_scope=$sql->row['SCOPE'];
			}
		}
		$sql_sites="
				select uc.center, c.denom 
				from {$xmrwf->prefix}_UTENTI_CENTRI uc, {$xmrwf->prefix}_CENTRI c 
						where 
						c.CENTER=uc.CENTER
						and uc.userid=:userid";
		$sql=new query($this->conn);
		$bind['userid']=$userid;
		$bind['prefix']=$xmrwf->prefix;
		$sql->exec($sql_sites, $bind);
		while ($sql->get_row()){
			$this->sites[$sql->row['CENTER']]=$sql->row['DENOM'];
		}
		$sql_query="
			select
			distinct
				a.nome||' '||a.cognome as nome,
				a.azienda_ente,
				a.email
			from ana_utenti a
			where a.userid=:userid
			";
		$sql=new query($this->conn);
		unset($bind_user);
		$bind_user['USERID']=$this->userid;
		$sql->exec($sql_query,$bind_user);//binded
		$sql->get_row();
		$this->nome_azienda=$sql->row['AZIENDA_ENTE'];
		$this->nome_cognome=$sql->row['NOME'];
		$this->email=$sql->row['EMAIL'];
		return;
	}

}

/**
 * Classe prototipo per studi XMR multiprotocollo
 *
 * @package CORE
 */
class Study_prototype_mxmr extends Study_prototype {
	/**
	 * Specifiche protocollo
	 *
	 * @var String
	 */
	var $xmr;
	/**
	 * Specifiche multiprotocollo
	 *
	 * @var String
	 */
	var $mxmr;

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
	 * @param String $workflow_name
	 * @param String $xmr
	 * @param String $mxmr
	 * @return Study_prototype_mxmr
	 */
	function Study_prototype_mxmr($xml_dir, $service, $visit_structure_xml, $conn, $session_vars, $config_service, $user, $configure = false, $workflow_name = null, $xmr=null, $mxmr=null) {
		$this->xmr=$xmr;
		$this->mxmr=$mxmr;
		parent::Study_prototype($xml_dir, $service, $visit_structure_xml, $conn, $session_vars, $config_service, $user, $configure, $workflow_name);
	}

	/**
	 * Controller principale dell'oggetto
	 *
	 */
	function Controller(){
        $user=null;
		if (isset ( $_GET ['form'] ) || isset ( $_GET ['ESAM'] )) {
            //print_r($this->xmr->entries); //entry-points
            //se non sono SDV, altrimenti passo...
            if ($_GET['module']=='SDV' && ($_GET['sdv_action']=='defineStrategyStep3' || $_GET['sdv_action']=='readStrategyStep3' || $_GET['sdv_action']=='saveStrategyStep3')){
                //Non faccio nulla, gestisco nel controller
            }else {
                if (!isset($_GET[$this->config_service['PK_SERVICE']]) && !$this->xmr->entries[$_GET['ESAM']]) {

                    error_page($user->userid, "Not possible to open the form (la scheda)", "Not possible to open the form (la scheda)");
                } else if ($this ->config_service['BookPkService'] && $this ->session_vars[$this ->config_service['PK_SERVICE']] == '') {
                    global $in;
                    $query = new query($this ->conn);
                    $query ->get_row("select {$this->config_service['PK_SEQ']}.nextval as {$this->config_service['PK_SERVICE']}  from dual");
                    $in[$this ->config_service['PK_SERVICE']] = $_GET[$this ->config_service['PK_SERVICE']] = $this ->pk_service = $this ->session_vars[$this ->config_service['PK_SERVICE']] = $query ->row[$this ->config_service['PK_SERVICE']];
                }
                //$this->EsamPage ();
            }
		}
        
		parent::Controller();
	}



}

/**
 * Classe XMR con interazione WorkFlow
 *
 * @package CORE
 */
class xmrwf {

	/**
	 * Cartella con i file xml
	 *
	 * @var String
	 */
	var $xml_dir;
	/**
	 * Directory dello studio (filesystem)
	 *
	 * @var String
	 */
	var $dir;
	/**
	 * Connession DB
	 *
	 * @var dbconn
	 */
	var $conn;
	var $prefix;
	/**
	 * Chiave del servizio
	 *
	 * @var String
	 */
	var $pk_service;
	/**
	 * Configurazioni
	 *
	 * @var array
	 */
	var $configurations;
	/**
	 * Etichette breadCrumb
	 *
	 * @var unknown_type
	 */
	var $labels;
	/**
	 * WorkFlow associato alla studio
	 *
	 * @var WF
	 */
	var $workflow;
	/**
	 * Sottostudi presenti
	 *
	 * @var array
	 */
	var $substudies;
	/**
	 * Vista Utenti_centri
	 *
	 * @var String
	 */
	var $center_view;
	/**
	 * Query di construzione
	 *
	 * @var array
	 */
	var $queries;
	/**
	 * Parametro di configurazione
	 *
	 * @var Array
	 */
	var $entries;
	/**
	 * Variabili di sessione
	 *
	 * @var array
	 */
	var $session_vars;
	/**
	 * Configurazioni del servizio
	 *
	 * @var array
	 */
	var $config_service;
	/**
	 * Profondit dello studio
	 *
	 * @var number
	 */
	var $depth;

	/**
	 * Avvia la configurazione
	 *
	 * @return Study
	 */
	function study_start(){
		$dir=$_SERVER['PATH_TRANSLATED'];
		$dirs=split("/", $dir);
		$dir='';
		for ($i=0;$i<count($dirs)-1;$i++){
			$dir.=$dirs[$i]."/";
		}
		$dir=rtrim($dir, "/");
		$sub_service=str_replace($this->dir, "", $dir);
		$sub_service=rtrim($sub_service, "/");
		$sub_service=ltrim($sub_service, "/");
		$xml_dir="$dir/xml";

		if ($sub_service!=''){
			foreach ($this->substudies as $key => $val){
				if ($val->prefix==$sub_service) $curr_substudy=$val;
				$xml_dir=str_replace("$sub_service/xml", "xml/$sub_service", $xml_dir);
			}
		}
		else {
			$curr_substudy=$this;
		}
		$curr_substudy->setConfigParam();

		$user=new user($this->conn, $this->session_vars['remote_userid'], $curr_substudy);
		if (class_exists("Study_{$curr_substudy->prefix}")){
			$class_name="Study_".$curr_substudy->prefix;
		}
		else $class_name="Study";

		if ($this->session_vars ['VISITNUM_PROGR'] == '')
			$this->session_vars ['VISITNUM_PROGR'] = 0;
		//print_r($this->config_service);
		$study_=new $class_name($xml_dir, $curr_substudy->prefix, "visite_exams.xml", $this->conn, $this->session_vars, $this->config_service, $user,false, $this->config_service['WF_NAME'], $curr_substudy, $this);
		$study_->Controller();
		return $study_;
	}

	/**
	 * Restituisce le configurazioni
	 *
	 * @return array
	 */
	function getConfigService(){
		return $this->config_service;
	}



	/**
	 * Imposta i parametri di configurazione
	 *
	 * @param boolean $no_global
	 */
	function setConfigParam($no_global=false) {
        $config_service = array();
		if(!$no_global){
		global $service;
		global $config_service;
		global $in;
		}else{
            if ($GLOBALS["config_service"]['production']){
                $config_service['production']=$GLOBALS["config_service"]['production'];
            }
        }
		$service = $this->prefix;
		if ($in ['VISITNUM_PROGR'] == '')
			$in ['VISITNUM_PROGR'] = 0;
		$config_service ['VISITNUM_PROGR'] = $this->configurations['VISITNUM_PROGR'];
		$config_service ['PK_SEQ'] = $service . "_PK_SEQ";
		$config_service ['ROLE_TB'] = true;
		$config_service ['CENTER_TB'] = true;
		$config_service ['menu_laterale'] = 0;
		$config_service ['PK_SERVICE'] = $this->pk_service;
		$config_service ['service'] = $service;
		$config_service ['DM'] = $this->configurations['DM'];
		$config_service ['Menu_paziente'] = $this->labels['MENU_PAZIENTE'];
		$config_service ['Lista_schede'] = $this->labels['LISTA_SCHEDE'];
		$config_service ['Patients_list'] = $this->labels['PATIENTS_LIST'];
		$config_service ['patients_list_substudy'] = $this->labels['PATIENTS_LIST_SUBSTUDY'];
		$config_service ['Torna_lista_schede'] = $this->labels['TORNA_LISTA_SCHEDE'];
		$config_service['WF_NAME']=$this->workflow['DESCR'];
		$config_service['lang']=$this->configurations['LANG'];
		$config_service['field_lib']=$this->configurations['FIELD_LIB'];
		$config_service['QUERYNAMES']=$this->configurations['QUERYNAMES'];
		$config_service['BookPkService']=$this->configurations['BookPkService'];
        $config_service['eQueryXmlConfigurations']['SingleRegistry']=$this->configurations['eQueryXmlConfigurations']['SingleRegistry'];
		$config_service['aLanguages']=$this->configurations['LANGUAGES'];
        if ($_COOKIE["{$service}_selected_lang"]!="") $config_service['lang']=$_COOKIE["{$service}_selected_lang"];
        $this->ml=new axmr_ml($service, $config_service['lang'], $this->conn, $config_service);
        $this->config_service=$config_service;
        
        
	}

	/**
	 * Costruttore
	 *
	 * @param String $xml
	 * @param dbconn $conn
	 * @param boolean $isfile
	 * @param array $in
	 * @param number $depth
	 * @return xmrwf
	 */
	function xmrwf($xml, $conn, $isfile = true, $in=null,$depth=0) {
		$this->conn = $conn;
		$this->session_vars=$in;
		$this->depth=$depth;
		if ($isfile) {
			$xml_content = file_get_contents ( $xml );
			$p = xml_parser_create ();
			xml_parse_into_struct ( $p, $xml_content, $vals, $index );
			xml_parser_free ( $p );
			$ret = call_myself ( $vals );
			$array_struct = $ret ['array'];
		} else {
			$array_struct = $xml;
		}
		foreach ( $array_struct ['STUDY'] as $key => $val ) {
			$this->buildConfigs ( $val ['CONFIGURATION'] [0] );
			$this->dir=$val['DIR_BASE'][0]['value'];
			/*
			 * TODO: esclusione Workflow
			$this->buildWorkflow ( $val ['WORKFLOW'] [0] );
			$this->buildCenterView ( $val ['CENTER_VIEW'] [0] );
			*/
			if (is_array($val ['SUBSTUDIES'])) foreach ( $val ['SUBSTUDIES'][0]['STUDY'] as $key_s => $val_s ) {
				$subxmr['STUDY'][0]=$val ['SUBSTUDIES'][0]['STUDY'][$key_s];
				$this->substudies [$key_s] = new xmrwf ( $subxmr, $conn, false ,$this->session_vars,$this->depth+1);
			}
		}
		if (isset ( $_GET ['init_service'] )) {
			$this->XMR_Sql ();
			/*
			 * TODO: esclusione Workflow
				
			$this->WF_setup ();
			*/
			$this->generate_XMR_DB ();
			/*
			 * TODO: esclusione Workflow
			$this->init_WF ();
			*/
			$this->init_System();
		}
	}

	/**
	 * Inizializa il sistema
	 *
	 */
	function init_System(){
		foreach ($this->substudies as $key => $val){
			$xml_dir=$this->dir."/xml/{$val->prefix}";
			$ln_dir=$this->dir."/{$val->prefix}";
			if (!is_dir($xml_dir)){
				mkdir($xml_dir);
			}
			$system="chmod 2777 $xml_dir";
			system ("chmod 2777 $xml_dir");
			if (!is_link($ln_dir)){
				system ("ln -s servizio {$val->prefix}");
			}

		}
	}

	/**
	 * Inizializza il WorkFlow
	 *
	 */
	function init_WF() {
		$prefix = $this->workflow ['PREFIX'];
		$values ['DESCR'] = $this->workflow ['DESCR'];
		$values ['OBJECT'] = $this->workflow ['OBJECT'];
		$values ['PREFIX'] = $this->workflow ['PREFIX'];
		$sql_query = "select count(*) as conto from workflow where DESCR='{$values['DESCR']}'";
		$sql = new query ( $this->conn );
		$sql->get_row ( $sql_query );
		if ($sql->row ['CONTO'] == 0) {
			$sql_max = "select max(id) as maxid from workflow";
			$sql->exec ( $sql_max );//non richiede binding
			$sql->get_row ();
			$nextid = $sql->row ['MAXID'] + 1;
			$values ['ID'] = $nextid;
			$pk ['ID'] = '';
			$sql->insert ( $values, "workflow", $pk );
			$this->conn->commit ();
		}
		unset ( $values );
		foreach ( $this->workflow ['ATTORE'] as $key => $val ) {
			$sql_query = "select count(*) as conto from {$prefix}_attori where id='{$key}'";
			$sql = new query ( $this->conn );
			$sql->get_row ( $sql_query );
			if ($sql->row ['CONTO'] == 0) {
				$values ['ID'] = $key;
				$values ['DECODE'] = $val ['NOME'];
				$values ['POS'] = $key;
				$sql->insert ( $values, "{$prefix}_attori", $pk );
				$this->conn->commit ();
			}
		}
		unset ( $values );
		foreach ( $this->workflow ['STATO'] as $key => $val ) {
			$sql_query = "select count(*) as conto from {$prefix}_stati where id='{$key}'";
			$sql = new query ( $this->conn );
			$sql->get_row ( $sql_query );
			if ($sql->row ['CONTO'] == 0) {
				$values ['ID'] = $key;
				$values ['DECODE'] = $val ['NOME'];
				$values ['SPEC'] = $val ['NOME'];
				$values ['ID_ATTORE'] = $val ['ID_ATTORE'];
				$values ['POS'] = $key;
				$sql->insert ( $values, "{$prefix}_stati", $pk );
				$this->conn->commit ();
			}
		}
		unset ( $values );
		foreach ( $this->workflow ['RAMO'] as $key => $val ) {
			$sql_query = "select count(*) as conto from {$prefix}_rami where id_stato_orig='{$val['ID_STATO_ORIG']}' and id_stato_dest='{$val['ID_STATO_DEST']}'";
			$sql = new query ( $this->conn );
			$sql->get_row ( $sql_query );
			if ($sql->row ['CONTO'] == 0) {
				$pk = '';
				$sql->insert ( $val, "{$prefix}_rami", $pk );
				$this->conn->commit ();
			}
		}

	}

	/**
	 * SetUp del Workflow
	 *
	 */
	function WF_setup() {
		$this->queries ['WORKFLOW'] [0] = "
		create table WORKFLOW
				(
				  ID         NUMBER not null,
				  DESCR      VARCHAR2(200),
				  PREFIX     VARCHAR2(10),
				  OBJECT     VARCHAR2(200),
				  USERID_INS VARCHAR2(32 CHAR),
				  DESCR_LONG VARCHAR2(4000)
				)
			";
		$this->queries ['WORKFLOW'] [1] = "
				alter table WORKFLOW add constraint PK_{$this->table} primary key (ID)
			";
		$prefix = strtoupper ( $this->workflow ['PREFIX'] );
		$this->queries [$prefix . '_ATTORI'] [0] = "
			create table {$prefix}_ATTORI
				(
				  ID     NUMBER not null,
				  DECODE VARCHAR2(200),
				  POS    NUMBER
				)
		";
		$this->queries [$prefix . '_ATTORI'] [1] = "
			alter table {$prefix}_ATTORI add constraint PK_{$prefix}_ATTORI primary key (ID)
		";
		$this->queries [$prefix . '_STATI'] [0] = "
			create table {$prefix}_STATI(
  				ID        NUMBER not null,
  				DECODE    VARCHAR2(400),
  				SPEC      VARCHAR2(4000),
  				ID_ATTORE NUMBER,
  				POS       NUMBER
  			)
		";
		$this->queries [$prefix . '_STATI'] [1] = "
			alter table {$prefix}_STATI add constraint PK_{$prefix}_STATI primary key (ID)
		";

		$this->queries [$prefix . '_RAMI'] [0] = "
			create table {$prefix}_RAMI(
  				ID_STATO_ORIG NUMBER not null,
  				ID_STATO_DEST NUMBER not null,
  				XML_FORM      VARCHAR2(400),
  				CONDITION     VARCHAR2(200)
			)
		";
		$this->queries [$prefix . '_RAMI'] [1] = "
			alter table {$prefix}_RAMI add constraint PK_{$prefix}_RAMI primary key (ID_STATO_ORIG, ID_STATO_DEST)
		";
		$this->queries [$prefix . '_RAMI'] [2] = "
			alter table {$prefix}_RAMI add constraint FK_{$prefix}_RAMI_DEST foreign key (ID_STATO_DEST) references {$prefix}_STATI (ID) on delete cascade
		";
		$this->queries [$prefix . '_RAMI'] [3] = "
			alter table {$prefix}_RAMI add constraint FK_{$prefix}_RAMI_ORIG foreign key (ID_STATO_ORIG) references {$prefix}_STATI (ID) on delete cascade
		";
		$this->queries [$prefix . '_REP'] = "
			create table {$prefix}_REP(
  				ID_ORIG NUMBER not null,
  				ID_DEST NUMBER not null,
  				PK_SERVICE NUMBER,
  				USERID VARCHAR2(32 CHAR),
  				DT_CHANGE DATE
			)
		";
		$this->queries [$prefix . '_STATO'] [0] = "
			create table {$prefix}_STATO(
  				ID_STATO NUMBER not null,
  				PK_SERVICE NUMBER,
  				DT_INI DATE
			)
		";
		$this->queries [$prefix . '_STATO'] [1] = "
                alter table {$prefix}_STATO add constraint PK_{$prefix}_STATO primary key (PK_SERVICE)
         ";
	}

	/**
	 * Costruisce il DB per l'XMR
	 *
	 */
	function generate_XMR_DB() {
		foreach ( $this->queries as $key => $val ) {
			$sql_query = "select count(*) as conto from user_objects where object_NAME ='" . strtoupper ( $key ) . "'";
			$sql = new query ( $this->conn );
			$sql->get_row ( $sql_query );
			if ($sql->row ['CONTO'] == 0) {
				if (is_array ( $val )) {
					foreach ( $val as $k => $v ) {
						$sql_do = new query ( $this->conn );
						$sql_do->set_sql ( $v );
						$sql_do->ins_upd ();//non richiede binding
					}
				} else {
					$sql_do = new query ( $this->conn );
					$sql_do->set_sql ( $val );
					$sql_do->ins_upd ();//non richiede binding
				}
			}
		}
	}

	/**
	 * Sql di costruzione del DB XMR
	 *
	 */
	function XMR_Sql() {
		$this->queries [$this->prefix . "_" . 'CENTRI'] = "
		  CREATE OR REPLACE FORCE VIEW {$this->prefix}_CENTRI (\"CENTER\", \"DENOM\", \"USERID\") AS 
		  select s.id as CENTER, s.descr as DENOM, '' as USERID from 
			SITES s, SITES_STUDIES ss
			where ss.STUDY_PREFIX='{$this->prefix}'
			and ss.ACTIVE=1
			and ss.SITE_ID=s.id
		";
		/*
		 * TODO: eliminazione workflow

		foreach ( $this->workflow ['ATTORE'] as $key => $val ) {
			if ($utenti_centri_view != '')
				$utenti_centri_view .= "
			 union
			 ";
			$utenti_centri_view .= "select t.*, '{$val['NOME']}' as TIPOLOGIA from ({$val['QUERY']}) t";
		}
		*/
		$this->queries [$this->prefix . "_" . 'UTENTI_CENTRI'] = "
			  CREATE OR REPLACE FORCE VIEW {$this->prefix}_UTENTI_CENTRI (\"USERID\", \"CENTER\", \"TIPOLOGIA\") AS 
				  select up.userid as USERID, uss.SITE_ID as CENTER, sp.POLICY as TIPOLOGIA
				from users_profiles up, studies_profiles sp, USERS_SITES_STUDIES uss
				where 
				up.profile_id=sp.id
				and up.active=1
				and sp.active=1
				and sp.scope>0
				and sp.STUDY_PREFIX='{$this->prefix}'
				and uss.ACTIVE=1 and uss.STUDY_PREFIX=sp.STUDY_PREFIX and uss.USER_PROFILE_ID=up.PROFILE_ID
				union all
				select up.userid as USERID,ss.SITE_ID as CENTER,sp.POLICY as TIPOLOGIA
				from users_profiles up, studies_profiles sp, SITES_STUDIES ss
				where 
				up.profile_id=sp.id
				and up.active=1
				and sp.active=1
				and sp.scope=0
				and sp.STUDY_PREFIX='{$this->prefix}'
				and ss.ACTIVE=1 and ss.STUDY_PREFIX=sp.STUDY_PREFIX
				
		";

		$this->queries["{$this->prefix}_USER_PROFILE"]="
		  CREATE OR REPLACE FORCE VIEW {$this->prefix}_USER_PROFILE (\"PROFILE_CODE\", \"DESCRIZIONE\", \"POLICY\", \"SCOPE\", \"USERID\") AS 
		  select 
						  sp.code as profile_code, 
						  ag.descrizione,
						  sp.policy, 
              sp.scope, 
              us.userid
						from 
              studies_profiles sp, 
              studies s,
						  users_profiles up, 
              users_studies us,
              utenti_gruppiu ug, 
              ana_gruppiu ag
						where 
						  sp.study_prefix=s.prefix
						  and us.study_prefix=s.prefix
						  and up.profile_id=sp.id
						  and us.userid=up.userid
						  and s.active=1
						  and sp.active=1
              and up.active=1
						  and ug.userid=us.userid
			        and ug.abilitato=1
			        and ug.id_gruppou=ag.id_gruppou
			        and ag.nome_gruppo=s.prefix||'_'||sp.code
						  and s.prefix='{$this->prefix}'
		";

		$this->queries["{$this->prefix}_USER_PROFILES"]="
			CREATE OR REPLACE FORCE VIEW {$this->prefix}_USER_PROFILES (\"PROFILE_CODE\", \"DESCRIZIONE\", \"POLICY\", \"SCOPE\", \"USERID\", \"ACTIVE\", \"PROFILE_ID\") AS 
  			select 
						  sp.code as profile_code, 
						  ag.descrizione,
						  sp.policy, 
              sp.scope, 
              us.userid,
              up.active,
              sp.id
						from 
              studies_profiles sp, 
              studies s,
						  users_profiles up, 
              users_studies us,
              utenti_gruppiu ug, 
              ana_gruppiu ag
						where 
						  sp.study_prefix=s.prefix
						  and us.study_prefix=s.prefix
						  and up.profile_id=sp.id
						  and us.userid=up.userid
						  and s.active=1
						  and sp.active=1
              and ug.userid=us.userid
			        and ug.abilitato=1
			        and ug.id_gruppou=ag.id_gruppou
			        and ag.nome_gruppo=s.prefix||'_'||sp.code
						  and s.prefix='{$this->prefix}'
		";

		$this->queries ['STORICO_ID'] = "
			create sequence STORICO_ID
				minvalue 1
				maxvalue 99999999
				start with 21
				increment by 1
				cache 20
		";
		$this->queries [$this->prefix . "_" . 'PK_SEQ'] = "
			create sequence {$this->prefix}_PK_SEQ
					minvalue 1
					maxvalue 99999999
					start with 1
					increment by 1
					cache 20
		";

		$this->queries [$this->prefix . "_" . 'COORDINATE'][0] = "
			create table {$this->prefix}_COORDINATE
			(
			  VISITNUM       NUMBER not null,
			  VISITNUM_PROGR NUMBER not null,
			  PROGR          NUMBER not null,
			  ESAM           NUMBER not null,
			  INIZIO         NUMBER(1),
			  FINE           NUMBER(1),
			  INSERTDT       DATE,
			  MODDT          DATE,
			  USERID         VARCHAR2(200 CHAR),
			  VISITCLOSE     NUMBER(1) default 0,
			  INV_QUERY      VARCHAR2(200 CHAR),
			  {$this->pk_service}      NUMBER not null,
			  ABILITATO      NUMBER,
			  EQ_ACTION		 NUMBER,
			  CREATE_USER	 VARCHAR2(200 CHAR),
			  SEND_DT        DATE,
			  LAST_MOD_USER  VARCHAR2(255 CHAR)
			)
		";
		$this->queries [$this->prefix . "_" . 'COORDINATE'][1] = "
			alter table {$this->prefix}_COORDINATE
  			add constraint {$this->prefix}_COORD_PK primary key (VISITNUM, VISITNUM_PROGR, PROGR, ESAM, {$this->pk_service})
		";
		$this->queries [$this->prefix ."_USER_PROFILE"]="
			CREATE OR REPLACE FORCE VIEW ".$this->prefix."_USER_PROFILE ( PROFILE_CODE ,  DESCRIZIONE ,  POLICY ,  SCOPE ,  USERID ) AS 
  				SELECT
							    sp.code AS profile_code
							  , ag.descrizione
							  , sp.policy
							  , sp.scope
							  , us.userid
							  FROM
							    studies_profiles sp
							  , studies s
							  , users_profiles up
							  , users_studies us
							  , utenti_gruppiu ug
							  , ana_gruppiu ag
							  WHERE
							    sp.study_prefix  =s.prefix
							  AND us.study_prefix=s.prefix
							  AND up.profile_id  =sp.id
							  AND us.userid      =up.userid
							  AND s.active       =1
							  AND sp.active      =1
							  AND up.active      =1
							  AND ug.userid      =us.userid
							  AND ug.abilitato   =1
							  AND ug.id_gruppou  =ag.id_gruppou
							  AND ag.nome_gruppo =s.prefix
							    ||'_'
							    ||sp.code
							  AND s.prefix='".$this->prefix."'		
		";
		$this->queries [$this->prefix."_USER_PROFILES"]="
				 CREATE OR REPLACE FORCE VIEW ".$this->prefix."_USER_PROFILES (PROFILE_CODE, DESCRIZIONE, POLICY, SCOPE, USERID, ACTIVE, PROFILE_ID) AS 
  					SELECT
							    sp.code AS profile_code
							  , ag.descrizione
							  , sp.policy
							  , sp.scope
							  , us.userid
							  , up.active
							  , sp.id
							  FROM
							    studies_profiles sp
							  , studies s
							  , users_profiles up
							  , users_studies us
							  , utenti_gruppiu ug
							  , ana_gruppiu ag
							  WHERE
							    sp.study_prefix  =s.prefix
							  AND us.study_prefix=s.prefix
							  AND up.profile_id  =sp.id
							  AND us.userid      =up.userid
							  AND s.active       =1
							  AND sp.active      =1 
							  AND ug.userid      =us.userid
							  AND ug.abilitato   =1
							  AND ug.id_gruppou  =ag.id_gruppou
							  AND ag.nome_gruppo =s.prefix
							    ||'_'
							    ||sp.code
							  AND s.prefix='".$this->prefix."'
		";

		$this->queries [$this->prefix . "_" . 'EQUERY'] [0] = "

			create table {$this->prefix}_EQUERY
				(
  					ID             NUMBER not null,
 					CENTER         VARCHAR2(200 CHAR),
  					{$this->pk_service}         NUMBER,
  					VISITNUM       NUMBER,
  					ESAM           NUMBER,
  					PROGR          NUMBER,
  					Q_USERID       VARCHAR2(200 CHAR),
  					QUESTION       VARCHAR2(4000 CHAR),
	  				QUEST_DT       DATE,
  					TO_BE_VALIDATE NUMBER,
  					ANSWER         VARCHAR2(4000 CHAR),
  					ANS_DT         DATE,
  					A_USERID       VARCHAR2(200 CHAR),
  					VALIDATA       NUMBER,
  					CHIUSA         NUMBER,
  					VAL_DT         DATE,
  					VAL_USERID     VARCHAR2(200 CHAR),
  					VISITNUM_PROGR NUMBER,
  					CHIUSA_DT      DATE,
  					REGISTRY       VARCHAR2(200 CHAR)
				)
  		";
		$this->queries [$this->prefix . "_" . 'EQUERY'] [1] = "
			alter table {$this->prefix}_EQUERY
  			add constraint PK_{$this->prefix}_EQUERY primary key (ID)
			";
	}

	/**
	 * Costruisce la vista _UTENTI_CENTRI
	 *
	 * @param array $vals
	 */
	function buildCenterView($vals) {
		$this->center_view = $vals ['value'];
	}

	/**
	 * Costruisce l'array delle configurazioni
	 *
	 * @param array $vals
	 */
	function buildConfigs($vals) {

		
		foreach ( $vals as $key => $val ) {
			switch ($key) {
				case 'LABELS' :
					$this->buildLabels ( $val [0] );
					break;
				case 'ENTRY-POINT':

					foreach ($val[0]['ESAM'] as $k => $v){
						$this->entries[$v['value']]=true;
					}
					break;
				case 'PK_SEQ' :
					$this->configurations [$key] = "_PK_SEQ";
					break;
				case 'QUERYNAMES' :
    				foreach ($val [0] ['QUERYNAME'] as $qkey => $qvalue) {
    					$this->configurations['QUERYNAMES'][]=$qvalue['value'];
    				}
				    break;
				case 'BOOK_PK_SERVICE' :
                    $this->configurations['BookPkService']=$val [0]['value']=='true'?true:false;
                    break;
                case 'EQUERY' :
                    $this->configurations['eQueryXmlConfigurations']['SingleRegistry']=$val [0]['SINGLE_REGISTRY'][0]['value']=='true'?true:false;
                    break;
                case 'LANGUAGES':
                	foreach ($val[0]['LANG'] as $k=>$v){
                		$this->configurations['LANGUAGES'][$v['attributes']['CODE']]=$v['value'];
                	}
                	//$this->configurations->languages[$val]
                	break;
				default :
					$this->configurations [$key] = $val [0] ['value'];
					break;
			}
		}
		$this->prefix = $this->configurations ['PREFIX'];
		$this->pk_service = $this->configurations ['PK_SERVICE'];
		$this->configurations ['VISITNUM_PROGR'] = 1;
	}

	/**
	 * Costruisce le etichette della breadcrumb
	 *
	 * @param array $vals
	 */
	function buildLabels($vals) {
		foreach ( $vals as $key => $val ) {
			$this->labels [$key] = $val [0] ['value'];
		}
	}

	/**
	 * Costruisce le specifche del Workflow
	 *
	 * @param array $vals
	 */
	function buildWorkflow($vals) {
		return;
	}

}

function call_myself($vals, $key = 0) {
	$break = false;
	for($i = $key; $i < count ( $vals ); $i ++) {
		$val = $vals [$i];
		switch ($val ['type']) {
			case 'cdata' :
				break;
			case 'open' :
				$ret_1 = call_myself ( $vals, $i + 1 );
				$i = $ret_1 ['this'];
				$ret ['array'] [$val ['tag']] [] = $ret_1 ['array'];
				break;
			case 'close' :
				$ret ['this'] = $i;
				$ret ['array'];
				$break = true;
				break;
			case 'complete' :
				$next_key = count ( $ret ['array'] [$val ['tag']] );
				if (isset ( $val ['value'] ))
					$ret ['array'] [$val ['tag']] [$next_key] ['value'] = $val ['value'];
				if (isset ( $val ['attributes'] ))
					$ret ['array'] [$val ['tag']] [$next_key] ['attributes'] = $val ['attributes'];
				break;
		}
		if ($break)
			break;
	}
	return $ret;
}



?>