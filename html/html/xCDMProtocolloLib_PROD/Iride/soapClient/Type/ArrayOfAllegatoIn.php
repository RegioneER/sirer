<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAllegatoIn implements RequestInterface
{

    /**
     * @var \IrideWS\Type\AllegatoIn
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\AllegatoIn $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\AllegatoIn
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\AllegatoIn $item
     * @return ArrayOfAllegatoIn
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

