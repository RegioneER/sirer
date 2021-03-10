<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RetrieveCardsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $RetrieveCardsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfCard
     */
    private $oCards = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getRetrieveCardsResult()
    {
        return $this->RetrieveCardsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $RetrieveCardsResult
     * @return RetrieveCardsResponse
     */
    public function withRetrieveCardsResult($RetrieveCardsResult)
    {
        $new = clone $this;
        $new->RetrieveCardsResult = $RetrieveCardsResult;

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
     * @return RetrieveCardsResponse
     */
    public function withOCards($oCards)
    {
        $new = clone $this;
        $new->oCards = $oCards;

        return $new;
    }


}

