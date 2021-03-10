<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DeleteListItemResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $DeleteListItemResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getDeleteListItemResult()
    {
        return $this->DeleteListItemResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $DeleteListItemResult
     * @return DeleteListItemResponse
     */
    public function withDeleteListItemResult($DeleteListItemResult)
    {
        $new = clone $this;
        $new->DeleteListItemResult = $DeleteListItemResult;

        return $new;
    }


}

