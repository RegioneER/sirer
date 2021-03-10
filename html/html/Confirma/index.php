<?php
/**
 * Created by JetBrains PhpStorm.
 * User: Carlo
 * Date: 14/05/13
 * Time: 9.13
 * To change this template use File | Settings | File Templates.
 */

include_once "lib/ConfirmaService.php";

$service=new ConfirmaService();

if (isset($_GET['create'])){
    $doc=new ToSignDocument("DocumentoDiProva.pdf","Documento di prova",DescriptionMimeType::_value1);
    $tid=$_GET['create'];
    $cf="DLSGRG83C13L750P";
    $create=$service->createSingleDocumentTransaction($tid, $cf, $doc);
    if ($create){
        echo "Transazione $tid creata";
    }else {
        echo "Transazione $tid gi&agrave; esistente";
    }
}

if (isset($_GET['getStatus'])){
    $checkTidExistReq=new getTransactionStatusRequest();
    $checkTidExistReq->transactionID=$_GET['getStatus'];
    var_dump($service->getTransactionStatus($checkTidExistReq));
}

if (isset($_GET['sign'])){
    $tid=$_GET['sign'];
    $applet=ConfirmaService::getApplet($tid,$_GET['risposta']);
    echo $applet;
}
if (isset($_GET['Signed'])){
    echo "Risultato {$_GET['Signed']} per transazione {$_GET['TID']}";
}

if (isset($_GET['delete'])){
	// commentato per verificare il funzionamento del sistema (12/01/2015)
    //$service->deleteTransaction($_GET['delete']);
}

if (isset($_GET["getSignedDoc"])){
    header("Cache-Control: public");
    header("Content-Description: File Transfer");
    header("Content-Disposition: attachment; filename= " . $_GET["getSignedDoc"].".pdf.p7m");
    header("Content-Transfer-Encoding: binary");
    $signedDocument=$service->getSigleTxSignedDocument($_GET["getSignedDoc"]);
    echo $signedDocument;
}

?>
