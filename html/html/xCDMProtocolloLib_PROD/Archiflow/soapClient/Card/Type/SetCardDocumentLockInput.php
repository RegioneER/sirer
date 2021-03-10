<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardDocumentLockInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var bool
     */
    private $LockDocument = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var bool $LockDocument
     */
    public function __construct($CardId, $LockDocument)
    {
        $this->CardId = $CardId;
        $this->LockDocument = $LockDocument;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $CardId
     * @return SetCardDocumentLockInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getLockDocument()
    {
        return $this->LockDocument;
    }

    /**
     * @param bool $LockDocument
     * @return SetCardDocumentLockInput
     */
    public function withLockDocument($LockDocument)
    {
        $new = clone $this;
        $new->LockDocument = $LockDocument;

        return $new;
    }


}

