<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetListItemsByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetListItemsOutput
     */
    private $GetListItemsByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetListItemsOutput
     */
    public function getGetListItemsByParamResult()
    {
        return $this->GetListItemsByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetListItemsOutput $GetListItemsByParamResult
     * @return GetListItemsByParamResponse
     */
    public function withGetListItemsByParamResult($GetListItemsByParamResult)
    {
        $new = clone $this;
        $new->GetListItemsByParamResult = $GetListItemsByParamResult;

        return $new;
    }


}

