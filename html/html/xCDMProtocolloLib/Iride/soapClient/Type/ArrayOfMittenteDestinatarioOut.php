<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfMittenteDestinatarioOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\MittenteDestinatarioOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\MittenteDestinatarioOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\MittenteDestinatarioOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\MittenteDestinatarioOut $item
     * @return ArrayOfMittenteDestinatarioOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

