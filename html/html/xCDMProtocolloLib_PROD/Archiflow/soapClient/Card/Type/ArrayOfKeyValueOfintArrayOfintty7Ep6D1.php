<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfKeyValueOfintArrayOfintty7Ep6D1 implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\KeyValueOfintArrayOfintty7Ep6D1
     */
    private $KeyValueOfintArrayOfintty7Ep6D1 = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\KeyValueOfintArrayOfintty7Ep6D1
     * $KeyValueOfintArrayOfintty7Ep6D1
     */
    public function __construct($KeyValueOfintArrayOfintty7Ep6D1)
    {
        $this->KeyValueOfintArrayOfintty7Ep6D1 = $KeyValueOfintArrayOfintty7Ep6D1;
    }

    /**
     * @return \ArchiflowWSCard\Type\KeyValueOfintArrayOfintty7Ep6D1
     */
    public function getKeyValueOfintArrayOfintty7Ep6D1()
    {
        return $this->KeyValueOfintArrayOfintty7Ep6D1;
    }

    /**
     * @param \ArchiflowWSCard\Type\KeyValueOfintArrayOfintty7Ep6D1
     * $KeyValueOfintArrayOfintty7Ep6D1
     * @return ArrayOfKeyValueOfintArrayOfintty7Ep6D1
     */
    public function withKeyValueOfintArrayOfintty7Ep6D1($KeyValueOfintArrayOfintty7Ep6D1)
    {
        $new = clone $this;
        $new->KeyValueOfintArrayOfintty7Ep6D1 = $KeyValueOfintArrayOfintty7Ep6D1;

        return $new;
    }


}

