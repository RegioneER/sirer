<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

$classificazione = "06-05-01";
$vicari = array(); //"CNICRD86E29F943O");
$attori = array(); //array di oggetti con utente e permesso //Opzionale
$permessi =array(); //serve per popolare attori
if ($argv && count($argv)>5) {
    $azienda = $argv[2]; //"080105";
    $registro = $argv[3]; //"PG";
    $anno = $argv[4]; //2019;
    $utenteCreazione = $argv[1]; //"MSRRNT64S69A944K";
    $utenteResponsabile = $argv[1]; //"MSRRNT64S69A944K";
    $codStudio = $argv[5]; //"1"; //Fascicolo origine
    $classificazione= $argv[6];
    $tipo_fascicolo= $argv[7];
    $vicari = explode(',',$argv[8]);
    $permessi = explode(',',$argv[9]);
    $aziendaDescr = $argv[10];
    $protStudio = $argv[11];
    $piCognome = $argv[12];
}else{
    $data = $_POST;
    $azienda = $data['AZIENDA']; //"080105";
    $aziendaDescr=$data['AZIENDA_DESCR'];
    $registro = $data['REGISTRO']; //"PG";
    $anno = $data['ANNO']; //2019;
    $utenteCreazione = $data['USERCF']; //"MSRRNT64S69A944K";
    $utenteResponsabile = $data['USERCF']; //"MSRRNT64S69A944K";
    $codStudio = $data['STUDIO_CODE']; //"1"; //Fascicolo origine
    $protStudio=$data['STUDIO_PROT_CODE'];
    $classificazione= $data['INTEGRAZIONE_CLASSIFICAZIONE'];
    $tipo_fascicolo= $data['INTEGRAZIONE_TIPOFASCICOLO'];
    $vicari = explode(',',$data['INTEGRAZIONE_VICARI']);
    $permessi = explode(',',$data['INTEGRAZIONE_PERMESSI']);
    $piCognome=$data['PICognome'];
    $tipoDoc=$data['TIPO_DOC'];
}


$payload = array(
    "iss" => "SIRER",
    "sub" => $utenteCreazione,
    "codiceRegioneAzienda", $azienda,
    "mode" => "test",
    "iat" => 1356999524,
    "nbf" => 1357000000,
    "context" => array(
        "azienda" => $azienda,
        "id_fascicolo_origine" => $codStudio
    )
);
$applicazione_chiamante="SIRER";
$id_fascicolo_origine=$codStudio;
foreach ($permessi as $permesso){
    /*$tmp["utente"]=$permesso;
    $tmp["permesso"]="LEGGE";
    $attori[]=$tmp;
    $tmp["utente"]=$permesso;
    $tmp["permesso"]="MODIFICA";
    $attori[]=$tmp;*/
    $tmp["utente"]=$permesso;
    $tmp["permesso"]="ELIMINA";
    $attori[]=$tmp;
}
//$attori=json_encode($attori);
$properties = array(
    "applicazione_chiamante" => $applicazione_chiamante,
    "azienda" => $azienda,
    "id_fascicolo_origine" => $id_fascicolo_origine,
    "nome_fascicolo" => "SIRER {$codStudio} {$protStudio} {$aziendaDescr} {$piCognome} ${tipoDoc}",
    "utente_creazione" => $utenteCreazione,
    "classificazione" => $classificazione,
    "tipo_fascicolo" => $tipo_fascicolo,
    "utente_responsabile" => $utenteResponsabile,
    "vicari" => $vicari,
    "attori" => $attori
);

//echo($attori);
//die();
global $babelHost;



$jwt = GenerateJWTToken($payload);
//echo "Encode:\n" . print_r($jwt, true) . "\n";
//vmazzeo 04.11.2019 INSERISCO CONTROLLO SULL'ESISTENZA DELL'id_fascicolo_origine che se esiste mi restituisce il protocollo altrimenti ne creo uno nuovo
$base64_id_fascicolo_origine=base64_encode($id_fascicolo_origine);
$url = "https://{$babelHost}/internauta-bridge/fascicolo/{$azienda}/{$applicazione_chiamante}/{$base64_id_fascicolo_origine}";
$response = SendJWTCURLGet($url, $jwt);

if($response=="") {
    $jwt = GenerateJWTToken($payload);
    //echo "Encode:\n" . print_r($jwt, true) . "\n";

    $body = json_encode($properties);

    $url = "https://{$babelHost}/internauta-bridge/fascicolo";
    $response = SendJWTCURLPostJson($url, $jwt, $body);
}
echo $response;

/*
print_r($response);
if (!is_object($response)) {
    $response = json_decode($response);
}

foreach ($response as $item){
    print_r($item);
    echo "\n";
}
*/


/*
$decoded = JWT::decode($jwt, $publicKey, array('RS256'));

// NOTE: This will now be an object instead of an associative array. To get
// an associative array, you will need to cast it as such:

$decoded_array = (array) $decoded;
echo "Decode:\n" . print_r($decoded_array, true) . "\n";

*/

