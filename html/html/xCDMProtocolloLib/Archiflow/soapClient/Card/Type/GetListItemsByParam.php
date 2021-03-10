<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetListItemsByParam implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetListItemsInput
     */
    private $getListItemsInput = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\GetListItemsInput $getListItemsInput
     */
    public function __construct($getListItemsInput)
    {
        $this->getListItemsInput = $getListItemsInput;
    }

    /**
     * @return \ArchiflowWSCard\Type\GetListItemsInput
     */
    public function getGetListItemsInput()
    {
        return $this->getListItemsInput;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetListItemsInput $getListItemsInput
     * @return GetListItemsByParam
     */
    public function withGetListItemsInput($getListItemsInput)
    {
        $new = clone $this;
        $new->getListItemsInput = $getListItemsInput;

        return $new;
    }


}

