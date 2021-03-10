<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetSingleLicense implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSLogin\Type\LicenseOptions
     */
    private $oLicenseOption = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSLogin\Type\LicenseOptions $oLicenseOption
     */
    public function __construct($strSessionId, $oLicenseOption)
    {
        $this->strSessionId = $strSessionId;
        $this->oLicenseOption = $oLicenseOption;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return GetSingleLicense
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\LicenseOptions
     */
    public function getOLicenseOption()
    {
        return $this->oLicenseOption;
    }

    /**
     * @param \ArchiflowWSLogin\Type\LicenseOptions $oLicenseOption
     * @return GetSingleLicense
     */
    public function withOLicenseOption($oLicenseOption)
    {
        $new = clone $this;
        $new->oLicenseOption = $oLicenseOption;

        return $new;
    }


}

