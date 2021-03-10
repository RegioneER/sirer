<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfTabellaUtente implements RequestInterface
{

    /**
     * @var \IrideWS\Type\TabellaUtente
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\TabellaUtente $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\TabellaUtente
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\TabellaUtente $item
     * @return ArrayOfTabellaUtente
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

