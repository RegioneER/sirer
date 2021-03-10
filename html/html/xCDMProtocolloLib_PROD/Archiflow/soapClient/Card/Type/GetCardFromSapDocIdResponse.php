<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardFromSapDocIdResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardFromSapDocIdResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Card
     */
    private $card = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardFromSapDocIdResult()
    {
        return $this->GetCardFromSapDocIdResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardFromSapDocIdResult
     * @return GetCardFromSapDocIdResponse
     */
    public function withGetCardFromSapDocIdResult($GetCardFromSapDocIdResult)
    {
        $new = clone $this;
        $new->GetCardFromSapDocIdResult = $GetCardFromSapDocIdResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Card
     */
    public function getCard()
    {
        return $this->card;
    }

    /**
     * @param \ArchiflowWSCard\Type\Card $card
     * @return GetCardFromSapDocIdResponse
     */
    public function withCard($card)
    {
        $new = clone $this;
        $new->card = $card;

        return $new;
    }


}

