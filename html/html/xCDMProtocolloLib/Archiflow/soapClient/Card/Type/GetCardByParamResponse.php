<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardOutput
     */
    private $GetCardByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardOutput
     */
    public function getGetCardByParamResult()
    {
        return $this->GetCardByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardOutput $GetCardByParamResult
     * @return GetCardByParamResponse
     */
    public function withGetCardByParamResult($GetCardByParamResult)
    {
        $new = clone $this;
        $new->GetCardByParamResult = $GetCardByParamResult;

        return $new;
    }


}

