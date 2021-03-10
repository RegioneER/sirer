<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

$annoDoc = 2019;
$codStruttura = "8001623";
if ($argv && count($argv)>5) {
    $azienda = $argv[2]; //"080105";
    $registro = $argv[3]; //"PG";
    $annoDoc = $argv[4]; //2019;
    $numeroDoc = $argv[7]; //"3";
    $utenteCF = $argv[1]; //"MNGDRA83R19A944N";
    $utentePROT = $argv[1]; //"MSRRNT64S69A944K";
    $codStudio = $argv[5]; //"1";
    $fascicolo_babel = $argv[6]; //"110/2019"; //Arriva creato da createFolder (crea fascicolo)
    //$filePath = $argv[8];
    //$fileMimeType = $argv[9];
}else{
    $data = $_POST;
    $azienda = $data['AZIENDA']; //"080105";
    $registro = $data['REGISTRO']; //"PG";
    $annoDoc = $data['ANNO']-0; //2019;
    $utenteCF = $data['USERCF']; //"MNGDRA83R19A944N";
    $utentePROT = $data['USERCF']; //"MSRRNT64S69A944K";
    $codStudio = $data['STUDIO_CODE']; //"1"; //Fascicolo origine
    $fascicolo_babel = $data['STUDIO_FASCICOLO']; //"110/2019"; //Arriva creato da createFolder (crea fascicolo)
    $codStruttura = $data['INTEGRAZIONE_STRUTTURA'];
    $assegnatari = explode(',',$data['INTEGRAZIONE_ASSEGNATARI']);
    $utente_responsabile= $data['INTEGRAZIONE_RESPONSABILE'];
    $vicari= explode(',',$data['INTEGRAZIONE_VICARI']);
    $numeroDoc = $data['DOCUMENTO_CODE']; //"3";
    $fileContent = $data['DOCUMENTO_BODY'];
    $fileName = $data['DOCUMENTO_FILENAME'];
}


$codDocumento = $numeroDoc . "-" . $codStudio;
$oggettoDocumento = "Documento PE {$codDocumento}";
if ($fileContent){
    $fileContent = base64_decode(str_replace(' ','+', $fileContent)); //base64_decode_fromJS($fileContent);
    $filePath = __DIR__ . '/../doctmp/'.$numeroDoc.'-'.$fileName;
    mkdir(__DIR__ . '/../doctmp',0777,true);
    file_put_contents($filePath,$fileContent);
    $fileMimeType = mime_content_type($filePath);
    //var_dump($filePath);
    //var_dump($fileMimeType);
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
        "numero_documento_origine" => $codDocumento,
        "anno_documento_origine" => $annoDoc
    )
);

$jwt = GenerateJWTToken($payload);
//echo "Encode:\n" . print_r($jwt, true) . "\n";


$properties = array(
    "applicazione_chiamante" => "SIRER",
    "azienda" => $azienda,
    "oggetto" => $oggettoDocumento,
    "numero_documento_origine" => $codDocumento,
    "anno_documento_origine" => $annoDoc,
    "data_arrivo_origine" => date("Y-m-d"),
    "data_registrazione_origine" => date("Y-m-d"),
    "utente_protocollante" => $utentePROT,
    "struttura_protocollante" => $codStruttura,
    "fascicolo_origine" => $codStudio,
    "fascicolo_babel" => $fascicolo_babel,
    "riservato" => "NO",
    "mittente" => array(
        "descrizione" => "MITTENTE", //Può essere cf o username o nome e cognome dell'utente che ha caricato il doc dentro SIRER
        "indirizzo_spedizione" => $utentePROT,
        "tipo" => "esterno",
        "mezzo_spedizione" => "email" //"portale_web"
    ),
    "destinatari" => array(
        array(
            "struttura" => $codStruttura,
            "tipo" => "A",
            "utente_responsabile" => "",//$utente_responsabile,
            "assegnatari" => $assegnatari
        )
    )

);

$postData = array();
$postData['properties'] = json_encode($properties);
$postData['documento_principale'] = new \CurlFile($filePath, $fileMimeType, $fileName);
$postData['allegati'] = array();
$postData['annessi'] = array();
$postData['annotazioni'] = array();

//var_dump($postData);
//die();


$url = "https://babelhg.ausl.bologna.it/internauta-bridge/document/pe";
$response = SendJWTCURLPost($url, $jwt, $postData);

if ($fileContent && $filePath){
    //unlink($filePath);
}
echo($response);
//!!!! - Ottengo questa stringa di risposta: 0000322/2019 - !!!!! Dovrebbe essere il numero di protocollo inserito
//0000323/2019



/*
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

