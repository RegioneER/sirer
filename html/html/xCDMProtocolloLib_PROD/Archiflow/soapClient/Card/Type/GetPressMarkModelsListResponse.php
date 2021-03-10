<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetPressMarkModelsListResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetPressMarkModelsListOutput
     */
    private $GetPressMarkModelsListResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetPressMarkModelsListOutput
     */
    public function getGetPressMarkModelsListResult()
    {
        return $this->GetPressMarkModelsListResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetPressMarkModelsListOutput
     * $GetPressMarkModelsListResult
     * @return GetPressMarkModelsListResponse
     */
    public function withGetPressMarkModelsListResult($GetPressMarkModelsListResult)
    {
        $new = clone $this;
        $new->GetPressMarkModelsListResult = $GetPressMarkModelsListResult;

        return $new;
    }


}

