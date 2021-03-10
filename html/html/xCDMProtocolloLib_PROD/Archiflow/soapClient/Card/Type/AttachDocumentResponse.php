<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AttachDocumentResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $AttachDocumentResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getAttachDocumentResult()
    {
        return $this->AttachDocumentResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $AttachDocumentResult
     * @return AttachDocumentResponse
     */
    public function withAttachDocumentResult($AttachDocumentResult)
    {
        $new = clone $this;
        $new->AttachDocumentResult = $AttachDocumentResult;

        return $new;
    }


}

