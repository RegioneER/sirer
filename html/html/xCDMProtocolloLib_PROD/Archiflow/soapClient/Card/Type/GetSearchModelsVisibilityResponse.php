<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetSearchModelsVisibilityResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetSearchModelsVisibilityOutput
     */
    private $GetSearchModelsVisibilityResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetSearchModelsVisibilityOutput
     */
    public function getGetSearchModelsVisibilityResult()
    {
        return $this->GetSearchModelsVisibilityResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetSearchModelsVisibilityOutput
     * $GetSearchModelsVisibilityResult
     * @return GetSearchModelsVisibilityResponse
     */
    public function withGetSearchModelsVisibilityResult($GetSearchModelsVisibilityResult)
    {
        $new = clone $this;
        $new->GetSearchModelsVisibilityResult = $GetSearchModelsVisibilityResult;

        return $new;
    }


}

