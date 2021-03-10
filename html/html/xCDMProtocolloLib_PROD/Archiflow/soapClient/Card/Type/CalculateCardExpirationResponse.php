<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CalculateCardExpirationResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CalculateCardExpirationOutput
     */
    private $CalculateCardExpirationResult = null;

    /**
     * @return \ArchiflowWSCard\Type\CalculateCardExpirationOutput
     */
    public function getCalculateCardExpirationResult()
    {
        return $this->CalculateCardExpirationResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\CalculateCardExpirationOutput
     * $CalculateCardExpirationResult
     * @return CalculateCardExpirationResponse
     */
    public function withCalculateCardExpirationResult($CalculateCardExpirationResult)
    {
        $new = clone $this;
        $new->CalculateCardExpirationResult = $CalculateCardExpirationResult;

        return $new;
    }


}

