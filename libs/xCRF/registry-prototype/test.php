<?php

require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/http_lib.inc";
include_once "config.inc";

$dbh_far = "farmaci";
$ammin_file = $_SERVER ['DOCUMENT_ROOT'];
$ammin_file = preg_replace ( "/html/i", "config/" . $dbh_far . ".cfg", $ammin_file );
$handle = fopen ( $ammin_file, "r" );
$contents = fread ( $handle, filesize ( $ammin_file ) );
fclose ( $handle );
$ammin_config_line = preg_split ( "/\n/", $contents );
for($i = 0; $i < count ( $ammin_config_line ); $i ++) {
	if (preg_match ( "/OraUserid/i", $ammin_config_line [$i] ))
		$Ora_Userid = preg_replace ( "/OraUserid (.*)/i", "\\1", $ammin_config_line [$i] );
	if (preg_match ( "/OraPassword/i", $ammin_config_line [$i] ))
		$Ora_Pass = preg_replace ( "/OraPassword (.*)/i", "\\1", $ammin_config_line [$i] );
	if (preg_match ( "/OraInstance/i", $ammin_config_line [$i] ))
		$Ora_Host = preg_replace ( "/OraInstance (.*)/i", "\\1", $ammin_config_line [$i] );
}
$Ora_Userid = preg_replace ( "/\s/ ", "", $Ora_Userid );
$Ora_Pass = preg_replace ( "/\s/", "", $Ora_Pass );
$Ora_Host = preg_replace ( "/\s/", "", $Ora_Host );
$conn_far = new dbconn($Ora_Userid,$Ora_Pass,$Ora_Host);

$q_search=new query($conn_far);
$result = array();

$q_sql = "SELECT DISTINCT ATC,DATC,NOTACTS1 AS NOTACUF FROM V_FARMACI_PT ORDER BY DATC" ;
$ris = $q_search->exec($q_sql);
while ($q_search->get_row()) {
	array_push($result,$q_search->row);
}
echo json_encode($result);
?>
