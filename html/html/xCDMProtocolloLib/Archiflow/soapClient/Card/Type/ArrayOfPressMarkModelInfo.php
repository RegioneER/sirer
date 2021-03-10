<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfPressMarkModelInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\PressMarkModelInfo
     */
    private $PressMarkModelInfo = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\PressMarkModelInfo $PressMarkModelInfo
     */
    public function __construct($PressMarkModelInfo)
    {
        $this->PressMarkModelInfo = $PressMarkModelInfo;
    }

    /**
     * @return \ArchiflowWSCard\Type\PressMarkModelInfo
     */
    public function getPressMarkModelInfo()
    {
        return $this->PressMarkModelInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\PressMarkModelInfo $PressMarkModelInfo
     * @return ArrayOfPressMarkModelInfo
     */
    public function withPressMarkModelInfo($PressMarkModelInfo)
    {
        $new = clone $this;
        $new->PressMarkModelInfo = $PressMarkModelInfo;

        return $new;
    }


}

