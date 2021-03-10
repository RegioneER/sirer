<?php

namespace DocsuiteWS;

use DocsuiteWS\DocsuiteWSClient;
use DocsuiteWS\DocsuiteWSClassmap;
use Phpro\SoapClient\ClientFactory as PhproClientFactory;
use Phpro\SoapClient\ClientBuilder;
use Phpro\SoapClient\Soap\Handler\HttPlugHandle;
use Phpro\SoapClient\Wsdl\Provider\HttPlugWsdlProvider;
//use Phpro\SoapClient\Middleware\NtlmMiddleware;
use GuzzleHttp\Client as GuzzleClient;
use Http\Adapter\Guzzle6\Client as GuzzleAdapter;
use Http\Discovery\MessageFactoryDiscovery;

class DocsuiteWSClientFactory
{

    public static function factory(string $wsdl, string $azienda) : \DocsuiteWS\DocsuiteWSClient
    {
        $config = ['timeout' => 15];
        switch ($azienda){
            case "RE":
                $config = ['timeout' => 15, 'curl' => [
                    CURLOPT_HTTPAUTH => CURLAUTH_NTLM,
                    CURLOPT_USERPWD => 'app_sirer:D92SX8!"kdd02',
                ]];
                break;
            case "PC":
                $config = ['timeout' => 15, 'curl' => [
                    CURLOPT_HTTPAUTH => CURLAUTH_NTLM,
                    CURLOPT_USERPWD => 'SIRER:S1r3R178',
                ]];
                break;
        }

        $guzzle = new GuzzleClient($config);
        $adapter = new GuzzleAdapter($guzzle);
        $clientFactory = new PhproClientFactory(DocsuiteWSClient::class);
        $clientBuilder = new ClientBuilder($clientFactory, $wsdl, []);
        $clientBuilder->withHandler(HttPlugHandle::createForClient($adapter));
        //$clientBuilder->withWsdlProvider(HttPlugWsdlProvider::createForClient($adapter));
        $clientBuilder->withClassMaps(DocsuiteWSClassmap::getCollection());
        //$clientBuilder->addMiddleware(new NtlmMiddleware('app_sirer','D92SX8!"kdd02'));

        return $clientBuilder->build();
    }


}

