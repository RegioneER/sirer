<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardAttachmentSignatureCertificateInput implements RequestInterface
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
     * @var int
     */
    private $Code = null;

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
     * @var int $Code
     * @var bool $GetCertificate
     */
    public function __construct($CardId, $CertificateIssuer, $CertificateSerialNumber, $CheckDateTime, $Code, $GetCertificate)
    {
        $this->CardId = $CardId;
        $this->CertificateIssuer = $CertificateIssuer;
        $this->CertificateSerialNumber = $CertificateSerialNumber;
        $this->CheckDateTime = $CheckDateTime;
        $this->Code = $Code;
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
     * @return GetCardAttachmentSignatureCertificateInput
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
     * @return GetCardAttachmentSignatureCertificateInput
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
     * @return GetCardAttachmentSignatureCertificateInput
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
     * @return GetCardAttachmentSignatureCertificateInput
     */
    public function withCheckDateTime($CheckDateTime)
    {
        $new = clone $this;
        $new->CheckDateTime = $CheckDateTime;

        return $new;
    }

    /**
     * @return int
     */
    public function getCode()
    {
        return $this->Code;
    }

    /**
     * @param int $Code
     * @return GetCardAttachmentSignatureCertificateInput
     */
    public function withCode($Code)
    {
        $new = clone $this;
        $new->Code = $Code;

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
     * @return GetCardAttachmentSignatureCertificateInput
     */
    public function withGetCertificate($GetCertificate)
    {
        $new = clone $this;
        $new->GetCertificate = $GetCertificate;

        return $new;
    }


}

