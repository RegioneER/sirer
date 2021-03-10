<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfCorrispondenteOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\CorrispondenteOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\CorrispondenteOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\CorrispondenteOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\CorrispondenteOut $item
     * @return ArrayOfCorrispondenteOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

