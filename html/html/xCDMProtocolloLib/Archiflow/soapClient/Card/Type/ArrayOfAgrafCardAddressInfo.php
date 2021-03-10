<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAgrafCardAddressInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AgrafCardAddressInfo
     */
    private $AgrafCardAddressInfo = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AgrafCardAddressInfo $AgrafCardAddressInfo
     */
    public function __construct($AgrafCardAddressInfo)
    {
        $this->AgrafCardAddressInfo = $AgrafCardAddressInfo;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafCardAddressInfo
     */
    public function getAgrafCardAddressInfo()
    {
        return $this->AgrafCardAddressInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafCardAddressInfo $AgrafCardAddressInfo
     * @return ArrayOfAgrafCardAddressInfo
     */
    public function withAgrafCardAddressInfo($AgrafCardAddressInfo)
    {
        $new = clone $this;
        $new->AgrafCardAddressInfo = $AgrafCardAddressInfo;

        return $new;
    }


}

