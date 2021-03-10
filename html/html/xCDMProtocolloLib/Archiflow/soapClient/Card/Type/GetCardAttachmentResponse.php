<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardAttachmentResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardAttachmentResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Attachment
     */
    private $oAttachment = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardAttachmentResult()
    {
        return $this->GetCardAttachmentResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardAttachmentResult
     * @return GetCardAttachmentResponse
     */
    public function withGetCardAttachmentResult($GetCardAttachmentResult)
    {
        $new = clone $this;
        $new->GetCardAttachmentResult = $GetCardAttachmentResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Attachment
     */
    public function getOAttachment()
    {
        return $this->oAttachment;
    }

    /**
     * @param \ArchiflowWSCard\Type\Attachment $oAttachment
     * @return GetCardAttachmentResponse
     */
    public function withOAttachment($oAttachment)
    {
        $new = clone $this;
        $new->oAttachment = $oAttachment;

        return $new;
    }


}

