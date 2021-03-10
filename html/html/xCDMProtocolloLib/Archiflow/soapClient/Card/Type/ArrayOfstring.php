<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfstring implements RequestInterface
{

    /**
     * @var string
     */
    private $string = null;

    /**
     * Constructor
     *
     * @var string $string
     */
    public function __construct($string)
    {
        $this->string = $string;
    }

    /**
     * @return string
     */
    public function getString()
    {
        return $this->string;
    }

    /**
     * @param string $string
     * @return ArrayOfstring
     */
    public function withString($string)
    {
        $new = clone $this;
        $new->string = $string;

        return $new;
    }


}

