<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAttributeType implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AttributeType
     */
    private $AttributeType = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AttributeType $AttributeType
     */
    public function __construct($AttributeType)
    {
        $this->AttributeType = $AttributeType;
    }

    /**
     * @return \ArchiflowWSCard\Type\AttributeType
     */
    public function getAttributeType()
    {
        return $this->AttributeType;
    }

    /**
     * @param \ArchiflowWSCard\Type\AttributeType $AttributeType
     * @return ArrayOfAttributeType
     */
    public function withAttributeType($AttributeType)
    {
        $new = clone $this;
        $new->AttributeType = $AttributeType;

        return $new;
    }


}

