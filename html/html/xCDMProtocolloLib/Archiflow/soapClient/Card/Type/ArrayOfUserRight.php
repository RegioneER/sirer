<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfUserRight implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\UserRight
     */
    private $UserRight = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\UserRight $UserRight
     */
    public function __construct($UserRight)
    {
        $this->UserRight = $UserRight;
    }

    /**
     * @return \ArchiflowWSCard\Type\UserRight
     */
    public function getUserRight()
    {
        return $this->UserRight;
    }

    /**
     * @param \ArchiflowWSCard\Type\UserRight $UserRight
     * @return ArrayOfUserRight
     */
    public function withUserRight($UserRight)
    {
        $new = clone $this;
        $new->UserRight = $UserRight;

        return $new;
    }


}

