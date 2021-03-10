<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardFromReferenceResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardFromReferenceResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Card
     */
    private $oCard = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardFromReferenceResult()
    {
        return $this->GetCardFromReferenceResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardFromReferenceResult
     * @return GetCardFromReferenceResponse
     */
    public function withGetCardFromReferenceResult($GetCardFromReferenceResult)
    {
        $new = clone $this;
        $new->GetCardFromReferenceResult = $GetCardFromReferenceResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Card
     */
    public function getOCard()
    {
        return $this->oCard;
    }

    /**
     * @param \ArchiflowWSCard\Type\Card $oCard
     * @return GetCardFromReferenceResponse
     */
    public function withOCard($oCard)
    {
        $new = clone $this;
        $new->oCard = $oCard;

        return $new;
    }


}

