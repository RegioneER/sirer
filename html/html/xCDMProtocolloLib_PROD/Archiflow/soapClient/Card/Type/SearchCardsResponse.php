<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SearchCardsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SearchCardsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $oCardIds = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSearchCardsResult()
    {
        return $this->SearchCardsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SearchCardsResult
     * @return SearchCardsResponse
     */
    public function withSearchCardsResult($SearchCardsResult)
    {
        $new = clone $this;
        $new->SearchCardsResult = $SearchCardsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getOCardIds()
    {
        return $this->oCardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     * @return SearchCardsResponse
     */
    public function withOCardIds($oCardIds)
    {
        $new = clone $this;
        $new->oCardIds = $oCardIds;

        return $new;
    }


}

