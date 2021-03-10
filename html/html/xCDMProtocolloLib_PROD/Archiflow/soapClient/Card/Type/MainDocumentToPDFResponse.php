<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class MainDocumentToPDFResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\MainDocumentToPDFOutput
     */
    private $MainDocumentToPDFResult = null;

    /**
     * @return \ArchiflowWSCard\Type\MainDocumentToPDFOutput
     */
    public function getMainDocumentToPDFResult()
    {
        return $this->MainDocumentToPDFResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\MainDocumentToPDFOutput $MainDocumentToPDFResult
     * @return MainDocumentToPDFResponse
     */
    public function withMainDocumentToPDFResult($MainDocumentToPDFResult)
    {
        $new = clone $this;
        $new->MainDocumentToPDFResult = $MainDocumentToPDFResult;

        return $new;
    }


}

