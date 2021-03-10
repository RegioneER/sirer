<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CheckCreateZipCardsDataResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CheckCreateZipCardsDataOutput
     */
    private $CheckCreateZipCardsDataResult = null;

    /**
     * @return \ArchiflowWSCard\Type\CheckCreateZipCardsDataOutput
     */
    public function getCheckCreateZipCardsDataResult()
    {
        return $this->CheckCreateZipCardsDataResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\CheckCreateZipCardsDataOutput
     * $CheckCreateZipCardsDataResult
     * @return CheckCreateZipCardsDataResponse
     */
    public function withCheckCreateZipCardsDataResult($CheckCreateZipCardsDataResult)
    {
        $new = clone $this;
        $new->CheckCreateZipCardsDataResult = $CheckCreateZipCardsDataResult;

        return $new;
    }


}

