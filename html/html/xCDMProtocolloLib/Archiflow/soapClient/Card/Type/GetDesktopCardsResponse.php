<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDesktopCardsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDesktopCardsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfCard
     */
    private $oCards = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDesktopCardsResult()
    {
        return $this->GetDesktopCardsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetDesktopCardsResult
     * @return GetDesktopCardsResponse
     */
    public function withGetDesktopCardsResult($GetDesktopCardsResult)
    {
        $new = clone $this;
        $new->GetDesktopCardsResult = $GetDesktopCardsResult;

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
     * @return GetDesktopCardsResponse
     */
    public function withOCards($oCards)
    {
        $new = clone $this;
        $new->oCards = $oCards;

        return $new;
    }


}

