<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';
echo "NA";//IRIDE NON UTILIZZA IL CREATEFOLDER, RESTITUIAMO NA PER UNIFORMARE INTERFACCIAMENTO - vmazzeo 24.09.2019
/*
//use IrideWS;
use IrideWS\Type;
use IrideWS\IrideWSClient;
use IrideWS\IrideWSClassmap;


//$azienda = "080105";
//$registro = "PG";
//$numero = 43;
$anno = 2019;

$utente = "";
$ruolo = "";
$codiceAmministrazione = "wsprototest"; //"wsproto" -> PRODUZIONE (comitato etico) //"wsprototest" -> TEST (ufficio ced)
$codiceAOO = "aoo1";



$classificazione = "1.5";
$vicari = array(); //"CNICRD86E29F943O");
$attori = array(); //array di oggetti con utente e permesso //Opzionale
if ($argv && count($argv)>5) {
    $azienda = $argv[2]; //"080105";
    $registro = $argv[3]; //"PG";
    $anno = $argv[4]; //2019;
    $utenteCreazione = $argv[1]; //"MSRRNT64S69A944K";
    $utenteResponsabile = $argv[1]; //"MSRRNT64S69A944K";
    $codStudio = $argv[5]; //"1"; //Fascicolo origine
}else{
    $data = $_POST;
    $azienda = $data['AZIENDA']; //"080105";
    $registro = $data['REGISTRO']; //"PG";
    $anno = $data['ANNO']; //2019;
    $utenteCreazione = $data['USERCF']; //"MSRRNT64S69A944K";
    $utenteResponsabile = $data['USERCF']; //"MSRRNT64S69A944K";
    $codStudio = $data['STUDIO_CODE']; //"1"; //Fascicolo origine

}

$client = getWSClient();
//Da verificare con Maggioli. Ho chiesto via mail.

$response = $client->leggiProtocolloString(new Type\LeggiProtocolloString($anno,$numero,$utente,$ruolo,$codiceAmministrazione,$codiceAOO,$outputBreve));
//$response = $client->leggiProtocollo(new Type\LeggiProtocollo($anno,$numero,$utente,$ruolo));
$result = $response->getLeggiProtocolloStringResult();
print_r($result);
*/