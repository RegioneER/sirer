<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SendCardsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SendCardsOutput
     */
    private $SendCardsResult = null;

    /**
     * @return \ArchiflowWSCard\Type\SendCardsOutput
     */
    public function getSendCardsResult()
    {
        return $this->SendCardsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendCardsOutput $SendCardsResult
     * @return SendCardsResponse
     */
    public function withSendCardsResult($SendCardsResult)
    {
        $new = clone $this;
        $new->SendCardsResult = $SendCardsResult;

        return $new;
    }


}

