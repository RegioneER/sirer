<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfMittenteDestinatarioIn implements RequestInterface
{

    /**
     * @var \IrideWS\Type\MittenteDestinatarioIn
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\MittenteDestinatarioIn $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\MittenteDestinatarioIn
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\MittenteDestinatarioIn $item
     * @return ArrayOfMittenteDestinatarioIn
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

