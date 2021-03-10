<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetGraphometricSignatureTemplate implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetGraphometricSignatureTemplateInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\GetGraphometricSignatureTemplateInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\GetGraphometricSignatureTemplateInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetGraphometricSignatureTemplateInput $paramIn
     * @return GetGraphometricSignatureTemplate
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

