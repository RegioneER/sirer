<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfLicenseOptions implements RequestInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\LicenseOptions
     */
    private $LicenseOptions = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSLogin\Type\LicenseOptions $LicenseOptions
     */
    public function __construct($LicenseOptions)
    {
        $this->LicenseOptions = $LicenseOptions;
    }

    /**
     * @return \ArchiflowWSLogin\Type\LicenseOptions
     */
    public function getLicenseOptions()
    {
        return $this->LicenseOptions;
    }

    /**
     * @param \ArchiflowWSLogin\Type\LicenseOptions $LicenseOptions
     * @return ArrayOfLicenseOptions
     */
    public function withLicenseOptions($LicenseOptions)
    {
        $new = clone $this;
        $new->LicenseOptions = $LicenseOptions;

        return $new;
    }


}

