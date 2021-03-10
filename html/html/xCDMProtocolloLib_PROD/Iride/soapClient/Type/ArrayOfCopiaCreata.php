<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfCopiaCreata implements RequestInterface
{

    /**
     * @var \IrideWS\Type\CopiaCreata
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\CopiaCreata $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\CopiaCreata
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\CopiaCreata $item
     * @return ArrayOfCopiaCreata
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

