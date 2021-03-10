<?php

namespace ArchiflowWSFolder;

use ArchiflowWSFolder\ArchiFlowFolderClientClient;
use ArchiflowWSFolder\ArchiFlowFolderClientClassmap;
use Phpro\SoapClient\ClientFactory as PhproClientFactory;
use Phpro\SoapClient\ClientBuilder;

class ArchiFlowFolderClientClientFactory
{

    public static function factory(string $wsdl) : \ArchiflowWSFolder\ArchiFlowFolderClientClient
    {
        $clientFactory = new PhproClientFactory(ArchiFlowFolderClientClient::class);
        $clientBuilder = new ClientBuilder($clientFactory, $wsdl, []);
        $clientBuilder->withClassMaps(ArchiFlowFolderClientClassmap::getCollection());
        
        return $clientBuilder->build();
    }


}

