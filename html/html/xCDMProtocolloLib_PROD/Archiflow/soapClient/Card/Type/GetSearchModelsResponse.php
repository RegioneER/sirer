<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetSearchModelsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetSearchModelsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfstring
     */
    private $searchModelNames = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetSearchModelsResult()
    {
        return $this->GetSearchModelsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetSearchModelsResult
     * @return GetSearchModelsResponse
     */
    public function withGetSearchModelsResult($GetSearchModelsResult)
    {
        $new = clone $this;
        $new->GetSearchModelsResult = $GetSearchModelsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfstring
     */
    public function getSearchModelNames()
    {
        return $this->searchModelNames;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfstring $searchModelNames
     * @return GetSearchModelsResponse
     */
    public function withSearchModelNames($searchModelNames)
    {
        $new = clone $this;
        $new->searchModelNames = $searchModelNames;

        return $new;
    }


}

