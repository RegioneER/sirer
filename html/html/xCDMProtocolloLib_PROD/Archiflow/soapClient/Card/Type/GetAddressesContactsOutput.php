<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetAddressesContactsOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardTagAddressInfo
     */
    private $AgrafCardTagAddresses = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfAgrafCardTagAddressInfo $AgrafCardTagAddresses
     */
    public function __construct($AgrafCardTagAddresses)
    {
        $this->AgrafCardTagAddresses = $AgrafCardTagAddresses;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAgrafCardTagAddressInfo
     */
    public function getAgrafCardTagAddresses()
    {
        return $this->AgrafCardTagAddresses;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAgrafCardTagAddressInfo
     * $AgrafCardTagAddresses
     * @return GetAddressesContactsOutput
     */
    public function withAgrafCardTagAddresses($AgrafCardTagAddresses)
    {
        $new = clone $this;
        $new->AgrafCardTagAddresses = $AgrafCardTagAddresses;

        return $new;
    }


}

