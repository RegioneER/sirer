<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

if ($argv && count($argv)>5) {
    $azienda = "080105";
    $registro = "PG";
    $numero = 332; //326; //43;
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
$payload = array(
    "iss" => "SIRER",
    "sub" => $utentePROT,
    "codiceRegioneAzienda", $azienda,
    "mode" => "test",
    "iat" => 1356999524,
    "nbf" => 1357000000,
    "context" => array(
        "azienda" => $azienda,
        "registro" => $registro,
        "numero" => $numero,
        "anno" => $anno
    )
);

$jwt = GenerateJWTToken($payload);
//echo "Encode:\n" . print_r($jwt, true) . "\n";

global $babelHost;
$url = "https://{$babelHost}/internauta-bridge/document/{$azienda}/{$registro}/{$numero}/{$anno}";
$response = SendJWTCURLGet($url, $jwt);

print_r($response);
/*if (!is_object($response)) {
    print_r("is_object");
    $response = json_decode($response);
}

foreach ($response as $item){
    print_r("foreach");
    print_r($item);
    echo "\n";
}*/


/*
$decoded = JWT::decode($jwt, $publicKey, array('RS256'));

// NOTE: This will now be an object instead of an associative array. To get
// an associative array, you will need to cast it as such:

$decoded_array = (array) $decoded;
echo "Decode:\n" . print_r($decoded_array, true) . "\n";

*/

