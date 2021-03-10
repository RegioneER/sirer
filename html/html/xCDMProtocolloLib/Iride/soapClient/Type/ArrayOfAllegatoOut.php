<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAllegatoOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\AllegatoOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\AllegatoOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\AllegatoOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\AllegatoOut $item
     * @return ArrayOfAllegatoOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

