<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardsByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardsOutput
     */
    private $GetCardsByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardsOutput
     */
    public function getGetCardsByParamResult()
    {
        return $this->GetCardsByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardsOutput $GetCardsByParamResult
     * @return GetCardsByParamResponse
     */
    public function withGetCardsByParamResult($GetCardsByParamResult)
    {
        $new = clone $this;
        $new->GetCardsByParamResult = $GetCardsByParamResult;

        return $new;
    }


}

