<?php 
global $db_user;
global $db_pwd;
global $db_host;
global $db_name;
global $db_type;
global $db_prefix;

global $base_url;

global $show_errors;

if (file_exists($_SERVER['DOCUMENT_ROOT']."../config/acm-defines.inc")){
	include_once $_SERVER['DOCUMENT_ROOT']."../config/acm-defines.inc";
}else {
	include_once $_SERVER['DOCUMENT_ROOT']."/../libs/acm/define.default.inc";
}

$ammin_file = $_SERVER ['DOCUMENT_ROOT'];
$ammin_file = preg_replace ( "/html/i", "config/amministrazione.cfg", $ammin_file );
$handle = fopen ( $ammin_file, "r" );
$contents = fread ( $handle, filesize ( $ammin_file ) );
fclose ( $handle );
$ammin_config_line = preg_split ( "/\n/", $contents );
for($i = 0; $i < count ( $ammin_config_line ); $i ++) {
    if (preg_match ( "/OraUserid/i", $ammin_config_line [$i] ))
        $db_user = preg_replace ( "/OraUserid (.*)/i", "\\1", $ammin_config_line [$i] );
    if (preg_match ( "/OraPassword/i", $ammin_config_line [$i] ))
        $db_pwd = preg_replace ( "/OraPassword (.*)/i", "\\1", $ammin_config_line [$i] );
    if (preg_match ( "/OraInstance/i", $ammin_config_line [$i] ))
        $db_host = preg_replace ( "/OraInstance (.*)/i", "\\1", $ammin_config_line [$i] );
}
$db_user=rtrim($db_user);
$db_pwd=rtrim($db_pwd);
$db_host=rtrim($db_host);
#DB database name
$db_name = $db_user;
#DB type
$db_type = "oracle";

#DB tables prefix
$db_prefix = "";

$base_url = "/acm/"; //dirname($_SERVER['SCRIPT_NAME']);

$siteInfo['logoSite']="/images/sirerlogo.png";

$show_errors = true;


?>
