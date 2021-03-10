<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Color implements RequestInterface
{

    /**
     * @var int
     */
    private $knownColor = null;

    /**
     * @var string
     */
    private $name = null;

    /**
     * @var int
     */
    private $state = null;

    /**
     * @var int
     */
    private $value = null;

    /**
     * Constructor
     *
     * @var int $knownColor
     * @var string $name
     * @var int $state
     * @var int $value
     */
    public function __construct($knownColor, $name, $state, $value)
    {
        $this->knownColor = $knownColor;
        $this->name = $name;
        $this->state = $state;
        $this->value = $value;
    }

    /**
     * @return int
     */
    public function getKnownColor()
    {
        return $this->knownColor;
    }

    /**
     * @param int $knownColor
     * @return Color
     */
    public function withKnownColor($knownColor)
    {
        $new = clone $this;
        $new->knownColor = $knownColor;

        return $new;
    }

    /**
     * @return string
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * @param string $name
     * @return Color
     */
    public function withName($name)
    {
        $new = clone $this;
        $new->name = $name;

        return $new;
    }

    /**
     * @return int
     */
    public function getState()
    {
        return $this->state;
    }

    /**
     * @param int $state
     * @return Color
     */
    public function withState($state)
    {
        $new = clone $this;
        $new->state = $state;

        return $new;
    }

    /**
     * @return int
     */
    public function getValue()
    {
        return $this->value;
    }

    /**
     * @param int $value
     * @return Color
     */
    public function withValue($value)
    {
        $new = clone $this;
        $new->value = $value;

        return $new;
    }


}

