<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAccertamentoOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\AccertamentoOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\AccertamentoOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\AccertamentoOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\AccertamentoOut $item
     * @return ArrayOfAccertamentoOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

