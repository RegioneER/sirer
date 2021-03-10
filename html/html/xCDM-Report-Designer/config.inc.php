<?php

include_once "db_wl.inc";
require_once "vendor/limonade/lib/limonade.php";
require_once "vendor/smarty/libs/Smarty.class.php";

// Error page Davide v.1.0.5
function error_page($user, $error, $error_spec) {
    $today = date("d/m/Y, H:m:s");
    // Dati generali
    $alltxt = "DATI GENERALI:\n* Data: {$today}\n* IP richiesta: {$_SERVER['REMOTE_ADDR']}\n* URL richiesta: {$prefisso}{$_SERVER['HTTP_HOST']}{$_SERVER['REQUEST_URI']}";
    // Specifiche errore
    if (is_array($error_spec))
        foreach ($error_spec as $key => $val)
            $spec .= "\n* $key : $val";
    else
        $spec = $error_spec;
    $alltxt .= "\n\nSPECIFICHE ERRORE:{$spec}";
    // Backtrace
    $alltxt .= "\n\nBACKTRACE:";
    $headers = "From: ERROR_" . $service . "@{$_SERVER['SERVER_NAME']}$eol";
    $headers .= "Content-type: text/plain; charset=utf-8$eol";
    $codice = debug_backtrace();
    foreach ($codice as $key => $val) {
        $alltxt .= "\n* $val[file]:$val[line] ($val[function])";
    }
    $body = "<p align=center><font size=4><b>Warning</b></p><br><br>";
    $filetxt = preg_replace("/<!--body-->/", $body, $filetxt);
    $btrace = debug_backtrace(false, false);
    $stackstr = print_r($btrace, true);
    // Notifica
    //mail("d.saraceno@cineca.it", "Errore[" . $in['remote_userid'] . "]", "$today\n\n" . $alltxt, "From: ERROR_" . $service . "@{$_SERVER['SERVER_NAME']}\r\n");
 	echo "<pre>";
 	print_r($error_spec);
 	echo "</pre>";
    die('ERR');
}
?>