<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAllegatoInseritoOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\AllegatoInseritoOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\AllegatoInseritoOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\AllegatoInseritoOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\AllegatoInseritoOut $item
     * @return ArrayOfAllegatoInseritoOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

