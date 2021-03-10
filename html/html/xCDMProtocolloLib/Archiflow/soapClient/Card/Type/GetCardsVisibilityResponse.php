<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardsVisibilityResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardsVisibilityOutput
     */
    private $GetCardsVisibilityResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardsVisibilityOutput
     */
    public function getGetCardsVisibilityResult()
    {
        return $this->GetCardsVisibilityResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardsVisibilityOutput $GetCardsVisibilityResult
     * @return GetCardsVisibilityResponse
     */
    public function withGetCardsVisibilityResult($GetCardsVisibilityResult)
    {
        $new = clone $this;
        $new->GetCardsVisibilityResult = $GetCardsVisibilityResult;

        return $new;
    }


}

