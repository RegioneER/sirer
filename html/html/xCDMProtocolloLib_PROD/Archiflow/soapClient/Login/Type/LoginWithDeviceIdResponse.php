<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LoginWithDeviceIdResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $LoginWithDeviceIdResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getLoginWithDeviceIdResult()
    {
        return $this->LoginWithDeviceIdResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo $LoginWithDeviceIdResult
     * @return LoginWithDeviceIdResponse
     */
    public function withLoginWithDeviceIdResult($LoginWithDeviceIdResult)
    {
        $new = clone $this;
        $new->LoginWithDeviceIdResult = $LoginWithDeviceIdResult;

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
     * @return LoginWithDeviceIdResponse
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

        return $new;
    }


}

