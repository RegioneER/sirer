<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RegisterInvoiceInputBase implements RequestInterface
{

    /**
     * @var string
     */
    private $CompId = null;

    /**
     * @var string
     */
    private $Company = null;

    /**
     * @var string
     */
    private $ContRep = null;

    /**
     * @var string
     */
    private $DateFormat = null;

    /**
     * @var string
     */
    private $DocId = null;

    /**
     * @var string
     */
    private $Language = null;

    /**
     * @var string
     */
    private $LoginTicket = null;

    /**
     * @var \ArchiflowWSCard\Type\LoginSapType
     */
    private $LoginType = null;

    /**
     * @var bool
     */
    private $UserConversion = null;

    /**
     * @var string
     */
    private $UserId = null;

    /**
     * Constructor
     *
     * @var string $CompId
     * @var string $Company
     * @var string $ContRep
     * @var string $DateFormat
     * @var string $DocId
     * @var string $Language
     * @var string $LoginTicket
     * @var \ArchiflowWSCard\Type\LoginSapType $LoginType
     * @var bool $UserConversion
     * @var string $UserId
     */
    public function __construct($CompId, $Company, $ContRep, $DateFormat, $DocId, $Language, $LoginTicket, $LoginType, $UserConversion, $UserId)
    {
        $this->CompId = $CompId;
        $this->Company = $Company;
        $this->ContRep = $ContRep;
        $this->DateFormat = $DateFormat;
        $this->DocId = $DocId;
        $this->Language = $Language;
        $this->LoginTicket = $LoginTicket;
        $this->LoginType = $LoginType;
        $this->UserConversion = $UserConversion;
        $this->UserId = $UserId;
    }

    /**
     * @return string
     */
    public function getCompId()
    {
        return $this->CompId;
    }

    /**
     * @param string $CompId
     * @return RegisterInvoiceInputBase
     */
    public function withCompId($CompId)
    {
        $new = clone $this;
        $new->CompId = $CompId;

        return $new;
    }

    /**
     * @return string
     */
    public function getCompany()
    {
        return $this->Company;
    }

    /**
     * @param string $Company
     * @return RegisterInvoiceInputBase
     */
    public function withCompany($Company)
    {
        $new = clone $this;
        $new->Company = $Company;

        return $new;
    }

    /**
     * @return string
     */
    public function getContRep()
    {
        return $this->ContRep;
    }

    /**
     * @param string $ContRep
     * @return RegisterInvoiceInputBase
     */
    public function withContRep($ContRep)
    {
        $new = clone $this;
        $new->ContRep = $ContRep;

        return $new;
    }

    /**
     * @return string
     */
    public function getDateFormat()
    {
        return $this->DateFormat;
    }

    /**
     * @param string $DateFormat
     * @return RegisterInvoiceInputBase
     */
    public function withDateFormat($DateFormat)
    {
        $new = clone $this;
        $new->DateFormat = $DateFormat;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocId()
    {
        return $this->DocId;
    }

    /**
     * @param string $DocId
     * @return RegisterInvoiceInputBase
     */
    public function withDocId($DocId)
    {
        $new = clone $this;
        $new->DocId = $DocId;

        return $new;
    }

    /**
     * @return string
     */
    public function getLanguage()
    {
        return $this->Language;
    }

    /**
     * @param string $Language
     * @return RegisterInvoiceInputBase
     */
    public function withLanguage($Language)
    {
        $new = clone $this;
        $new->Language = $Language;

        return $new;
    }

    /**
     * @return string
     */
    public function getLoginTicket()
    {
        return $this->LoginTicket;
    }

    /**
     * @param string $LoginTicket
     * @return RegisterInvoiceInputBase
     */
    public function withLoginTicket($LoginTicket)
    {
        $new = clone $this;
        $new->LoginTicket = $LoginTicket;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\LoginSapType
     */
    public function getLoginType()
    {
        return $this->LoginType;
    }

    /**
     * @param \ArchiflowWSCard\Type\LoginSapType $LoginType
     * @return RegisterInvoiceInputBase
     */
    public function withLoginType($LoginType)
    {
        $new = clone $this;
        $new->LoginType = $LoginType;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUserConversion()
    {
        return $this->UserConversion;
    }

    /**
     * @param bool $UserConversion
     * @return RegisterInvoiceInputBase
     */
    public function withUserConversion($UserConversion)
    {
        $new = clone $this;
        $new->UserConversion = $UserConversion;

        return $new;
    }

    /**
     * @return string
     */
    public function getUserId()
    {
        return $this->UserId;
    }

    /**
     * @param string $UserId
     * @return RegisterInvoiceInputBase
     */
    public function withUserId($UserId)
    {
        $new = clone $this;
        $new->UserId = $UserId;

        return $new;
    }


}

