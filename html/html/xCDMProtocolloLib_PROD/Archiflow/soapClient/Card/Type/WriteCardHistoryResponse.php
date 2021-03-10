<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class WriteCardHistoryResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $WriteCardHistoryResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getWriteCardHistoryResult()
    {
        return $this->WriteCardHistoryResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $WriteCardHistoryResult
     * @return WriteCardHistoryResponse
     */
    public function withWriteCardHistoryResult($WriteCardHistoryResult)
    {
        $new = clone $this;
        $new->WriteCardHistoryResult = $WriteCardHistoryResult;

        return $new;
    }


}

