<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetLicenseResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $GetLicenseResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\ArrayOfLicenseOption
     */
    private $oLicenses = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getGetLicenseResult()
    {
        return $this->GetLicenseResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo $GetLicenseResult
     * @return GetLicenseResponse
     */
    public function withGetLicenseResult($GetLicenseResult)
    {
        $new = clone $this;
        $new->GetLicenseResult = $GetLicenseResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\ArrayOfLicenseOption
     */
    public function getOLicenses()
    {
        return $this->oLicenses;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ArrayOfLicenseOption $oLicenses
     * @return GetLicenseResponse
     */
    public function withOLicenses($oLicenses)
    {
        $new = clone $this;
        $new->oLicenses = $oLicenses;

        return $new;
    }


}

