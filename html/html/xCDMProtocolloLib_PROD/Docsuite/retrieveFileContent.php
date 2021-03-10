<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

require_once "soapClient/Type/GetDocumentsViewerLink.php";
require_once "soapClient/Type/GetDocumentsViewerLinkResponse.php";

$azienda = "PC";
$numero = 70588;
$anno = 2019;
//var_dump($argv);
if ($argv && count($argv)>2) {
    $azienda = $argv[2];
    $numero = $argv[5]; //326; //43;
    $anno = $argv[4];
    $utentePROT = "MSRRNT64S69A944K";
}else{
    $data = $_GET;
    $azienda = $data['AZIENDA']; //"080105";
    $registro = $data['REGISTRO']; //"PG";
    $numero = $data['NUMERO']-0; //"1"; //Fascicolo origine
    $anno = $data['ANNO']-0; //2019;
    $utentePROT = $data['USERCF']; //"MSRRNT64S69A944K";
}

$client = null;
$endpoint = "/viewers/protocolviewer.aspx?";
switch ($azienda){
    case "RE":
        $istanzaAzienda = "http://apps.ausl.re.it/DocSuite";
        $client = getWSClientRE();
        break;
    case "PC":
        $client = getWSClientPC();
        $istanzaAzienda = "http://apps.ausl.pc.it/DocSuite";
        break;
}

if ($client == null){
    die("AZIENDA NON CONFIGURATA");
}


//Insert
//Add Document
//Insert commit
//Get protocollo info

$response = $client->getDocumentsViewerLink(new \DocsuiteWS\Type\GetDocumentsViewerLink($anno,$numero));

$respLink = $response->getGetDocumentsViewerLinkResult();
echo $istanzaAzienda.$endpoint.$respLink;


