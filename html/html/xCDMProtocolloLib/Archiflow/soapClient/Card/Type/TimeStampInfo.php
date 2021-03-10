<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class TimeStampInfo implements RequestInterface
{

    /**
     * @var string
     */
    private $Algorithm = null;

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
    private $Hash = null;

    /**
     * @var string
     */
    private $Policy = null;

    /**
     * @var string
     */
    private $SerialNumber = null;

    /**
     * @var string
     */
    private $TimeStampAuth = null;

    /**
     * @var \DateTime
     */
    private $TimeStampTimeUTC = null;

    /**
     * @var bool
     */
    private $Valid = null;

    /**
     * Constructor
     *
     * @var string $Algorithm
     * @var string $CertificateIssuer
     * @var string $CertificateSerialNumber
     * @var string $Hash
     * @var string $Policy
     * @var string $SerialNumber
     * @var string $TimeStampAuth
     * @var \DateTime $TimeStampTimeUTC
     * @var bool $Valid
     */
    public function __construct($Algorithm, $CertificateIssuer, $CertificateSerialNumber, $Hash, $Policy, $SerialNumber, $TimeStampAuth, $TimeStampTimeUTC, $Valid)
    {
        $this->Algorithm = $Algorithm;
        $this->CertificateIssuer = $CertificateIssuer;
        $this->CertificateSerialNumber = $CertificateSerialNumber;
        $this->Hash = $Hash;
        $this->Policy = $Policy;
        $this->SerialNumber = $SerialNumber;
        $this->TimeStampAuth = $TimeStampAuth;
        $this->TimeStampTimeUTC = $TimeStampTimeUTC;
        $this->Valid = $Valid;
    }

    /**
     * @return string
     */
    public function getAlgorithm()
    {
        return $this->Algorithm;
    }

    /**
     * @param string $Algorithm
     * @return TimeStampInfo
     */
    public function withAlgorithm($Algorithm)
    {
        $new = clone $this;
        $new->Algorithm = $Algorithm;

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
     * @return TimeStampInfo
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
     * @return TimeStampInfo
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
    public function getHash()
    {
        return $this->Hash;
    }

    /**
     * @param string $Hash
     * @return TimeStampInfo
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
    public function getPolicy()
    {
        return $this->Policy;
    }

    /**
     * @param string $Policy
     * @return TimeStampInfo
     */
    public function withPolicy($Policy)
    {
        $new = clone $this;
        $new->Policy = $Policy;

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
     * @return TimeStampInfo
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
    public function getTimeStampAuth()
    {
        return $this->TimeStampAuth;
    }

    /**
     * @param string $TimeStampAuth
     * @return TimeStampInfo
     */
    public function withTimeStampAuth($TimeStampAuth)
    {
        $new = clone $this;
        $new->TimeStampAuth = $TimeStampAuth;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getTimeStampTimeUTC()
    {
        return $this->TimeStampTimeUTC;
    }

    /**
     * @param \DateTime $TimeStampTimeUTC
     * @return TimeStampInfo
     */
    public function withTimeStampTimeUTC($TimeStampTimeUTC)
    {
        $new = clone $this;
        $new->TimeStampTimeUTC = $TimeStampTimeUTC;

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
     * @return TimeStampInfo
     */
    public function withValid($Valid)
    {
        $new = clone $this;
        $new->Valid = $Valid;

        return $new;
    }


}

