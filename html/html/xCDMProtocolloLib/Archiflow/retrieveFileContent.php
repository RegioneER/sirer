<?php
ob_start();

/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

require_once __DIR__ . '/soapClient/Card/Type/SearchCriteria.php';
require_once __DIR__ . '/soapClient/Card/Type/SearchCards.php';
require_once __DIR__ . '/soapClient/Card/Type/SearchCardsResponse.php';
require_once __DIR__ . '/soapClient/Card/Type/GetCardIndexes.php';
require_once __DIR__ . '/soapClient/Card/Type/GetCardIndexesResponse.php';
require_once __DIR__ . '/soapClient/Card/Type/GetCardDocument.php';
require_once __DIR__ . '/soapClient/Card/Type/GetCardDocumentResponse.php';


require_once __DIR__ . '/soapClient/Card/Type/ArrayOfguid.php';
require_once __DIR__ . '/soapClient/Card/Type/ArrayOfArchive.php';
require_once __DIR__ . '/soapClient/Card/Type/ArrayOfField.php';
require_once __DIR__ . '/soapClient/Card/Type/Archive.php';
require_once __DIR__ . '/soapClient/Card/Type/DocumentType.php';
require_once __DIR__ . '/soapClient/Card/Type/Field.php';
require_once __DIR__ . '/soapClient/Card/Type/Document.php';
require_once __DIR__ . '/soapClient/Card/Type/Card.php';



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

$numero = "0053730";
$anno = 2019;
if ($argv && count($argv)>2) {
    $azienda = "RE";
    $numero = 53730; //326; //43;
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
if ($anno>99) {
    $anno = substr($anno, 2);
}

$sessionObj = generateLoginSession();

$client = getWSCardClient();

//Il GUID degli oggetti è un vero guid stringa 8-4-4-4-12 caratteri esadecimali (0-9a-f)

$AgrafSearchCriteria  = null;
$AnnotationValue = null;
$Archives = new \ArchiflowWSCard\Type\ArrayOfArchive(new \ArchiflowWSCard\Type\Archive(null,null,$idarchivio,null,null,null,null,null,null,null,null));
$CardProgFrom = null;
$CardProgTo = null;
$CardWithOutDoc = false;
$CheckSearchTooLong = null;
$ClassificationSearchCriteria=null;
$Context = "ScArchive"; //0->"ScArchive";
$ContextFullText = null;
$DocumentType = new \ArchiflowWSCard\Type\DocumentType(null,null,null,null,null,$idTipoDoc,null,null,null,null,null,null,null);
$DurationSearchCriteria = null;
$ExtendedDocumentType = null;
//Id Fields: -1/Unknown, 0/IfReference, 1/IfDateReg, 2/IfProtocol, 3/IfDateDoc, 4-8/IfKey11-15,
// 9-13/IfKey21-25, 14-18/IfKey31-35, 19-23/IFKey41-45, 24/IfObj,
$Fields = new \ArchiflowWSCard\Type\ArrayOfField();
$Fields->setField(new \ArchiflowWSCard\Type\Field(null,$idTipoDoc,null,null,null,"IfReference",null,"{$numero}/{$anno}","{$numero}/{$anno}",null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null));
$FilterFullText = null;
$FuzzySearchFullText = null;
$InvoiceDataTransmSearchCriteria = null;
$InvoiceSearchCriteria = null;
$IsForcedDate = null;
$IsForcedIndex = null;
$MainDoc = null;
$MaxFounded = null;
$MaxToWait = null;
$NoFormatKey = null;
$NoWordFullText = null;
$NotDisplayInvalidatedCards = true;
$OneWordFullText = null;
$OnlyConnectedUser = null;
$OrderByField = null;
$OrderType = null;
$PluralSearchFullText = null;
$RegisterOperation = null;
$SearchResult = null;
$SearchType = "StIndexes"; // 0-> StIndexes
$SortDescending = null;
$StringFullText = null;
$UseDefaultOptions = null;
$WordsFullText = null;

$searchCriteria = new \ArchiflowWSCard\Type\SearchCriteria($AgrafSearchCriteria, $AnnotationValue, $Archives, $CardProgFrom,
    $CardProgTo, $CardWithOutDoc, $CheckSearchTooLong, $ClassificationSearchCriteria, $Context, $ContextFullText,
    $DocumentType, $DurationSearchCriteria, $ExtendedDocumentType, $Fields, $FilterFullText, $FuzzySearchFullText,
    $InvoiceDataTransmSearchCriteria, $InvoiceSearchCriteria, $IsForcedDate, $IsForcedIndex, $MainDoc, $MaxFounded,
    $MaxToWait, $NoFormatKey, $NoWordFullText, $NotDisplayInvalidatedCards, $OneWordFullText, $OnlyConnectedUser,
    $OrderByField, $OrderType, $PluralSearchFullText, $RegisterOperation, $SearchResult, $SearchType, $SortDescending,
    $StringFullText, $UseDefaultOptions, $WordsFullText);
$response = $client->searchCards(new \ArchiflowWSCard\Type\SearchCards($sessionObj->getSessionId(),$searchCriteria));
$result = $response->getOCardIds();
$cardGUID = $result->getGuid()[0];
//var_dump($cardGUID);
$response = $client->getCardDocument(new \ArchiflowWSCard\Type\GetCardDocument($sessionObj->getSessionId(),$cardGUID, true));
$oDocument = $response->getODocument();
//print_r($oDocument);

$base64Documento = $oDocument->getContent();
$nomeDocumento = $oDocument->getOriginalFileName();
//$contentType = $oDocument->get
$dimensioneDocumento = $oDocument->getFileSize();
$estensioneDocumento = $oDocument->getDocumentExtension();

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

/*
$response = $client->getCardIndexes(new \ArchiflowWSCard\Type\GetCardIndexes($sessionObj->getSessionId(),$cardGUID));
$indexes = $response->getOIndexes()->getField();
print_r($indexes);
*/


/*
$cardId = "{$numero}/$anno";
$attachment = new \ArchiflowWSCard\Type\Attachment($cardId,1,"Documento prova Archiflow","",0);
$response = $client->attachDocument(new \ArchiflowWSCard\Type\AttachDocument($session->getSessionId(),$cardId,$attachment,false,false))
*/