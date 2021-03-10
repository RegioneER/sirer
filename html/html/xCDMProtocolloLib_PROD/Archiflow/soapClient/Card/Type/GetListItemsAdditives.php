<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetListItemsAdditives implements RequestInterface
{

    /**
     * @var string
     */
    private $sessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\IdAdditive
     */
    private $additiveId = null;

    /**
     * @var int
     */
    private $documentType = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\IdAdditive $additiveId
     * @var int $documentType
     */
    public function __construct($sessionId, $additiveId, $documentType)
    {
        $this->sessionId = $sessionId;
        $this->additiveId = $additiveId;
        $this->documentType = $documentType;
    }

    /**
     * @return string
     */
    public function getSessionId()
    {
        return $this->sessionId;
    }

    /**
     * @param string $sessionId
     * @return GetListItemsAdditives
     */
    public function withSessionId($sessionId)
    {
        $new = clone $this;
        $new->sessionId = $sessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdAdditive
     */
    public function getAdditiveId()
    {
        return $this->additiveId;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdAdditive $additiveId
     * @return GetListItemsAdditives
     */
    public function withAdditiveId($additiveId)
    {
        $new = clone $this;
        $new->additiveId = $additiveId;

        return $new;
    }

    /**
     * @return int
     */
    public function getDocumentType()
    {
        return $this->documentType;
    }

    /**
     * @param int $documentType
     * @return GetListItemsAdditives
     */
    public function withDocumentType($documentType)
    {
        $new = clone $this;
        $new->documentType = $documentType;

        return $new;
    }


}

