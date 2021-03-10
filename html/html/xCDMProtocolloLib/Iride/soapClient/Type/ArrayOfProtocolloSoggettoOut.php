<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfProtocolloSoggettoOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\ProtocolloSoggettoOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\ProtocolloSoggettoOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\ProtocolloSoggettoOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\ProtocolloSoggettoOut $item
     * @return ArrayOfProtocolloSoggettoOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

