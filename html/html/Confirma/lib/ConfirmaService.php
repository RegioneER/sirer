<?php
include_once "addAuthenticationTokenRequest.php";
include_once "addAuthenticationTokenResponse.php";
include_once "addTemplateRequest.php";
include_once "addTemplateResponse.php";
include_once "addTransactionRequest.php";
include_once "addTransactionResponse.php";
include_once "AuthenticationToken.php";
include_once "Description.php";
include_once "DescriptionMimeType.php";
include_once "getAvailableAuthenticationTokensResponse.php";
include_once "getAvailableTemplatesResponse.php";
include_once "getAvailableTransactionsResponse.php";
include_once "getSignedTransactionRequest.php";
include_once "getSignedTransactionResponse.php";
include_once "getTransactionStatusRequest.php";
include_once "getTransactionStatusResponse.php";
include_once "PresentationType.php";
include_once "removeAuthenticationTokenRequest.php";
include_once "removeAuthenticationTokenResponse.php";
include_once "removeTemplateRequest.php";
include_once "removeTemplateResponse.php";
include_once "removeTransactionRequest.php";
include_once "removeTransactionResponse.php";
include_once "SignedDocument.php";
include_once "SOAPMessage.php";
include_once "ToSignDocument.php";
include_once "TransactionInformation.php";
include_once "TransactionStatus.php";

class ConfirmaService {

    public $client;

    function typecast($old_object, $new_classname) {
        if(class_exists($new_classname)) {
            $old_serialized_prefix  = "O:".strlen(get_class($old_object));
            $old_serialized_prefix .= ":\"".get_class($old_object)."\":";
            $old_serialized_object = serialize($old_object);
            $new_serialized_object = 'O:'.strlen($new_classname).':"'.$new_classname . '":';
            $new_serialized_object .= substr($old_serialized_object,strlen($old_serialized_prefix));
            return unserialize($new_serialized_object);
        }
        else
            return false;
    }

    public static function getApplet($tid, $risposta){
       /* return "
			<applet code=\"cin.confirma.applet.ConfirmaAppletLoader\"
			archive=\"https://ades.cineca.it/ConfirmaSuite/applets/ConfirmaApplet.jar,https://ades.cineca.it/ConfirmaSuite/applets/lib/jks.jar\"
			height=\"130\" width=\"300\">
			<param name=\"TRANSACTION_ID\" value=\"{$tid}\">
			<param name=\"SERVICE_URL\" value=\"https://ades.cineca.it/SissService/http-restricted/MainService\">
			<param name=\"JAVA_5_LIBS_URL\" value=\"http://ades.cineca.it/ConfirmaSuite/applets/lib/java_1-5_to_1-6_libs.jar\">
			<param name=\"AUTHENTICATION_METHOD\" value=\"USERNAME-PASSWORD\">
			<param name=\"HTTP_USERNAME\" value=\"{$tid}\">
			<param name=\"HTTP_PASSWORD\" value=\"{$tid}\">
			<param name=\"TOKEN_CONFIGURATION_URL\" value=\"http://ades.cineca.it/ConfirmaSuite/token-resources/configuration/DefaultTokenEnvironment.jsp\">
			<param name=\"REDIRECT_URL\" value=\"{$risposta}?Signed=OK&TID={$tid}\" />
			<param name=\"ERROR_URL\" value=\"{$risposta}?Signed=error&TID={$tid}\" />
			<param name=\"CANCEL_URL\"	value=\"{$risposta}?Signed=cancel&TID={$tid}\" />
			<param name=\"WINDOW_WIDTH\" value=\"800\">
			<param name=\"WINDOW_HEIGHT\" value=\"600\">
		</applet>";*/
		
		
		 return "<applet code=\"cin.confirma.applet.ConfirmaAppletLoader\" archive=\"https://confirma.prod.cineca.it/ConfirmaServiceResources/applets/confirma-applet.jar,https://confirma.prod.cineca.it/ConfirmaServiceResources/applets/confirma-applet-tks.jar\" height=\"130\" width=\"300\">
                  <param name=\"TRANSACTION_ID\" value=\"{$tid}\">
                  <param name=\"SERVICE_URL\" value=\"https://confirma.prod.cineca.it/ConfirmaService4/http-restricted/MainService\">
                  <param name=\"AUTHENTICATION_METHOD\" value=\"USERNAME-PASSWORD\">
                  <param name=\"HTTP_USERNAME\" value=\"{$tid}\">
                  <param name=\"HTTP_PASSWORD\" value=\"{$tid}\">
                  <param name=\"REMOTE_LOGGER_URL\" value=\"https://confirma.prod.cineca.it/ConfirmaRemoteLogger/http-restricted/RemoteLoggingService\" />
                  <param name=\"REMOTE_LOGGER_USERNAME\" value=\"{$tid}\" />
                  <param name=\"REMOTE_LOGGER_PASSWORD\" value=\"{$tid}\" /> 
                  <param name=\"TOKEN_CONFIGURATION_URL\" value=\"https://confirma.prod.cineca.it/ConfirmaTokenManager/\">
                  <param name=\"REDIRECT_URL\" value=\"{$risposta}?Signed=OK&TID={$tid}\" />
			      <param name=\"ERROR_URL\" value=\"{$risposta}?Signed=error&TID={$tid}\" />
			      <param name=\"CANCEL_URL\" value=\"{$risposta}?Signed=cancel&TID={$tid}\" />
			      <param name=\"WINDOW_WIDTH\" value=\"800\">
                  <param name=\"WINDOW_HEIGHT\" value=\"600\">		 
		</applet>";
		
    }

    public function __construct($username=null, $password=null, $wsdl=null){
       /* if ($username==null) $username="SissService";
        if ($password==null) $password="aq9nebjey6";
        if ($wsdl==null) $wsdl="https://ades.cineca.it/ConfirmaServiceWebInterface/http-restricted/InterfaceWebService?wsdl";
*/
     	if ($username==null) $username="confirmaservice4";
        if ($password==null) $password="aq9nebjey6";
        if ($wsdl==null) $wsdl="https://confirma.prod.cineca.it/ConfirmaServiceWebInterface/http-restricted/InterfaceWebService?wsdl";

        $options =  array(
            'exceptions' => true,
            'cache_wsdl' => WSDL_CACHE_NONE,
            'login' => $username,
            'password' => $password,
        );
        $this->client = new SoapClient($wsdl, $options);
    }

    public function createSingleDocumentTransaction($tid,$codFisc=null,ToSignDocument $doc=null){
        $checkTidExistReq=new getTransactionStatusRequest();
        $checkTidExistReq->transactionID=$tid;
        $resp=$this->getTransactionStatus($checkTidExistReq);
        if ($resp->status=="NOT_EXISTS"){
            $txRequest=new addTransactionRequest();
            $txRequest->authenticationToken=new AuthenticationToken();
            $txRequest->authenticationToken->tokenUsername=$tid;
            $txRequest->authenticationToken->tokenPassword=$tid;
            $txRequest->transactionID=$tid;
            $txRequest->authUserID=".*";
            $txRequest->signUserID=$codFisc;
            $txRequest->descriptionMimeType=null;
            $txRequest->descriptionValue=null;
            $txRequest->presentationType=PresentationType::_SINGLE_DOCUMENT_VIEW;
            $txRequest->toSignDocuments[]=$doc;
            $this->addTransaction($txRequest);
            return true;
        }else {
            return false;
        }
    }

    public function deleteTransaction($tid){
        $txStatusReq=new getTransactionStatusRequest();
        $txStatusReq->transactionID=$tid;
        $resp=$this->getTransactionStatus($txStatusReq);
        if ($resp->status!="NOT_EXISTS"){
            $delTxRq=new removeTransactionRequest();
            $delTxRq->transactionID=$tid;
            $authenticationToken=new AuthenticationToken();
            $authenticationToken->tokenUsername=$tid;
            $authenticationToken->tokenPassword=$tid;
            $delTxRq->authenticationTokenUsername=$authenticationToken->tokenUsername;
            $resp=$this->removeTransaction($delTxRq);
            return true;
        }
        return true;
    }

    public function getSigleTxSignedDocument($tid){
        $txStatusReq=new getTransactionStatusRequest();
        $txStatusReq->transactionID=$tid;
        $resp=$this->getTransactionStatus($txStatusReq);
        if ($resp->status=="PROCESSED"){
            $txReq=new getSignedTransactionRequest();
            $txReq->transactionID=$tid;
            $resp=$this->getSignedTransaction($txReq);
            return $resp->signedDocuments->signature;
        }
    }

    public function addTemplate(addTemplateRequest $request){
        return self::typecast($this->client->addTemplate($request), "addTemplateResponse");
    }

    public function removeTemplate(removeTemplateRequest $request){
        return self::typecast($this->removeTemplate($request), "removeTemplateResponse");
    }
    public function addAuthenticationToken(addAuthenticationTokenRequest $request){
        return self::typecast($this->client->addAuthenticationToken($request), "addAuthenticationTokenResponse");
    }
    public function removeAuthenticationToken(removeAuthenticationTokenRequest $request){
        return self::typecast($this->client->removeAuthenticationToken($request),"removeAuthenticationTokenResponse");
    }
    public function addTransaction(addTransactionRequest $request){
        return self::typecast($this->client->addTransaction($request), "addTransactionResponse");
    }

    public function removeTransaction(removeTransactionRequest $request){
        return self::typecast($this->client->removeTransaction($request), "removeTransactionResponse");
    }

    public function getSignedTransaction(getSignedTransactionRequest $request){
        return self::typecast($this->client->getSignedTransaction($request),"getSignedTransactionResponse");
    }
    public function getTransactionStatus(getTransactionStatusRequest $request){
            return self::typecast($this->client->getTransactionStatus($request), "getTransactionStatusResponse");
    }
    public function getAvailableTransactions($request){
            return self::typecast($this->client->getAvailableTransactions($request), "getAvailableTransactionsResponse");
    }
    public function getAvailableTemplates(getAvailableTemplatesRequest $request){

            return self::typecast($this->client->getAvailableTemplates($request), "getAvailableTemplatesResponse");
    }

    public function getAvailableAuthenticationTokens(getAvailableAuthenticationTokensRequest $request){
            return self::typecast($this->client->getAvailableAuthenticationTokens($request), "getAvailableAuthenticationTokensResponse");
    }

}