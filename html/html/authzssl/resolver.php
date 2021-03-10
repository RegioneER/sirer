<?php
//ini_set("display_errors", "1");
//error_reporting(E_ALL);

include_once '/http/lib/IanusCas5Driver/libs/db_wl.inc';
global $casVersion;
$casVersion="5.2 - build(2)";
$data = [];

//mail("d.mengoli@cineca.it","RESOLVER SIRER CALL","Chiamata OK!");

//if (!isset($_SERVER['PHP_AUTH_USER']) || ($_SERVER['PHP_AUTH_USER'] != "resolver" && $_SERVER['PHP_AUTH_PW'] != "resolvpwd01!" ) ) {
//    header('WWW-Authenticate: Basic realm="SIRER-CAS"');
//    header('HTTP/1.0 401 Unauthorized');
//    echo 'Si sta cercando di accedere ad un area riservata.';
//    exit;
//}

// else {
//    echo "<p>Hello {$_SERVER['PHP_AUTH_USER']}.</p>";
//    echo "<p>You entered {$_SERVER['PHP_AUTH_PW']} as your password.</p>";
//}

//header('Content-Type: application/json');

//mail("d.mengoli@cineca.it","RESOLVER SIRER","Autenticazione OK!");
error_log("##########".print_r($_GET,true));
if (isset($_GET['getSamlAttributes']) && $_GET['getSamlAttributes']!=''){
	$conn=new dbconn();
	$username=null;
	
	if ($_POST['username']!='') $username=$_POST['username'];
	if ($_GET['username']!='' && !$username) $username=$_GET['username'];
	//mail("d.mengoli@cineca.it","RESOLVER SIRER RQ","[getSamlAttributes] REQUEST {$_POST['username']} \n- - ");
	//mail("d.mengoli@cineca.it","RESOLVER SIRER POST",print_r($_POST,true));
	//mail("d.mengoli@cineca.it","RESOLVER SIRER GET",print_r($_GET,true));
	$q=new query($conn);
//$inserts=array();
//$inserts[]="insert into cas5_user_repository select :username, '', 1, sysdate+100000, 0, :username, email, phone from cas5_user_repository where username=:username||'@'||:url";
//$inserts[]="insert into cas5_consent select :username, consent_flag, on_dt, SID from cas5_consent where username=:username||'@'||:url";
//$inserts[]="insert into cas5_user_service select :username, SID, ENABLED, SERVICE_USERID from cas5_user_service where username=:username||'@'||:url";
//$inserts[]="insert into cas5_user_profiles select :username, SID, PROFILE_CODE, PROFILE_NAME, UP_ENABLED, P_ENABLED from cas5_user_profiles where username=:username||'@'||:url";
    $sql="select a.codice_fiscale as CF, c.gruppi, c.servizi, c.uids serviceuserids, c.consent, c.userid, decode(c.disabled,0,1,1,0) enabled, c.expired, c.locked, c.mfa_enabled mfa, c.email, c.phone from 
cas5_users c, ana_utenti_1 a
where c.uids like '%|1.TSC:'||a.userid||'|%' and upper(username)=upper(:username)";
	$data=array();
	$bind=array();
	$bind['username']=strtoupper($username);
	//mail("d.mengoli@cineca.it","RESOLVER SIRER SQL",$sql);
	
	if ($q->get_row($sql, $bind)){
		$data=$q->row;
	}
	//var_dump($data);
	//mail("d.mengoli@cineca.it","RESOLVER SIRER DATA",print_r($data,true));
	error_log("########".print_r($data,true));
	header('Content-Type: application/json');
	echo json_encode($data);
	die();
}
?>
