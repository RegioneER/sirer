<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfImpegnoOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\ImpegnoOut
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\ImpegnoOut $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\ImpegnoOut
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\ImpegnoOut $item
     * @return ArrayOfImpegnoOut
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

