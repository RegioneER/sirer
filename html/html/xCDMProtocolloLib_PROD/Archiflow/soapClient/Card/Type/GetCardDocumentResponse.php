<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocumentResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardDocumentResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Document
     */
    private $oDocument = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardDocumentResult()
    {
        return $this->GetCardDocumentResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardDocumentResult
     * @return GetCardDocumentResponse
     */
    public function withGetCardDocumentResult($GetCardDocumentResult)
    {
        $new = clone $this;
        $new->GetCardDocumentResult = $GetCardDocumentResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Document
     */
    public function getODocument()
    {
        return $this->oDocument;
    }

    /**
     * @param \ArchiflowWSCard\Type\Document $oDocument
     * @return GetCardDocumentResponse
     */
    public function withODocument($oDocument)
    {
        $new = clone $this;
        $new->oDocument = $oDocument;

        return $new;
    }


}

