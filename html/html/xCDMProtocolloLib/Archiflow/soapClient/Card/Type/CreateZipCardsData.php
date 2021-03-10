<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreateZipCardsData implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CreateZipCardsDataInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CreateZipCardsDataInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\CreateZipCardsDataInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\CreateZipCardsDataInput $paramIn
     * @return CreateZipCardsData
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

