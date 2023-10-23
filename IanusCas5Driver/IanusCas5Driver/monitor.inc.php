<?php
$_SERVER['REMOTE_USERID']=$_SERVER['REMOTE_USER']=strtoupper($_SERVER['HTTP_AUTHZ_UID']);
//echo "<pre>";
//var_dump($_SERVER);
ini_set("display_errors","1");
error_reporting(E_ERROR);

try{
if (file_exists($_SERVER['DOCUMENT_ROOT']."/../config/ianus-addons.inc.php")){
	include_once $_SERVER['DOCUMENT_ROOT']."/../config/ianus-addons.inc.php";
}


$_SERVER['Shib-Application-ID']=strtolower(explode(".",$_SERVER['HTTP_HOST'])[0]);
if (isset($_SERVER['HTTP_AUTHZ_UID']) && $_SERVER['HTTP_AUTHZ_UID'] ){
	$uid=strtoupper($_SERVER['HTTP_AUTHZ_UID']);
	$host=strtoupper($_SERVER['HTTP_HOST']);
	$sid = strtoupper($_SERVER['SID']);
	$uid = preg_replace("!@".$host."$!", "", $uid);
	$uid = preg_replace("!@".$sid."$!", "", $uid);
	$_SERVER['REMOTE_USERID']=$uid;
	//$_SERVER['REMOTE_USER']=$_SERVER['REMOTE_USERID'];
}



if (!$_SERVER['HTTP_REMOTE_USERID'] || stristr($_SERVER['HTTP_REMOTE_USERID'],"(null)")!==false ){
    if (isset($_SERVER['HTTP_AUTHZ_CODICEFISCALE']) && $_SERVER['HTTP_AUTHZ_CODICEFISCALE']){
		$_SERVER['REMOTE_USERID'] = $_SERVER['HTTP_AUTHZ_CODICEFISCALE'];
	}
	$_SERVER['HTTP_REMOTE_USERID'] = $_SERVER['REMOTE_USERID'];
	$_SERVER['HTTP_X_REMOTE_USER'] = $_SERVER['REMOTE_USERID'];
	$_SERVER['HTTP_AUTHZ_USERPRINCIPALNAME'] = $_SERVER['REMOTE_USERID'];
	$_SERVER['HTTP_AUTHZ_UID'] = $_SERVER['REMOTE_USERID'];
}

//echo "<pre>";
//var_dump($_SERVER);

#da non eliminare la seguente riga di codice se non si sa cosa si sta facendo. Giorgio Delsignore 25/03/2013
error_reporting(E_ERROR|E_PARSE);
ini_set("display_errors",1);
global $newFarm;
$newFarm=true;
if ($_SERVER['REQUEST_URI']=='/DriverIanus/monitor.inc.php'){
	header("location: /");
	die();
}
if ($_SERVER['REQUEST_URI']=='/header'){
        echo "<pre>";
	var_dump($_SERVER);
        die();
}

//echo "<pre>";
//var_dump($_SERVER);
//echo "</pre>";


if ($_SERVER['REDIRECT_URL']=="/authzssl/httpError.php"){
/*echo "<pre>";
print_r($_SERVER);
echo "</pre>";*/
	$httpCode=$_GET['code'];
	header("HTTP/1.0 $httpCode Not Found");
	$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
	if ($language=='') $language='it';
	$language=strtoupper($language);
	if (file_exists("/http/lib/IanusCas5Driver/template/httpError_{$httpCode}_{$language}.html")) $errorPage=file_get_contents("/http/lib/IanusCas5Driver/template/httpError_{$httpCode}_{$language}.html");
	else $errorPage=file_get_contents("/http/lib/IanusCas5Driver/template/httpError_{$httpCode}_IT.html");
	die($errorPage);
}

//include_once("/http/lib/php_utils/nosuch_web.php");
//per far funzionare FirePHP nel debug (chiedere a Giorgio, Edoardo)
//die("QUA2");
ob_start();

putenv("NLS_LANG=AMERICAN_AMERICA.AL32UTF8");
if(!defined('DEFAULT_LIBS')) define('DEFAULT_LIBS',"/http/lib/php_utils/");
clearstatcache();
if (file_exists(DEFAULT_LIBS."debug/FirePHPCore/fb.php")) {
//echo(DEFAULT_LIBS."debug/FirePHPCore/fb.php");
    include_once(DEFAULT_LIBS."debug/FirePHPCore/fb.php");
//die("includi fine");
}
if (file_exists(DEFAULT_LIBS."config/Configurable.php")){
	include_once(DEFAULT_LIBS."config/Configurable.php");
}
if (file_exists(DEFAULT_LIBS."config/DefaultConfig.php")) include_once (DEFAULT_LIBS."config/DefaultConfig.php");
set_error_handler("myErrorHandler", E_NOTICE);
function myErrorHandler($errno, $errstr, $errfile, $errline)
{
	
	$string_log="[".date("d/m/Y H:i:s")."] ";
	if (isset($_SERVER['REMOTE_USER'])) $string_log.="[{$_SERVER['REMOTE_USER']}] ";
    switch ($errno) {
    case E_ERROR:
    	$file_log.=preg_replace("!html$!", "PHP_ERROR.log",$_SERVER['DOCUMENT_ROOT']);
    	$string_log.="ERROR LOG [$errno] $errstr - $errfile($errline)\n";
    	break;

    case E_WARNING:
    	$file_log=preg_replace("!html$!", "PHP_WARNING.log",$_SERVER['DOCUMENT_ROOT']);
        $string_log.="WARNING [$errno] $errstr - $errfile($errline)\n";
        break;

    case E_NOTICE:
    	$file_log=preg_replace("!html$!", "PHP_NOTICE.log",$_SERVER['DOCUMENT_ROOT']);
    	$string_log.="NOTICE [$errno] $errstr - $errfile($errline)\n";
        break;

    default:
    	$file_log=preg_replace("!html$!", "PHP_UNKNOWN.log",$_SERVER['DOCUMENT_ROOT']);
    	$string_log.="UNKNOWN [$errno] $errstr - $errfile($errline)\n";
        break;
    }
	echo "<hr/>"."ERRORE: [$errno] $errstr - $errfile($errline)\n"."<hr/>";
	return true;
}

$config_service='';
//die("KKK");
include_once 'libs.inc';

//die("QUA");

if ($_SERVER ['REQUEST_URI'] == "/NagiosProbe") {
	try{
		$conn=new DriverIanusDBConnection();
	} catch ( Exception $e ) {
		die("ERROR 1");
	}
}
if ($_SERVER ['REQUEST_URI'] == "/SSLNagiosProbe") {
	try{
		$conn=new DriverIanusDBConnection();
	} catch ( Exception $e ) {
		die("ERROR 2");
	}
	die($_SERVER['REMOTE_USER']);
}

if ($_SERVER ['REQUEST_URI'] == "/SSLProbe") {
	try{
		$conn=new DriverIanusDBConnection();
	} catch ( Exception $e ) {
		die("ERROR 3");
	}
	die("OK");
}

$DriverIanusConnection = new DriverIanusDBConnection ( );
if (preg_match ( "!inactivityCron!", $_SERVER ['REQUEST_URI'] )){
	inactivityCron($DriverIanusConnection);
	die();
}


//Gestione cookieConsent
if ($_SERVER ['REQUEST_URI'] == "/authzssl/cookieConsentCss") {
	$content=file_get_contents( "/http/lib/IanusCas5Driver/cookieConsent/cookieConsent.css" );
	header("Content-type: text/css");
	die($content);
}

if ($_SERVER ['REQUEST_URI'] == "/authzssl/cookieConsentJs") {
	readfile ( "/http/lib/IanusCas5Driver/cookieConsent/cookieconsent.js" );
	die();
}

if ($_SERVER ['REQUEST_URI'] == "/authzssl/cookieInform") {
	$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
	if (strtoupper($language) == strtoupper("it")){$language_show='IT';}else {$language_show='EN';}
	readfile( "/http/lib/IanusCas5Driver/cookieConsent/cookieInform_{$language}.htm" );
	die();
}

if (preg_match("!^/authzssl/pentaho-public/!",$_SERVER ['REQUEST_URI'])){
	include_once 'pentaho-proxy.inc.php';
	die();
}

if (preg_match("!/reps/!", $_SERVER ['REQUEST_URI'])) {
	$reportFile=preg_replace("!/reps/!", "", $_SERVER ['REQUEST_URI']);
	require_once "reps/index.php";
	die();
}


/*
 * GESTIONE DELLE PAGINE DI CORTESIA PER BLOCCHI
 *
 */
if (!isset($_GET ['URI'])) {
	
	$sql_query="select * from CAS5_SERVICES where upper(trim(URL))='".strtoupper($_SERVER['HTTP_HOST'])."'";
$sql=new DriverIanusSql($DriverIanusConnection);



$sql->getRow($sql_query);
$sid=$sql->row['SID'];
$remote_users_spec=explode("|", $_SERVER['HTTP_AUTHZ_SERVICEUSERIDS']);
foreach ($remote_users_spec as $key=>$val){
	$tmpExplode=explode(":", $val);
	$remote_users[$tmpExplode[0]]=$tmpExplode[1];
}
$thisRemoteUser=$remote_users[$sid];
if ($sql->row['ENABLED']!='1'){
	$lang = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
	$lang=strtoupper($lang);
	$force_open=false;
	if ($_GET['FORCEOPEN']!='') {
		setcookie("FORCEOPEN","ok");
		$force_open=true;
	}
	if ($_COOKIE['FORCEOPEN']=='ok') $force_open=true;
	if (!$force_open){
		if(file_exists($_SERVER['DOCUMENT_ROOT']."/stop_service.php")){
			include_once($_SERVER['DOCUMENT_ROOT']."/stop_service.php");
			die($html_stop_page);
		}
        else if ( preg_match("/agenziafarmaco/", strtolower($_SERVER['HTTP_HOST']))){
            $html=file_get_contents("/http/servizi/AIFA_WF/idp-aifa/html/cortesia.html");
            die($html);
        }
		else{
			if (file_exists("/http/lib/DriverIanus/template/fermo_{$lang}.html"))
				$html=file_get_contents("/http/lib/DriverIanus/template/fermo_{$lang}.html");
			else
				$html=file_get_contents("/http/lib/DriverIanus/template/fermo_IT.html");
			die($html);
		}
	}
}
$authzsslEnabled[$_SERVER['HTTP_HOST']]=true;
}





/*
if (preg_match ( "!login.php$!", $_SERVER ['REQUEST_URI'] ) && !preg_match("/ticket\/osticket/",$_SERVER ['REQUEST_URI']) ) {
	if (($authzsslEnabled[$_SERVER['HTTP_HOST']]) && $_SERVER['SERVER_PORT']!='443'){
		$_SERVER['REQUEST_URI']=str_replace('/authzssl','',$_SERVER['REQUEST_URI']);	
		header("location: https://{$_SERVER['HTTP_HOST']}/authzssl".$_SERVER['REQUEST_URI']);
		die();
	}
	LoginGest($DriverIanusConnection);
}
*/
if (preg_match ( "!forget_password!", $_SERVER ['REQUEST_URI'] )) {
	if (($authzsslEnabled[$_SERVER['HTTP_HOST']]) && $_SERVER['SERVER_PORT']!='443'){
	    $_SERVER['REQUEST_URI']=str_replace('/authzssl','',$_SERVER['REQUEST_URI']);
		header("location: https://{$_SERVER['HTTP_HOST']}/authzssl".$_SERVER['REQUEST_URI']);
		die();
	}
	ForgetPassword($DriverIanusConnection);
}

if (preg_match ( "!forget_userid!", $_SERVER ['REQUEST_URI'] )) {
	if (($authzsslEnabled[$_SERVER['HTTP_HOST']]) && $_SERVER['SERVER_PORT']!='443'){
		$_SERVER['REQUEST_URI']=str_replace('/authzssl','',$_SERVER['REQUEST_URI']);
		header("location: https://{$_SERVER['HTTP_HOST']}/authzssl".$_SERVER['REQUEST_URI']);
		die();
	}
	ForgetUserid($DriverIanusConnection);
}

if ($_SERVER ['REQUEST_URI'] == "/accessError.html") AccessError();
if ($_SERVER ['REQUEST_URI'] == "/ShibLogOut" || $_SERVER ['REQUEST_URI'] == "/ShibLogOut\?\&" || preg_match ( "!ShibLogOut!", $_SERVER ['REQUEST_URI'] )) GlobalLogout($DriverIanusConnection);


foreach ( $_SERVER as $key => $val ) {
	$new_key = preg_replace ( "!^REDIRECT_!", "", $key );
	$_SERVER [$new_key] = $val;
}

/* Compatibilità con php4*/
foreach ( $_GET as $key => $val ) {
	$HTTP_GET_VARS [$key] = $val;
}
foreach ( $_POST as $key => $val ) {
	$HTTP_POST_VARS [$key] = $val;
}
/* Fine Compatibilità con php4*/

$link_to = $_SERVER ['REQUEST_URI'];
$script = explode ( "?", $link_to );
$script = $script [0];
//echo "<hr/>$link_to###$script<hr/>";



if ($script=='/sessionNameJs'){
	echo "var SESSION_NAME = '{$_SERVER['HTTP_AUTHZ_UID']}';\n";
	echo "var HOME_FOLDER = '/home/{$_SERVER['HTTP_AUTHZ_UID']}';\n";
	echo "var FULL_QUALIFIED_URL='https://{$_SERVER['HTTP_HOST']}/pentaho/';\n";
	die();
}


if (preg_match("!^\/global-overrides\/!", $_SERVER['REDIRECT_URL'])){
	$finfo = finfo_open(FILEINFO_MIME_TYPE);
	$filePath=$_SERVER['DOCUMENT_ROOT']."/global-overrides".$_SERVER['REDIRECT_SCRIPT_URL'];
	$script=$_SERVER['REDIRECT_SCRIPT_URL'];
	if (preg_match("/\.css$/",$script)) {
		header ( "Content-type:text/css" );
	} elseif (preg_match("/\.xls$/",$script)) {
		header('Content-Disposition: attachment;');
	} elseif (preg_match("/\.pdf$/",$script)) {
		header('Content-type: application/pdf; Content-Disposition: attachment;');
	} elseif (preg_match("/\.avi1$/",$script)) {
		header("Content-Transfer-Encoding: binary\n;".'Content-type: video/x-msvideo; Content-Disposition: inline; Cache-Control: no-cache, must-revalidate; ');
	} elseif (preg_match("/\.mov1$/",$script)) {
		header('Content-type: video/quicktime; Content-Disposition: inline; Cache-Control: no-cache, must-revalidate; ');
	} elseif (preg_match("/\.svg$/",$script)) {
		header('Content-type: image/svg+xml; Content-Disposition: inline; Cache-Control: no-cache, must-revalidate; ');
	}
	readfile($filePath);
	die();
}


$is_cgi = false;
$found = false;
$service_script_dir = $_SERVER ['DOCUMENT_ROOT'];
if (is_dir ( "{$service_script_dir}{$script}" )) {
	if (file_exists ( "{$service_script_dir}{$script}/index.html" ) && ! $found) {
		$found = true;
		$script .= "index.html";
	}
	if (file_exists ( "{$service_script_dir}{$script}/index.htm" ) && ! $found) {
		$found = true;
		$script .= "index.htm";
	}
	if (file_exists ( "{$service_script_dir}{$script}/index.php" ) && ! $found) {
		$found = true;
		$script .= "index.php";
	}
}

$_SERVER ['SCRIPT_NAME'] = $script;
$_SERVER ['SCRIPT_FILENAME'] = $script;
$_SERVER ['PHP_SELF'] = $script;



if (is_dir(getDir ( "{$service_script_dir}{$script}" )))
chdir ( getDir ( "{$service_script_dir}{$script}" ) );

$ret = isPublic ( $script, $DriverIanusConnection );

if ($ret ['passwd_flag'] == '1')
	$public = false;
else
	$public = true;
/* Mi svuota l'utente
if (isset ( $_SERVER ['REMOTE_USERID'] )) {
	
	$sql=new DriverIanusSql($DriverIanusConnection);
	$sql_sso="select userid from IDP_SSO_USERS where upper(userid)=:remote_userid";
    unset($bind);
    $bind['REMOTE_USERID']=$_SERVER ['REMOTE_USERID'];
    if(!preg_match("/@/",$_SERVER['HTTP_AUTHZ_UID'])){
    	$_SERVER ['SSO_USERID']=$_SERVER['HTTP_AUTHZ_UID'];
    	$sso_user=true;
    }
    $_SERVER['REMOTE_USER']=$thisRemoteUser;
	$_SERVER['REMOTE_USERID']=$thisRemoteUser;
	$remote_user=$thisRemoteUser;
	$remote_userid=$thisRemoteUser;
	$_SERVER['PHP_AUTH_USER']=$thisRemoteUser;
	$sidSplit=explode(".", $sid);
	$auths[0]=$thisRemoteUser;
	$auths[1]=$sidSplit[0];
	$_SERVER ['ID_PRINC_SERV'] = $auths [1];
	ForceChangeUserGest($DriverIanusConnection, $auths);
	
}
*/


/*Blcocco controllo abilitazione */
if ($_SERVER['REMOTE_USER']!=''){
	//echo "<hr/>{$_SERVER['REMOTE_USER']}<hr/>";
	$sql=new DriverIanusSql($DriverIanusConnection);
	$sqlCheckAbilitazione="select abilitato from utenti where userid=:remote_userid";
	unset($bind);
	//var_dump($sqlCheckAbilitazione);
	$_SERVER['REMOTE_USERID']=strtoupper($_SERVER['REMOTE_USERID']);
	$bind['REMOTE_USERID']=$_SERVER['REMOTE_USERID'];
	//var_dump($bind);
	$sql->setSql($sqlCheckAbilitazione);
	$row=$sql->getRow($sqlCheckAbilitazione, $bind);
        if (!$row && stristr($_SERVER['SCRIPT_FILENAME'],"casAuthn")===false && stristr($_SERVER['SCRIPT_FILENAME'],"cas5Authn")===false && stristr($_SERVER['SCRIPT_FILENAME'],"authzssl")===false ){
		//echo "<pre>";
		//var_dump($_SERVER);
		die("Utente non abilitato al sistema: {$_SERVER['REMOTE_USERID']}");
	}
	//var_dump($sql->row);
        if ($sql->row['ABILITATO']==0 && stristr($_SERVER['SCRIPT_FILENAME'],"change_password")===false && stristr($_SERVER['SCRIPT_FILENAME'],"casAuthn")===false && stristr($_SERVER['SCRIPT_FILENAME'],"cas5Authn")===false && stristr($_SERVER['SCRIPT_FILENAME'],"authzssl")===false ) {
		//die("FORBIDDEN");
		echo ("FORBIDDEN");
		forbidden("...", "it");
		die();
	}
}
if ($_SERVER['REQUEST_URI']=='/change_password'){
	ChangePassword($DriverIanusConnection);
	die();
}

if (preg_match("!^/ConfirmaGestSuccess!",$_SERVER['REQUEST_URI'])){
	include_once '/http/lib/DriverIanus/ConfirmaGest.inc.php';
	$ist=new ConfirmaGest();
	$ist->gestSuccess();
	die();
}

#LUIGI: ConfirmaDownload, chiamata di passaggio tra metodi get_links e get_signed per firma digitale
if (preg_match("!^/ConfirmaDownload!",$_SERVER['REQUEST_URI'])){
	include_once '/http/lib/DriverIanus/ConfirmaGest.inc.php';
	$ist=new ConfirmaGest();
	$ist->get_signed($_GET['TID'],$_GET['DOCID']);
	die();
}

if (preg_match("!html2ps.php!",$_SERVER['REQUEST_URI'])){
	$_GET['URL']=str_replace("https", "http", $_GET['URL']);
	$_REQUEST['URL']=str_replace("https", "http", $_REQUEST['URL']);
	$url=str_replace("https", "http", $_GET['URL']);
	if (preg_match("!\?!", $url)){
		$url.="&MON_USERID={$_SERVER['REMOTE_USER']}&MON_CALLER={$_SERVER['PHP_SELF']}";
	}
	else $url.="?MON_USERID={$_SERVER['REMOTE_USER']}&MON_CALLER={$_SERVER['PHP_SELF']}";
	if (!preg_match("!html2ps\.php!",$_SERVER['PHP_SELF'])){
		$lock_file=$_SERVER['DOCUMENT_ROOT'];
		$lock_file=rtrim($lock_file,"/");
		$lock_file.=$_GET['MON_CALLER'];
		$lock_file=str_replace("demo/html2ps.php", "monitor_control/".$_SERVER['HTTP_HOST']."-".$_GET['MON_USERID'].".lock", $lock_file);
		$lock_content=file_get_contents($lock_file);
		$splits=explode("\n",$lock_content);
		$_SERVER['REMOTE_USERID']=$splits[0];
		$_SERVER['GRUPPI']=$splits[1];
		
		if (isset ( $_SERVER ['HTTP_AUTHZ_UID'] )) {
			$auths = explode ( "@", $_SERVER ['HTTP_AUTHZ_UID'] );
			
			$_SERVER ['REMOTE_USER'] = $auths [0];
			$_SERVER ['PHP_AUTH_USER'] = $auths [0];
			$_SERVER ['ID_PRINC_SERV'] = $auths [1];
			ForceChangeUserGest($DriverIanusConnection, $auths);
		}
		$public=true;
	}
	$_GET['URL']=$url;
	$_REQUEST['URL']=$url;
	$_SERVER['QUERY_STRING']=str_replace("URL=https", "URL=http", $_SERVER['QUERY_STRING']);
	$_SERVER['REDIRECT_QUERY_STRING']=str_replace("URL=https", "URL=http", $_SERVER['REDIRECT_QUERY_STRING']);
}

include_once("functionpoint.php");
if(false && $_SERVER['SERVER_NAME']=='antineoplastici.agenziafarmaco.it'){
	$FPConnection=new DriverIanusDBConnection();
	$FPTracker=FPTracker::newFPTracker($FPConnection);
}



//$service_script_dir=getcwd();
$_SERVER ['PATH_TRANSLATED'] = "{$service_script_dir}{$script}";
$_SERVER ['SCRIPT_FILENAME'] = "{$service_script_dir}{$script}";
$_SERVER ['SCRIPT_NAME'] = "{$script}";
if (! isset ( $_SERVER ['PATH_TRANSLATED'] ))
	$_SERVER ['PATH_TRANSLATED'] = $_SERVER ['SCRIPT_FILENAME'];
if ($_SERVER['SERVER_PORT']=='443') $_SERVER['HTTPS']=1;
if ($_SERVER['SERVER_PORT']=='8443') $_SERVER['HTTPS']=1;



if (! $public && ! isset ( $_SERVER ['HTTPS'] )) {
	header ( "Location: https://{$_SERVER['SERVER_NAME']}{$_SERVER['REQUEST_URI']}" );
	die();
}


$_SERVER['REMOTE_USER'] = $_SERVER['REMOTE_USERID']; //ATTENZIONE: TOLGO IL @IDSERVIZIO da REMOTE_USER (da qui in poi...)

if (! $public) {
    //echo "<hr/>SECURED AREA<hr/>";
//Update della data di ultimo accesso
    $sql=new DriverIanusSql($DriverIanusConnection);
    $updateUltimoAccesso="update utenti set dttm_ultimoaccesso=sysdate where userid = :remote_userid";
    unset($bind);
    $bind['REMOTE_USERID']=$_SERVER['REMOTE_USER'];
    $sql->doCommand($updateUltimoAccesso,$bind);
    $DriverIanusConnection->commit ();
//Fine update data di ultimo accesso
    
if(userDisabledForInactivity($_SERVER ['REMOTE_USER'],$DriverIanusConnection)){

	
	if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc")){

		/* File personalizzato per il singolo servizio
		* SETTARE LA VARIABILE $language al suo interno e i corrispondenti valori nella lingua scelta!!!
		*/
		include_once("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc");
	}else{

		/* Carico la configurazione standard */
		include_once("/http/lib/DriverIanus/LOGIN/login.conf.inc");
		//$login_template = file_get_contents("/http/lib/DriverIanus/LOGIN/template/login.html");
		//$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
	}
	$lang=strtoupper($language);
	forbidden($script, $lang,'AMR01 - User disabled for inactivity');
}
//$_SERVER['REMOTE_USERID']=$_SERVER['REMOTE_USER'];
$_SERVER['REMOTE_USER'] = $_SERVER['REMOTE_USERID']; //ATTENZIONE: TOLGO IL @IDSERVIZIO da REMOTE_USER (da qui in poi...)

	$_SERVER ['GRUPPI']=$_SERVER ['HTTP_AUTHZ_GRUPPI'];
	//var_dump($_SERVER['GRUPPI']);
	if (! UserAuthorized ( $_SERVER ['REMOTE_USERID'], $_SERVER ['GRUPPI'], $ret ['script_ammin'], $DriverIanusConnection )) {
		$values_log[]=$_SERVER ['REMOTE_USER'];
		$values_log[]= $_SERVER ['GRUPPI'];
		$values_log[]= $ret ['script_ammin'];
		$values_log[]= $DriverIanusConnection ;
		$lang = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
		
		/* Carico la configurazione */
		if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc")){

			/* File personalizzato per il singolo servizio
			 * SETTARE LA VARIABILE $language al suo interno e i corrispondenti valori nella lingua scelta!!!
			 */
			include_once("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc");
		}else{

			/* Carico la configurazione standard */
			include_once("/http/lib/DriverIanus/LOGIN/login.conf.inc");
			//$login_template = file_get_contents("/http/lib/DriverIanus/LOGIN/template/login.html");
			//$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
		}
		$lang=strtoupper($language);
		forbidden($script, $lang, 'AMR02 - User not authorized');
	}
}

/*
if($_SERVER['HTTP_AUTHZ_AUTHENTICATIONMETHOD']=='QueryDatabaseAuthenticationHandler'){
    // Gestione della scadenza password, assegnare l'utente al gruppo di funzioni base-profile e mettare la password scaduta per farla cambiare al primo accesso
    //if(!isset($sso_user) || !$sso_user){
        $SQL_SCADENZA_PWD="select case when nvl(dttm_scadenzapwd,sysdate) < sysdate then 1 else 0 end as REDIRECT from utenti
    where userid=:remote_userid
    ";
        unset($bind);
        $bind['REMOTE_USERID']=$_SERVER['REMOTE_USERID'];
    //}
    //else{
    //	$SQL_SCADENZA_PWD="select case when nvl(sso.dttm_scadenzapwd,sysdate) < sysdate then 1 else 0 end as REDIRECT from CAS_USERS sso where sso.userid=:sso_userid";
    //    unset($bind);
    //    $bind['SSO_USERID']=$_SERVER ['SSO_USERID'];
    //}
    $sql = new DriverIanusSql ( $DriverIanusConnection );
    $sql->getRow ( $SQL_SCADENZA_PWD ,$bind);



    if ($sql->row['REDIRECT']==1){
        if (
        $script!='/change_password'
        && stristr($script,"ShibLogOut")===false
        && !preg_match("!\.css$!", $script)
        && !preg_match("!\.jpg$!", $script)
        && !preg_match("!\.gif$!", $script)
        && !preg_match("!\.png$!", $script)
        ) {
            //die($script);
            header ("Location: /change_password");
            die();
        }
    }
    //Fine gestione scadenza passwd
}
*/

if ($script=="/cas5Authn/login.php"){
	
	include "LOGIN/login.cas.php";
}

$DriverIanusConnection->__destruct ();

//echo "<hr/>$script<hr/>";
if (preg_match ( "!.php$!", $script )) {
    
    
	//die("QUA");
    if(!$public && Configurable::queryConfiguration("Shibboleth","PassiveLogout")=='on'){
        PassiveLogoutCheck($DriverIanusConnection,Configurable::queryConfiguration("Shibboleth","PassiveLogoutSeconds"));
        
    }
	if (file_exists ( "{$service_script_dir}{$script}" )) {
	    $DriverIanusScript = "{$service_script_dir}{$script}";
		$script = '';
		
		include_once ($DriverIanusScript);
		
	} else {
		$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
		if ($language=='') $language='it';
		$language=strtoupper($language);
		$page_not_found_content=file_get_contents("/http/lib/IanusCas5Driver/template/pageNotFound_{$language}.html");
		die($page_not_found_content);
	}
} else {
    
	//die("NONPHP QUA");
	$script=urldecode($script);
	
	if (file_exists ( "{$service_script_dir}{$script}" )) {
		if (preg_match ( "/\.htm/", $script ) || preg_match ( "/\.html/", $script )) {

			//system("rm -f ".xdebug_get_profiler_filename());
			//header ( "Content-type:text/html" );
			//readfile ( "{$service_script_dir}{$script}" );
			$filename=explode("/", $script);
			$filename=$filename[count($filename)-1];
			if (preg_match("!HASHCONTROLLED!", $script)){
				$hash=MonMD5AdminMd5Crypt($filename, $_GET['sed']);
				if ($hash!=$_GET['hash']){
					die("errore di accesso alla pagina");
				}
			}
			$html=file_get_contents("{$service_script_dir}{$script}");
			foreach ($url_prod as $key => $val){
				if ($_SERVER['SERVER_ADDR']=='10.253.4.23' || $_SERVER['SERVER_ADDR']=='10.253.4.24'){
					$html=str_replace("http://$val", "http://{$key}.sissdev.cineca.it", $html);
					$html=str_replace("https://$val", "http://{$key}.sissdev.cineca.it", $html);
				}
			}
			die ($html);
		} else	{
			if (preg_match("/\.css$/",$script)) {
				header ( "Content-type:text/css" );
			} elseif (preg_match("/\.xls$/",$script)) {
				header('Content-Disposition: attachment;');
			} elseif (preg_match("/\.pdf$/",$script)) {
				header('Content-type: application/pdf; Content-Disposition: attachment;');
			} elseif (preg_match("/\.avi1$/",$script)) {
				header("Content-Transfer-Encoding: binary\n;".'Content-type: video/x-msvideo; Content-Disposition: inline; Cache-Control: no-cache, must-revalidate; ');
			} elseif (preg_match("/\.mov1$/",$script)) {
				header('Content-type: video/quicktime; Content-Disposition: inline; Cache-Control: no-cache, must-revalidate; ');
			} elseif (preg_match("/\.m4v1$/",$script) || preg_match("/\.mov1$/",$script) || preg_match("/\.mp4$/",$script) || preg_match("/\.avi$/",$script) ) {
				ob_clean();
				$file = $service_script_dir.$script;
				//$fp = @fopen($file, 'rb');
				//$size   = filesize($file); // File size
				if (file_exists($file)){
				$size = intval(sprintf("%u", filesize($file)));
				$length = $size;           // Content length
				$start  = 0;               // Start byte
				$end    = $size - 1;       // End byte
				$chunksize = 5*(1024*1024); //5MB
				set_time_limit(0); //Infinito
				header('Content-type: application/octet-stream');
				header('Content-Disposition: attachment; filename='.basename($file));
				//header("Accept-Ranges: 0-$length");
				//header("Content-Range: bytes $start-$end/$size");
				header("Content-Transfer-Encoding: binary");
				header("Content-Length: ".$length);
				/*
    $filesize = filesize($file);

    $chunksize = 4096;
    if($filesize > $chunksize)
    {
        $srcStream = fopen($filename, 'rb');
        $dstStream = fopen('php://output', 'wb');

        $offset = 0;
        while(!feof($srcStream)) {
            $offset += stream_copy_to_stream($srcStream, $dstStream, $chunksize, $offset);
        }

        fclose($dstStream);
        fclose($srcStream);   
    }
    else 
    {
        // stream_copy_to_stream behaves() strange when filesize > chunksize.
        // Seems to never hit the EOF.
        // On the other handside file_get_contents() is not scalable. 
        // Therefore we only use file_get_contents() on small files.
        echo file_get_contents($filename);
    }
*/
				
				if($size > $chunksize){
					$handle = fopen($file, 'rb'); 
					while (!feof($handle)){
						print(@fread($handle, $chunksize));
						ob_flush();
						flush();
					}
					fclose($handle); 
				} else readfile($file);
				}else{
					die("File {$file} not found");
				}
				/*
				$buffer = 10240 * 8;
				while(!feof($fp) && ($p = ftell($fp)) <= $end) {
				    if ($p + $buffer > $end) {
				        $buffer = $end - $p + 1;
				    }
				    set_time_limit(0);
				    echo fread($fp, $buffer);
				    flush();
				}
				fclose($fp);
				*/
			} elseif (preg_match("/\.m4v2$/",$script)){
				header("Content-Transfer-Encoding: binary\n");
				header("Content-type: video/x-m4v; Content-Disposition: inline; filename=\"".$service_script_dir.$script."\"; Content-Length: ".filesize($service_script_dir.$script).";");
			} elseif (preg_match("/\.svg$/",$script)) {
				header('Content-type: image/svg+xml; Content-Disposition: inline; Cache-Control: no-cache, must-revalidate; ');
			} elseif (preg_match("!/SHIB_DOWNLOAD/!", $script)) {
				header('Content-Disposition: attachment;');
			} else {
				header ( "Content-type:*" );
			}
		}
		ob_clean();
		if (!preg_match("/\.m4v$/",$script) && !preg_match("/\.mov$/",$script) && !preg_match("/\.mp4$/",$script) && !preg_match("/\.avi$/",$script) ) {
			$file = $service_script_dir.$script;
			if(pathinfo($file, PATHINFO_EXTENSION) != 'pdf'){
	   			header("Content-Disposition: attachment; filename=" . basename($script) );   
				header("Content-Length: " . filesize($file));
				$handle = @fopen($file, "rb");
				if ($handle) {
					while (!feof($handle)) {
	    				echo fread($handle, 1024);
						ob_flush();
					}
					fclose($handle);
				}
				exit;				
			} else {
				readfile ( "{$service_script_dir}{$script}" );
			}
		}
		//ob_end_flush();
		//die();
	} else {
		header("HTTP/1.0 404 Not Found");
		$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
		if ($language=='') $language='it';
		$language=strtoupper($language);
		$page_not_found_content=file_get_contents("/http/lib/IanusCas5Driver/template/pageNotFound_{$language}.html");
		die($page_not_found_content);
	}
}
}catch( Exception $e ) {
    echo "<pre>";
    print_r($e);
    echo "\n";
    die("ERROR 4");
}
