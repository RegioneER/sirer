<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LoginWithCredentialAndDeviceTokenResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $LoginWithCredentialAndDeviceTokenResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getLoginWithCredentialAndDeviceTokenResult()
    {
        return $this->LoginWithCredentialAndDeviceTokenResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo
     * $LoginWithCredentialAndDeviceTokenResult
     * @return LoginWithCredentialAndDeviceTokenResponse
     */
    public function withLoginWithCredentialAndDeviceTokenResult($LoginWithCredentialAndDeviceTokenResult)
    {
        $new = clone $this;
        $new->LoginWithCredentialAndDeviceTokenResult = $LoginWithCredentialAndDeviceTokenResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\SessionInfo
     */
    public function getOSessionInfo()
    {
        return $this->oSessionInfo;
    }

    /**
     * @param \ArchiflowWSLogin\Type\SessionInfo $oSessionInfo
     * @return LoginWithCredentialAndDeviceTokenResponse
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

        return $new;
    }


}

