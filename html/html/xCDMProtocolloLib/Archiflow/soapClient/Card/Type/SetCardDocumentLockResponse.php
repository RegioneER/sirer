<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SetCardDocumentLockResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SetCardDocumentLockOutput
     */
    private $SetCardDocumentLockResult = null;

    /**
     * @return \ArchiflowWSCard\Type\SetCardDocumentLockOutput
     */
    public function getSetCardDocumentLockResult()
    {
        return $this->SetCardDocumentLockResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\SetCardDocumentLockOutput
     * $SetCardDocumentLockResult
     * @return SetCardDocumentLockResponse
     */
    public function withSetCardDocumentLockResult($SetCardDocumentLockResult)
    {
        $new = clone $this;
        $new->SetCardDocumentLockResult = $SetCardDocumentLockResult;

        return $new;
    }


}

