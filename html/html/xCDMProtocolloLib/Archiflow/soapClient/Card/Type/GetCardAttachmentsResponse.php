<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardAttachmentsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardAttachmentsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAttachment
     */
    private $oAttachments = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardAttachmentsResult()
    {
        return $this->GetCardAttachmentsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardAttachmentsResult
     * @return GetCardAttachmentsResponse
     */
    public function withGetCardAttachmentsResult($GetCardAttachmentsResult)
    {
        $new = clone $this;
        $new->GetCardAttachmentsResult = $GetCardAttachmentsResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAttachment
     */
    public function getOAttachments()
    {
        return $this->oAttachments;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAttachment $oAttachments
     * @return GetCardAttachmentsResponse
     */
    public function withOAttachments($oAttachments)
    {
        $new = clone $this;
        $new->oAttachments = $oAttachments;

        return $new;
    }


}

