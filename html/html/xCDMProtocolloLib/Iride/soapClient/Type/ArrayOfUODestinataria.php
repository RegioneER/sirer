<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfUODestinataria implements RequestInterface
{

    /**
     * @var \IrideWS\Type\UODestinataria
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\UODestinataria $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\UODestinataria
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\UODestinataria $item
     * @return ArrayOfUODestinataria
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

