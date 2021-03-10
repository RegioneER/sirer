<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardAttachmentInChunkResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardAttachmentInChunkOutput
     */
    private $GetCardAttachmentInChunkResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardAttachmentInChunkOutput
     */
    public function getGetCardAttachmentInChunkResult()
    {
        return $this->GetCardAttachmentInChunkResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardAttachmentInChunkOutput
     * $GetCardAttachmentInChunkResult
     * @return GetCardAttachmentInChunkResponse
     */
    public function withGetCardAttachmentInChunkResult($GetCardAttachmentInChunkResult)
    {
        $new = clone $this;
        $new->GetCardAttachmentInChunkResult = $GetCardAttachmentInChunkResult;

        return $new;
    }


}

