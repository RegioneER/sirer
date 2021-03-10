<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RemoveVisibilityByIdResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $RemoveVisibilityByIdResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getRemoveVisibilityByIdResult()
    {
        return $this->RemoveVisibilityByIdResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $RemoveVisibilityByIdResult
     * @return RemoveVisibilityByIdResponse
     */
    public function withRemoveVisibilityByIdResult($RemoveVisibilityByIdResult)
    {
        $new = clone $this;
        $new->RemoveVisibilityByIdResult = $RemoveVisibilityByIdResult;

        return $new;
    }


}

