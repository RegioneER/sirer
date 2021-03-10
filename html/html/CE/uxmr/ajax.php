<?php
include_once "libs/db.inc";
$service = "CE";
$conn = new dbconn();

Logger::send("ajax.php - script = ".$_GET['script']);

if ($_GET['script'] == 'ISTITUTO') {
	Logger::send('ISTITUTO');
		unset($bind);
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select DISTINCT ID_IST as code, DESCR_IST decode from {$service}_GEMELLI_TOTAL where ID_REF_STR = :val order by DESCR_IST";
	Logger::send($sql);
	$query -> exec($sql, $bind);
	
	print("<option value=''>&nbsp;</option>");
	while ($query -> get_row()) {
		print("<option value='".$query -> row['CODE']."'>".$query -> row['DECODE']."</option>");
	}
}
if ($_GET['script'] == 'DIR_ISTITUTO') {
	Logger::send('DIR_ISTITUTO');
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select DIR_IST from {$service}_GEMELLI_TOTAL where id_ist = :val";
	Logger::send($sql);
	$query -> exec($sql, $bind);
	if ($query -> get_row()) {
		Logger::send($query -> row['DIR_IST']);
		print($query -> row['DIR_IST']);
	}
}
if ($_GET['script'] == 'DIPARTIMENTO') {
	Logger::send('DIPARTIMENTO');
		unset($bind);
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select DISTINCT ID_DIP as code, DESCR_DIP decode from {$service}_VENETO_DIP where ID_REF_STR = :val order by descr_dip";
	Logger::send($sql);
	$query -> exec($sql, $bind);
	
	print("<option value=''>&nbsp;</option>");
	while ($query -> get_row()) {
		print("<option value='".$query -> row['CODE']."'>".$query -> row['DECODE']."</option>");
	}
}
if ($_GET['script'] == 'DIR_DIPARTIMENTO') {
	Logger::send('DIR_DIPARTIMENTO');
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select DIR_DIP from {$service}_VENETO_DIP where id_dip = :val";
	Logger::send($sql);
	$query -> exec($sql, $bind);
	if ($query -> get_row()) {
		Logger::send($query -> row['DIR_DIP']);
		print($query -> row['DIR_DIP']);
	}
} 
if ($_GET['script'] == 'UNITA_OP') {
	Logger::send('UNITA_OP');
		unset($bind);
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select DISTINCT ID_UO as code, DESCR_UO decode from {$service}_VENETO_DIP where ID_DIP = :val order by descr_uo";
	Logger::send($sql);
	$query -> exec($sql, $bind);
	
	print("<option value=''>&nbsp;</option>");
	while ($query -> get_row()) {
		Logger::send($query -> row['CODE']);
		print("<option value='".$query -> row['CODE']."'>".$query -> row['DECODE']."</option>");
	}
}
if ($_GET['script'] == 'DIR_UO') {
	Logger::send('DIR_UO');
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select DIR_UO from {$service}_VENETO_DIP where id_uo = :val";
	Logger::send($sql);
	$query -> exec($sql, $bind);
	if ($query -> get_row()) {
		Logger::send($query -> row['DIR_UO']);
		print($query -> row['DIR_UO']);
	}
}
if ($_GET['script'] == 'PRINC_INV') {
	Logger::send('PRINC_INV');
		unset($bind);
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select PROGR_PRINC_INV as code, PRINC_INV as decode from {$service}_VENETO_PRINC_INV where ID_DIP = :val order by princ_inv";
	Logger::send($sql);
	$query -> exec($sql, $bind);
	
	print("<option value=''>&nbsp;</option>");
	while ($query -> get_row()) {
		Logger::send($query -> row['CODE']);
		print("<option value='".$query -> row['CODE']."'>".$query -> row['DECODE']."</option>");
	}
}



if (substr($_GET['script'], strlen($_GET['script'])-10, strlen($_GET['script'])) == '_PROVINCIA') {
		unset($bind);
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select DISTINCT ID_PROVINCIA as code, PROVINCIA decode from {$service}_DBITALIA where ID_REGIONE = :val order by provincia";
	$query -> exec($sql, $bind);
	print("<option value=''>&nbsp;</option>");
	while ($query -> get_row()) {
		print("<option value='".$query -> row['CODE']."'>".$query -> row['DECODE']."</option>");
	}
} else if (substr($_GET['script'], strlen($_GET['script'])-7, strlen($_GET['script'])) == '_COMUNE') {
	unset($bind);
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select DISTINCT ISTAT as code, COMUNE decode, PROVINCIA from {$service}_DBITALIA where ID_PROVINCIA = :val order by comune";
	$query -> exec($sql, $bind);
	print("<option value=''>&nbsp;</option>");
	while ($query -> get_row()) {
		print("<option value='".$query -> row['CODE']."' ".($query -> row['DECODE'] == $query -> row['PROVINCIA']?"selected=\"selected\"":"").">".$query -> row['DECODE']."</option>");
	}
}  else if (substr($_GET['script'], strlen($_GET['script'])-4, strlen($_GET['script'])) == '_CAP') {
	$bind['VAL'] = $_GET['val'];
	$query = new query($conn);
	$sql = "select cap from {$service}_DBITALIA where ISTAT = :val";
	$query -> exec($sql, $bind);
	if ($query -> get_row()) {
		print($query -> row['CAP']);
	}
} 
// AJAX
function error_page($user, $error, $error_spec) {
	global $bind;
	$eol = PHP_EOL;
	$email_admin = "g.contino@cineca.it";
	$error_spec = ocierror($conn);
	$today = date("j/m/Y, H:m:s");
	$decode_bind = strtoupper(str_replace(":", "", $error));
	$decode_bind = str_replace("ERRORE QUERY", "In chiaro:", strtoupper($decode_bind));
	foreach ($bind as $key => $val) {
		$spec_bind .= " $key:$val";
		$decode_bind = str_replace(':'.strtoupper($key), "'{$val}'", $decode_bind);
	}
	$prefisso = "http".($_SERVER['SERVER_PORT']=='443'?'s':'')."://";
	$alltxt = "DATI GENERALI:\n* Data: {$today}\n* IP richiesta: {$_SERVER['REMOTE_ADDR']}\n* URL richiesta: {$prefisso}{$_SERVER['HTTP_HOST']}{$_SERVER['REQUEST_URI']}\n\nBACKTRACE:";
	$headers = "From: ERROR_CE@{$_SERVER['SERVER_NAME']}$eol";
	$headers .= "Content-type: text/plain; charset=utf-8$eol";
	$codice = debug_backtrace();
	foreach ($codice as $key => $val) {
		$alltxt .= "\n* $val[file]:$val[line] ($val[function])";
	}
	$alltxt .= "\n\nSPECIFICHE ERRORE:\n* {$error}\n* {$decode_bind}";
	mail($email_admin, "Errore [" . $_SERVER['REMOTE_USER'] . "]", $alltxt, $headers);
	die("ERRORE");
}
?>
