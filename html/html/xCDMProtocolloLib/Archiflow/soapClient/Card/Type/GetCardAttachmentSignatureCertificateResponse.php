<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardAttachmentSignatureCertificateResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardAttachmentSignatureCertificateOutput
     */
    private $GetCardAttachmentSignatureCertificateResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardAttachmentSignatureCertificateOutput
     */
    public function getGetCardAttachmentSignatureCertificateResult()
    {
        return $this->GetCardAttachmentSignatureCertificateResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardAttachmentSignatureCertificateOutput
     * $GetCardAttachmentSignatureCertificateResult
     * @return GetCardAttachmentSignatureCertificateResponse
     */
    public function withGetCardAttachmentSignatureCertificateResult($GetCardAttachmentSignatureCertificateResult)
    {
        $new = clone $this;
        $new->GetCardAttachmentSignatureCertificateResult = $GetCardAttachmentSignatureCertificateResult;

        return $new;
    }


}

