<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfProtocolloGeneratoOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\ProtocolloGeneratoOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\ProtocolloGeneratoOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\ProtocolloGeneratoOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\ProtocolloGeneratoOut $item
     * @return ArrayOfProtocolloGeneratoOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

