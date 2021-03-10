<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfCentriDiCostoOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\CentriDiCostoOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\CentriDiCostoOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\CentriDiCostoOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\CentriDiCostoOut $item
     * @return ArrayOfCentriDiCostoOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

