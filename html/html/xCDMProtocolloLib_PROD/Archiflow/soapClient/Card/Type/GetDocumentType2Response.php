<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocumentType2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDocumentType2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\DocumentType
     */
    private $oDocumentType = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDocumentType2Result()
    {
        return $this->GetDocumentType2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetDocumentType2Result
     * @return GetDocumentType2Response
     */
    public function withGetDocumentType2Result($GetDocumentType2Result)
    {
        $new = clone $this;
        $new->GetDocumentType2Result = $GetDocumentType2Result;

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
     * @return GetDocumentType2Response
     */
    public function withODocumentType($oDocumentType)
    {
        $new = clone $this;
        $new->oDocumentType = $oDocumentType;

        return $new;
    }


}

