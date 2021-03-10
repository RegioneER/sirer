<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';


//use IrideWS;
use IrideWS\Fascicolo\Type;
use IrideWS\Fascicolo\IrideWSClient;
use IrideWS\Fascicolo\IrideWSClassmap;

require_once __DIR__ . '/soapClient/Fascicolo/Type/CreaFascicolo.php';
require_once __DIR__ . '/soapClient/Fascicolo/Type/CreaFascicoloString.php';
require_once __DIR__ . '/soapClient/Fascicolo/Type/CreaFascicoloResponse.php';
require_once __DIR__ . '/soapClient/Fascicolo/Type/CreaFascicoloStringResponse.php';

//$azienda = "080105";
//$registro = "PG";
//$numero = 43;
$anno = 2019;

$utente = "";
$ruolo = "";
$codiceAmministrazione = "wsproto"; //"wsproto" -> PRODUZIONE (comitato etico) //"wsprototest" -> TEST (ufficio ced)
$codiceAOO = "aoo1";
$classificazione = "1.5";
if ($argv && count($argv)>1) {
    $classificazione=$argv[0];
    $classificazione=$argv[1];
    $oggettoDocumento="Fascicolo PE ".$argv[2];
}else{
    $data = $_POST;
    $classificazione=$data['REGISTRO'];
    $codStudio = $data['STUDIO_CODE']; //"1"; //Fascicolo origine
    $protStudio=$data['STUDIO_PROT_CODE'];
    $aziendaDescr=$data['AZIENDA_DESCR'];
    $piCognome=$data['PICognome'];
    $tipoDoc=$data['TIPO_DOC'];
    $oggettoDocumento = "SIRER {$codStudio} {$protStudio} {$aziendaDescr} {$piCognome} {$tipoDoc}";

}

$titolario = "1.5";
$tipoDocumento = "GENERICO";

$protocolloInStrXML = ""; //XML di richiesta protocollazione

$protocolloInStrXML.="<FascicoloIn>";
$protocolloInStrXML.="<Classifica>{$titolario}</Classifica>";
$protocolloInStrXML.="<Oggetto>{$oggettoDocumento}</Oggetto>";
$protocolloInStrXML.="</FascicoloIn>";



$client = getWSClient(true);

$response = $client->creaFascicoloString(new IrideWFFascicolo\Type\CreaFascicoloString($protocolloInStrXML,$codiceAmministrazione,$codiceAOO));
$result = $response->getCreaFascicoloStringResult();
//print_r($result);

$protoResponse = new SimpleXMLElement($result);
$id = $protoResponse->xpath("/FascicoloOut/NumeroSenzaClassifica")[0];
//$anno= $protoResponse->xpath("/FascicoloOut/Anno")[0];
echo $id;
//$numeroProtocollo = $protoResponse->xpath("/ProtocolloOut/NumeroProtocollo")[0];
