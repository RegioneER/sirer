<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class LicenseOption implements RequestInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\LicenseOptions
     */
    private $Id = null;

    /**
     * @var bool
     */
    private $IsStringValue = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var \ArchiflowWSLogin\Type\AnyType
     */
    private $Value = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSLogin\Type\LicenseOptions $Id
     * @var bool $IsStringValue
     * @var string $Name
     * @var \ArchiflowWSLogin\Type\AnyType $Value
     */
    public function __construct($Id, $IsStringValue, $Name, $Value)
    {
        $this->Id = $Id;
        $this->IsStringValue = $IsStringValue;
        $this->Name = $Name;
        $this->Value = $Value;
    }

    /**
     * @return \ArchiflowWSLogin\Type\LicenseOptions
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param \ArchiflowWSLogin\Type\LicenseOptions $Id
     * @return LicenseOption
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
    public function getIsStringValue()
    {
        return $this->IsStringValue;
    }

    /**
     * @param bool $IsStringValue
     * @return LicenseOption
     */
    public function withIsStringValue($IsStringValue)
    {
        $new = clone $this;
        $new->IsStringValue = $IsStringValue;

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
     * @return LicenseOption
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\AnyType
     */
    public function getValue()
    {
        return $this->Value;
    }

    /**
     * @param \ArchiflowWSLogin\Type\AnyType $Value
     * @return LicenseOption
     */
    public function withValue($Value)
    {
        $new = clone $this;
        $new->Value = $Value;

        return $new;
    }


}

