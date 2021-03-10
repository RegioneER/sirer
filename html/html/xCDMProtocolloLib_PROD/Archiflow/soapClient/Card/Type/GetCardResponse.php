<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Card
     */
    private $oCard = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardResult()
    {
        return $this->GetCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardResult
     * @return GetCardResponse
     */
    public function withGetCardResult($GetCardResult)
    {
        $new = clone $this;
        $new->GetCardResult = $GetCardResult;

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
     * @return GetCardResponse
     */
    public function withOCard($oCard)
    {
        $new = clone $this;
        $new->oCard = $oCard;

        return $new;
    }


}

