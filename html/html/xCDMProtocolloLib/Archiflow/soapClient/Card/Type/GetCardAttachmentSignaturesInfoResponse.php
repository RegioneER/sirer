<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardAttachmentSignaturesInfoResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardAttachmentSignaturesInfoOutput
     */
    private $GetCardAttachmentSignaturesInfoResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardAttachmentSignaturesInfoOutput
     */
    public function getGetCardAttachmentSignaturesInfoResult()
    {
        return $this->GetCardAttachmentSignaturesInfoResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardAttachmentSignaturesInfoOutput
     * $GetCardAttachmentSignaturesInfoResult
     * @return GetCardAttachmentSignaturesInfoResponse
     */
    public function withGetCardAttachmentSignaturesInfoResult($GetCardAttachmentSignaturesInfoResult)
    {
        $new = clone $this;
        $new->GetCardAttachmentSignaturesInfoResult = $GetCardAttachmentSignaturesInfoResult;

        return $new;
    }


}

