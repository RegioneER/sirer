<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfRegistroAssegnatoOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\RegistroAssegnatoOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\RegistroAssegnatoOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\RegistroAssegnatoOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\RegistroAssegnatoOut $item
     * @return ArrayOfRegistroAssegnatoOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

