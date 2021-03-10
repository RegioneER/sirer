<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 17/05/2019
 * Time: 11:24
 */

require_once __DIR__ . '/../vendor/autoload.php';

require_once __DIR__ . '/../utils.php';


require_once __DIR__ . '/soapClient/Login/ArchiFlowLoginClientClientFactory.php';
require_once __DIR__ . '/soapClient/Login/ArchiFlowLoginClientClient.php';
require_once __DIR__ . '/soapClient/Login/ArchiFlowLoginClientClassmap.php';
require_once __DIR__ . '/soapClient/Login/Type/ConnectionInfo.php';
require_once __DIR__ . '/soapClient/Login/Type/Login.php';
require_once __DIR__ . '/soapClient/Login/Type/LoginResponse.php';
require_once __DIR__ . '/soapClient/Login/Type/SessionInfo.php';
require_once __DIR__ . '/soapClient/Login/Type/ArrayOfOfficeChart.php';

require_once __DIR__ . '/soapClient/Card/ArchiFlowCardClientClientFactory.php';
require_once __DIR__ . '/soapClient/Card/ArchiFlowCardClientClient.php';
require_once __DIR__ . '/soapClient/Card/ArchiFlowCardClientClassmap.php';

require_once __DIR__ . '/soapClient/Folder/ArchiFlowFolderClientClientFactory.php';
require_once __DIR__ . '/soapClient/Folder/ArchiFlowFolderClientClient.php';
require_once __DIR__ . '/soapClient/Folder/ArchiFlowFolderClientClassmap.php';


function generateLoginSession(){
	$user = "SIRER";
	$pass = "r3r!sha9Ta";
	$domain = "SIAV";
    $client = getWSLoginClient();
    $ClientType = 0;
    $DateFormat = "dd/mm/yyyy";
    $ExecutiveOfficeCode = 0;
    $Language="Italian";
    $LoginTicket="";
    $Mode = "None";
    $NewPassword = "";
    $SecurityToken = "";
    $SystemDomain = $domain;
    $TokenSess = "";
    $UseSystemUser = "";
    $WorkflowDomain = $domain;
    $connInfo = new ArchiflowWSLogin\Type\ConnectionInfo($ClientType, $DateFormat, $ExecutiveOfficeCode, $Language, $LoginTicket, $Mode, $NewPassword, $SecurityToken, $SystemDomain, $TokenSess, $UseSystemUser, $WorkflowDomain);
    $response = $client->login(new ArchiflowWSLogin\Type\Login($user,$pass,$connInfo));
    $result = $response->getLoginResult();
    //print_r($result);
    $session = $response->getOSessionInfo();

    //print_r($session);
    return $session;
}

function getWSLoginClient(){
    $client = ArchiflowWSLogin\ArchiFlowLoginClientClientFactory::factory($wsdl = 'https://documentale.ausl.mo.it/ArchiflowService/Login.svc?wsdl');// PROD https://documentale.ausl.mo.it - PREP http://bgdocumenttest
    return $client;
}
function getWSCardClient(){
    $client = ArchiflowWSCard\ArchiFlowCardClientClientFactory::factory($wsdl = 'https://documentale.ausl.mo.it/ArchiflowService/Card.svc?wsdl');// PROD https://documentale.ausl.mo.it - PREP http://bgdocumenttest
    return $client;
}
function getWSFolderClient(){
    $client = ArchiflowWSCard\ArchiFlowFolderClientClientFactory::factory($wsdl = 'https://documentale.ausl.mo.it/ArchiflowService/Folder.svc?wsdl');// PROD https://documentale.ausl.mo.it - PREP http://bgdocumenttest
    return $client;
}
