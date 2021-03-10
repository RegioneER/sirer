<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RetrieveCardsFromSearchModelResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $RetrieveCardsFromSearchModelResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfCard
     */
    private $oCards = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getRetrieveCardsFromSearchModelResult()
    {
        return $this->RetrieveCardsFromSearchModelResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $RetrieveCardsFromSearchModelResult
     * @return RetrieveCardsFromSearchModelResponse
     */
    public function withRetrieveCardsFromSearchModelResult($RetrieveCardsFromSearchModelResult)
    {
        $new = clone $this;
        $new->RetrieveCardsFromSearchModelResult = $RetrieveCardsFromSearchModelResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfCard
     */
    public function getOCards()
    {
        return $this->oCards;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfCard $oCards
     * @return RetrieveCardsFromSearchModelResponse
     */
    public function withOCards($oCards)
    {
        $new = clone $this;
        $new->oCards = $oCards;

        return $new;
    }


}

