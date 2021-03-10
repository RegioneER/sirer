<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SaveDocumentVersionResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SaveDocumentVersionOutput
     */
    private $SaveDocumentVersionResult = null;

    /**
     * @return \ArchiflowWSCard\Type\SaveDocumentVersionOutput
     */
    public function getSaveDocumentVersionResult()
    {
        return $this->SaveDocumentVersionResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\SaveDocumentVersionOutput
     * $SaveDocumentVersionResult
     * @return SaveDocumentVersionResponse
     */
    public function withSaveDocumentVersionResult($SaveDocumentVersionResult)
    {
        $new = clone $this;
        $new->SaveDocumentVersionResult = $SaveDocumentVersionResult;

        return $new;
    }


}

