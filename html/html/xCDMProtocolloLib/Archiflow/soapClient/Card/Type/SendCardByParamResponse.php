<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SendCardByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SendCardOutput
     */
    private $SendCardByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\SendCardOutput
     */
    public function getSendCardByParamResult()
    {
        return $this->SendCardByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendCardOutput $SendCardByParamResult
     * @return SendCardByParamResponse
     */
    public function withSendCardByParamResult($SendCardByParamResult)
    {
        $new = clone $this;
        $new->SendCardByParamResult = $SendCardByParamResult;

        return $new;
    }


}

