<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SendCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SendCardResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSendCardResult()
    {
        return $this->SendCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SendCardResult
     * @return SendCardResponse
     */
    public function withSendCardResult($SendCardResult)
    {
        $new = clone $this;
        $new->SendCardResult = $SendCardResult;

        return $new;
    }


}

