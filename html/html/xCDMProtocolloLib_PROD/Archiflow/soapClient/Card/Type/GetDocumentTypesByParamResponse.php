<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetDocumentTypesByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetDocumentTypesOutput
     */
    private $GetDocumentTypesByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetDocumentTypesOutput
     */
    public function getGetDocumentTypesByParamResult()
    {
        return $this->GetDocumentTypesByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetDocumentTypesOutput
     * $GetDocumentTypesByParamResult
     * @return GetDocumentTypesByParamResponse
     */
    public function withGetDocumentTypesByParamResult($GetDocumentTypesByParamResult)
    {
        $new = clone $this;
        $new->GetDocumentTypesByParamResult = $GetDocumentTypesByParamResult;

        return $new;
    }


}

