<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfRegistroOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\RegistroOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\RegistroOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\RegistroOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\RegistroOut $item
     * @return ArrayOfRegistroOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

