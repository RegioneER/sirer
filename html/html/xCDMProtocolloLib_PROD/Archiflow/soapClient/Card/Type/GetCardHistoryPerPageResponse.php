<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardHistoryPerPageResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardHistoryPerPageResult = null;

    /**
     * @var int
     */
    private $HitCount = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfHistory
     */
    private $oHistories = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardHistoryPerPageResult()
    {
        return $this->GetCardHistoryPerPageResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardHistoryPerPageResult
     * @return GetCardHistoryPerPageResponse
     */
    public function withGetCardHistoryPerPageResult($GetCardHistoryPerPageResult)
    {
        $new = clone $this;
        $new->GetCardHistoryPerPageResult = $GetCardHistoryPerPageResult;

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
     * @return GetCardHistoryPerPageResponse
     */
    public function withHitCount($HitCount)
    {
        $new = clone $this;
        $new->HitCount = $HitCount;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfHistory
     */
    public function getOHistories()
    {
        return $this->oHistories;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfHistory $oHistories
     * @return GetCardHistoryPerPageResponse
     */
    public function withOHistories($oHistories)
    {
        $new = clone $this;
        $new->oHistories = $oHistories;

        return $new;
    }


}

