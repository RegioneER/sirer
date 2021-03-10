<?php

namespace IrideWS;

use IrideWS\IrideWSClient;
use IrideWS\IrideWSClassmap;
use Phpro\SoapClient\ClientFactory as PhproClientFactory;
use Phpro\SoapClient\ClientBuilder;

class IrideWSClientFactory
{

    public static function factory(string $wsdl) : \IrideWS\IrideWSClient
    {
        $clientFactory = new PhproClientFactory(IrideWSClient::class);
        $clientBuilder = new ClientBuilder($clientFactory, $wsdl, []);
        $clientBuilder->withClassMaps(IrideWSClassmap::getCollection());

        return $clientBuilder->build();
    }


}

