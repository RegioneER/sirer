<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocumentSignaturesInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardDocumentSignaturesInfoInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\GetCardDocumentSignaturesInfoInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\GetCardDocumentSignaturesInfoInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardDocumentSignaturesInfoInput $paramIn
     * @return GetCardDocumentSignaturesInfo
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

