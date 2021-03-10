<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DocumentDigestResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\DocumentDigestOutput
     */
    private $DocumentDigestResult = null;

    /**
     * @return \ArchiflowWSCard\Type\DocumentDigestOutput
     */
    public function getDocumentDigestResult()
    {
        return $this->DocumentDigestResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\DocumentDigestOutput $DocumentDigestResult
     * @return DocumentDigestResponse
     */
    public function withDocumentDigestResult($DocumentDigestResult)
    {
        $new = clone $this;
        $new->DocumentDigestResult = $DocumentDigestResult;

        return $new;
    }


}

