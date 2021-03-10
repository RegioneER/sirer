<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocumentTypesFromArchivesResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDocumentTypesFromArchivesResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentType
     */
    private $oDocumentTypes = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDocumentTypesFromArchivesResult()
    {
        return $this->GetDocumentTypesFromArchivesResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetDocumentTypesFromArchivesResult
     * @return GetDocumentTypesFromArchivesResponse
     */
    public function withGetDocumentTypesFromArchivesResult($GetDocumentTypesFromArchivesResult)
    {
        $new = clone $this;
        $new->GetDocumentTypesFromArchivesResult = $GetDocumentTypesFromArchivesResult;

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
     * @return GetDocumentTypesFromArchivesResponse
     */
    public function withODocumentTypes($oDocumentTypes)
    {
        $new = clone $this;
        $new->oDocumentTypes = $oDocumentTypes;

        return $new;
    }


}

