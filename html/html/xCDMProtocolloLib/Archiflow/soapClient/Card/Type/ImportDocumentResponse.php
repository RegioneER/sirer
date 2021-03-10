<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ImportDocumentResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $ImportDocumentResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getImportDocumentResult()
    {
        return $this->ImportDocumentResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $ImportDocumentResult
     * @return ImportDocumentResponse
     */
    public function withImportDocumentResult($ImportDocumentResult)
    {
        $new = clone $this;
        $new->ImportDocumentResult = $ImportDocumentResult;

        return $new;
    }


}

