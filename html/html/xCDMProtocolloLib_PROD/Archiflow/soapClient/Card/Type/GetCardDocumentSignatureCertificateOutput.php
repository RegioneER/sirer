<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocumentSignatureCertificateOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CertificateInfo
     */
    private $CertificateInfo = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CertificateInfo $CertificateInfo
     */
    public function __construct($CertificateInfo)
    {
        $this->CertificateInfo = $CertificateInfo;
    }

    /**
     * @return \ArchiflowWSCard\Type\CertificateInfo
     */
    public function getCertificateInfo()
    {
        return $this->CertificateInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\CertificateInfo $CertificateInfo
     * @return GetCardDocumentSignatureCertificateOutput
     */
    public function withCertificateInfo($CertificateInfo)
    {
        $new = clone $this;
        $new->CertificateInfo = $CertificateInfo;

        return $new;
    }


}

