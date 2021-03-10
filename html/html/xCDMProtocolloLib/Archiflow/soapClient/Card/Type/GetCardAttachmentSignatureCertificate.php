<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardAttachmentSignatureCertificate implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardAttachmentSignatureCertificateInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\GetCardAttachmentSignatureCertificateInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\GetCardAttachmentSignatureCertificateInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardAttachmentSignatureCertificateInput $paramIn
     * @return GetCardAttachmentSignatureCertificate
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

