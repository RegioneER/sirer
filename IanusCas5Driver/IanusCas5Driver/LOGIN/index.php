<?php 

include_once("lib/http_lib.inc");

/* Linguaggio */
if(isset($in['LANG']) && $in['LANG'] != ""){
	$language = $in['LANG'];
}else{
	$language = "en";
}

if(file_exists("login.conf.inc")){
	include_once("login.conf.inc");
}

$login_template = file_get_contents("template/login.html");

/* Replace */
$login_template = preg_replace("/<!-- titolo -->/i", $login['label']['titolo'], $login_template);
$login_template = preg_replace("/<!-- username -->/i", $login['label']['username'][$language], $login_template);
$login_template = preg_replace("/<!-- password -->/i", $login['label']['password'][$language], $login_template);
$login_template = preg_replace("/<!-- siss -->/i", $login['label']['siss'][$language], $login_template);
$login_template = preg_replace("/<!-- reserved -->/i", $login['label']['reserved'][$language], $login_template);
$login_template = preg_replace("/<!-- login-button -->/i", $login['label']['login-button'][$language], $login_template);
$login_template = preg_replace("/<!-- cancel-button -->/i", $login['label']['cancel-button'][$language], $login_template);

echo $login_template;

?>
