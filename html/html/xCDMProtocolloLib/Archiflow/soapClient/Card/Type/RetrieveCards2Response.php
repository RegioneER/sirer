<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RetrieveCards2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $RetrieveCards2Result = null;

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
    public function getRetrieveCards2Result()
    {
        return $this->RetrieveCards2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $RetrieveCards2Result
     * @return RetrieveCards2Response
     */
    public function withRetrieveCards2Result($RetrieveCards2Result)
    {
        $new = clone $this;
        $new->RetrieveCards2Result = $RetrieveCards2Result;

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
     * @return RetrieveCards2Response
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
     * @return RetrieveCards2Response
     */
    public function withOCards($oCards)
    {
        $new = clone $this;
        $new->oCards = $oCards;

        return $new;
    }


}

