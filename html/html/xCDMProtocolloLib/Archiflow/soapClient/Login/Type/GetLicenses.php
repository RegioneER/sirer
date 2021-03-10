<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetLicenses implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSLogin\Type\ArrayOfLicenseOptions
     */
    private $oLicenseOptions = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSLogin\Type\ArrayOfLicenseOptions $oLicenseOptions
     */
    public function __construct($strSessionId, $oLicenseOptions)
    {
        $this->strSessionId = $strSessionId;
        $this->oLicenseOptions = $oLicenseOptions;
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
     * @return GetLicenses
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\ArrayOfLicenseOptions
     */
    public function getOLicenseOptions()
    {
        return $this->oLicenseOptions;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ArrayOfLicenseOptions $oLicenseOptions
     * @return GetLicenses
     */
    public function withOLicenseOptions($oLicenseOptions)
    {
        $new = clone $this;
        $new->oLicenseOptions = $oLicenseOptions;

        return $new;
    }


}

