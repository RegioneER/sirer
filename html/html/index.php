<?php

if ($_GET['DEBUG_AUTH']!=''){
	echo "<pre>";
	var_dump($_SERVER);
	die();
}

header("Location: https://{$_SERVER['SERVER_NAME']}/entryPoint.php");
die();

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
		    //die("Utente {$_SERVER['REMOTE_USER']}  autenticato non abilitato ai servizi");
		    header("Location: https://{$sname}/sirer/");
			die();
		}
	}
	else{
	    header("Location: https://{$sname}/");
		die();
	}
	
?>
