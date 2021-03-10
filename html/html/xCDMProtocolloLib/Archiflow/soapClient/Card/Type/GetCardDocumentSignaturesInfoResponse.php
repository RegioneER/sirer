<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocumentSignaturesInfoResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardDocumentSignaturesInfoOutput
     */
    private $GetCardDocumentSignaturesInfoResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardDocumentSignaturesInfoOutput
     */
    public function getGetCardDocumentSignaturesInfoResult()
    {
        return $this->GetCardDocumentSignaturesInfoResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardDocumentSignaturesInfoOutput
     * $GetCardDocumentSignaturesInfoResult
     * @return GetCardDocumentSignaturesInfoResponse
     */
    public function withGetCardDocumentSignaturesInfoResult($GetCardDocumentSignaturesInfoResult)
    {
        $new = clone $this;
        $new->GetCardDocumentSignaturesInfoResult = $GetCardDocumentSignaturesInfoResult;

        return $new;
    }


}

