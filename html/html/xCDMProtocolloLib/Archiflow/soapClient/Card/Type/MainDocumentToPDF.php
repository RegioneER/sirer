<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class MainDocumentToPDF implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\MainDocumentToPDFInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\MainDocumentToPDFInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\MainDocumentToPDFInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\MainDocumentToPDFInput $paramIn
     * @return MainDocumentToPDF
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

