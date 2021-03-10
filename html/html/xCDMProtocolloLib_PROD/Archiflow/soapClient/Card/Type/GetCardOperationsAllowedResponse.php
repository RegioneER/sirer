<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardOperationsAllowedResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CardOperationsOutput
     */
    private $GetCardOperationsAllowedResult = null;

    /**
     * @return \ArchiflowWSCard\Type\CardOperationsOutput
     */
    public function getGetCardOperationsAllowedResult()
    {
        return $this->GetCardOperationsAllowedResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardOperationsOutput
     * $GetCardOperationsAllowedResult
     * @return GetCardOperationsAllowedResponse
     */
    public function withGetCardOperationsAllowedResult($GetCardOperationsAllowedResult)
    {
        $new = clone $this;
        $new->GetCardOperationsAllowedResult = $GetCardOperationsAllowedResult;

        return $new;
    }


}

