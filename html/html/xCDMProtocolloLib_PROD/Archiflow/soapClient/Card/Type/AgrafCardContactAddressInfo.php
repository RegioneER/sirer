<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AgrafCardContactAddressInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardAddressInfo
     */
    private $CardAddresses = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $EntityId = null;

    /**
     * @var \ArchiflowWSCard\Type\AgrafEntityType
     */
    private $EntityType = null;

    /**
     * @var bool
     */
    private $IsVisible = null;

    /**
     * @var string
     */
    private $Lastname = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var int
     */
    private $Version = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardAddressInfo $CardAddresses
     * @var \ArchiflowWSCard\Type\Guid $EntityId
     * @var \ArchiflowWSCard\Type\AgrafEntityType $EntityType
     * @var bool $IsVisible
     * @var string $Lastname
     * @var string $Name
     * @var int $Version
     */
    public function __construct($CardAddresses, $EntityId, $EntityType, $IsVisible, $Lastname, $Name, $Version)
    {
        $this->CardAddresses = $CardAddresses;
        $this->EntityId = $EntityId;
        $this->EntityType = $EntityType;
        $this->IsVisible = $IsVisible;
        $this->Lastname = $Lastname;
        $this->Name = $Name;
        $this->Version = $Version;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAgrafCardAddressInfo
     */
    public function getCardAddresses()
    {
        return $this->CardAddresses;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAgrafCardAddressInfo $CardAddresses
     * @return AgrafCardContactAddressInfo
     */
    public function withCardAddresses($CardAddresses)
    {
        $new = clone $this;
        $new->CardAddresses = $CardAddresses;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getEntityId()
    {
        return $this->EntityId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $EntityId
     * @return AgrafCardContactAddressInfo
     */
    public function withEntityId($EntityId)
    {
        $new = clone $this;
        $new->EntityId = $EntityId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafEntityType
     */
    public function getEntityType()
    {
        return $this->EntityType;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafEntityType $EntityType
     * @return AgrafCardContactAddressInfo
     */
    public function withEntityType($EntityType)
    {
        $new = clone $this;
        $new->EntityType = $EntityType;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsVisible()
    {
        return $this->IsVisible;
    }

    /**
     * @param bool $IsVisible
     * @return AgrafCardContactAddressInfo
     */
    public function withIsVisible($IsVisible)
    {
        $new = clone $this;
        $new->IsVisible = $IsVisible;

        return $new;
    }

    /**
     * @return string
     */
    public function getLastname()
    {
        return $this->Lastname;
    }

    /**
     * @param string $Lastname
     * @return AgrafCardContactAddressInfo
     */
    public function withLastname($Lastname)
    {
        $new = clone $this;
        $new->Lastname = $Lastname;

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
     * @return AgrafCardContactAddressInfo
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return int
     */
    public function getVersion()
    {
        return $this->Version;
    }

    /**
     * @param int $Version
     * @return AgrafCardContactAddressInfo
     */
    public function withVersion($Version)
    {
        $new = clone $this;
        $new->Version = $Version;

        return $new;
    }


}

