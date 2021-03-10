<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LoginWithCredentialAndDeviceIdWhiteListResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $LoginWithCredentialAndDeviceIdWhiteListResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getLoginWithCredentialAndDeviceIdWhiteListResult()
    {
        return $this->LoginWithCredentialAndDeviceIdWhiteListResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo
     * $LoginWithCredentialAndDeviceIdWhiteListResult
     * @return LoginWithCredentialAndDeviceIdWhiteListResponse
     */
    public function withLoginWithCredentialAndDeviceIdWhiteListResult($LoginWithCredentialAndDeviceIdWhiteListResult)
    {
        $new = clone $this;
        $new->LoginWithCredentialAndDeviceIdWhiteListResult = $LoginWithCredentialAndDeviceIdWhiteListResult;

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
     * @return LoginWithCredentialAndDeviceIdWhiteListResponse
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

        return $new;
    }


}

