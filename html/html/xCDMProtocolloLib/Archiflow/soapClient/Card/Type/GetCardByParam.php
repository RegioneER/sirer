<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardByParam implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\GetCardInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\GetCardInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardInput $paramIn
     * @return GetCardByParam
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

