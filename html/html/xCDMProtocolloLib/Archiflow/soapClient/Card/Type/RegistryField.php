<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RegistryField implements RequestInterface
{

    /**
     * @var string
     */
    private $Description = null;

    /**
     * @var \ArchiflowWSCard\Type\IdRegistryField
     */
    private $Id = null;

    /**
     * @var bool
     */
    private $IsMandatory = null;

    /**
     * @var bool
     */
    private $IsUnique = null;

    /**
     * @var bool
     */
    private $IsVisible = null;

    /**
     * @var int
     */
    private $Position = null;

    /**
     * @var int
     */
    private $Priority = null;

    /**
     * @var string
     */
    private $Value = null;

    /**
     * Constructor
     *
     * @var string $Description
     * @var \ArchiflowWSCard\Type\IdRegistryField $Id
     * @var bool $IsMandatory
     * @var bool $IsUnique
     * @var bool $IsVisible
     * @var int $Position
     * @var int $Priority
     * @var string $Value
     */
    public function __construct($Description, $Id, $IsMandatory, $IsUnique, $IsVisible, $Position, $Priority, $Value)
    {
        $this->Description = $Description;
        $this->Id = $Id;
        $this->IsMandatory = $IsMandatory;
        $this->IsUnique = $IsUnique;
        $this->IsVisible = $IsVisible;
        $this->Position = $Position;
        $this->Priority = $Priority;
        $this->Value = $Value;
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
     * @return RegistryField
     */
    public function withDescription($Description)
    {
        $new = clone $this;
        $new->Description = $Description;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdRegistryField
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdRegistryField $Id
     * @return RegistryField
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
    public function getIsMandatory()
    {
        return $this->IsMandatory;
    }

    /**
     * @param bool $IsMandatory
     * @return RegistryField
     */
    public function withIsMandatory($IsMandatory)
    {
        $new = clone $this;
        $new->IsMandatory = $IsMandatory;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsUnique()
    {
        return $this->IsUnique;
    }

    /**
     * @param bool $IsUnique
     * @return RegistryField
     */
    public function withIsUnique($IsUnique)
    {
        $new = clone $this;
        $new->IsUnique = $IsUnique;

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
     * @return RegistryField
     */
    public function withIsVisible($IsVisible)
    {
        $new = clone $this;
        $new->IsVisible = $IsVisible;

        return $new;
    }

    /**
     * @return int
     */
    public function getPosition()
    {
        return $this->Position;
    }

    /**
     * @param int $Position
     * @return RegistryField
     */
    public function withPosition($Position)
    {
        $new = clone $this;
        $new->Position = $Position;

        return $new;
    }

    /**
     * @return int
     */
    public function getPriority()
    {
        return $this->Priority;
    }

    /**
     * @param int $Priority
     * @return RegistryField
     */
    public function withPriority($Priority)
    {
        $new = clone $this;
        $new->Priority = $Priority;

        return $new;
    }

    /**
     * @return string
     */
    public function getValue()
    {
        return $this->Value;
    }

    /**
     * @param string $Value
     * @return RegistryField
     */
    public function withValue($Value)
    {
        $new = clone $this;
        $new->Value = $Value;

        return $new;
    }


}

