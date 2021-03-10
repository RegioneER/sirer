<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class FieldVersion implements RequestInterface
{

    /**
     * @var bool
     */
    private $Changed = null;

    /**
     * @var \ArchiflowWSCard\Type\IdField
     */
    private $Id = null;

    /**
     * @var string
     */
    private $Value = null;

    /**
     * Constructor
     *
     * @var bool $Changed
     * @var \ArchiflowWSCard\Type\IdField $Id
     * @var string $Value
     */
    public function __construct($Changed, $Id, $Value)
    {
        $this->Changed = $Changed;
        $this->Id = $Id;
        $this->Value = $Value;
    }

    /**
     * @return bool
     */
    public function getChanged()
    {
        return $this->Changed;
    }

    /**
     * @param bool $Changed
     * @return FieldVersion
     */
    public function withChanged($Changed)
    {
        $new = clone $this;
        $new->Changed = $Changed;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdField
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdField $Id
     * @return FieldVersion
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

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
     * @return FieldVersion
     */
    public function withValue($Value)
    {
        $new = clone $this;
        $new->Value = $Value;

        return $new;
    }


}

