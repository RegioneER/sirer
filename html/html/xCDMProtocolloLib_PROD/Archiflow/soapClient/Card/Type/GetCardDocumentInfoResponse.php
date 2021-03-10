<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardDocumentInfoResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetCardDocumentInfoResult = null;

    /**
     * @var \ArchiflowWSCard\Type\Document
     */
    private $oDocument = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetCardDocumentInfoResult()
    {
        return $this->GetCardDocumentInfoResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetCardDocumentInfoResult
     * @return GetCardDocumentInfoResponse
     */
    public function withGetCardDocumentInfoResult($GetCardDocumentInfoResult)
    {
        $new = clone $this;
        $new->GetCardDocumentInfoResult = $GetCardDocumentInfoResult;

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
     * @return GetCardDocumentInfoResponse
     */
    public function withODocument($oDocument)
    {
        $new = clone $this;
        $new->oDocument = $oDocument;

        return $new;
    }


}

