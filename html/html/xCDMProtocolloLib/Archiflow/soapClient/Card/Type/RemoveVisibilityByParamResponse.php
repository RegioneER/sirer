<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RemoveVisibilityByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\RemoveVisibilityOutput
     */
    private $RemoveVisibilityByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\RemoveVisibilityOutput
     */
    public function getRemoveVisibilityByParamResult()
    {
        return $this->RemoveVisibilityByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\RemoveVisibilityOutput
     * $RemoveVisibilityByParamResult
     * @return RemoveVisibilityByParamResponse
     */
    public function withRemoveVisibilityByParamResult($RemoveVisibilityByParamResult)
    {
        $new = clone $this;
        $new->RemoveVisibilityByParamResult = $RemoveVisibilityByParamResult;

        return $new;
    }


}

