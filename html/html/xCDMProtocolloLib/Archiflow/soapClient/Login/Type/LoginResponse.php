<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LoginResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $LoginResult = null;

    /**
     * @var \ArchiflowWSLogin\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getLoginResult()
    {
        return $this->LoginResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo $LoginResult
     * @return LoginResponse
     */
    public function withLoginResult($LoginResult)
    {
        $new = clone $this;
        $new->LoginResult = $LoginResult;

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
     * @return LoginResponse
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

        return $new;
    }


}

