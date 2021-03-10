<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

require_once __DIR__ . '/soapClient/Type/InserisciProtocolloEAnagraficheString.php';
require_once __DIR__ . '/soapClient/Type/InserisciProtocolloEAnagraficheStringResponse.php';


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
$codiceAmministrazione = "wsproto"; //"wsproto" -> PRODUZIONE (comitato etico) //"wsprototest" -> TEST (ufficio ced)
$codiceAOO = "aoo1";



$annoDoc = 2019;
$codStruttura = "8001623";
if ($argv && count($argv)>5) {
    $azienda = $argv[2]; //"080105";
    $registro = $argv[3]; //"PG";
    $anno = $argv[4]; //2019;
    $numeroDoc = $argv[7]; //"3";
    $utenteCF = $argv[1]; //"MNGDRA83R19A944N";
    $utentePROT = $argv[1]; //"MSRRNT64S69A944K";
    $codStudio = $argv[5]; //"1";
    $fascicolo_iride= $argv[6]; //"110/2019"; //Arriva creato da createFolder (crea fascicolo)
    $filePath = $argv[8];
    $fileMimeType = $argv[9];
}else{
    $data = $_POST;
    $azienda = $data['AZIENDA']; //"080105";
    $registro = $data['REGISTRO']; //"PG";
    $anno = $data['ANNO']; //2019;
    $utenteCF = $data['USERCF']; //"MNGDRA83R19A944N";
    $utentePROT = $data['USERCF']; //"MSRRNT64S69A944K";
    $codStudio = $data['STUDIO_CODE']; //"1"; //Fascicolo origine
    $fascicolo_iride= $data['STUDIO_FASCICOLO']; //"110/2019"; //Arriva creato da createFolder (crea fascicolo)
    $numeroDoc = $data['DOCUMENTO_CODE']; //"3";
    $filePath = $data['DOCUMENTO_PATH'];
    $fileMimeType = $data['DOCUMENTO_MIMETYPE'];
}
$utenteCFCognome = $utenteCF;
$utenteCFNome = $utenteCF;
$codDocumento = $numeroDoc . "-" . $codStudio;
$pathStr = str_replace("\\", "/", $filePath);
$pathStrSpl = explode("/", $pathStr);
$fileName = $pathStrSpl[count($pathStrSpl) - 1];
$fileNameSpl = explode(".",$fileName);
$extFile = $fileNameSpl[count($fileNameSpl)-1];
$oggettoDocumento = "Documento PE {$codDocumento}";

$base64Doc = base64_encode(file_get_contents($filePath));

$titolario = "1.5";
$tipoDocumento = "GENERICO";

$protocolloInStrXML = ""; //XML di richiesta protocollazione

$protocolloInStrXML.="<ProtoIn>";
$protocolloInStrXML.="<Data>".date("d/m/Y")."</Data>";
$protocolloInStrXML.="<Classifica>{$titolario}</Classifica>"; //Da definire secondo regole
$protocolloInStrXML.="<TipoDocumento>{$tipoDocumento}</TipoDocumento>"; //Da definire secondo regole
$protocolloInStrXML.="<Oggetto>{$oggettoDocumento}</Oggetto>";
$protocolloInStrXML.="<Origine>A</Origine>"; //A-Arrivo, I-Interno, P-Partenza
$protocolloInStrXML.="<MezzoInvio>Interoperabile</MezzoInvio>";
$protocolloInStrXML.="<MittentiDestinatari>";
$protocolloInStrXML.="<MittenteDestinatario>";
$protocolloInStrXML.="<CodiceFiscale>{$utenteCF}</CodiceFiscale>";
$protocolloInStrXML.="<CognomeNome>{$utenteCFCognome}</CognomeNome>";
$protocolloInStrXML.="<Nome>{$utenteCFNome}</Nome>";
$protocolloInStrXML.="</MittenteDestinatario>";
$protocolloInStrXML.="</MittentiDestinatari>";
$protocolloInStrXML.="<AggiornaAnagrafiche>N</AggiornaAnagrafiche>";
$protocolloInStrXML.="<AnnoPratica>".date("Y")."</AnnoPratica>";
$protocolloInStrXML.="<NumeroPratica>{$fascicolo_iride}</NumeroPratica>";
$protocolloInStrXML.="<DataDocumento></DataDocumento>";
$protocolloInStrXML.="<NumeroDocumento>{$codDocumento}</NumeroDocumento>";
$protocolloInStrXML.="<NumeroAllegati></NumeroAllegati>";
$protocolloInStrXML.="<DataEvid></DataEvid>";
//$protocolloInStrXML.="<Utente></Utente>"; //Da capire come indicare l'utente nel sistema di protocollo
//$protocolloInStrXML.="<Ruolo></Ruolo>"; //Da definire secondo tabella ruoli
$protocolloInStrXML.="<Utente></Utente>"; //Da capire come indicare l'utente nel sistema di protocollo
$protocolloInStrXML.="<Ruolo></Ruolo>"; //Da definire secondo tabella ruoli
$protocolloInStrXML.="<Allegati>";
$protocolloInStrXML.="<Allegato>";
$protocolloInStrXML.="<TipoFile>{$extFile}</TipoFile>";
$protocolloInStrXML.="<ContentType>{$fileMimeType}</ContentType>";
$protocolloInStrXML.='<Image xmlns:dt="urn:schemas-microsoft-com:datatypes" dt:dt="bin.base64">'.$base64Doc.'</Image>';
$protocolloInStrXML.="<NomeAllegato>{$fileName}</NomeAllegato>";
$protocolloInStrXML.="</Allegato>";
$protocolloInStrXML.="</Allegati>";
//$protocolloInStrXML.="<LivelloRiservatezza>riservato_differito</LivelloRiservatezza>";
$protocolloInStrXML.="<DataFineRiservatezza>".date("d/m/Y")."</DataFineRiservatezza>";
$protocolloInStrXML.="<CodiceAmministrazione>{$codiceAmministrazione}</CodiceAmministrazione>";
$protocolloInStrXML.="<CodiceAOO>{$codiceAOO}</CodiceAOO>";
$protocolloInStrXML.="</ProtoIn>";

//var_dump($protocolloInStrXML);

/*
$result = "<ProtocolloOut>
 <IdDocumento>41</IdDocumento>
 <AnnoProtocollo>2019</AnnoProtocollo>
 <NumeroProtocollo>6</NumeroProtocollo>
 <DataProtocollo>2019-09-16T09:02:16.042+0200</DataProtocollo>
 <Messaggio>Inserimento Protocollo eseguito con successo, senza Avvio Iter</Messaggio>
 <Errore/>
 <Allegati>
  <Allegato>
   <Serial>381</Serial>
   <IDBase>381</IDBase>
   <Versione>0</Versione>
  </Allegato>
 </Allegati>
</ProtocolloOut>
";
*/
$client = getWSClient();
$response = $client->inserisciProtocolloEAnagraficheString(new Type\InserisciProtocolloEAnagraficheString($protocolloInStrXML,$codiceAmministrazione,$codiceAOO));
$result = $response->getInserisciProtocolloEAnagraficheStringResult();
//print_r($result);

$protoResponse = new SimpleXMLElement($result);
$annoProtocollo = $protoResponse->xpath("/ProtocolloOut/AnnoProtocollo")[0];
$numeroProtocollo = $protoResponse->xpath("/ProtocolloOut/NumeroProtocollo")[0];

die($numeroProtocollo."/".$annoProtocollo);

//!!!! - Ottengo questa stringa di risposta: 0000322/2019 - !!!!! Dovrebbe essere il numero di protocollo inserito
//0000323/2019


