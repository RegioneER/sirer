<?php


ini_set('display_errors','1');
error_reporting(E_ERROR);
/* vmazzeo 06.02.2017
 * TOSCANA-118
 */
include_once "../libs/xCRF/db.inc";
$conn = new dbconn();
$query = new query($conn);

$location='location:https://'.$_SERVER['SERVER_NAME'].'/';
$sname=$_SERVER['SERVER_NAME'];

//header("Location: https://{$sname}/sirer/");
//die();

$bind=array();

if(isset($_SERVER['REMOTE_USER']) && $_SERVER['REMOTE_USER']!=''){

	$bind['USERID'] = $_SERVER['REMOTE_USER'];
	$bind['STUDY_PREFIX'] = 'CE';
	$query -> exec("select profilo from ana_utenti_2 where userid =:USERID", $bind);
	if ($query -> get_row() && $query -> row['PROFILO'] =='CMP') {
		header("Location: https://{$sname}/sedute/");
		die();
	}
	else{
		/*STSANVIL-1261*/
		$bind=array();
		$bind['USERID'] = $_SERVER['REMOTE_USER'];
		$sql="select COUNT(ACM_USERS_ASSOC.USERID) AS CONTO from ACM_USERS_ASSOC where STUDY_PREFIX='CRMS' AND PROFILE_CODE NOT IN ('DATAMANAGER','tech-admin') AND  userid=:USERID";
		$query2 = new query($conn);
		$query2 -> exec($sql, $bind);
		if ($query2 -> get_row() && $query2 -> row['CONTO'] !="0" && $query2 -> row['CONTO'] !="1") {
			header("Location: https://{$sname}/switchProfile/?/user/view/".$_SERVER['REMOTE_USER']);
			die();
		}
		else{
			//die("Utente {$_SERVER['REMOTE_USER']}  autenticato non abilitato ai servizi");
			header("Location: https://{$sname}/sirer/");
			die();
		}
	}
}
else{
	//header("Location: https://{$sname}/");
	echo "Richiesta autenticazione";
	die();
}

?>
