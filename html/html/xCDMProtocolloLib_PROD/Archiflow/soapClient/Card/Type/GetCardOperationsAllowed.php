<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardOperationsAllowed implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CardOperationsInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CardOperationsInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardOperationsInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardOperationsInput $paramIn
     * @return GetCardOperationsAllowed
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

