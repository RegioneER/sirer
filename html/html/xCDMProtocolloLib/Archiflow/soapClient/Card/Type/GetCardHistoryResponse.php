<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardHistoryResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardHistoryResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfHistory
     */
    private $oHistories = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardHistoryResult()
    {
        return $this->GetCardHistoryResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardHistoryResult
     * @return GetCardHistoryResponse
     */
    public function withGetCardHistoryResult($GetCardHistoryResult)
    {
        $new = clone $this;
        $new->GetCardHistoryResult = $GetCardHistoryResult;

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
     * @return GetCardHistoryResponse
     */
    public function withOHistories($oHistories)
    {
        $new = clone $this;
        $new->oHistories = $oHistories;

        return $new;
    }


}

