<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocumentTypesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDocumentTypesResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentType
     */
    private $oDocumentTypes = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDocumentTypesResult()
    {
        return $this->GetDocumentTypesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetDocumentTypesResult
     * @return GetDocumentTypesResponse
     */
    public function withGetDocumentTypesResult($GetDocumentTypesResult)
    {
        $new = clone $this;
        $new->GetDocumentTypesResult = $GetDocumentTypesResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfDocumentType
     */
    public function getODocumentTypes()
    {
        return $this->oDocumentTypes;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfDocumentType $oDocumentTypes
     * @return GetDocumentTypesResponse
     */
    public function withODocumentTypes($oDocumentTypes)
    {
        $new = clone $this;
        $new->oDocumentTypes = $oDocumentTypes;

        return $new;
    }


}

