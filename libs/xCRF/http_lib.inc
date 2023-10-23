<?php

/**
 * @package CORE
 */

foreach ($_GET as $key => $val){
    $in[$key]= $_GET[$key];
    $HTTP_GET_VARS[$key]=$val;
    ${$key}=  $_GET[$key];
}

foreach ($_POST as $key =>$val){
	$val_new=str_replace("\\'", "'", $val);
	$HTTP_POST_VARS[$key]=$val_new;
	$_POST[$key]=$val_new;
}
if (isset($HTTP_GET_VARS) && count($HTTP_GET_VARS)>0)
foreach ($HTTP_GET_VARS as $key => $val){
	   $in[$key]=$HTTP_GET_VARS[$key];
	   ${$key}= $HTTP_GET_VARS[$key];
}

if (isset($HTTP_POST_VARS))
foreach ($HTTP_POST_VARS as $key => $val){
	   $in[$key]=$HTTP_POST_VARS[$key];
	   ${$key}= $HTTP_POST_VARS[$key];
}


foreach ($_SERVER as $key => $val){
	   $SRV[$key]=$_SERVER[$key];
	   #echo "<hr>$key => $val";
}


if (isset($_SERVER['PHP_AUTH_USER'])){
$remote_userid=strtoupper($_SERVER['PHP_AUTH_USER']);
$in['remote_userid']=strtoupper($_SERVER['PHP_AUTH_USER']);
}
if (isset($_SERVER['REMOTE_USER'])){
$remote_userid=strtoupper($_SERVER['REMOTE_USER']);
$in['remote_userid']=strtoupper($_SERVER['REMOTE_USER']);
}

//$xml="registered_patient_list.xml";
//if ($in['CENTER']!='') $xml="center_patients_list.xml";
//if (isset($in['ESAM'])) {
//	$vis=$in['VISITNUM'];
//	$es=$in['ESAM'];
//	$xml=$xml_form[$vis][$es];
//}

$root=$_SERVER['DOCUMENT_ROOT'];
$xml_dir=preg_replace("/html/", "xml", $root);
//$template_dir=preg_replace("/html/", "template", $root);
$filetxt = file_get_contents('template.htm');
//$filetxt=preg_replace("/<!--user_name-->/", $_SERVER['REMOTE_USER'], $filetxt);

?>