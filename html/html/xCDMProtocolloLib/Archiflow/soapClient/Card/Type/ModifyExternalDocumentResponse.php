<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ModifyExternalDocumentResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $ModifyExternalDocumentResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ExternalAttachment
     */
    private $oAttachment = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getModifyExternalDocumentResult()
    {
        return $this->ModifyExternalDocumentResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $ModifyExternalDocumentResult
     * @return ModifyExternalDocumentResponse
     */
    public function withModifyExternalDocumentResult($ModifyExternalDocumentResult)
    {
        $new = clone $this;
        $new->ModifyExternalDocumentResult = $ModifyExternalDocumentResult;

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
     * @return ModifyExternalDocumentResponse
     */
    public function withOAttachment($oAttachment)
    {
        $new = clone $this;
        $new->oAttachment = $oAttachment;

        return $new;
    }


}

