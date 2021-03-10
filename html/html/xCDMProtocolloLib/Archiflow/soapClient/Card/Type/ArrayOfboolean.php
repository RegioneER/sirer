<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfboolean implements RequestInterface
{

    /**
     * @var bool
     */
    private $boolean = null;

    /**
     * Constructor
     *
     * @var bool $boolean
     */
    public function __construct($boolean)
    {
        $this->boolean = $boolean;
    }

    /**
     * @return bool
     */
    public function getBoolean()
    {
        return $this->boolean;
    }

    /**
     * @param bool $boolean
     * @return ArrayOfboolean
     */
    public function withBoolean($boolean)
    {
        $new = clone $this;
        $new->boolean = $boolean;

        return $new;
    }


}

