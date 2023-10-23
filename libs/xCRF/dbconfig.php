<?php 
global $db_user;
global $db_pwd;
global $db_host;
global $db_name;
global $db_type;
global $db_prefix;

global $base_url;

global $show_errors;


define("SYSTEMBASEURL_LIBRARY","/http/servizi/NET/service/html/study/libs/ammconsole/");

#DB username
$db_user = "DEV_SERVICE";
#DB password
$db_pwd = "ecv0801!";
#DB host
$db_host = "generici_dev";
#DB database name
$db_name = "DEV_SERVICE";
#DB type
$db_type = "oracle";

#DB tables prefix
$db_prefix = "";

$base_url = "/study/libs/ammconsole/"; //dirname($_SERVER['SCRIPT_NAME']);

$show_errors = true;


?>