<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CertificateInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAttributeType
     */
    private $Attributes = null;

    /**
     * @var \ArchiflowWSCard\Type\Base64Binary
     */
    private $Certificate = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $Errors = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAttributeType
     */
    private $Extensions = null;

    /**
     * @var string
     */
    private $Issuer = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAttributeType
     */
    private $KeyUsage = null;

    /**
     * @var string
     */
    private $SerialNumber = null;

    /**
     * @var string
     */
    private $Subject = null;

    /**
     * @var \DateTime
     */
    private $ValidityFrom = null;

    /**
     * @var \DateTime
     */
    private $ValidityTo = null;

    /**
     * @var bool
     */
    private $Verify = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfAttributeType $Attributes
     * @var \ArchiflowWSCard\Type\Base64Binary $Certificate
     * @var \ArchiflowWSCard\Type\ArrayOfstring $Errors
     * @var \ArchiflowWSCard\Type\ArrayOfAttributeType $Extensions
     * @var string $Issuer
     * @var \ArchiflowWSCard\Type\ArrayOfAttributeType $KeyUsage
     * @var string $SerialNumber
     * @var string $Subject
     * @var \DateTime $ValidityFrom
     * @var \DateTime $ValidityTo
     * @var bool $Verify
     */
    public function __construct($Attributes, $Certificate, $Errors, $Extensions, $Issuer, $KeyUsage, $SerialNumber, $Subject, $ValidityFrom, $ValidityTo, $Verify)
    {
        $this->Attributes = $Attributes;
        $this->Certificate = $Certificate;
        $this->Errors = $Errors;
        $this->Extensions = $Extensions;
        $this->Issuer = $Issuer;
        $this->KeyUsage = $KeyUsage;
        $this->SerialNumber = $SerialNumber;
        $this->Subject = $Subject;
        $this->ValidityFrom = $ValidityFrom;
        $this->ValidityTo = $ValidityTo;
        $this->Verify = $Verify;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAttributeType
     */
    public function getAttributes()
    {
        return $this->Attributes;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAttributeType $Attributes
     * @return CertificateInfo
     */
    public function withAttributes($Attributes)
    {
        $new = clone $this;
        $new->Attributes = $Attributes;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Base64Binary
     */
    public function getCertificate()
    {
        return $this->Certificate;
    }

    /**
     * @param \ArchiflowWSCard\Type\Base64Binary $Certificate
     * @return CertificateInfo
     */
    public function withCertificate($Certificate)
    {
        $new = clone $this;
        $new->Certificate = $Certificate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getErrors()
    {
        return $this->Errors;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $Errors
     * @return CertificateInfo
     */
    public function withErrors($Errors)
    {
        $new = clone $this;
        $new->Errors = $Errors;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAttributeType
     */
    public function getExtensions()
    {
        return $this->Extensions;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAttributeType $Extensions
     * @return CertificateInfo
     */
    public function withExtensions($Extensions)
    {
        $new = clone $this;
        $new->Extensions = $Extensions;

        return $new;
    }

    /**
     * @return string
     */
    public function getIssuer()
    {
        return $this->Issuer;
    }

    /**
     * @param string $Issuer
     * @return CertificateInfo
     */
    public function withIssuer($Issuer)
    {
        $new = clone $this;
        $new->Issuer = $Issuer;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAttributeType
     */
    public function getKeyUsage()
    {
        return $this->KeyUsage;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAttributeType $KeyUsage
     * @return CertificateInfo
     */
    public function withKeyUsage($KeyUsage)
    {
        $new = clone $this;
        $new->KeyUsage = $KeyUsage;

        return $new;
    }

    /**
     * @return string
     */
    public function getSerialNumber()
    {
        return $this->SerialNumber;
    }

    /**
     * @param string $SerialNumber
     * @return CertificateInfo
     */
    public function withSerialNumber($SerialNumber)
    {
        $new = clone $this;
        $new->SerialNumber = $SerialNumber;

        return $new;
    }

    /**
     * @return string
     */
    public function getSubject()
    {
        return $this->Subject;
    }

    /**
     * @param string $Subject
     * @return CertificateInfo
     */
    public function withSubject($Subject)
    {
        $new = clone $this;
        $new->Subject = $Subject;

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
     * @return CertificateInfo
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
     * @return CertificateInfo
     */
    public function withValidityTo($ValidityTo)
    {
        $new = clone $this;
        $new->ValidityTo = $ValidityTo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getVerify()
    {
        return $this->Verify;
    }

    /**
     * @param bool $Verify
     * @return CertificateInfo
     */
    public function withVerify($Verify)
    {
        $new = clone $this;
        $new->Verify = $Verify;

        return $new;
    }


}

