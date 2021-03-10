<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SearchCardsGroupingResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SearchCardsGroupingResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfArchiveTypedocCardId
     */
    private $oCardIdsExt = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSearchCardsGroupingResult()
    {
        return $this->SearchCardsGroupingResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SearchCardsGroupingResult
     * @return SearchCardsGroupingResponse
     */
    public function withSearchCardsGroupingResult($SearchCardsGroupingResult)
    {
        $new = clone $this;
        $new->SearchCardsGroupingResult = $SearchCardsGroupingResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfArchiveTypedocCardId
     */
    public function getOCardIdsExt()
    {
        return $this->oCardIdsExt;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfArchiveTypedocCardId $oCardIdsExt
     * @return SearchCardsGroupingResponse
     */
    public function withOCardIdsExt($oCardIdsExt)
    {
        $new = clone $this;
        $new->oCardIdsExt = $oCardIdsExt;

        return $new;
    }


}

