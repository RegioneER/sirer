<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocumentTypeResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDocumentTypeResult = null;

    /**
     * @var \ArchiflowWSCard\Type\DocumentType
     */
    private $oDocumentType = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDocumentTypeResult()
    {
        return $this->GetDocumentTypeResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetDocumentTypeResult
     * @return GetDocumentTypeResponse
     */
    public function withGetDocumentTypeResult($GetDocumentTypeResult)
    {
        $new = clone $this;
        $new->GetDocumentTypeResult = $GetDocumentTypeResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\DocumentType
     */
    public function getODocumentType()
    {
        return $this->oDocumentType;
    }

    /**
     * @param \ArchiflowWSCard\Type\DocumentType $oDocumentType
     * @return GetDocumentTypeResponse
     */
    public function withODocumentType($oDocumentType)
    {
        $new = clone $this;
        $new->oDocumentType = $oDocumentType;

        return $new;
    }


}

