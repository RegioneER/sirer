<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CheckOutResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $CheckOutResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getCheckOutResult()
    {
        return $this->CheckOutResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $CheckOutResult
     * @return CheckOutResponse
     */
    public function withCheckOutResult($CheckOutResult)
    {
        $new = clone $this;
        $new->CheckOutResult = $CheckOutResult;

        return $new;
    }


}

