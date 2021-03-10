<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class KeyValueOfintArrayOfintty7Ep6D1 implements RequestInterface
{

    /**
     * @var int
     */
    private $Key = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $Value = null;

    /**
     * Constructor
     *
     * @var int $Key
     * @var \ArchiflowWSCard\Type\ArrayOfint $Value
     */
    public function __construct($Key, $Value)
    {
        $this->Key = $Key;
        $this->Value = $Value;
    }

    /**
     * @return int
     */
    public function getKey()
    {
        return $this->Key;
    }

    /**
     * @param int $Key
     * @return KeyValueOfintArrayOfintty7Ep6D1
     */
    public function withKey($Key)
    {
        $new = clone $this;
        $new->Key = $Key;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getValue()
    {
        return $this->Value;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $Value
     * @return KeyValueOfintArrayOfintty7Ep6D1
     */
    public function withValue($Value)
    {
        $new = clone $this;
        $new->Value = $Value;

        return $new;
    }


}

