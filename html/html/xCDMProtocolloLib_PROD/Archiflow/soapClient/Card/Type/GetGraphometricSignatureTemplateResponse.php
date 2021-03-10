<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetGraphometricSignatureTemplateResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetGraphometricSignatureTemplateOutput
     */
    private $GetGraphometricSignatureTemplateResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetGraphometricSignatureTemplateOutput
     */
    public function getGetGraphometricSignatureTemplateResult()
    {
        return $this->GetGraphometricSignatureTemplateResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetGraphometricSignatureTemplateOutput
     * $GetGraphometricSignatureTemplateResult
     * @return GetGraphometricSignatureTemplateResponse
     */
    public function withGetGraphometricSignatureTemplateResult($GetGraphometricSignatureTemplateResult)
    {
        $new = clone $this;
        $new->GetGraphometricSignatureTemplateResult = $GetGraphometricSignatureTemplateResult;

        return $new;
    }


}

