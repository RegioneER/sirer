<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DigestAttachmentResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $DigestAttachmentResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getDigestAttachmentResult()
    {
        return $this->DigestAttachmentResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $DigestAttachmentResult
     * @return DigestAttachmentResponse
     */
    public function withDigestAttachmentResult($DigestAttachmentResult)
    {
        $new = clone $this;
        $new->DigestAttachmentResult = $DigestAttachmentResult;

        return $new;
    }


}

