<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

require_once __DIR__ . '/soapClient/Card/Type/SearchCriteria.php';
require_once __DIR__ . '/soapClient/Card/Type/CreateCard.php';
require_once __DIR__ . '/soapClient/Card/Type/CreateCardResponse.php';
require_once __DIR__ . '/soapClient/Card/Type/GetCardIndexes.php';
require_once __DIR__ . '/soapClient/Card/Type/GetCardIndexesResponse.php';

require_once __DIR__ . '/soapClient/Card/Type/ArrayOfguid.php';
require_once __DIR__ . '/soapClient/Card/Type/ArrayOfArchive.php';
require_once __DIR__ . '/soapClient/Card/Type/ArrayOfField.php';
require_once __DIR__ . '/soapClient/Card/Type/Archive.php';
require_once __DIR__ . '/soapClient/Card/Type/DocumentType.php';
require_once __DIR__ . '/soapClient/Card/Type/Field.php';
require_once __DIR__ . '/soapClient/Card/Type/Document.php';
require_once __DIR__ . '/soapClient/Card/Type/Card.php';
require_once __DIR__ . '/soapClient/Card/Type/CardBundle.php';
require_once __DIR__ . '/soapClient/Card/Type/InsertParameters.php';
require_once __DIR__ . '/soapClient/Card/Type/ClassificationFolder.php';
require_once __DIR__ . '/soapClient/Card/Type/ArrayOfClassificationFolder.php';

require_once __DIR__ . '/soapClient/Card/Type/ArrayOfAdditive.php';
require_once __DIR__ . '/soapClient/Card/Type/CardExpirationInfo.php';
require_once __DIR__ . '/soapClient/Card/Type/ExternNotification.php';
require_once __DIR__ . '/soapClient/Card/Type/ExternNotificationOffice.php';
require_once __DIR__ . '/soapClient/Card/Type/ExternNotificationUsers.php';
require_once __DIR__ . '/soapClient/Card/Type/ArrayOfExternNotificationOffice.php';
require_once __DIR__ . '/soapClient/Card/Type/ArrayOfstring.php';
require_once __DIR__ . '/soapClient/Card/Type/CardHasData.php';
require_once __DIR__ . '/soapClient/Card/Type/Color.php';
require_once __DIR__ . '/soapClient/Card/Type/Annotation.php';
require_once __DIR__ . '/soapClient/Card/Type/ArrayOfAnnotation.php';
require_once __DIR__ . '/soapClient/Card/Type/InvoiceBase.php';
require_once __DIR__ . '/soapClient/Card/Type/InvoiceIn.php';
require_once __DIR__ . '/soapClient/Card/Type/InvoiceOut.php';
require_once __DIR__ . '/soapClient/Card/Type/InvoiceMonitor.php';
require_once __DIR__ . '/soapClient/Card/Type/CardOperationsFromList.php';
require_once __DIR__ . '/soapClient/Card/Type/CardOperations.php';
require_once __DIR__ . '/soapClient/Card/Type/CardOperationsInput.php';
require_once __DIR__ . '/soapClient/Card/Type/CardOperationsOutput.php';
require_once __DIR__ . '/soapClient/Card/Type/ArrayOfCardOperation.php';


$azienda = "080105";
$idarchivio = 8; //PROTOCOLLO GENERALE
$idTipoDoc = 15; //ARRIVO
$classFolderId = 703; //B.11 -> classificazione da "titolario".

$numero = 11;
$anno = 2019;


//$annoDoc = 2019;
//$codStruttura = "8001623";
if ($argv && count($argv)>5) {
    $azienda = $argv[2]; //"080105";
    $registro = $argv[3]; //"PG";
    $anno = $argv[4]; //2019;
    $numeroDoc = $argv[7]; //"3";
    $utenteCF = $argv[1]; //"MNGDRA83R19A944N";
    $utentePROT = $argv[1]; //"MSRRNT64S69A944K";
    $codStudio = $argv[5]; //"1";
    $fascicolo_babel = $argv[6]; //"110/2019"; //Arriva creato da createFolder (crea fascicolo)
    //$filePath = $argv[8];
    //$fileMimeType = $argv[9];
}else{
    $data = $_POST;
    $idarchivio = $data['AZIENDA']; //"080105";
    $aziendaDescr=$data['AZIENDA_DESCR'];
    $idTipoDoc = $data['REGISTRO']; //"PG";
    $anno = $data['ANNO']; //2019;
    $utenteCF = $data['USERCF']; //"MNGDRA83R19A944N";
    $utentePROT = $data['USERCF']; //"MSRRNT64S69A944K";
    $codStudio = $data['STUDIO_CODE']; //"1"; //Fascicolo origine
    $protStudio=$data['STUDIO_PROT_CODE'];
    $fascicolo_babel = $data['STUDIO_FASCICOLO']; //"110/2019"; //Arriva creato da createFolder (crea fascicolo)
    $numeroDoc = $data['DOCUMENTO_CODE']; //"3";
    $fileContent = $data['DOCUMENTO_BODY'];
    $fileName = $data['DOCUMENTO_FILENAME'];
    $piCognome=$data['PICognome'];
    $tipoDoc=$data['TIPO_DOC'];
}
$codDocumento = $numeroDoc . "-" . $codStudio;
$oggettoDocumento = "SIRER {$codStudio} {$protStudio} {$aziendaDescr} {$piCognome} {$tipoDoc}";
$base64DocStream = $fileContent;

if (stristr($fileName,".")!==false){
    $fileSpl = explode(".",$fileName);
    $fileExt = $fileSpl[count($fileSpl)-1];
}


$sessionObj = generateLoginSession();

$client = getWSCardClient();

//Ordine chiamate:
//Create_Card per creare la nuova scheda di documento (con dentro il documento inserito)
//Load_Card / GetCardIndexes per recuperare il numero di protocollo associato
$checkDupType = "None";
$IsVerifySignedFile = false;
$bIsAutomaticProtocol = false;
$bSorted = false;
$bSyncWF = false;
$bVisAllNote = false;
$bVisOnlyDoc = false;
$extCfg = null;
$strMessage = null;
$strNote = null;
$attachmentArray = null; //new \ArchiflowWSCard\Type\ArrayOfAttachment(new \ArchiflowWSCard\Type\Attachment(null,null,null,null,null));
//$arrayOfKeyValues = new \ArchiflowWSCard\Type\ArrayOfKeyValueOfintArrayOfintty7Ep6D1(new \ArchiflowWSCard\Type\KeyValueOfintArrayOfintty7Ep6D1())
$mainDocument = new \ArchiflowWSCard\Type\Document("00000000-0000-0000-0000-000000000000",$base64DocStream,$fileMimeType,null,"TIFFG4",null,$fileExt,null,"00000000-0000-0000-0000-000000000000",$oggettoDocumento,0,false,false,false,false,false,false,0,$fileName,null,"TSTSRFormat",0,false);
//Assegnazione titolario (ClassificationFolder, tramite Classification ID
$classArray = new \ArchiflowWSCard\Type\ArrayOfClassificationFolder(new \ArchiflowWSCard\Type\ClassificationFolder($classFolderId,null));
//Craezione cardbundle (comprensivo dei dati di card).
$oCard = new \ArchiflowWSCard\Type\CardBundle(null,null,$attachmentArray,null,$classArray,null,$mainDocument,null);
//CardBunde deve estendere l'oggetto Card!
//Oggetto card da modificare con setter ed eventualmente costruttore vuoto
$arrayOfFields = new \ArchiflowWSCard\Type\ArrayOfField();
//$field = \ArchiflowWSCard\Type\Field::createLite($idTipoDoc, "IfDateDoc", date("d/m/Y"), null, null);
$arrayOfFields->setFieldArray(\ArchiflowWSCard\Type\Field::createLite(0, "IfDateDoc", date("d/m/Y"), null, false));
$arrayOfFields->setFieldArray(\ArchiflowWSCard\Type\Field::createLite(0, "IfKey11", "LETTERA", null, false));
$arrayOfFields->setFieldArray(\ArchiflowWSCard\Type\Field::createLite(0, "IfKey12", "SIRER", null, false));
$arrayOfFields->setFieldArray(\ArchiflowWSCard\Type\Field::createLite(0, "IfKey13", date("d/m/Y"), null, false));
$arrayOfFields->setFieldArray(\ArchiflowWSCard\Type\Field::createLite(0, "IfKey21", "MITTENTE", null, false));
$arrayOfFields->setFieldArray(\ArchiflowWSCard\Type\Field::createLite(0, "IfKey31", "RICERCA INNOVAZIONE", null, false));
//$arrayOfFields->setFieldArray(\ArchiflowWSCard\Type\Field::createLite(0, "IfKey32", "PINI", null, false));
$arrayOfFields->setFieldArray(\ArchiflowWSCard\Type\Field::createLite(0, "IfKey41", "RICERCA INNOVAZIONE", null, false));
$arrayOfFields->setFieldArray(\ArchiflowWSCard\Type\Field::createLite(0, "IfObj", $oggettoDocumento, null, false));
$oCard->setIndexes($arrayOfFields);
$oCard->setArchiveId($idarchivio);
$oCard->setDocumentTypeId($idTipoDoc);
$oCard->setHasDocument(true);
$oCard->setCardId("00000000-0000-0000-0000-000000000000");
$oCard->setCardProg(0);
$oCard->setDocStatus("DsNone");
$oCard->setHasAttachment(false);
$oCard->setHasAdditionalData(false);
$oCard->setHasComputerizedClassification(false);
$oCard->setHasComputerizedFolder(false);
$oCard->setHasFolder(false);
$oCard->setHasKeyVersions(false);
$oCard->setHasNotes(false);
$oCard->setHasPartialInvalidations(false);
//indexes --> (inserito sopra)
$oCard->setIsCC(false);
$oCard->setIsCurrUserVisDoc(false);
$oCard->setIsDocumentLocked(false);
$oCard->setIsReadOnly(false);
$oCard->setIsSigned(false);
$oCard->setIsSignedPdf(false);
$oCard->setIsSignedXml(false);
$oCard->setIsSorted(false);
$oCard->setIsStoredProtocol(false);
$oCard->setIsValid(false);
$oCard->setIsVisOnlyDoc(false);
$oCard->setIsWf(false);
$oCard->setIsWfReadOnly(false);
$oCard->setNumPages(0);
$oCard->setProcWF("PWFNothing");
$oCard->setStatus("Standard");
$oCard->setTimeStampFormat("TSTSRFormat");
$oCard->setUserIdModifying(0);
//$oCard->setprotocolmaindoctype


$response = $client->createCard(new \ArchiflowWSCard\Type\CreateCard($sessionObj->getSessionId(),new \ArchiflowWSCard\Type\InsertParameters($checkDupType,$IsVerifySignedFile,$bIsAutomaticProtocol,$bSorted,$bSyncWF,$bVisAllNote,$bVisOnlyDoc,$extCfg,$oCard,$strMessage,$strNote)));
$insertGUID = $response->getOCardRet()->getCardId();
$response = $client->getCardIndexes(new \ArchiflowWSCard\Type\GetCardIndexes($sessionObj->getSessionId(),$insertGUID));
$indexes = $response->getOIndexes();
$protocollo = "[NOT_FOUND]";
foreach ($indexes->getField() as $field){
    if ($field->getFieldId()=="IfReference"){
        $protocollo = $field->getFieldValue();
    }
}
die($protocollo); // Numero/Anno //ritorno le informazioni che mi interessano per il front-end.
