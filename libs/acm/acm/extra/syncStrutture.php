<?php 
//Force https
if (!$_SERVER['HTTPS'] && $_SERVER['PORT']!="443"){
	$url = "https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
	header('Location: '.$url);
}

ini_set('display_errors','1');
error_reporting(E_ERROR|E_PARSE);

require_once '../UIManager.class.php';
//Common files and database connection
require_once '../dbconfig.php';
require_once '../database.php';
require_once '../multilanguage.php';
require_once '../utils.php';

$bind = array();
$sql = "SELECT * FROM CE_ELENCO_CENTRILOC";
$rs = db_query_bind($sql,$bind);
while ($row=db_nextrow($rs)){
	var_dump($row);
}

?>
