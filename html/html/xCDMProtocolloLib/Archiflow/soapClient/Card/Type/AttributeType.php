<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AttributeType implements RequestInterface
{

    /**
     * @var string
     */
    private $Attribute = null;

    /**
     * @var bool
     */
    private $Critical = null;

    /**
     * @var string
     */
    private $Value = null;

    /**
     * Constructor
     *
     * @var string $Attribute
     * @var bool $Critical
     * @var string $Value
     */
    public function __construct($Attribute, $Critical, $Value)
    {
        $this->Attribute = $Attribute;
        $this->Critical = $Critical;
        $this->Value = $Value;
    }

    /**
     * @return string
     */
    public function getAttribute()
    {
        return $this->Attribute;
    }

    /**
     * @param string $Attribute
     * @return AttributeType
     */
    public function withAttribute($Attribute)
    {
        $new = clone $this;
        $new->Attribute = $Attribute;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCritical()
    {
        return $this->Critical;
    }

    /**
     * @param bool $Critical
     * @return AttributeType
     */
    public function withCritical($Critical)
    {
        $new = clone $this;
        $new->Critical = $Critical;

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
     * @return AttributeType
     */
    public function withValue($Value)
    {
        $new = clone $this;
        $new->Value = $Value;

        return $new;
    }


}

