<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocumentTypes2Response implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetDocumentTypes2Result = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentType
     */
    private $oDocumentTypes = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetDocumentTypes2Result()
    {
        return $this->GetDocumentTypes2Result;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetDocumentTypes2Result
     * @return GetDocumentTypes2Response
     */
    public function withGetDocumentTypes2Result($GetDocumentTypes2Result)
    {
        $new = clone $this;
        $new->GetDocumentTypes2Result = $GetDocumentTypes2Result;

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
     * @return GetDocumentTypes2Response
     */
    public function withODocumentTypes($oDocumentTypes)
    {
        $new = clone $this;
        $new->oDocumentTypes = $oDocumentTypes;

        return $new;
    }


}

