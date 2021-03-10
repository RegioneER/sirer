<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

require_once "soapClient/Type/Insert.php";
require_once "soapClient/Type/AddDocument.php";
require_once "soapClient/Type/InsertCommit.php";
require_once "soapClient/Type/InsertResponse.php";
require_once "soapClient/Type/AddDocumentResponse.php";
require_once "soapClient/Type/InsertCommitResponse.php";


//$annoDoc = 2019;
//$codStruttura = "8001623";
if ($argv && count($argv)>5) {
    $utenteCF = $argv[1]; //"MNGDRA83R19A944N";
    $utentePROT = $argv[1]; //"MSRRNT64S69A944K";
    $azienda = $argv[2]; //"080105";
    $registro = $argv[3]; //"PG";
    $anno = $argv[4]; //2019;
    $codStudio = $argv[5]; //"1";
    $fascicolo_babel = $argv[6]; //"110/2019"; //Arriva creato da createFolder (crea fascicolo)
    $numeroDoc = $argv[7]; //"3";
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
    $fascicolo_babel = $data['STUDIO_FASCICOLO']; //"110/2019"; //Arriva creato da createFolder (crea fascicolo)
    $numeroDoc = $data['DOCUMENTO_CODE']; //"3";
    $filePath = $data['DOCUMENTO_PATH'];
    $fileMimeType = $data['DOCUMENTO_MIMETYPE'];
}
$codDocumento = $numeroDoc . "-" . $codStudio;
$pathStr = str_replace("\\", "/", $filePath);
$pathStrSpl = explode("/", $pathStr);
$fileName = $pathStrSpl[count($pathStrSpl) - 1];
$oggettoDocumento = "Documento PE {$codDocumento}";

$client = null;
$typeCode = "-1"; //Ingresso/Uscita I/U
$tipoDocumento="";//OBBLIGATORIO PC
$settore="";//OBBLIGATORIO PC
$category = "";
$container="";
switch ($azienda){
    case "RE":
        $client = getWSClientRE();
        $istanzaAzienda = "http://apps.ausl.re.it/DocSuite";
        $category = "-31397";
        $container = "-32601";
        break;
    case "PC":
        $client = getWSClientPC();
        $istanzaAzienda = "http://apps.ausl.pc.it/DocSuite";
        $category = "-32594"; //Sperimentazione farmaci (principale), se selezionabile come opzione anche Stipulazione e rinnovo contratti e convenzioni -32641
        $container = "-32765";
        $tipoDocumento="<DocumentType>40</DocumentType>";//37 test - 40 prod
        $settore="<Authorizations><RoleId>-32314</RoleId><RoleId>-32766</RoleId></Authorizations>";//OBBLIGATORIO PC //-32596
        //Contatto destinatario (recipients) da rubrica (inserire entrambi:
        // PROT. ENTRATA:
        //Comitato Etico - 4438 - contatto da rubrica
        //Direttore Generale - 480 - contatto da rubrica
        // PROT. USCITA:
        //Contatto manuale
        break;
}

if ($client == null){
    die("AZIENDA NON CONFIGURATA");
}

//Ordine chiamate:
//Insert
//Add Document
//Insert commit

//<RegistrationDate/>
$protocolXML = "";
$protocolXML.='<Protocol xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" Year="0" Number="0">';
//$protocolXML.="<Assignee></Assignee>";
$protocolXML.=$settore; //OBBLIGATORIO PER PC
$protocolXML.="<WorkflowMetadata>{$codStudio}</WorkflowMetadata>";
//$protocolXML.="<RegistrationDate/>";
$protocolXML.="<Status>A</Status>";
$protocolXML.="<IdStatus>0</IdStatus>";
$protocolXML.="<Category>{$category}</Category>";
$protocolXML.="<Container>{$container}</Container>";
//$protocolXML.="<Data>".date("d/m/Y")."</Data>"; //data d/M/yyyy del protocollo
$protocolXML.=$tipoDocumento; //OBBLIGATORIO PER PC
$protocolXML.="<Notes></Notes>";
$protocolXML.="<Object>{$oggettoDocumento}</Object>";
$protocolXML.="<Senders>";
$protocolXML.='<ContactBag sourceType="0" >';
$protocolXML.='<Contact type="P" cc="false" >';
$protocolXML.="<Name>${$utentePROT}</Name>";
$protocolXML.="<Surname>${$utentePROT}</Surname>";
$protocolXML.="</Contact>";
$protocolXML.="</ContactBag>";
$protocolXML.="</Senders>";
$protocolXML.="<Recipients>";
$protocolXML.='<ContactBag sourceType="1" >';
$protocolXML.='<Contact type="A">';
$protocolXML.="<Id>4438</Id>";//Comitato Etico 2673 test -- 4438 prod
$protocolXML.="</Contact>";
$protocolXML.='<Contact type="A" cc="true" >';
$protocolXML.="<Id>480</Id>";//Direttore Generale 480 test -- 480 prod
$protocolXML.="</Contact>";
$protocolXML.="</ContactBag>";
$protocolXML.="</Recipients>";
$protocolXML.="<ServiceCode>{$codStudio}</ServiceCode>";
$protocolXML.="<Type>{$typeCode}</Type>";
$protocolXML.="</Protocol>";

//echo "<pre>";
//print_r($protocolXML);
//echo "</pre>";
$base64DocStream = base64_encode(file_get_contents($pathStr));
//die($base64DocStream);

$response = $client->insert(new \DocsuiteWS\Type\Insert($protocolXML));
$protocolloInserito = $response->getInsertResult(); //Dovrebbe tornare anno e numero di protocollo.
$newProtocolloSPL = explode("/",$protocolloInserito);
$year = $newProtocolloSPL[0];
$protNumber = $newProtocolloSPL[1];
echo "STEP1: {$year}/{$protNumber}";


$response = $client->addDocument(new \DocsuiteWS\Type\AddDocument($year,$protNumber,$base64DocStream,$fileName,true));
//var_dump($response);
$response = $client->insertCommit(new \DocsuiteWS\Type\InsertCommit($year,$protNumber));
//var_dump($response);

echo $protNumber."/".$year; //ritorno le informazioni che mi interessano per il front-end.
