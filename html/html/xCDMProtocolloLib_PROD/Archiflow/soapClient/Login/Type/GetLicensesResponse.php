<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetLicensesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $GetLicensesResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\ArrayOfLicenseOption
     */
    private $oLicenses = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getGetLicensesResult()
    {
        return $this->GetLicensesResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo $GetLicensesResult
     * @return GetLicensesResponse
     */
    public function withGetLicensesResult($GetLicensesResult)
    {
        $new = clone $this;
        $new->GetLicensesResult = $GetLicensesResult;

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
     * @return GetLicensesResponse
     */
    public function withOLicenses($oLicenses)
    {
        $new = clone $this;
        $new->oLicenses = $oLicenses;

        return $new;
    }


}

