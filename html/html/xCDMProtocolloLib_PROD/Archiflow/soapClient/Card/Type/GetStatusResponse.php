<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetStatusResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetStatusResult = null;

    /**
     * @var \ArchiflowWSCard\Type\CardStatus
     */
    private $cardStatus = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetStatusResult()
    {
        return $this->GetStatusResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetStatusResult
     * @return GetStatusResponse
     */
    public function withGetStatusResult($GetStatusResult)
    {
        $new = clone $this;
        $new->GetStatusResult = $GetStatusResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardStatus
     */
    public function getCardStatus()
    {
        return $this->cardStatus;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardStatus $cardStatus
     * @return GetStatusResponse
     */
    public function withCardStatus($cardStatus)
    {
        $new = clone $this;
        $new->cardStatus = $cardStatus;

        return $new;
    }


}

