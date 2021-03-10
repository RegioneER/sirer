<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AgrafCardContact implements RequestInterface
{

    /**
     * @var string
     */
    private $Description = null;

    /**
     * @var \ArchiflowWSCard\Type\AgrafCardContactId
     */
    private $EntityId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $GuidCard = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var bool
     */
    private $IsUserSelected = null;

    /**
     * @var string
     */
    private $LastName = null;

    /**
     * @var string
     */
    private $MainAddress = null;

    /**
     * @var string
     */
    private $MainEMailAddress = null;

    /**
     * @var string
     */
    private $MainPecAddress = null;

    /**
     * @var string
     */
    private $MainPhoneNumber = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var string
     */
    private $TaxId = null;

    /**
     * @var string
     */
    private $VatId = null;

    /**
     * Constructor
     *
     * @var string $Description
     * @var \ArchiflowWSCard\Type\AgrafCardContactId $EntityId
     * @var \ArchiflowWSCard\Type\Guid $GuidCard
     * @var int $Id
     * @var bool $IsUserSelected
     * @var string $LastName
     * @var string $MainAddress
     * @var string $MainEMailAddress
     * @var string $MainPecAddress
     * @var string $MainPhoneNumber
     * @var string $Name
     * @var string $TaxId
     * @var string $VatId
     */
    public function __construct($Description, $EntityId, $GuidCard, $Id, $IsUserSelected, $LastName, $MainAddress, $MainEMailAddress, $MainPecAddress, $MainPhoneNumber, $Name, $TaxId, $VatId)
    {
        $this->Description = $Description;
        $this->EntityId = $EntityId;
        $this->GuidCard = $GuidCard;
        $this->Id = $Id;
        $this->IsUserSelected = $IsUserSelected;
        $this->LastName = $LastName;
        $this->MainAddress = $MainAddress;
        $this->MainEMailAddress = $MainEMailAddress;
        $this->MainPecAddress = $MainPecAddress;
        $this->MainPhoneNumber = $MainPhoneNumber;
        $this->Name = $Name;
        $this->TaxId = $TaxId;
        $this->VatId = $VatId;
    }

    /**
     * @return string
     */
    public function getDescription()
    {
        return $this->Description;
    }

    /**
     * @param string $Description
     * @return AgrafCardContact
     */
    public function withDescription($Description)
    {
        $new = clone $this;
        $new->Description = $Description;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafCardContactId
     */
    public function getEntityId()
    {
        return $this->EntityId;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafCardContactId $EntityId
     * @return AgrafCardContact
     */
    public function withEntityId($EntityId)
    {
        $new = clone $this;
        $new->EntityId = $EntityId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getGuidCard()
    {
        return $this->GuidCard;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $GuidCard
     * @return AgrafCardContact
     */
    public function withGuidCard($GuidCard)
    {
        $new = clone $this;
        $new->GuidCard = $GuidCard;

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
     * @return AgrafCardContact
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsUserSelected()
    {
        return $this->IsUserSelected;
    }

    /**
     * @param bool $IsUserSelected
     * @return AgrafCardContact
     */
    public function withIsUserSelected($IsUserSelected)
    {
        $new = clone $this;
        $new->IsUserSelected = $IsUserSelected;

        return $new;
    }

    /**
     * @return string
     */
    public function getLastName()
    {
        return $this->LastName;
    }

    /**
     * @param string $LastName
     * @return AgrafCardContact
     */
    public function withLastName($LastName)
    {
        $new = clone $this;
        $new->LastName = $LastName;

        return $new;
    }

    /**
     * @return string
     */
    public function getMainAddress()
    {
        return $this->MainAddress;
    }

    /**
     * @param string $MainAddress
     * @return AgrafCardContact
     */
    public function withMainAddress($MainAddress)
    {
        $new = clone $this;
        $new->MainAddress = $MainAddress;

        return $new;
    }

    /**
     * @return string
     */
    public function getMainEMailAddress()
    {
        return $this->MainEMailAddress;
    }

    /**
     * @param string $MainEMailAddress
     * @return AgrafCardContact
     */
    public function withMainEMailAddress($MainEMailAddress)
    {
        $new = clone $this;
        $new->MainEMailAddress = $MainEMailAddress;

        return $new;
    }

    /**
     * @return string
     */
    public function getMainPecAddress()
    {
        return $this->MainPecAddress;
    }

    /**
     * @param string $MainPecAddress
     * @return AgrafCardContact
     */
    public function withMainPecAddress($MainPecAddress)
    {
        $new = clone $this;
        $new->MainPecAddress = $MainPecAddress;

        return $new;
    }

    /**
     * @return string
     */
    public function getMainPhoneNumber()
    {
        return $this->MainPhoneNumber;
    }

    /**
     * @param string $MainPhoneNumber
     * @return AgrafCardContact
     */
    public function withMainPhoneNumber($MainPhoneNumber)
    {
        $new = clone $this;
        $new->MainPhoneNumber = $MainPhoneNumber;

        return $new;
    }

    /**
     * @return string
     */
    public function getName()
    {
        return $this->Name;
    }

    /**
     * @param string $Name
     * @return AgrafCardContact
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return string
     */
    public function getTaxId()
    {
        return $this->TaxId;
    }

    /**
     * @param string $TaxId
     * @return AgrafCardContact
     */
    public function withTaxId($TaxId)
    {
        $new = clone $this;
        $new->TaxId = $TaxId;

        return $new;
    }

    /**
     * @return string
     */
    public function getVatId()
    {
        return $this->VatId;
    }

    /**
     * @param string $VatId
     * @return AgrafCardContact
     */
    public function withVatId($VatId)
    {
        $new = clone $this;
        $new->VatId = $VatId;

        return $new;
    }


}

