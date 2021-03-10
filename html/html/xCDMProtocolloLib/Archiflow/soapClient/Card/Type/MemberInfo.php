<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class MemberInfo implements RequestInterface
{

    /**
     * @var string
     */
    private $BusinessName = null;

    /**
     * @var string
     */
    private $Code = null;

    /**
     * @var string
     */
    private $Email = null;

    /**
     * @var string
     */
    private $EmailPec = null;

    /**
     * @var string
     */
    private $TaxCode = null;

    /**
     * @var string
     */
    private $VatNumber = null;

    /**
     * Constructor
     *
     * @var string $BusinessName
     * @var string $Code
     * @var string $Email
     * @var string $EmailPec
     * @var string $TaxCode
     * @var string $VatNumber
     */
    public function __construct($BusinessName, $Code, $Email, $EmailPec, $TaxCode, $VatNumber)
    {
        $this->BusinessName = $BusinessName;
        $this->Code = $Code;
        $this->Email = $Email;
        $this->EmailPec = $EmailPec;
        $this->TaxCode = $TaxCode;
        $this->VatNumber = $VatNumber;
    }

    /**
     * @return string
     */
    public function getBusinessName()
    {
        return $this->BusinessName;
    }

    /**
     * @param string $BusinessName
     * @return MemberInfo
     */
    public function withBusinessName($BusinessName)
    {
        $new = clone $this;
        $new->BusinessName = $BusinessName;

        return $new;
    }

    /**
     * @return string
     */
    public function getCode()
    {
        return $this->Code;
    }

    /**
     * @param string $Code
     * @return MemberInfo
     */
    public function withCode($Code)
    {
        $new = clone $this;
        $new->Code = $Code;

        return $new;
    }

    /**
     * @return string
     */
    public function getEmail()
    {
        return $this->Email;
    }

    /**
     * @param string $Email
     * @return MemberInfo
     */
    public function withEmail($Email)
    {
        $new = clone $this;
        $new->Email = $Email;

        return $new;
    }

    /**
     * @return string
     */
    public function getEmailPec()
    {
        return $this->EmailPec;
    }

    /**
     * @param string $EmailPec
     * @return MemberInfo
     */
    public function withEmailPec($EmailPec)
    {
        $new = clone $this;
        $new->EmailPec = $EmailPec;

        return $new;
    }

    /**
     * @return string
     */
    public function getTaxCode()
    {
        return $this->TaxCode;
    }

    /**
     * @param string $TaxCode
     * @return MemberInfo
     */
    public function withTaxCode($TaxCode)
    {
        $new = clone $this;
        $new->TaxCode = $TaxCode;

        return $new;
    }

    /**
     * @return string
     */
    public function getVatNumber()
    {
        return $this->VatNumber;
    }

    /**
     * @param string $VatNumber
     * @return MemberInfo
     */
    public function withVatNumber($VatNumber)
    {
        $new = clone $this;
        $new->VatNumber = $VatNumber;

        return $new;
    }


}

