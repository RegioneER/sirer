<?
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/http_lib.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/db.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/xml_parser_wl.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/HTML_Parser.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/page.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/vlist.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/list.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/legend.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/esams_list.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/form.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/study_prototype.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/xmrwf.inc.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/integrazioni_ct.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/Installer.inc";
//Decommentare in caso di studio con ePRO. (viene sovrascritta la SubjidExist)
//include_once "epro.inc";

$config_service['STUDY_TYPE']='CLINICAL_TRIAL';

//UN-COMMENT to enable production environment (doesn't check for DB table alignment and LOG folder existance)
//$config_service['production'] = 1;

//Enable SDV
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/SDV_module_prototype.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/SourceDataVerification.inc";
class SDV_module extends SDV_module_prototype{}

//putenv("NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1");
$editing=false;

//$config_service["NoMessages"]=true;

$config_service['SHOW_MANDATORY_ON_HIDE'] = "yes";

$config_service['RegTable'] = 'REGISTRAZIONE';

// Configurazione ACMPath
$config_service['ACMPath'] = '/acm/';
// Configurazione ActivitiWF
$config_service['AWFConnectionId'] = 'sisa';
$config_service['AWFBaseURL'] = 'http://appserv-siss01.dev.cineca.it/GeniusWM/rest-service/';
$config_service['AWFUsername'] = 'admin';
$config_service['AWFPassword'] = 'xxx';

// Configurazione permetti modifica form chiusa al DE
$config_service['de_modify_form_allowed']=false; //se true può modificare qualsiasi form altrimenti rendere $config_service['de_modify_form_allowed'][VISITNUM][EXAM]=true per abilitare per singolo esame/visita


// Configurazione dblock
$config_service['dblock']=1;
$config_service['dblock_functions']=array();
$config_service['dblock_functions'][1]='NEWPATIENT'; //primo bit 0001
$config_service['dblock_functions'][2]='SAVESEND'; //secondo bit 0010
$config_service['dblock_functions'][3]='EQUERY'; //terzo bit 0100
$config_service['dblock_functions'][4]='OBVIOUSCORRECTION'; //quarto bit 1000

// Configurazione nuove eQuery
$config_service['eQuery']="1";
$config_service['eQuerySpec']['Integrazione']['ROLE']="DE";
$config_service['eQuerySpec']['Integrazione']['CONTROL_ROLE']="CRA";
$config_service['eQuerySpec']['Integrazione']['VALIDATOR']="DM"; 
// Fine configurazione nuove eQuery

//GENHD-44
$config_service['SHOW_ALL_EXAMS']=1; //se settato permette anche al DM  di visualizzare le form non chiuse nella exam_list con link disattivati


// Configurazione alert onload
//$config_service['javascript_alert']['onunload_page']="1";
//$config_service['javascript_alert']['onsave_page']="1";
//$config_service['javascript_alert']['onsend_page']="1";

$config_service['lang']='en';
$lang=$config_service['lang'];

//criptaggio dati:
$config_service['crypto']="no";

// Log abilitato
$config_service['force_log']=false;

$email_admin="c.contino@cineca.it";
$root=$_SERVER['DOCUMENT_ROOT'];
$dir=$_SERVER['PATH_TRANSLATED'];
$dirs=explode("/", $dir);
$dir='';
for ($i=0;$i<count($dirs)-1;$i++){
	$dir.=$dirs[$i]."/";
}
$dir=rtrim($dir, "/");
$xml_dir=$dir."/xml";
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/log_trace.php";

if(isset($_GET['init_service']) ){
	$xml = simplexml_load_file("study.xml") or die("feed not loading");
	$study_name=$xml->workflow->nome;
	$study_prefix=$xml->configuration->prefix;
	
	$conn = new dbconn();
	$installer = new Installer($study_prefix, $conn, $config_service, $study_name);
	$installer->CreateSessionsTable();
	$installer->CreateCMMTable();
	$installer->FixViews();
	//echo "<a href=\"/study/{$study_name}/index.php?install\">complete installation</a>";
	header("Location: /study/{$study_name}/index.php?install");
	die();
}

$conn=new dbconn();
$sql=new query($conn);

$sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");
$sql->ins_upd();

class audit_trail extends audit_trail_core_prototype{
}
class integrazioni extends integrazioni_prototype_ct{
}

class xml_form extends xml_form_prototype{
	
}

class xml_vlist extends xml_vlist_prototype{}

class xml_page extends xml_page_prototype{}

class xml_list extends xml_list_prototype{}

class legend extends legend_prototype{}

class user extends user_prototype{}

class xml_esams_list extends xml_esams_list_prototype{}

// Includo le f_to_calls abilitate (rinominate E_)
$f_to_calls_dir = substr($_SERVER['SCRIPT_FILENAME'],0,strrpos($_SERVER['SCRIPT_FILENAME'],"/"))."/f_to_calls";
//echo $f_to_calls_dir;
if (is_dir($f_to_calls_dir)) {
    if ($dh = opendir($f_to_calls_dir)) {
        while (($file = readdir($dh)) !== false) {
        	if (reset(explode('_', $file)) == "E") {
        		include_once "f_to_calls/".$file;
        	}
        }
        closedir($dh);
    }
}

function var_glob($value){
	global $in;
	global $inputval;
	if (isset($inputval[$value]) && $inputval[$value]!='') return $inputval[$value];
	if (isset($in[$value]) && $in[$value]!='') return $in[$value];
	if (isset($GLOBALS[$value]) && $GLOBALS[$value]!='') return $GLOBALS[$value];
}

function error_page($user, $error, $error_spec){
    global $filetxt;
    global $in;
    global $SRV;
    global $log_conn;
    global $service;
    global $remote_userid;
    global $session_number;
	
	/*VMAZZEO FIX ERROR_PAGE SU RICHIESTA AJAX SAVE/SEND 06.10.2014*/
	if($_POST['ajax_call']=='yes'){
		echo json_encode ( array (
				"sstatus" => "ko",
				"user" => $user,
				"error" => $error,
				"detail" => "Database ERROR: <br/>Code: ".$error_spec['code']."<br/>Message: ".$error_spec['message']
		) );
		die ();
	}
	else{
	    #echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
	    $today = date("j/m/Y, H:m:s");
	    if (is_array($error_spec)) foreach ($error_spec as $key => $val) $spec.="\n $key : $val";
	    mail("v.mazzeo@cineca.it, dario.mengoli@gmail.com", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n");
	    $body="<p align=center><font size=4><b>An error occurred</b></p><br><br>";
	    $filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
	    global $study_;
        $btrace = debug_backtrace();
        $stackstr = print_r($btrace,true);
	    do_render($study_, "<div class=\"alert alert-danger\"><i class=\"icon-remove\"></i><strong>Error: </strong>".$error."</div><pre>{$stackstr}</pre>");
	    //die(print_r(array("d.saraceno@cineca.it", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n"),1));
    } 
}

function do_render($study_, $body=null){

global $conn;
global $filetxt;

if ($body!=null) $study_->body=$body;
	
$onload=$study_->onload;
$script=$study_->script;
$body="".$body;
$user_name="<p class='profile-block' align=right>
	<b>Profile:</b> {$user->profilo}&nbsp;&nbsp;&nbsp;&nbsp;<br>
	<b>{$user->nome_azienda}&nbsp;User: </b>{$user->nome_cognome}&nbsp;&nbsp;&nbsp;&nbsp;<br>
	<b><a href='/change_password'>Change password</a>&nbsp;&nbsp;&nbsp;&nbsp;<br>
    <b><a href='/ShibLogOut'>Logout</a>&nbsp;&nbsp;&nbsp;&nbsp;<br>
	</p>
	
	";

$filetxt=preg_replace("/<!--script-->/", $script, $filetxt);
$filetxt=str_replace("<!--breadcrumb-->", $study_->breadcrumb, $filetxt);

$filetxt=str_replace("<!--navbar-->", $study_->configurer->navbar, $filetxt);
/*
if ($study_->configurer->sidebar->__toString()==""){
	$customStyle.=".main-content-no-sidebar{margin-left:0px;}\n";
	$customStyle.=".breadcrumb-no-sidebar{left:0px !important;}\n";
}
*/
$filetxt=str_replace("<!--title-->", $study_->title, $filetxt);
$pageTitleHtml="";
if ($study_->page_title!="") $pageTitleHtml="<div class=\"page-header\"><h1>".$study_->page_title."</h1></div>";
$filetxt=str_replace("<!--page_title-->", $pageTitleHtml, $filetxt);

/*$inbox = new inbox($conn);
$filetxt=str_replace("<!--inbox-->", $inbox->get_navbar(), $filetxt);
$filetxt=str_replace("<!--inbox_bottone-->", $inbox->get_navbarbtn(), $filetxt);
*/
$searchBox=' <div class="nav-search" id="nav-search">
                            <span class="input-icon">
                                <input type="text" placeholder="'.mlOut("System.Search","Search").' ..." class="nav-search-input" id="nav-search-input" autocomplete="off" />
                                <i class="fa fa-search nav-search-icon"></i>
                                <i id=\'search-icon\' class=""></i> 
                                </span>
                        </div>';
if (!$study_->configurer->hasFastSearch) $addSerachBox=" style='display:none'";
	
	$searchBox=' <div class="nav-search" id="nav-search"'.$addSerachBox.'>
                            <span class="input-icon">
                                <input type="text" placeholder="'.mlOut("System.Search","Search").' ..." class="nav-search-input" id="nav-search-input" autocomplete="off" />
                                <i class="fa fa-search nav-search-icon"></i>
                                <i id=\'search-icon\' class=""></i>
                                </span>
                        </div>';

$filetxt=str_replace("<!--searchBox-->", $searchBox, $filetxt);

$filetxt=str_replace("<!--customStyle-->", $customStyle, $filetxt);
$filetxt=str_replace("<!--sidebar-->", $study_->configurer->sidebar, $filetxt);
$filetxt=preg_replace("/<!--lang-->/", $study_->xmr->config_service['lang'], $filetxt);
$filetxt=preg_replace("/<!--utente-->/", $user_name, $filetxt);
$onload.=";\nif (document.forms[0]) document.forms[0].action='';";
$filetxt=preg_replace("/\/\/<!--onload-->/", $onload, $filetxt);
$filetxt=preg_replace("/<!--user_name-->/", $nome_user, $filetxt);
$filetxt=preg_replace("/<!--page_content-->/", $body, $filetxt);
$filetxt=preg_replace("/<!--legend_lower-->/", $legend_lower->html_legend_lower, $filetxt);
$filetxt=preg_replace("/<!--legend_upper-->/", $legend_upper->html_legend_upper, $filetxt);
$filetxt=str_replace("<br>", "<br/>", $filetxt);

die($filetxt);

}

function error_page_old($user, $error, $error_spec){
	global $filetxt;
	global $in;
	global $SRV;
	global $log_conn;
	global $service;
	global $remote_userid;
	global $session_number;
	
	
	//TODO: sistemare link a ErrorPage 
	include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/ErrorPage.v2.inc";
	$ErrorPage=new error_page();
	$ErrorPage->cineca_user ="v.mazzeo@cineca.it";
	$ErrorPage->hd_pierrelgroup="";
	$ErrorPage->send_error_page($filetxt,$in,$SRV,$log_conn,$service,$remote_userid,$session_number,$user, $error, $error_spec);
	//$ErrorPage->print_error_page($filetxt, $error, $error_spec);
}
/**
 * Funzione ausiliaria e-signature esame specifico
 *
 */
function esig_singleform($xml_form) {
	//Modificato x gestire pi� TimeZones
	global $in;
	global $conn;
	global $service;
	global $lang;

	if($lang=='en') {
		$visit_sign=" All forms must be sent.";
		$alert_enable=" Your Username is not able to sign eCRF. ";
		$alert_eqpending=" The electronic signature can be affixed only if there are no query pending in the related visit. At the moment there is at least one query pending in this visit. ";
		$alert_access=" The username inserted does not match with the one used to access.";
		$alert_user=" The username and/or the password is not valid.";
		$alert_passwd=" The password and/or the username is not correct.";
		$alert_doc=" An error occurrend generating the PDF document.";
	} else {
		$visit_sign=" Tutti gli esami devono essere inviati.";
		$alert_enable=" L'username non corrisponde a quello con cui si è effettuato l'accesso.";
		$alert_eqpending=" La firma elettronica può essere apposto solo se non ci sono query in attesa della visita correlati. Al momento non vi è almeno una query in attesa di questa visita. ";
		$alert_access=" L'username non corrisponde a quello con cui si è effettuato l'accesso.";
		$alert_user=" L'username non è valido.";
		$alert_passwd=" La password inserita non è corretta.";
		$alert_doc=" Errore nel generare il documento PDF.";
	}

	// Controllo solo la combinazione user/password
	if ($in['INVIOCO']==1 || $in['INVIOCO']==0) {
		$condition_passed=false;
		include_once '/http/lib/DriverIanus/libs.inc';
		$driver_conn=new DriverIanusDBConnection();
		$in['SAEPWD']=ereg_replace( ' ', "+", $in['SAEPWD']);
		//Controllo correttezza passwd immessa rispetto a quella dell'usserid in DB
		//SINVSIGN
		//if (CheckPWD($driver_conn, strtoupper($in['remote_userid']), strtoupper($in['SAEPWD']))) {
		if (CheckPWD($driver_conn, strtoupper($in['SINVSIGN']), strtoupper($in['SAEPWD']))) {
			if(CheckUserSignEnable($in['SINVSIGN']) != 0) {
				$condition_passed = true;
			} else {
				$condition_passed=false;
				if( $in['ajax_call']!='') {
					if($in['esig_singleform']!=''){ //rispondo alla chiamata ajax da ESAE_TYPE_SAVE per controllare la signature per evitare che i campi disabilitati si riabilitino
						echo json_encode(array("sstatus" => "ko", "error" => $alert_enable));
						die();
					}
					else{
						echo "Error:#error#";
						die($alert_enable);
					}
				}
			}
		} else {
			$condition_passed = false;
			if( $in['ajax_call']!=''){
				if($in['esig_singleform']!=''){ //rispondo alla chiamata ajax da ESAE_TYPE_SAVE per controllare la signature per evitare che i campi disabilitati si riabilitino
					echo json_encode(array("sstatus" => "ko", "error" => $alert_passwd));
					die();
				}
				else{
					echo "Error:#error#";
					die($alert_passwd);
				}
			}
		}
		
	/*	if($condition_passed == true && $in['esig_singleform']!=''){ //rispondo alla chiamata ajax da ESAE_TYPE_SAVE per controllare la signature per evitare che i campi disabilitati si riabilitino
			echo json_encode(array("sstatus" => "ok","error" => "TUTTO OK!"));
			die();
		}
*/
		if($condition_passed == true){
			//Salvo data e ora in tabella
			//print_r($xml_form);
			$nometab = $xml_form->form['TABLE'];
			//die($nometab);
			//Calcolo Timezones
			$center = $in['CENTER'];
			$dateTimeL = new DateTime("now", new DateTimeZone('Europe/Rome'));
			$STZDT="TO_DATE('{$dateTimeL->format("Y-m-d")}','YYYY-MM-DD')";
			$STZTM="'{$dateTimeL->format("Hi")}'";
			$STZTM_H = "'{$dateTimeL->format("H")}'";
			$STZTM_M = "'{$dateTimeL->format("i")}'";
			/*$select_rdnumber="SELECT iso.TIMEZONE FROM {$service}_ISO_COUNTRY_LIST iso, CMM_CENTER cnt WHERE cnt.ID_CENTER={$center} AND iso.ISO=cnt.COUNTRY";
			$select_rdnumber_query=new query($conn);
			$select_rdnumber_query->exec($select_rdnumber);
			$select_rdnumber_query->get_row();
			$tzname = $select_rdnumber_query->row['TIMEZONE'];
			//die($tzname);
			if ($tzname){
				$localDTZ = new DateTimeZone($tzname);
				$dateTimeL->setTimezone($localDTZ);
			}*/
			//$LTZ="TO_DATE({$dateTimeL->format("Y-m-d H:i:s")},'YYYY-MM-DD HH24:MI:SS')";
			$LTZDT="TO_DATE('{$dateTimeL->format("Y-m-d")}','YYYY-MM-DD')";
			$LTZTM="'{$dateTimeL->format("Hi")}'";
			$LTZTM_H = "'{$dateTimeL->format("H")}'";
			$LTZTM_M = "'{$dateTimeL->format("i")}'";
			//Server Timezone
			$sql=new query($conn);
			$sql_upd="update {$nometab} set SINVDAT={$STZDT}, SINVDATRC='OKOKOK',  SINVTIM_H={$STZTM_H}, SINVTIM_M={$STZTM_M}  where  visitnum={$in['VISITNUM']} and  visitnum_progr={$in['VISITNUM_PROGR']} and codpat={$in['CODPAT']} and esam={$in['ESAM']} and progr={$in['PROGR']}  ";
			//echo($sql_upd);
			$sql->set_sql($sql_upd);
			$sql->exec();
			// Forzo il commit
			$xml_form->conn->commit();
			//Altro timezone
			$sql=new query($conn);
			$sql_upd="update {$nometab} set SINVDATL={$LTZDT}, SINVDATLRC='OKOKOK', SINVTIML_H={$LTZTM_H}, SINVTIML_M={$LTZTM_M} where  visitnum={$in['VISITNUM']} and  visitnum_progr={$in['VISITNUM_PROGR']} and codpat={$in['CODPAT']} and esam={$in['ESAM']} and progr={$in['PROGR']}  ";
			//echo($sql_upd);
			$sql->set_sql($sql_upd);
			$sql->exec();
			//die();
			// Forzo il commit
			$xml_form->conn->commit();

			//FINE , tracciamento nella tabella delle firme.
			UpdateDbSignatureSingle($xml_form);

			return true;
		}else{
			return false;
		}
	}
}

function UpdateDbSignatureSingle($xml_form){
	global $in;
	global $conn;
	global $service;
	global $lang;
	$sql3=new query($conn);
	//Gestione Audit Trail
	$pk='';
	$vals_at['VISITNUM']=$in['VISITNUM'];
	$vals_at['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
	$vals_at['ESAM']=$in['ESAM'];
	$vals_at['PROGR']=$in['PROGR'];
	$vals_at['CODPAT']=$in['CODPAT'];
	$vals_at['CENTER']=$in['CENTER'];
	$vals_at['VALUE_NEW']="to_char(sysdate , 'DD/MM/YYYY HH24:MI:SS')";
	$vals_at['NOMETAB']=$xml_form->form['TABLE'];
	$vals_at['USERID']=$in['remote_userid'];
	$vals_at['MODDT']="sysdate";
	$vals_at['VAR']='TIME_SIG';
	$vals_at['ACTION']="Change/update by Investigator";
	$sql3->insert($vals_at, "S_X_".$service,$pk);
	//	$conn->commit();

	$visite_exams_path=str_replace("index.php", "", $_SERVER['SCRIPT_FILENAME'])."xml/visite_exams.xml";
	$vlist = new xml_esams_list ( $visite_exams_path ,$config,$session_vars, $conn);



	$sql_check3="select count(*) as CONTO from {$service}_SIGNATURES where  codpat={$in['CODPAT']} and visitnum={$in['VISITNUM']}  AND VISITNUM_PROGR={$in['VISITNUM_PROGR']} AND ESAM={$in['ESAM']} AND PROGR={$in['PROGR']} ";
	$sql3->set_sql($sql_check3);
	$sql3->exec();
	$sql3->get_row();
	if($sql3->row['CONTO']==0){
		$pk='';
		$vals['SIGN_DATE']="sysdate";
		$vals['ACCOUNT']=$in['remote_userid'];

		$vals['VISITNUM']=$in['VISITNUM'];
		$vals['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
		$vals['ESAM']=$in['ESAM'];
		$vals['PROGR']=$in['PROGR'];
		$vals['CODPAT']=$in['CODPAT'];
		$sql3->insert($vals, $service."_SIGNATURES ",$pk);
	}
	else{
		if($in['VISITNUM_PROGR']!=""){
			$and_visitnumprogr="and  visitnum_progr={$in['VISITNUM_PROGR']}";
		}
		else{$and_visitnumprogr="and  visitnum_progr=0";
		}
		//Al successivo re-send- eSignature della form signature deve essere aggiornato il record precedentemente cancellato
		$sql_update="update {$service}_signatures set sign_date=sysdate, account='{$in['remote_userid']}'
		where visitnum={$in['VISITNUM']}  and codpat={$in['CODPAT']}  $and_visitnumprogr
		and esam={$in['ESAM']} and progr={$in['PROGR']} and account is null and sign_date is null";
		$sql3->set_sql($sql_update);
		$sql3->ins_upd();
	}


	$sql_fine="update {$service}_coordinate set fine=1  where  visitnum={$in['VISITNUM']} and  visitnum_progr={$in['VISITNUM_PROGR']} and codpat={$in['CODPAT']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
	$sql3->set_sql($sql_fine);
	$sql3->ins_upd();

	$conn->commit();
}

function SendMailESAE($xml_form) {
	global $in;
	global $conn;
	global $service;
	global $lang;

	
	/**
	 * PIERHD-2064
	 * vmazzeo 10.01.2014
	 * 
	 * se il sae viene salvato con la firma elettronica (� tutto come prima... crea pdf e invia mail)
	 */
	
	//
	if ($in['SINVSIGN']==""||$in['SAEPWD']==""){
		return false;
	}
	else if(!esig_singleform($xml_form)){
		return false;
	}
	
	if ($in['SINVSIGN']==""||$in['SAEPWD']==""){
		return false;
	}
	else if (!generateDoc($xml_form)){
		return false;
	}
	
	if( !$in['ajax_call']){
		//$xml_form->conn->commit();
// 		echo "<pre>";
// 		print_r($in);
// 		echo "</pre>";
		//die();
		
		
		/**
		 * PIERHD-2199
		 * vmazzeo 20.02.2014
		 * aggiunti SC[1-6] alla mail da inviare (sono checkbox quindi devo caricarmi il testo da xml_form->fields
		 */
		/**
		 * PIERHD-2800
		 * vmazzeo 14.01.2015
		 * 2.6 aggiungo data esae e se � un AESI
		 */		
		$sql_mailsent="SELECT s.SITEID, s.SUBJID, s.SAE1, s.SAE2, s.SAE3, s.SAE4, s.SAE5,s.SC1, s.SC2, s.SC3, s.SC4, s.SC5, s.SC6, s.RECDAT_D, s.RECDAT_M, s.RECDAT_Y, s.D_SAETYPE, s.SAESTDAT_D, s.SAESTDAT_M, s.SAESTDAT_Y,s.D_NSAESI from {$service}_SAE s NATURAL JOIN {$service}_COORDINATE c WHERE INIZIO=1 AND CODPAT={$in['CODPAT']} AND PROGR={$in['PROGR']}";
		$sql = new query ( $conn );
		$sql->set_sql($sql_mailsent);
		$sql->exec();
		$sql->get_row();
		$row=$sql->row;
		//print_r($row);
		$siteid=$sql->row['SITEID'];
		$subjid=$sql->row['SUBJID'];
		$sae1=$sql->row['SAE1'];
		$sae2=$sql->row['SAE2'];
		$sae3=$sql->row['SAE3'];
		$sae4=$sql->row['SAE4'];
		$sae5=$sql->row['SAE5'];
		/**
		 * PIERHD-2199
		 * vmazzeo 20.02.2014
		 * aggiunti SC[1-6] alla mail da inviare (sono checkbox quindi devo caricarmi il testo da xml_form->fields
		 */
		$seriousness_criteria_txt=array();
		//var_dump($xml_form->fields);
		foreach($xml_form->fields as $field){
			if($field['VAR']=='SC1'){
				$seriousness_criteria_txt['SC1']=$field['VALUE']['SC1'];
			}
			if($field['VAR']=='SC2'){
				$seriousness_criteria_txt['SC2']=$field['VALUE']['SC2'];
			}
			if($field['VAR']=='SC3'){
				$seriousness_criteria_txt['SC3']=$field['VALUE']['SC3'];
			}
			if($field['VAR']=='SC4'){
				$seriousness_criteria_txt['SC4']=$field['VALUE']['SC4'];
			}
			if($field['VAR']=='SC5'){
				$seriousness_criteria_txt['SC5']=$field['VALUE']['SC5'];
			}
			if($field['VAR']=='SC6'){
				$seriousness_criteria_txt['SC6']=$field['VALUE']['SC6'];
			}
		}
		//var_dump($seriousness_criteria_txt);
		//die();
		$seriousness_criteria="";
		$comma="";
		if($sql->row['SC1']==1)
		{
			
			$seriousness_criteria.=$seriousness_criteria_txt['SC1'];
			$comma=", ";
			//$seriousness_criteria.=$sql->row['SC1'];
			
		}
		if($sql->row['SC2']==1)
		{
			$seriousness_criteria.=$comma.$seriousness_criteria_txt['SC2'];
			$comma=", ";
		}
		if($sql->row['SC3']==1)
		{
			$seriousness_criteria.=$comma.$seriousness_criteria_txt['SC3'];
			$comma=", ";
		}
		if($sql->row['SC4']==1)
		{
			$seriousness_criteria.=$comma.$seriousness_criteria_txt['SC4'];
			$comma=", ";
		}
		if($sql->row['SC5']==1)
		{
			$seriousness_criteria.=$comma.$seriousness_criteria_txt['SC5'];
			$comma=", ";
		}
		if($sql->row['SC6']==1)
		{
			$seriousness_criteria.=$comma.$seriousness_criteria_txt['SC6'];
		}
		
		$recdat=$sql->row['RECDAT_D']!= "" ? $sql->row['RECDAT_D']."/".$sql->row['RECDAT_M']."/".$sql->row['RECDAT_Y'] : "";
		$d_saetype=$sql->row['D_SAETYPE'];
		$saestdat=$sql->row['SAESTDAT_D'] != "" ? $sql->row['SAESTDAT_D']."/".$sql->row['SAESTDAT_M']."/".$sql->row['SAESTDAT_Y'] : "";//PIERHD-2800
		$d_nsaesi=$sql->row['D_NSAESI'];//PIERHD-2800
		$test="";
		
		
		$sql_storico="SELECT * 
						FROM
						  S_{$service}_SAE s
						WHERE s.CODPAT={$in['CODPAT']}
						AND s.VISITNUM={$in['VISITNUM']}
						AND s.VISITNUM_PROGR={$in['VISITNUM_PROGR']}
						AND s.ESAM={$in['ESAM']}
						AND s.PROGR={$in['PROGR']}
						ORDER BY MODPROG DESC"; //prendo il pi� recente
		$sql = new query ( $conn );
		$sql->set_sql($sql_storico);
		$sql->exec();
		$sql->get_row();//PIERHD-2800 prendo row per eseguire controllo su campi modificati
		$row_storico=$sql->row;
		//print_r($row_storico);
		//die();
		$FIRST=empty($row_storico) ? "first saving of the form": "change"; //PIERHD-2800
		
		$changes="";
		if(!empty($row_storico)){
			$seriousness_criteria_storico="";
			$comma="";
			if($row_storico['SC1']==1)
			{
				
				$seriousness_criteria_storico.=$seriousness_criteria_txt['SC1'];
				$comma=", ";
				//$seriousness_criteria.=$sql->row['SC1'];
				
			}
			if($row_storico['SC2']==1)
			{
				$seriousness_criteria_storico.=$comma.$seriousness_criteria_txt['SC2'];
				$comma=", ";
			}
			if($row_storico['SC3']==1)
			{
				$seriousness_criteria_storico.=$comma.$seriousness_criteria_txt['SC3'];
				$comma=", ";
			}
			if($row_storico['SC4']==1)
			{
				$seriousness_criteria_storico.=$comma.$seriousness_criteria_txt['SC4'];
				$comma=", ";
			}
			if($row_storico['SC5']==1)
			{
				$seriousness_criteria_storico.=$comma.$seriousness_criteria_txt['SC5'];
				$comma=", ";
			}
			if($row_storico['SC6']==1)
			{
				$seriousness_criteria_storico.=$comma.$seriousness_criteria_txt['SC6'];
			}
			$saestdat_storico=$row_storico['SAESTDAT_D'] != "" ? $row_storico['SAESTDAT_D']."/".$row_storico['SAESTDAT_M']."/".$row_storico['SAESTDAT_Y'] : "";//PIERHD-2800
			echo "<pre>";
			print_r($saestdat);
			print_r($saestdat_storico);
			echo "</pre>";
			//die();
			if($saestdat!=$saestdat_storico){
				$changes.="Onset date: <b>{$saestdat_storico}</b><br/>";
			}			
			if($row['SAE1']!=$row_storico['SAE1'] || $row['SAE2']!=$row_storico['SAE2'] || $row['SAE3']!=$row_storico['SAE3'] || $row['SAE4']!=$row_storico['SAE4'] || $row['SAE5']!=$row_storico['SAE5']){
				$changes.="SAE/AESI description: <b>{$row_storico['SAE1']} {$row_storico['SAE2']} {$row_storico['SAE3']} {$row_storico['SAE4']} {$row_storico['SAE5']}</b> <br/>";
			}
			if($seriousness_criteria!=$seriousness_criteria_storico){
				$changes.="Seriousness criteria: <b>{$seriousness_criteria_storico}</b><br/>";
			}
			if($row['D_NSAESI']!=$row_storico['D_NSAESI']){
				$changes.="Is the event an AESI?: <b>{$row_storico['D_NSAESI']}</b><br/><br/>";
			}			
			if($changes!=""){
				$changes="Information on changed data (<em>only last version of changed data are shown</em>)<br><br>".$changes;
			}		
		}
		
		
		/*if (preg_match("/\.dev\./i",$_SERVER['HTTP_HOST'])) {
			// Dev
		} elseif (preg_match("/\.test\./i",$_SERVER['HTTP_HOST']) || $in['CENTER'] =='599') {
			// Test
			$mailto="hypernet@pierrel-research.com";//::autoemail::aaaiii01::AAAIII01 - eSAE Report::test::
			$test="<span style=\"color:red\"><b>\"TEST ENVIRONMENT\"</b></span><br/><br/>";
		} elseif (preg_match("/-preprod\./i",$_SERVER['HTTP_HOST'])) {
			// PreProd
			$mailto="paola.santoro@adacap.com, safety@fordrugconsulting.fr, pharmacovigilance@adacap.com, hypernet@pierrel-research.com";//::autoemail::aaaiii01::AAAIII01 - eSAE Report::prep::
			$test="<span style=\"color:red\"><b>\"TEST ENVIRONMENT\"</b></span><br/><br/>";
		} else {
			// Prod
			$mailto="paola.santoro@adacap.com, safety@fordrugconsulting.fr, pharmacovigilance@adacap.com,  n.okeeffe@pierrel-research.com, l.merlini@pierrel-research.com, m.mazzoleni@pierrel-research.com, r.Pogoda@pierrel-research.com, hypernet@pierrel-research.com,   v.borghi@pierrel-research.com, i.ilia@pierrel-research.com,s.siafrigoli@pierrel-research.com,m.casiraghi@pierrel-research.com,c.silva@pierrel-research.com,  e.leonardo@pierrel-research.com, s.parisi@pierrel-research.com, l.clarke@pierrel-research.com, e.forlanelli@pierrel-research.com, s.keffel@pierrel-research.com, s.mccallum@pierrel-research.com";//::autoemail::aaaiii01::AAAIII01 - eSAE Report::prod::
		}
		$mailto.=",hypersuite@cineca.it";
		$headers  = "From: AAAIII01@{$_SERVER['SERVER_NAME']}\n";
		$headers .= "Content-type: text/html; charset=utf-8 \n";
		mail($mailto, "AAAIII01 - eSAE Report", 
					  "{$test}It is a: <b>{$FIRST}</b><br/><br/>
					   Subject ID: <b>{$siteid}-{$subjid}</b><br/><br/>
					   SAE/AESI No.: <b>{$in['PROGR']}</b><br/>
					   Onset date: <b>{$saestdat}</b><br/>
					   SAE/AESI description: <b>{$sae1} {$sae2} {$sae3} {$sae4} {$sae5}</b><br/><br/>
					   Seriousness criteria: <b>{$seriousness_criteria}</b><br/>
					   Is the event an AESI?: <b>{$d_nsaesi}</b><br/><br/>
					   {$changes}<br/><br/>
					   Date of SAE reporting to Laboratories AAA: <b>".$recdat."</b><br/><br/>Type of SAE report: <b>{$d_saetype}</b><br/><br/><i>AAA Project Team.</i><br/><br/>", $headers);
		*/
		return true;
	}
}
function generateDoc($xml_form, $actionName="", $fileName=null){
	global $in;
	global $conn;
	global $service;
	global $lang;

	if($lang=='en') {
		$alert_doc=" An error occurrend generating the PDF document.";
	} else {
		$alert_doc=" Errore nel generare il documento PDF.";
	}

	$retval = true;

	if( !$in['ajax_call'] ){
		// Genero il documento
		//echo $fileName;
		$mydocgen = new DocumentGenerator(null,null,null,null,null,$fileName);
		$response = $mydocgen->doDocGen_f_to_call("","",$actionName,""); //"","","aaa_sae_report.prpt","");

		//die($response);
		/*
		echo "<hr/>". $mydocgen->default_document_dir;
		echo "<hr/>". $mydocgen->pk_service;
		echo "<hr/>". $mydocgen->ws_base_url;
		echo "<hr/>". $mydocgen->siteid;
		echo "<hr/>". $mydocgen->subjid;
		echo "<hr/>". $mydocgen->center;
		echo "<hr/>". $mydocgen->file_name;
		*/
		/*
		 if ($fileName != null){
		print_r($response);
		die("END.");
		}
		*/
		if (!$response) {
			error_page(strtoupper($in['remote_userid']), $alert_doc, array($response));
			//die("QUA?");
			$retval = false;
		}
		//die("END.");
	}
	return $retval;
}
?>
