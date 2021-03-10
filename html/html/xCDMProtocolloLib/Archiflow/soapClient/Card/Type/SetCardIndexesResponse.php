<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardIndexesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SetCardIndexesResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSetCardIndexesResult()
    {
        return $this->SetCardIndexesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SetCardIndexesResult
     * @return SetCardIndexesResponse
     */
    public function withSetCardIndexesResult($SetCardIndexesResult)
    {
        $new = clone $this;
        $new->SetCardIndexesResult = $SetCardIndexesResult;

        return $new;
    }


}

