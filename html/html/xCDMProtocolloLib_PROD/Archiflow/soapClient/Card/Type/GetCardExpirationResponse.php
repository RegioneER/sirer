<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardExpirationResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardExpirationOutput
     */
    private $GetCardExpirationResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardExpirationOutput
     */
    public function getGetCardExpirationResult()
    {
        return $this->GetCardExpirationResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardExpirationOutput $GetCardExpirationResult
     * @return GetCardExpirationResponse
     */
    public function withGetCardExpirationResult($GetCardExpirationResult)
    {
        $new = clone $this;
        $new->GetCardExpirationResult = $GetCardExpirationResult;

        return $new;
    }


}

