<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvoiceSearchCriteria implements RequestInterface
{

    /**
     * @var string
     */
    private $Barcode = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $Channels = null;

    /**
     * @var string
     */
    private $ConservationState = null;

    /**
     * @var string
     */
    private $CurrencyCode = null;

    /**
     * @var \ArchiflowWSCard\Type\MemberInfo
     */
    private $Customer = null;

    /**
     * @var int
     */
    private $Error = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    private $FirstExpirationDate = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    private $InsertDate = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    private $InvoiceDate = null;

    /**
     * @var string
     */
    private $InvoiceNumber = null;

    /**
     * @var string
     */
    private $Note = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $PhaseList = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    private $PublicationDate = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    private $RegistrationDate = null;

    /**
     * @var \ArchiflowWSCard\Type\SdiInfo
     */
    private $Sdi = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    private $SendReceiveDate = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $StatusList = null;

    /**
     * @var \ArchiflowWSCard\Type\MemberInfo
     */
    private $Supplier = null;

    /**
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdecimal5F2dSckg
     */
    private $Total = null;

    /**
     * @var string
     */
    private $Transmitter = null;

    /**
     * @var \ArchiflowWSCard\Type\InvoiceSearchCriteriaInvoiceFilterType
     */
    private $Type = null;

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
     * @var \ArchiflowWSCard\Type\ArrayOfguid $Channels
     * @var string $ConservationState
     * @var string $CurrencyCode
     * @var \ArchiflowWSCard\Type\MemberInfo $Customer
     * @var int $Error
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     * $FirstExpirationDate
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $InsertDate
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $InvoiceDate
     * @var string $InvoiceNumber
     * @var string $Note
     * @var \ArchiflowWSCard\Type\ArrayOfstring $PhaseList
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $PublicationDate
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $RegistrationDate
     * @var \ArchiflowWSCard\Type\SdiInfo $Sdi
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $SendReceiveDate
     * @var \ArchiflowWSCard\Type\ArrayOfstring $StatusList
     * @var \ArchiflowWSCard\Type\MemberInfo $Supplier
     * @var \ArchiflowWSCard\Type\RangeOfNullableOfdecimal5F2dSckg $Total
     * @var string $Transmitter
     * @var \ArchiflowWSCard\Type\InvoiceSearchCriteriaInvoiceFilterType $Type
     * @var string $UniqueProtocol
     * @var string $VatProtocol
     * @var string $VatRegister
     */
    public function __construct($Barcode, $Channels, $ConservationState, $CurrencyCode, $Customer, $Error, $FirstExpirationDate, $InsertDate, $InvoiceDate, $InvoiceNumber, $Note, $PhaseList, $PublicationDate, $RegistrationDate, $Sdi, $SendReceiveDate, $StatusList, $Supplier, $Total, $Transmitter, $Type, $UniqueProtocol, $VatProtocol, $VatRegister)
    {
        $this->Barcode = $Barcode;
        $this->Channels = $Channels;
        $this->ConservationState = $ConservationState;
        $this->CurrencyCode = $CurrencyCode;
        $this->Customer = $Customer;
        $this->Error = $Error;
        $this->FirstExpirationDate = $FirstExpirationDate;
        $this->InsertDate = $InsertDate;
        $this->InvoiceDate = $InvoiceDate;
        $this->InvoiceNumber = $InvoiceNumber;
        $this->Note = $Note;
        $this->PhaseList = $PhaseList;
        $this->PublicationDate = $PublicationDate;
        $this->RegistrationDate = $RegistrationDate;
        $this->Sdi = $Sdi;
        $this->SendReceiveDate = $SendReceiveDate;
        $this->StatusList = $StatusList;
        $this->Supplier = $Supplier;
        $this->Total = $Total;
        $this->Transmitter = $Transmitter;
        $this->Type = $Type;
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
     * @return InvoiceSearchCriteria
     */
    public function withBarcode($Barcode)
    {
        $new = clone $this;
        $new->Barcode = $Barcode;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getChannels()
    {
        return $this->Channels;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $Channels
     * @return InvoiceSearchCriteria
     */
    public function withChannels($Channels)
    {
        $new = clone $this;
        $new->Channels = $Channels;

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
     * @return InvoiceSearchCriteria
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
     * @return InvoiceSearchCriteria
     */
    public function withCurrencyCode($CurrencyCode)
    {
        $new = clone $this;
        $new->CurrencyCode = $CurrencyCode;

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
     * @return InvoiceSearchCriteria
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
     * @return InvoiceSearchCriteria
     */
    public function withError($Error)
    {
        $new = clone $this;
        $new->Error = $Error;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    public function getFirstExpirationDate()
    {
        return $this->FirstExpirationDate;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     * $FirstExpirationDate
     * @return InvoiceSearchCriteria
     */
    public function withFirstExpirationDate($FirstExpirationDate)
    {
        $new = clone $this;
        $new->FirstExpirationDate = $FirstExpirationDate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    public function getInsertDate()
    {
        return $this->InsertDate;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $InsertDate
     * @return InvoiceSearchCriteria
     */
    public function withInsertDate($InsertDate)
    {
        $new = clone $this;
        $new->InsertDate = $InsertDate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    public function getInvoiceDate()
    {
        return $this->InvoiceDate;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $InvoiceDate
     * @return InvoiceSearchCriteria
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
     * @return InvoiceSearchCriteria
     */
    public function withInvoiceNumber($InvoiceNumber)
    {
        $new = clone $this;
        $new->InvoiceNumber = $InvoiceNumber;

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
     * @return InvoiceSearchCriteria
     */
    public function withNote($Note)
    {
        $new = clone $this;
        $new->Note = $Note;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getPhaseList()
    {
        return $this->PhaseList;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $PhaseList
     * @return InvoiceSearchCriteria
     */
    public function withPhaseList($PhaseList)
    {
        $new = clone $this;
        $new->PhaseList = $PhaseList;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    public function getPublicationDate()
    {
        return $this->PublicationDate;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $PublicationDate
     * @return InvoiceSearchCriteria
     */
    public function withPublicationDate($PublicationDate)
    {
        $new = clone $this;
        $new->PublicationDate = $PublicationDate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    public function getRegistrationDate()
    {
        return $this->RegistrationDate;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $RegistrationDate
     * @return InvoiceSearchCriteria
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
     * @return InvoiceSearchCriteria
     */
    public function withSdi($Sdi)
    {
        $new = clone $this;
        $new->Sdi = $Sdi;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg
     */
    public function getSendReceiveDate()
    {
        return $this->SendReceiveDate;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdateTime5F2dSckg $SendReceiveDate
     * @return InvoiceSearchCriteria
     */
    public function withSendReceiveDate($SendReceiveDate)
    {
        $new = clone $this;
        $new->SendReceiveDate = $SendReceiveDate;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getStatusList()
    {
        return $this->StatusList;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $StatusList
     * @return InvoiceSearchCriteria
     */
    public function withStatusList($StatusList)
    {
        $new = clone $this;
        $new->StatusList = $StatusList;

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
     * @return InvoiceSearchCriteria
     */
    public function withSupplier($Supplier)
    {
        $new = clone $this;
        $new->Supplier = $Supplier;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RangeOfNullableOfdecimal5F2dSckg
     */
    public function getTotal()
    {
        return $this->Total;
    }

    /**
     * @param \ArchiflowWSCard\Type\RangeOfNullableOfdecimal5F2dSckg $Total
     * @return InvoiceSearchCriteria
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
     * @return InvoiceSearchCriteria
     */
    public function withTransmitter($Transmitter)
    {
        $new = clone $this;
        $new->Transmitter = $Transmitter;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\InvoiceSearchCriteriaInvoiceFilterType
     */
    public function getType()
    {
        return $this->Type;
    }

    /**
     * @param \ArchiflowWSCard\Type\InvoiceSearchCriteriaInvoiceFilterType $Type
     * @return InvoiceSearchCriteria
     */
    public function withType($Type)
    {
        $new = clone $this;
        $new->Type = $Type;

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
     * @return InvoiceSearchCriteria
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
     * @return InvoiceSearchCriteria
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
     * @return InvoiceSearchCriteria
     */
    public function withVatRegister($VatRegister)
    {
        $new = clone $this;
        $new->VatRegister = $VatRegister;

        return $new;
    }


}

