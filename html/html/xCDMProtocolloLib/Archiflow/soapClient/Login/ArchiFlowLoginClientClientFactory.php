<?php

namespace ArchiflowWSLogin;

use ArchiflowWSLogin\ArchiFlowLoginClientClient;
use ArchiflowWSLogin\ArchiFlowLoginClientClassmap;
use Phpro\SoapClient\ClientFactory as PhproClientFactory;
use Phpro\SoapClient\ClientBuilder;

class ArchiFlowLoginClientClientFactory
{

    public static function factory(string $wsdl) : \ArchiflowWSLogin\ArchiFlowLoginClientClient
    {
        $clientFactory = new PhproClientFactory(ArchiFlowLoginClientClient::class);
        $clientBuilder = new ClientBuilder($clientFactory, $wsdl, []);
        $clientBuilder->withClassMaps(ArchiFlowLoginClientClassmap::getCollection());
        
        return $clientBuilder->build();
    }


}

