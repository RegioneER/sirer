<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InserisciDocumentoEAnagrafiche implements RequestInterface
{

    /**
     * @var \IrideWS\Type\ProtocolloIn
     */
    private $ProtoIn = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\ProtocolloIn $ProtoIn
     */
    public function __construct($ProtoIn)
    {
        $this->ProtoIn = $ProtoIn;
    }

    /**
     * @return \IrideWS\Type\ProtocolloIn
     */
    public function getProtoIn()
    {
        return $this->ProtoIn;
    }

    /**
     * @param \IrideWS\Type\ProtocolloIn $ProtoIn
     * @return InserisciDocumentoEAnagrafiche
     */
    public function withProtoIn($ProtoIn)
    {
        $new = clone $this;
        $new->ProtoIn = $ProtoIn;

        return $new;
    }


}

