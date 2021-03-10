<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */
ob_start();
require_once __DIR__ . '/authentication.php';
if ($argv && count($argv)>5) {
    $azienda = "080105";
    $registro = "PG";
    $numero = 43;
    $anno = 2019;
    $id_file = "FRONTESPIZIO";
}
else{
    $data = $_GET;
    $azienda = $data['AZIENDA']; //"080105";
    $registro = $data['REGISTRO']; //"PG";
    $numero = $data['NUMERO']-0; //"1"; //Fascicolo origine
    $anno = $data['ANNO']-0; //2019;
    $id_file=$data['ID_FILE'];
    $nome_file=$data['NOME_FILE'];
    $utentePROT = $data['USERCF']; //"MSRRNT64S69A944K";
}

$payload = array(
    "iss" => "SIRER",
    "sub" => $utentePROT,
    "codiceRegioneAzienda", $azienda,
    "mode" => "test",
    "iat" => time(),
    "nbf" => time(),
    "context" => array(
        "azienda" => $azienda,
        "registro" => $registro,
        "numero" => $numero,
        "anno" => $anno,
        "file" => $id_file
    )
);

$jwt = GenerateJWTToken($payload);
//echo "Encode:\n" . print_r($jwt, true) . "\n";

global $babelHost;
$url = "https://{$babelHost}/internauta-bridge/document/{$azienda}/{$registro}/{$numero}/{$anno}/{$id_file}";
$response = SendJWTCURLGet($url, $jwt);
ob_clean();
header('Content-Description: File Transfer');
header('Content-Type: application/octet-stream');
header('Content-Disposition: attachment; filename="'.$nome_file.'"');
header('Content-Transfer-Encoding: binary');
header('Expires: 0');
header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
header('Pragma: public');
//header('Content-Length: ' . ($dimensioneDocumento-0) ); //Absolute URL
//die(base64_decode($response));
echo $response;



