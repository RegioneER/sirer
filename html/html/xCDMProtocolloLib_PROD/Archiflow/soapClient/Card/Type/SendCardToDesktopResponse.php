<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SendCardToDesktopResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SendCardToDesktopResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSendCardToDesktopResult()
    {
        return $this->SendCardToDesktopResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SendCardToDesktopResult
     * @return SendCardToDesktopResponse
     */
    public function withSendCardToDesktopResult($SendCardToDesktopResult)
    {
        $new = clone $this;
        $new->SendCardToDesktopResult = $SendCardToDesktopResult;

        return $new;
    }


}

