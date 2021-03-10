<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardIndexesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardIndexesResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfField
     */
    private $oIndexes = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardIndexesResult()
    {
        return $this->GetCardIndexesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardIndexesResult
     * @return GetCardIndexesResponse
     */
    public function withGetCardIndexesResult($GetCardIndexesResult)
    {
        $new = clone $this;
        $new->GetCardIndexesResult = $GetCardIndexesResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfField
     */
    public function getOIndexes()
    {
        return $this->oIndexes;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfField $oIndexes
     * @return GetCardIndexesResponse
     */
    public function withOIndexes($oIndexes)
    {
        $new = clone $this;
        $new->oIndexes = $oIndexes;

        return $new;
    }


}

