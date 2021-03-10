<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetSearchModelResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetSearchModelResult = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchCriteria
     */
    private $searchCriteria = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetSearchModelResult()
    {
        return $this->GetSearchModelResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetSearchModelResult
     * @return GetSearchModelResponse
     */
    public function withGetSearchModelResult($GetSearchModelResult)
    {
        $new = clone $this;
        $new->GetSearchModelResult = $GetSearchModelResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchCriteria
     */
    public function getSearchCriteria()
    {
        return $this->searchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchCriteria $searchCriteria
     * @return GetSearchModelResponse
     */
    public function withSearchCriteria($searchCriteria)
    {
        $new = clone $this;
        $new->searchCriteria = $searchCriteria;

        return $new;
    }


}

