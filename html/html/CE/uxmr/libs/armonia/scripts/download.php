<?php
require_once "libs/http_lib.inc";

function enforceSaferDownload($wantedDir,$finalFile){
	$wantedDir=realpath($wantedDir);
	$finalFile=realpath($finalFile);
	$pos=strpos($finalFile,$wantedDir);
	if($pos===FALSE){
		echo "Bad Request!";
		die();
		return false;
	}
	else {
		return true;
	}
}

$nome_file=str_replace(" ", "_", $nome_file);
$dir=$_SERVER['PATH_TRANSLATED'];
$dir=preg_replace("/\/download.php/", "", $dir);
$wantedDir=$dir."/uploaded_file/";
$dir.="/uploaded_file/$nome_real_file";
enforceSaferDownload($wantedDir,$dir);
header("Content-type:*");
header("Content-Disposition: attachment; filename=".$nome_file);
readfile($dir);

exit;
