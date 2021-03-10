<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ModifyAddInEmailMapping implements RequestInterface
{

    /**
     * @var string
     */
    private $sessionId = null;

    /**
     * @var int
     */
    private $documentTypeId = null;

    /**
     * @var string
     */
    private $addInEmailMapping = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var int $documentTypeId
     * @var string $addInEmailMapping
     */
    public function __construct($sessionId, $documentTypeId, $addInEmailMapping)
    {
        $this->sessionId = $sessionId;
        $this->documentTypeId = $documentTypeId;
        $this->addInEmailMapping = $addInEmailMapping;
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
     * @return ModifyAddInEmailMapping
     */
    public function withSessionId($sessionId)
    {
        $new = clone $this;
        $new->sessionId = $sessionId;

        return $new;
    }

    /**
     * @return int
     */
    public function getDocumentTypeId()
    {
        return $this->documentTypeId;
    }

    /**
     * @param int $documentTypeId
     * @return ModifyAddInEmailMapping
     */
    public function withDocumentTypeId($documentTypeId)
    {
        $new = clone $this;
        $new->documentTypeId = $documentTypeId;

        return $new;
    }

    /**
     * @return string
     */
    public function getAddInEmailMapping()
    {
        return $this->addInEmailMapping;
    }

    /**
     * @param string $addInEmailMapping
     * @return ModifyAddInEmailMapping
     */
    public function withAddInEmailMapping($addInEmailMapping)
    {
        $new = clone $this;
        $new->addInEmailMapping = $addInEmailMapping;

        return $new;
    }


}

