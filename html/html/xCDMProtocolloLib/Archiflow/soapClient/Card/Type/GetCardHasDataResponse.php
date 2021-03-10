<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardHasDataResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardHasDataOutput
     */
    private $GetCardHasDataResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardHasDataOutput
     */
    public function getGetCardHasDataResult()
    {
        return $this->GetCardHasDataResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardHasDataOutput $GetCardHasDataResult
     * @return GetCardHasDataResponse
     */
    public function withGetCardHasDataResult($GetCardHasDataResult)
    {
        $new = clone $this;
        $new->GetCardHasDataResult = $GetCardHasDataResult;

        return $new;
    }


}

