<?php

use Phpro\SoapClient\CodeGenerator\Assembler;
use Phpro\SoapClient\CodeGenerator\Rules;
use Phpro\SoapClient\CodeGenerator\Config\Config;

return Config::create()
    ->setWsdl('http://bgdocumenttest/ArchiflowService/Card.svc?wsdl')
    ->setTypeDestination('Archiflow\soapClient\Card\Type')
    ->setTypeNamespace('ArchiflowWSCard\Type')
    ->setClientDestination('Archiflow\soapClient\Card')
    ->setClientName('ArchiFlowCardClientClient')
    ->setClientNamespace('ArchiflowWSCard')
    ->setClassMapDestination('Archiflow\soapClient\Card')
    ->setClassMapName('ArchiFlowCardClientClassmap')
    ->setClassMapNamespace('ArchiflowWSCard')
    ->addRule(new Rules\AssembleRule(new Assembler\GetterAssembler(new Assembler\GetterAssemblerOptions())))
    ->addRule(new Rules\AssembleRule(new Assembler\ImmutableSetterAssembler()))
    ->addRule(
        new Rules\TypenameMatchesRule(
            new Rules\MultiRule([
                new Rules\AssembleRule(new Assembler\RequestAssembler()),
                new Rules\AssembleRule(new Assembler\ConstructorAssembler(new Assembler\ConstructorAssemblerOptions())),
            ]),
            '/(?<!Response)$/i'
        )
    )
    ->addRule(
        new Rules\TypenameMatchesRule(
            new Rules\MultiRule([
                new Rules\AssembleRule(new Assembler\ResultAssembler()),
            ]),
            '/Response$/i'
        )
    )
;
