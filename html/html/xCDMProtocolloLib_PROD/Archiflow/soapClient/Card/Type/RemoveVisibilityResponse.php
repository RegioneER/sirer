<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RemoveVisibilityResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $RemoveVisibilityResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getRemoveVisibilityResult()
    {
        return $this->RemoveVisibilityResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $RemoveVisibilityResult
     * @return RemoveVisibilityResponse
     */
    public function withRemoveVisibilityResult($RemoveVisibilityResult)
    {
        $new = clone $this;
        $new->RemoveVisibilityResult = $RemoveVisibilityResult;

        return $new;
    }


}

