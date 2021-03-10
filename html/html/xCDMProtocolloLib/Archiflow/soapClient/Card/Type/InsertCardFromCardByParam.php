<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertCardFromCardByParam implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\InsertCardFromCardInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\InsertCardFromCardInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\InsertCardFromCardInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\InsertCardFromCardInput $paramIn
     * @return InsertCardFromCardByParam
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

