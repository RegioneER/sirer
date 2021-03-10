<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocumentSignatureCertificateResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardDocumentSignatureCertificateOutput
     */
    private $GetCardDocumentSignatureCertificateResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardDocumentSignatureCertificateOutput
     */
    public function getGetCardDocumentSignatureCertificateResult()
    {
        return $this->GetCardDocumentSignatureCertificateResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardDocumentSignatureCertificateOutput
     * $GetCardDocumentSignatureCertificateResult
     * @return GetCardDocumentSignatureCertificateResponse
     */
    public function withGetCardDocumentSignatureCertificateResult($GetCardDocumentSignatureCertificateResult)
    {
        $new = clone $this;
        $new->GetCardDocumentSignatureCertificateResult = $GetCardDocumentSignatureCertificateResult;

        return $new;
    }


}

