<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ImportDocumentByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ImportDocumentByParamOutput
     */
    private $ImportDocumentByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ImportDocumentByParamOutput
     */
    public function getImportDocumentByParamResult()
    {
        return $this->ImportDocumentByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ImportDocumentByParamOutput
     * $ImportDocumentByParamResult
     * @return ImportDocumentByParamResponse
     */
    public function withImportDocumentByParamResult($ImportDocumentByParamResult)
    {
        $new = clone $this;
        $new->ImportDocumentByParamResult = $ImportDocumentByParamResult;

        return $new;
    }


}

