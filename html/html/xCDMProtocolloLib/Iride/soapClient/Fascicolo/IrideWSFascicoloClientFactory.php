<?php

namespace IrideWFFascicolo;

use IrideWFFascicolo\IrideWSFascicoloClient;
use IrideWFFascicolo\IrideWSFascicoloClassmap;
use Phpro\SoapClient\ClientFactory as PhproClientFactory;
use Phpro\SoapClient\ClientBuilder;

class IrideWSFascicoloClientFactory
{

    public static function factory(string $wsdl) : \IrideWFFascicolo\IrideWSFascicoloClient
    {
        $clientFactory = new PhproClientFactory(IrideWSFascicoloClient::class);
        $clientBuilder = new ClientBuilder($clientFactory, $wsdl, []);
        $clientBuilder->withClassMaps(IrideWSFascicoloClassmap::getCollection());
        
        return $clientBuilder->build();
    }


}

