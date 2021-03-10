<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfLicenseOption implements RequestInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\LicenseOption
     */
    private $LicenseOption = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSLogin\Type\LicenseOption $LicenseOption
     */
    public function __construct($LicenseOption)
    {
        $this->LicenseOption = $LicenseOption;
    }

    /**
     * @return \ArchiflowWSLogin\Type\LicenseOption
     */
    public function getLicenseOption()
    {
        return $this->LicenseOption;
    }

    /**
     * @param \ArchiflowWSLogin\Type\LicenseOption $LicenseOption
     * @return ArrayOfLicenseOption
     */
    public function withLicenseOption($LicenseOption)
    {
        $new = clone $this;
        $new->LicenseOption = $LicenseOption;

        return $new;
    }


}

