<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfRecordUtente implements RequestInterface
{

    /**
     * @var \IrideWS\Type\RecordUtente
     */
    private $item = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\RecordUtente $item
     */
    public function __construct($item)
    {
        $this->item = $item;
    }

    /**
     * @return \IrideWS\Type\RecordUtente
     */
    public function getItem()
    {
        return $this->item;
    }

    /**
     * @param \IrideWS\Type\RecordUtente $item
     * @return ArrayOfRecordUtente
     */
    public function withItem($item)
    {
        $new = clone $this;
        $new->item = $item;

        return $new;
    }


}

