<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DeleteCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $DeleteCardResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getDeleteCardResult()
    {
        return $this->DeleteCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $DeleteCardResult
     * @return DeleteCardResponse
     */
    public function withDeleteCardResult($DeleteCardResult)
    {
        $new = clone $this;
        $new->DeleteCardResult = $DeleteCardResult;

        return $new;
    }


}

