<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetPressMarkInfoResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetPressMarkInfoOutput
     */
    private $GetPressMarkInfoResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetPressMarkInfoOutput
     */
    public function getGetPressMarkInfoResult()
    {
        return $this->GetPressMarkInfoResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetPressMarkInfoOutput $GetPressMarkInfoResult
     * @return GetPressMarkInfoResponse
     */
    public function withGetPressMarkInfoResult($GetPressMarkInfoResult)
    {
        $new = clone $this;
        $new->GetPressMarkInfoResult = $GetPressMarkInfoResult;

        return $new;
    }


}

