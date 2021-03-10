<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfUserRight implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\UserRight
     */
    private $UserRight = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\UserRight $UserRight
     */
    public function __construct($UserRight)
    {
        $this->UserRight = $UserRight;
    }

    /**
     * @return \ArchiflowWSFolder\Type\UserRight
     */
    public function getUserRight()
    {
        return $this->UserRight;
    }

    /**
     * @param \ArchiflowWSFolder\Type\UserRight $UserRight
     * @return ArrayOfUserRight
     */
    public function withUserRight($UserRight)
    {
        $new = clone $this;
        $new->UserRight = $UserRight;

        return $new;
    }


}

