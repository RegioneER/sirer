<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AttachExternalDocumentResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $AttachExternalDocumentResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ExternalAttachment
     */
    private $oAttachment = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getAttachExternalDocumentResult()
    {
        return $this->AttachExternalDocumentResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $AttachExternalDocumentResult
     * @return AttachExternalDocumentResponse
     */
    public function withAttachExternalDocumentResult($AttachExternalDocumentResult)
    {
        $new = clone $this;
        $new->AttachExternalDocumentResult = $AttachExternalDocumentResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExternalAttachment
     */
    public function getOAttachment()
    {
        return $this->oAttachment;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExternalAttachment $oAttachment
     * @return AttachExternalDocumentResponse
     */
    public function withOAttachment($oAttachment)
    {
        $new = clone $this;
        $new->oAttachment = $oAttachment;

        return $new;
    }


}

