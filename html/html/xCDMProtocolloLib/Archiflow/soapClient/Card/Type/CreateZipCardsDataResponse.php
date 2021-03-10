<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CreateZipCardsDataResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CreateZipCardsDataOutput
     */
    private $CreateZipCardsDataResult = null;

    /**
     * @return \ArchiflowWSCard\Type\CreateZipCardsDataOutput
     */
    public function getCreateZipCardsDataResult()
    {
        return $this->CreateZipCardsDataResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\CreateZipCardsDataOutput $CreateZipCardsDataResult
     * @return CreateZipCardsDataResponse
     */
    public function withCreateZipCardsDataResult($CreateZipCardsDataResult)
    {
        $new = clone $this;
        $new->CreateZipCardsDataResult = $CreateZipCardsDataResult;

        return $new;
    }


}

