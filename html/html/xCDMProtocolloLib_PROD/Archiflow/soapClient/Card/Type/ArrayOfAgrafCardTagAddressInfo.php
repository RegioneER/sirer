<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAgrafCardTagAddressInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AgrafCardTagAddressInfo
     */
    private $AgrafCardTagAddressInfo = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AgrafCardTagAddressInfo $AgrafCardTagAddressInfo
     */
    public function __construct($AgrafCardTagAddressInfo)
    {
        $this->AgrafCardTagAddressInfo = $AgrafCardTagAddressInfo;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafCardTagAddressInfo
     */
    public function getAgrafCardTagAddressInfo()
    {
        return $this->AgrafCardTagAddressInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafCardTagAddressInfo $AgrafCardTagAddressInfo
     * @return ArrayOfAgrafCardTagAddressInfo
     */
    public function withAgrafCardTagAddressInfo($AgrafCardTagAddressInfo)
    {
        $new = clone $this;
        $new->AgrafCardTagAddressInfo = $AgrafCardTagAddressInfo;

        return $new;
    }


}

