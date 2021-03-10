<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 17/05/2019
 * Time: 11:24
 */

require_once __DIR__ . '/../vendor/autoload.php';

require_once __DIR__ . '/../utils.php';

require_once 'soapClient/DocsuiteWSClassmap.php';
require_once 'soapClient/DocsuiteWSClientFactory.php';
require_once 'soapClient/DocsuiteWSClient.php';

//Autenticazione con basic authentication (anche per recuperare wsdl)
//app_sirer
//D92SX8!"kdd02

function getWSClientRE(){
    $client = \DocsuiteWS\DocsuiteWSClientFactory::factory($wsdl = __DIR__ . '/wsdl/RE/WSProt.svc.wsdl', $azienda = "RE");
    return $client;
}

function getWSClientPC(){
    $client = \DocsuiteWS\DocsuiteWSClientFactory::factory($wsdl =  __DIR__ . '/wsdl/PC/WSProt.svc.wsdl', $azienda = "PC");
    return $client;
}
