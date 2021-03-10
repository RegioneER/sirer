<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardValidationByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SetCardValidationOutput
     */
    private $SetCardValidationByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\SetCardValidationOutput
     */
    public function getSetCardValidationByParamResult()
    {
        return $this->SetCardValidationByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\SetCardValidationOutput
     * $SetCardValidationByParamResult
     * @return SetCardValidationByParamResponse
     */
    public function withSetCardValidationByParamResult($SetCardValidationByParamResult)
    {
        $new = clone $this;
        $new->SetCardValidationByParamResult = $SetCardValidationByParamResult;

        return $new;
    }


}

