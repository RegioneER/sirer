<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RetrieveCardsFromSearchModel2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $RetrieveCardsFromSearchModel2Result = null;

    /**
     * @var int
     */
    private $HitCount = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfCard
     */
    private $oCards = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getRetrieveCardsFromSearchModel2Result()
    {
        return $this->RetrieveCardsFromSearchModel2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $RetrieveCardsFromSearchModel2Result
     * @return RetrieveCardsFromSearchModel2Response
     */
    public function withRetrieveCardsFromSearchModel2Result($RetrieveCardsFromSearchModel2Result)
    {
        $new = clone $this;
        $new->RetrieveCardsFromSearchModel2Result = $RetrieveCardsFromSearchModel2Result;

        return $new;
    }

    /**
     * @return int
     */
    public function getHitCount()
    {
        return $this->HitCount;
    }

    /**
     * @param int $HitCount
     * @return RetrieveCardsFromSearchModel2Response
     */
    public function withHitCount($HitCount)
    {
        $new = clone $this;
        $new->HitCount = $HitCount;

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
     * @return RetrieveCardsFromSearchModel2Response
     */
    public function withOCards($oCards)
    {
        $new = clone $this;
        $new->oCards = $oCards;

        return $new;
    }


}

