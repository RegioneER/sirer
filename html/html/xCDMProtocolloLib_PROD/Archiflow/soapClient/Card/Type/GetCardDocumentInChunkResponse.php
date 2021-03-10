<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocumentInChunkResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardDocumentInChunkOutput
     */
    private $GetCardDocumentInChunkResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardDocumentInChunkOutput
     */
    public function getGetCardDocumentInChunkResult()
    {
        return $this->GetCardDocumentInChunkResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardDocumentInChunkOutput
     * $GetCardDocumentInChunkResult
     * @return GetCardDocumentInChunkResponse
     */
    public function withGetCardDocumentInChunkResult($GetCardDocumentInChunkResult)
    {
        $new = clone $this;
        $new->GetCardDocumentInChunkResult = $GetCardDocumentInChunkResult;

        return $new;
    }


}

