<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

require_once "soapClient/Type/GetProtocolInfo.php";
require_once "soapClient/Type/GetProtocolInfoResponse.php";

$azienda = "PC";
$numero = 70588;
$anno = 2019;
if ($argv && count($argv)>2) {
    $azienda = "PC";
    $numero = 70502; //326; //43;
    $anno = 2019;
    $utentePROT = "MSRRNT64S69A944K";
}else{
    $data = $_POST;
    $azienda = $data['AZIENDA']; //"080105";
    $registro = $data['REGISTRO']; //"PG";
    $numero = $data['NUMERO']-0; //"1"; //Fascicolo origine
    $anno = $data['ANNO']-0; //2019;
    $utentePROT = $data['USERCF']; //"MSRRNT64S69A944K";
}

$client = null;
switch ($azienda){
    case "RE":
        $client = getWSClientRE();
        break;
    case "PC":
        $client = getWSClientPC();
        break;
}

if ($client == null){
    die("AZIENDA NON CONFIGURATA");
}

//Insert
//Add Document
//Insert commit
//Get protocollo info

$response = $client->getProtocolInfo(new \DocsuiteWS\Type\GetProtocolInfo($anno,$numero));

var_dump($response->getGetProtocolInfoResult());


