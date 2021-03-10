<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAgrafCardContactAddressInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AgrafCardContactAddressInfo
     */
    private $AgrafCardContactAddressInfo = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AgrafCardContactAddressInfo
     * $AgrafCardContactAddressInfo
     */
    public function __construct($AgrafCardContactAddressInfo)
    {
        $this->AgrafCardContactAddressInfo = $AgrafCardContactAddressInfo;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafCardContactAddressInfo
     */
    public function getAgrafCardContactAddressInfo()
    {
        return $this->AgrafCardContactAddressInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafCardContactAddressInfo
     * $AgrafCardContactAddressInfo
     * @return ArrayOfAgrafCardContactAddressInfo
     */
    public function withAgrafCardContactAddressInfo($AgrafCardContactAddressInfo)
    {
        $new = clone $this;
        $new->AgrafCardContactAddressInfo = $AgrafCardContactAddressInfo;

        return $new;
    }


}

