<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LoginResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\LoginOut
     */
    private $LoginResult = null;

    /**
     * @return \IrideWS\Type\LoginOut
     */
    public function getLoginResult()
    {
        return $this->LoginResult;
    }

    /**
     * @param \IrideWS\Type\LoginOut $LoginResult
     * @return LoginResponse
     */
    public function withLoginResult($LoginResult)
    {
        $new = clone $this;
        $new->LoginResult = $LoginResult;

        return $new;
    }


}

