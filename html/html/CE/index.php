<?php 
$sname = $_SERVER['SERVER_NAME'];

if ($_SERVER['REMOTE_USER']){
	$userid = $_SERVER['REMOTE_USER'];
	
	//Connessione al DB
	$ammin_file=$_SERVER['DOCUMENT_ROOT'];
	$ammin_file=preg_replace("/html/i", "config/amministrazione.cfg", $ammin_file);
	$handle = fopen($ammin_file, "r");
	$contents = fread($handle, filesize($ammin_file));
	fclose($handle);
	$ammin_config_line=preg_split("/\n/", $contents);
	for ($i=0;$i<count($ammin_config_line);$i++) {
		if (preg_match("/OraUserid/i",$ammin_config_line[$i])) $Ora_Userid=preg_replace("/OraUserid (.*)/i", "\\1" , $ammin_config_line[$i]);
		if (preg_match("/OraPassword/i",$ammin_config_line[$i])) $Ora_Pass=preg_replace("/OraPassword (.*)/i", "\\1" , $ammin_config_line[$i]);
		if (preg_match("/OraInstance/i",$ammin_config_line[$i])) $Ora_Host=preg_replace("/OraInstance (.*)/i", "\\1" , $ammin_config_line[$i]);
	}
	$Ora_Userid=preg_replace("/\s/ ", "",$Ora_Userid);
	$Ora_Pass=preg_replace("/\s/", "",$Ora_Pass);
	$Ora_Host=preg_replace("/\s/", "",$Ora_Host);
	$username=$Ora_Userid;
	$pass=$Ora_Pass;
	$host=$Ora_Host;

	$redirect = "https://$sname/uxmr/";
	
	$conn=ocilogon($username,$pass,$host) or die ("<hr>Errore connessione al DB $username<hr>");
	$SQL = "SELECT PROFILO FROM ANA_UTENTI_2 WHERE USERID = '$userid'";
	$stmt=ociparse($conn, $SQL);
	if (ociexecute($stmt, OCI_DEFAULT)) {
		$row = oci_fetch_assoc($stmt);
		if ($row['PROFILO'] == "CMP"){
			$redirect = "https://$sname/sedute/";
		}
	}
	//echo($userid);
	//die($redirect);
	header("Location: $redirect");
	die();
}


header("Location: https://$sname/");

?>