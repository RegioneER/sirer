<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SendCard1Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SendCard1Result = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSendCard1Result()
    {
        return $this->SendCard1Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SendCard1Result
     * @return SendCard1Response
     */
    public function withSendCard1Result($SendCard1Result)
    {
        $new = clone $this;
        $new->SendCard1Result = $SendCard1Result;

        return $new;
    }


}

