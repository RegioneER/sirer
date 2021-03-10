<?php

/* Creazione cartella log_trace sulla partizione data
 * La cartella log_trace diventa un symlink alla partizione data
 */
$service_path = preg_replace("/\/http\/www\//i", "", $dir);
$service_path = preg_replace("/\/html/i", "", $service_path);
$service_path = preg_replace("/index.php(.*?)$/i", "", $_SERVER['REQUEST_URI']);

// print($service_path."<hr />");

if(preg_match("/sissdev/i", $_SERVER['SERVER_NAME'])){
	$machine = "siss-devel";
	$symlink = preg_replace("/http\/www/i", $machine."/data/log_xmr", $root);	
}else if(preg_match("/sissprep/i", $_SERVER['SERVER_NAME'])){
	$machine = "sissprep";
	$symlink = preg_replace("/http\/www/i", $machine."/data/log_xmr", $root);
}else{
	$machine = "sissprod";
	$symlink = preg_replace("/http\/www/i", $machine."/data/log_xmr", $root);
}

$symlink = preg_replace("/\/html/i", "", $symlink);
$symlink_path = $symlink.$service_path."log_trace/";
$service_name = preg_replace("/\/".$machine."\/data\/log_xmr/i", "", $symlink);

/* Creazione cartella log_trace sulla partizione data (riproduce la struttura della document root del servizio) */
if(!file_exists($symlink_path)){
	
	mkdir($symlink_path, 0777, true);
	//system("chmod g+ws -R /".$machine."/data/log_xmr".$service_name);
	chmod($symlink_path, 0777);
}

/* Se non esiste il link log_trace lo crea
 */
if(!file_exists($GLOBALS['dir']."/log_trace")){
	symlink($symlink_path, $GLOBALS['dir']."/log_trace");
}

?>
