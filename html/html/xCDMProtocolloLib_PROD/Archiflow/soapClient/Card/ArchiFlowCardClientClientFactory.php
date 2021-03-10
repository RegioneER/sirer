<?php

namespace ArchiflowWSCard;

use ArchiflowWSCard\ArchiFlowCardClientClient;
use ArchiflowWSCard\ArchiFlowCardClientClassmap;
use Phpro\SoapClient\ClientFactory as PhproClientFactory;
use Phpro\SoapClient\ClientBuilder;
use Phpro\SoapClient\Soap\Handler\HttPlugHandle;
use Phpro\SoapClient\Middleware\RemoveEmptyNodesMiddleware;
use GuzzleHttp\Client as GuzzleClient;
use Http\Adapter\Guzzle6\Client as GuzzleAdapter;
use Http\Discovery\MessageFactoryDiscovery;


class ArchiFlowCardClientClientFactory
{

    public static function factory(string $wsdl) : \ArchiflowWSCard\ArchiFlowCardClientClient
    {
        $config = ['timeout' => 5];
        $guzzle = new GuzzleClient($config);
		$adapter = new GuzzleAdapter($guzzle);
        $clientFactory = new PhproClientFactory(ArchiFlowCardClientClient::class);
        $clientBuilder = new ClientBuilder($clientFactory, $wsdl, []);
        $clientBuilder->withHandler(HttPlugHandle::createForClient($adapter));
        $clientBuilder->withClassMaps(ArchiFlowCardClientClassmap::getCollection());
        $clientBuilder->addMiddleware(new RemoveEmptyNodesMiddleware());
        
        return $clientBuilder->build();
    }


}

