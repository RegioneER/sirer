<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetSingleLicenseResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $GetSingleLicenseResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\LicenseOption
     */
    private $oLicense = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getGetSingleLicenseResult()
    {
        return $this->GetSingleLicenseResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo $GetSingleLicenseResult
     * @return GetSingleLicenseResponse
     */
    public function withGetSingleLicenseResult($GetSingleLicenseResult)
    {
        $new = clone $this;
        $new->GetSingleLicenseResult = $GetSingleLicenseResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\LicenseOption
     */
    public function getOLicense()
    {
        return $this->oLicense;
    }

    /**
     * @param \ArchiflowWSLogin\Type\LicenseOption $oLicense
     * @return GetSingleLicenseResponse
     */
    public function withOLicense($oLicense)
    {
        $new = clone $this;
        $new->oLicense = $oLicense;

        return $new;
    }


}

