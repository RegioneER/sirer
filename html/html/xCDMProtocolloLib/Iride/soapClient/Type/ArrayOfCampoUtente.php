<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfCampoUtente implements RequestInterface
{

    /**
     * @var \IrideWS\Type\CampoUtente
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\CampoUtente $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\CampoUtente
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\CampoUtente $item
     * @return ArrayOfCampoUtente
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

