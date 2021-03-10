<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocumentSignatureCertificateInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var string
     */
    private $CertificateIssuer = null;

    /**
     * @var string
     */
    private $CertificateSerialNumber = null;

    /**
     * @var \DateTime
     */
    private $CheckDateTime = null;

    /**
     * @var bool
     */
    private $GetCertificate = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var string $CertificateIssuer
     * @var string $CertificateSerialNumber
     * @var \DateTime $CheckDateTime
     * @var bool $GetCertificate
     */
    public function __construct($CardId, $CertificateIssuer, $CertificateSerialNumber, $CheckDateTime, $GetCertificate)
    {
        $this->CardId = $CardId;
        $this->CertificateIssuer = $CertificateIssuer;
        $this->CertificateSerialNumber = $CertificateSerialNumber;
        $this->CheckDateTime = $CheckDateTime;
        $this->GetCertificate = $GetCertificate;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $CardId
     * @return GetCardDocumentSignatureCertificateInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return string
     */
    public function getCertificateIssuer()
    {
        return $this->CertificateIssuer;
    }

    /**
     * @param string $CertificateIssuer
     * @return GetCardDocumentSignatureCertificateInput
     */
    public function withCertificateIssuer($CertificateIssuer)
    {
        $new = clone $this;
        $new->CertificateIssuer = $CertificateIssuer;

        return $new;
    }

    /**
     * @return string
     */
    public function getCertificateSerialNumber()
    {
        return $this->CertificateSerialNumber;
    }

    /**
     * @param string $CertificateSerialNumber
     * @return GetCardDocumentSignatureCertificateInput
     */
    public function withCertificateSerialNumber($CertificateSerialNumber)
    {
        $new = clone $this;
        $new->CertificateSerialNumber = $CertificateSerialNumber;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getCheckDateTime()
    {
        return $this->CheckDateTime;
    }

    /**
     * @param \DateTime $CheckDateTime
     * @return GetCardDocumentSignatureCertificateInput
     */
    public function withCheckDateTime($CheckDateTime)
    {
        $new = clone $this;
        $new->CheckDateTime = $CheckDateTime;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetCertificate()
    {
        return $this->GetCertificate;
    }

    /**
     * @param bool $GetCertificate
     * @return GetCardDocumentSignatureCertificateInput
     */
    public function withGetCertificate($GetCertificate)
    {
        $new = clone $this;
        $new->GetCertificate = $GetCertificate;

        return $new;
    }


}

