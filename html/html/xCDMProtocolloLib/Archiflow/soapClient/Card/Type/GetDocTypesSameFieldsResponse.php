<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocTypesSameFieldsResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDocTypesSameFieldsResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentType
     */
    private $oDocumentTypes = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDocTypesSameFieldsResult()
    {
        return $this->GetDocTypesSameFieldsResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetDocTypesSameFieldsResult
     * @return GetDocTypesSameFieldsResponse
     */
    public function withGetDocTypesSameFieldsResult($GetDocTypesSameFieldsResult)
    {
        $new = clone $this;
        $new->GetDocTypesSameFieldsResult = $GetDocTypesSameFieldsResult;

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
     * @return GetDocTypesSameFieldsResponse
     */
    public function withODocumentTypes($oDocumentTypes)
    {
        $new = clone $this;
        $new->oDocumentTypes = $oDocumentTypes;

        return $new;
    }


}

