<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardsVisibilityOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SendObject
     */
    private $SendObj = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SendObject $SendObj
     */
    public function __construct($SendObj)
    {
        $this->SendObj = $SendObj;
    }

    /**
     * @return \ArchiflowWSCard\Type\SendObject
     */
    public function getSendObj()
    {
        return $this->SendObj;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendObject $SendObj
     * @return GetCardsVisibilityOutput
     */
    public function withSendObj($SendObj)
    {
        $new = clone $this;
        $new->SendObj = $SendObj;

        return $new;
    }


}

