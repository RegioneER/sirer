<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CheckInResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $CheckInResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getCheckInResult()
    {
        return $this->CheckInResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $CheckInResult
     * @return CheckInResponse
     */
    public function withCheckInResult($CheckInResult)
    {
        $new = clone $this;
        $new->CheckInResult = $CheckInResult;

        return $new;
    }


}

