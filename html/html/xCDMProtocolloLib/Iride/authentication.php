<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 17/05/2019
 * Time: 11:24
 */

require_once __DIR__ . '/../vendor/autoload.php';

require_once __DIR__ . '/../utils.php';

require_once __DIR__ . '/soapClient/IrideWSClientFactory.php';
require_once __DIR__ . '/soapClient/IrideWSClient.php';
require_once __DIR__ . '/soapClient/IrideWSClassmap.php';

require_once __DIR__ . '/soapClient/Fascicolo/IrideWSFascicoloClientFactory.php';
require_once __DIR__ . '/soapClient/Fascicolo/IrideWSFascicoloClient.php';
require_once __DIR__ . '/soapClient/Fascicolo/IrideWSFascicoloClassmap.php';

//use IrideWS;
use IrideWS\IrideWSClientFactory;
use IrideWS\Type;
use IrideWS\IrideWSClient;
use IrideWS\IrideWSClassmap;

function getWSClient($createFolder=false){
    //http://sicraweb.irst.dom:58000/client/services/ProtocolloSoap?wsdl --> PRODUZIONE
    //https://wssirer.irst.emr.it/ -->TEST


    if($createFolder) {
        $client = IrideWFFascicolo\IrideWSFascicoloClientFactory::factory($wsdl = 'http://sicraweb.irst.dom:58000/client/services/DocWSFascicoliSoap?wsdl'); //---> CREAZIONE FASCICOLO ULTIMA MAIL 18.10.2019
    }
    else{
        $client = IrideWS\IrideWSClientFactory::factory($wsdl = 'http://sicraweb.irst.dom:58000/client/services/ProtocolloSoap?wsdl');
    }
    return $client;
}