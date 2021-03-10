<?php

use Phpro\SoapClient\CodeGenerator\Assembler;
use Phpro\SoapClient\CodeGenerator\Rules;
use Phpro\SoapClient\CodeGenerator\Config\Config;

return Config::create()
    ->setWsdl('C:\app\xCDMProtocolloLib\Docsuite\wsdl\WSProt.svc.wsdl')
    ->setTypeDestination('Docsuite\soapClient\Type')
    ->setTypeNamespace('DocsuiteWS\Type')
    ->setClientDestination('Docsuite\soapClient')
    ->setClientName('DocsuiteWSClient')
    ->setClientNamespace('DocsuiteWS')
    ->setClassMapDestination('Docsuite\soapClient')
    ->setClassMapName('DocsuiteWSClassmap')
    ->setClassMapNamespace('DocsuiteWS')
    ->addRule(new Rules\AssembleRule(new Assembler\GetterAssembler(new Assembler\GetterAssemblerOptions())))
    ->addRule(new Rules\AssembleRule(new Assembler\ImmutableSetterAssembler()))
    ->addRule(
        new Rules\TypenameMatchesRule(
            new Rules\MultiRule([
                new Rules\AssembleRule(new Assembler\RequestAssembler()),
                new Rules\AssembleRule(new Assembler\ConstructorAssembler(new Assembler\ConstructorAssemblerOptions())),
            ]),
            '/InputMessage$/i'
        )
    )
    ->addRule(
        new Rules\TypenameMatchesRule(
            new Rules\MultiRule([
                new Rules\AssembleRule(new Assembler\ResultAssembler()),
            ]),
            '/OutputMessage$/i'
        )
    )
;
