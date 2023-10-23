<?php

include_once( dirname(__FILE__) . DIRECTORY_SEPARATOR . 'ajax_utilities.inc.php');
if (EnvironmentCheck::isAjax() === false)
	die("access not allowed");
require_once dirname(__FILE__)."/../../../db_wl.inc";

$conn = new dbconn();
$query = new query($conn);
function error_page($user, $error, $error_spec){
	global $filetxt;
	global $in;
	global $SRV;
	global $log_conn;
	global $service;
	global $remote_userid;
	global $session_number;
	#echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
	$val=debug_backtrace();
	$text="PHP Debug:".var_export($val,true)."fine PHP Debug";
	$today = date("j/m/Y, H:m:s");
	if (is_array($error_spec)) foreach ($error_spec as $key => $val) $spec.="\n $key : $val";
	mail("g.tufano@cineca.it", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n.$text");
	$body="<p align=center><font size=4><b>Si è verificato un errore</b></p><br><br>$error_spec<br>$error<hr>";
	$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
	die($filetxt);
}






$sql = "SELECT distinct codpat code from {$_POST['service']}_registrazione where nascpz is null and center = :center order by codpat";

$bind=array();
$bind['center'] = $_POST['val_master'];

$query -> exec($sql,$bind);
//A quanto pare il mondo non è pronto per gestire array di oggetti javascript scritti in json per creare selects-
//scrivo direttamente l'HTML

$res = array();

while ($query -> get_row()) {
	$res[$query->row['CODE']] = $query->row['CODE'];
}

print json_encode( $res );
die();
// $res = '<option value=""> </options>';
// while ($query->get_row()) {
// 	$res .= '<option value="'.$query->row['CODE'].'">Codpat nr. '. $query->row['CODE'].'</option>';
// }
// print $res;
