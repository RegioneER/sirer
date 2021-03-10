<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardValidationResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SetCardValidationResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSetCardValidationResult()
    {
        return $this->SetCardValidationResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SetCardValidationResult
     * @return SetCardValidationResponse
     */
    public function withSetCardValidationResult($SetCardValidationResult)
    {
        $new = clone $this;
        $new->SetCardValidationResult = $SetCardValidationResult;

        return $new;
    }


}

