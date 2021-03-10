<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LoginMultiDBResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\LoginOut
     */
    private $LoginMultiDBResult = null;

    /**
     * @return \IrideWS\Type\LoginOut
     */
    public function getLoginMultiDBResult()
    {
        return $this->LoginMultiDBResult;
    }

    /**
     * @param \IrideWS\Type\LoginOut $LoginMultiDBResult
     * @return LoginMultiDBResponse
     */
    public function withLoginMultiDBResult($LoginMultiDBResult)
    {
        $new = clone $this;
        $new->LoginMultiDBResult = $LoginMultiDBResult;

        return $new;
    }


}

