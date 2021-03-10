<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LogoutResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ResultInfo
     */
    private $LogoutResult = null;

    /**
     * @return \ArchiflowWSLogin\Type\ResultInfo
     */
    public function getLogoutResult()
    {
        return $this->LogoutResult;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ResultInfo $LogoutResult
     * @return LogoutResponse
     */
    public function withLogoutResult($LogoutResult)
    {
        $new = clone $this;
        $new->LogoutResult = $LogoutResult;

        return $new;
    }


}

