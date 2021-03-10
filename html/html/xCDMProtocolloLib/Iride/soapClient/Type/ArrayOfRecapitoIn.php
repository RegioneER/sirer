<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfRecapitoIn implements RequestInterface
{

    /**
     * @var \IrideWS\Type\RecapitoIn
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\RecapitoIn $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\RecapitoIn
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\RecapitoIn $item
     * @return ArrayOfRecapitoIn
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

