<?php
ob_start();

/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

require_once __DIR__ . '/soapClient/Type/LeggiProtocolloString.php';
//require_once __DIR__ . '/soapClient/Type/LeggiProtocollo.php';
require_once __DIR__ . '/soapClient/Type/LeggiProtocolloStringResponse.php';


//use IrideWS;
use IrideWS\Type;
use IrideWS\IrideWSClient;
use IrideWS\IrideWSClassmap;


//$azienda = "080105";
//$registro = "PG";
$numero = 8; // 7547;
$anno = 2019;
$annoDoc = 2019;
$codStruttura = "8001623";
$ruolo = "";
$utente="";
if ($argv && count($argv)>5) {
    $numero = 8; //"PG";
    $anno = 2019; //2019;
    $utente = $argv[1]; //"MNGDRA83R19A944N";
}else{
    $data = $_GET;
    $azienda = $data['AZIENDA']; //"080105";
    $numero = $data['NUMERO']; //"PG";
    $anno = $data['ANNO']; //2019;
    $utente =  $data['USERCF'];
}

$codiceAmministrazione = "wsprototest"; //"wsproto" -> PRODUZIONE (comitato etico) //"wsprototest" -> TEST (ufficio ced)
$codiceAOO = "aoo1";
$outputBreve = ""; //vuoto o S


$client = getWSClient();
$response = $client->leggiProtocolloString(new Type\LeggiProtocolloString($anno,$numero,$utente,$ruolo,$codiceAmministrazione,$codiceAOO,$outputBreve));
//$response = $client->leggiProtocollo(new Type\LeggiProtocollo($anno,$numero,$utente,$ruolo));
$result = $response->getLeggiProtocolloStringResult();
//var_dump($result);
$protoResponse = new SimpleXMLElement($result);
$base64Documento = $protoResponse->xpath("/DocumentoOut/Allegati/Allegato")[0]->xpath("Image")[0];
$nomeDocumento = $protoResponse->xpath("/DocumentoOut/Allegati/Allegato")[0]->xpath("NomeAllegato")[0];
$contentType = $protoResponse->xpath("/DocumentoOut/Allegati/Allegato")[0]->xpath("ContentType")[0]; //Non sembra essere valorizzato
$dimensioneDocumento = $protoResponse->xpath("/DocumentoOut/Allegati/Allegato")[0]->xpath("Size")[0];
$estensioneDocumento = $protoResponse->xpath("/DocumentoOut/Allegati/Allegato")[0]->xpath("TipoFile")[0];

ob_clean();
header('Content-Description: File Transfer');
header('Content-Type: application/octet-stream');
header('Content-Disposition: attachment; filename="'.$nomeDocumento.'"');
header('Content-Transfer-Encoding: binary');
header('Expires: 0');
header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
header('Pragma: public');
header('Content-Length: ' . ($dimensioneDocumento-0) ); //Absolute URL
die(base64_decode($base64Documento));
