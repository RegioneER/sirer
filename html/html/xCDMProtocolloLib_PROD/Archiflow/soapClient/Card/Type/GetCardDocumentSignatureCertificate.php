<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocumentSignatureCertificate implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardDocumentSignatureCertificateInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\GetCardDocumentSignatureCertificateInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\GetCardDocumentSignatureCertificateInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardDocumentSignatureCertificateInput $paramIn
     * @return GetCardDocumentSignatureCertificate
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

