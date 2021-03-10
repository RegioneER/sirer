<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RetrieveCardsByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\RetrieveCardsOutput
     */
    private $RetrieveCardsByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\RetrieveCardsOutput
     */
    public function getRetrieveCardsByParamResult()
    {
        return $this->RetrieveCardsByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\RetrieveCardsOutput $RetrieveCardsByParamResult
     * @return RetrieveCardsByParamResponse
     */
    public function withRetrieveCardsByParamResult($RetrieveCardsByParamResult)
    {
        $new = clone $this;
        $new->RetrieveCardsByParamResult = $RetrieveCardsByParamResult;

        return $new;
    }


}

