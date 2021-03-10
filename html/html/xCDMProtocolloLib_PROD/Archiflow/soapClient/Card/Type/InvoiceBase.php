<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvoiceBase implements RequestInterface
{

    /**
     * @var string
     */
    private $Barcode = null;

    /**
     * @var \DateTime
     */
    private $ChangeStatusDate = null;

    /**
     * @var string
     */
    private $ConservationState = null;

    /**
     * @var string
     */
    private $CurrencyCode = null;

    /**
     * @var string
     */
    private $CurrentPhase = null;

    /**
     * @var string
     */
    private $CurrentStatus = null;

    /**
     * @var \ArchiflowWSCard\Type\MemberInfo
     */
    private $Customer = null;

    /**
     * @var int
     */
    private $Error = null;

    /**
     * @var string
     */
    private $ErrorDescription = null;

    /**
     * @var \DateTime
     */
    private $FirstExpirationDate = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var \DateTime
     */
    private $InsertDate = null;

    /**
     * @var \DateTime
     */
    private $InvoiceDate = null;

    /**
     * @var string
     */
    private $InvoiceNumber = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $MainChannel = null;

    /**
     * @var string
     */
    private $Note = null;

    /**
     * @var \DateTime
     */
    private $PublicationDate = null;

    /**
     * @var \DateTime
     */
    private $RegistrationDate = null;

    /**
     * @var \ArchiflowWSCard\Type\SdiInfo
     */
    private $Sdi = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $SentChannelType = null;

    /**
     * @var \ArchiflowWSCard\Type\MemberInfo
     */
    private $Supplier = null;

    /**
     * @var float
     */
    private $Total = null;

    /**
     * @var string
     */
    private $Transmitter = null;

    /**
     * @var string
     */
    private $UniqueProtocol = null;

    /**
     * @var string
     */
    private $VatProtocol = null;

    /**
     * @var string
     */
    private $VatRegister = null;

    /**
     * Constructor
     *
     * @var string $Barcode
     * @var \DateTime $ChangeStatusDate
     * @var string $ConservationState
     * @var string $CurrencyCode
     * @var string $CurrentPhase
     * @var string $CurrentStatus
     * @var \ArchiflowWSCard\Type\MemberInfo $Customer
     * @var int $Error
     * @var string $ErrorDescription
     * @var \DateTime $FirstExpirationDate
     * @var int $Id
     * @var \DateTime $InsertDate
     * @var \DateTime $InvoiceDate
     * @var string $InvoiceNumber
     * @var \ArchiflowWSCard\Type\Guid $MainChannel
     * @var string $Note
     * @var \DateTime $PublicationDate
     * @var \DateTime $RegistrationDate
     * @var \ArchiflowWSCard\Type\SdiInfo $Sdi
     * @var \ArchiflowWSCard\Type\ArrayOfguid $SentChannelType
     * @var \ArchiflowWSCard\Type\MemberInfo $Supplier
     * @var float $Total
     * @var string $Transmitter
     * @var string $UniqueProtocol
     * @var string $VatProtocol
     * @var string $VatRegister
     */
    public function __construct($Barcode, $ChangeStatusDate, $ConservationState, $CurrencyCode, $CurrentPhase, $CurrentStatus, $Customer, $Error, $ErrorDescription, $FirstExpirationDate, $Id, $InsertDate, $InvoiceDate, $InvoiceNumber, $MainChannel, $Note, $PublicationDate, $RegistrationDate, $Sdi, $SentChannelType, $Supplier, $Total, $Transmitter, $UniqueProtocol, $VatProtocol, $VatRegister)
    {
        $this->Barcode = $Barcode;
        $this->ChangeStatusDate = $ChangeStatusDate;
        $this->ConservationState = $ConservationState;
        $this->CurrencyCode = $CurrencyCode;
        $this->CurrentPhase = $CurrentPhase;
        $this->CurrentStatus = $CurrentStatus;
        $this->Customer = $Customer;
        $this->Error = $Error;
        $this->ErrorDescription = $ErrorDescription;
        $this->FirstExpirationDate = $FirstExpirationDate;
        $this->Id = $Id;
        $this->InsertDate = $InsertDate;
        $this->InvoiceDate = $InvoiceDate;
        $this->InvoiceNumber = $InvoiceNumber;
        $this->MainChannel = $MainChannel;
        $this->Note = $Note;
        $this->PublicationDate = $PublicationDate;
        $this->RegistrationDate = $RegistrationDate;
        $this->Sdi = $Sdi;
        $this->SentChannelType = $SentChannelType;
        $this->Supplier = $Supplier;
        $this->Total = $Total;
        $this->Transmitter = $Transmitter;
        $this->UniqueProtocol = $UniqueProtocol;
        $this->VatProtocol = $VatProtocol;
        $this->VatRegister = $VatRegister;
    }

    /**
     * @return string
     */
    public function getBarcode()
    {
        return $this->Barcode;
    }

    /**
     * @param string $Barcode
     * @return InvoiceBase
     */
    public function withBarcode($Barcode)
    {
        $new = clone $this;
        $new->Barcode = $Barcode;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getChangeStatusDate()
    {
        return $this->ChangeStatusDate;
    }

    /**
     * @param \DateTime $ChangeStatusDate
     * @return InvoiceBase
     */
    public function withChangeStatusDate($ChangeStatusDate)
    {
        $new = clone $this;
        $new->ChangeStatusDate = $ChangeStatusDate;

        return $new;
    }

    /**
     * @return string
     */
    public function getConservationState()
    {
        return $this->ConservationState;
    }

    /**
     * @param string $ConservationState
     * @return InvoiceBase
     */
    public function withConservationState($ConservationState)
    {
        $new = clone $this;
        $new->ConservationState = $ConservationState;

        return $new;
    }

    /**
     * @return string
     */
    public function getCurrencyCode()
    {
        return $this->CurrencyCode;
    }

    /**
     * @param string $CurrencyCode
     * @return InvoiceBase
     */
    public function withCurrencyCode($CurrencyCode)
    {
        $new = clone $this;
        $new->CurrencyCode = $CurrencyCode;

        return $new;
    }

    /**
     * @return string
     */
    public function getCurrentPhase()
    {
        return $this->CurrentPhase;
    }

    /**
     * @param string $CurrentPhase
     * @return InvoiceBase
     */
    public function withCurrentPhase($CurrentPhase)
    {
        $new = clone $this;
        $new->CurrentPhase = $CurrentPhase;

        return $new;
    }

    /**
     * @return string
     */
    public function getCurrentStatus()
    {
        return $this->CurrentStatus;
    }

    /**
     * @param string $CurrentStatus
     * @return InvoiceBase
     */
    public function withCurrentStatus($CurrentStatus)
    {
        $new = clone $this;
        $new->CurrentStatus = $CurrentStatus;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\MemberInfo
     */
    public function getCustomer()
    {
        return $this->Customer;
    }

    /**
     * @param \ArchiflowWSCard\Type\MemberInfo $Customer
     * @return InvoiceBase
     */
    public function withCustomer($Customer)
    {
        $new = clone $this;
        $new->Customer = $Customer;

        return $new;
    }

    /**
     * @return int
     */
    public function getError()
    {
        return $this->Error;
    }

    /**
     * @param int $Error
     * @return InvoiceBase
     */
    public function withError($Error)
    {
        $new = clone $this;
        $new->Error = $Error;

        return $new;
    }

    /**
     * @return string
     */
    public function getErrorDescription()
    {
        return $this->ErrorDescription;
    }

    /**
     * @param string $ErrorDescription
     * @return InvoiceBase
     */
    public function withErrorDescription($ErrorDescription)
    {
        $new = clone $this;
        $new->ErrorDescription = $ErrorDescription;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getFirstExpirationDate()
    {
        return $this->FirstExpirationDate;
    }

    /**
     * @param \DateTime $FirstExpirationDate
     * @return InvoiceBase
     */
    public function withFirstExpirationDate($FirstExpirationDate)
    {
        $new = clone $this;
        $new->FirstExpirationDate = $FirstExpirationDate;

        return $new;
    }

    /**
     * @return int
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param int $Id
     * @return InvoiceBase
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getInsertDate()
    {
        return $this->InsertDate;
    }

    /**
     * @param \DateTime $InsertDate
     * @return InvoiceBase
     */
    public function withInsertDate($InsertDate)
    {
        $new = clone $this;
        $new->InsertDate = $InsertDate;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getInvoiceDate()
    {
        return $this->InvoiceDate;
    }

    /**
     * @param \DateTime $InvoiceDate
     * @return InvoiceBase
     */
    public function withInvoiceDate($InvoiceDate)
    {
        $new = clone $this;
        $new->InvoiceDate = $InvoiceDate;

        return $new;
    }

    /**
     * @return string
     */
    public function getInvoiceNumber()
    {
        return $this->InvoiceNumber;
    }

    /**
     * @param string $InvoiceNumber
     * @return InvoiceBase
     */
    public function withInvoiceNumber($InvoiceNumber)
    {
        $new = clone $this;
        $new->InvoiceNumber = $InvoiceNumber;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getMainChannel()
    {
        return $this->MainChannel;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $MainChannel
     * @return InvoiceBase
     */
    public function withMainChannel($MainChannel)
    {
        $new = clone $this;
        $new->MainChannel = $MainChannel;

        return $new;
    }

    /**
     * @return string
     */
    public function getNote()
    {
        return $this->Note;
    }

    /**
     * @param string $Note
     * @return InvoiceBase
     */
    public function withNote($Note)
    {
        $new = clone $this;
        $new->Note = $Note;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getPublicationDate()
    {
        return $this->PublicationDate;
    }

    /**
     * @param \DateTime $PublicationDate
     * @return InvoiceBase
     */
    public function withPublicationDate($PublicationDate)
    {
        $new = clone $this;
        $new->PublicationDate = $PublicationDate;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getRegistrationDate()
    {
        return $this->RegistrationDate;
    }

    /**
     * @param \DateTime $RegistrationDate
     * @return InvoiceBase
     */
    public function withRegistrationDate($RegistrationDate)
    {
        $new = clone $this;
        $new->RegistrationDate = $RegistrationDate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SdiInfo
     */
    public function getSdi()
    {
        return $this->Sdi;
    }

    /**
     * @param \ArchiflowWSCard\Type\SdiInfo $Sdi
     * @return InvoiceBase
     */
    public function withSdi($Sdi)
    {
        $new = clone $this;
        $new->Sdi = $Sdi;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getSentChannelType()
    {
        return $this->SentChannelType;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $SentChannelType
     * @return InvoiceBase
     */
    public function withSentChannelType($SentChannelType)
    {
        $new = clone $this;
        $new->SentChannelType = $SentChannelType;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\MemberInfo
     */
    public function getSupplier()
    {
        return $this->Supplier;
    }

    /**
     * @param \ArchiflowWSCard\Type\MemberInfo $Supplier
     * @return InvoiceBase
     */
    public function withSupplier($Supplier)
    {
        $new = clone $this;
        $new->Supplier = $Supplier;

        return $new;
    }

    /**
     * @return float
     */
    public function getTotal()
    {
        return $this->Total;
    }

    /**
     * @param float $Total
     * @return InvoiceBase
     */
    public function withTotal($Total)
    {
        $new = clone $this;
        $new->Total = $Total;

        return $new;
    }

    /**
     * @return string
     */
    public function getTransmitter()
    {
        return $this->Transmitter;
    }

    /**
     * @param string $Transmitter
     * @return InvoiceBase
     */
    public function withTransmitter($Transmitter)
    {
        $new = clone $this;
        $new->Transmitter = $Transmitter;

        return $new;
    }

    /**
     * @return string
     */
    public function getUniqueProtocol()
    {
        return $this->UniqueProtocol;
    }

    /**
     * @param string $UniqueProtocol
     * @return InvoiceBase
     */
    public function withUniqueProtocol($UniqueProtocol)
    {
        $new = clone $this;
        $new->UniqueProtocol = $UniqueProtocol;

        return $new;
    }

    /**
     * @return string
     */
    public function getVatProtocol()
    {
        return $this->VatProtocol;
    }

    /**
     * @param string $VatProtocol
     * @return InvoiceBase
     */
    public function withVatProtocol($VatProtocol)
    {
        $new = clone $this;
        $new->VatProtocol = $VatProtocol;

        return $new;
    }

    /**
     * @return string
     */
    public function getVatRegister()
    {
        return $this->VatRegister;
    }

    /**
     * @param string $VatRegister
     * @return InvoiceBase
     */
    public function withVatRegister($VatRegister)
    {
        $new = clone $this;
        $new->VatRegister = $VatRegister;

        return $new;
    }


}

