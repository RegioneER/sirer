<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SignatureInfo implements RequestInterface
{

    /**
     * @var string
     */
    private $CertificateIssuer = null;

    /**
     * @var string
     */
    private $CertificateSerialNumber = null;

    /**
     * @var string
     */
    private $ComplianceInfo = null;

    /**
     * @var bool
     */
    private $Compliant = null;

    /**
     * @var string
     */
    private $Hash = null;

    /**
     * @var string
     */
    private $SignerName = null;

    /**
     * @var \DateTime
     */
    private $SigningTimeUTC = null;

    /**
     * @var bool
     */
    private $Valid = null;

    /**
     * @var \DateTime
     */
    private $ValidityFrom = null;

    /**
     * @var \DateTime
     */
    private $ValidityTo = null;

    /**
     * Constructor
     *
     * @var string $CertificateIssuer
     * @var string $CertificateSerialNumber
     * @var string $ComplianceInfo
     * @var bool $Compliant
     * @var string $Hash
     * @var string $SignerName
     * @var \DateTime $SigningTimeUTC
     * @var bool $Valid
     * @var \DateTime $ValidityFrom
     * @var \DateTime $ValidityTo
     */
    public function __construct($CertificateIssuer, $CertificateSerialNumber, $ComplianceInfo, $Compliant, $Hash, $SignerName, $SigningTimeUTC, $Valid, $ValidityFrom, $ValidityTo)
    {
        $this->CertificateIssuer = $CertificateIssuer;
        $this->CertificateSerialNumber = $CertificateSerialNumber;
        $this->ComplianceInfo = $ComplianceInfo;
        $this->Compliant = $Compliant;
        $this->Hash = $Hash;
        $this->SignerName = $SignerName;
        $this->SigningTimeUTC = $SigningTimeUTC;
        $this->Valid = $Valid;
        $this->ValidityFrom = $ValidityFrom;
        $this->ValidityTo = $ValidityTo;
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
     * @return SignatureInfo
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
     * @return SignatureInfo
     */
    public function withCertificateSerialNumber($CertificateSerialNumber)
    {
        $new = clone $this;
        $new->CertificateSerialNumber = $CertificateSerialNumber;

        return $new;
    }

    /**
     * @return string
     */
    public function getComplianceInfo()
    {
        return $this->ComplianceInfo;
    }

    /**
     * @param string $ComplianceInfo
     * @return SignatureInfo
     */
    public function withComplianceInfo($ComplianceInfo)
    {
        $new = clone $this;
        $new->ComplianceInfo = $ComplianceInfo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCompliant()
    {
        return $this->Compliant;
    }

    /**
     * @param bool $Compliant
     * @return SignatureInfo
     */
    public function withCompliant($Compliant)
    {
        $new = clone $this;
        $new->Compliant = $Compliant;

        return $new;
    }

    /**
     * @return string
     */
    public function getHash()
    {
        return $this->Hash;
    }

    /**
     * @param string $Hash
     * @return SignatureInfo
     */
    public function withHash($Hash)
    {
        $new = clone $this;
        $new->Hash = $Hash;

        return $new;
    }

    /**
     * @return string
     */
    public function getSignerName()
    {
        return $this->SignerName;
    }

    /**
     * @param string $SignerName
     * @return SignatureInfo
     */
    public function withSignerName($SignerName)
    {
        $new = clone $this;
        $new->SignerName = $SignerName;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getSigningTimeUTC()
    {
        return $this->SigningTimeUTC;
    }

    /**
     * @param \DateTime $SigningTimeUTC
     * @return SignatureInfo
     */
    public function withSigningTimeUTC($SigningTimeUTC)
    {
        $new = clone $this;
        $new->SigningTimeUTC = $SigningTimeUTC;

        return $new;
    }

    /**
     * @return bool
     */
    public function getValid()
    {
        return $this->Valid;
    }

    /**
     * @param bool $Valid
     * @return SignatureInfo
     */
    public function withValid($Valid)
    {
        $new = clone $this;
        $new->Valid = $Valid;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getValidityFrom()
    {
        return $this->ValidityFrom;
    }

    /**
     * @param \DateTime $ValidityFrom
     * @return SignatureInfo
     */
    public function withValidityFrom($ValidityFrom)
    {
        $new = clone $this;
        $new->ValidityFrom = $ValidityFrom;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getValidityTo()
    {
        return $this->ValidityTo;
    }

    /**
     * @param \DateTime $ValidityTo
     * @return SignatureInfo
     */
    public function withValidityTo($ValidityTo)
    {
        $new = clone $this;
        $new->ValidityTo = $ValidityTo;

        return $new;
    }


}

