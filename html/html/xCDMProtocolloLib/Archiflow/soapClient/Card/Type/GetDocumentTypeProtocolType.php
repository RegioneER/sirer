<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocumentTypeProtocolType implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $nArchiveId = null;

    /**
     * @var int
     */
    private $nDocumentTypeId = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $nArchiveId
     * @var int $nDocumentTypeId
     */
    public function __construct($strSessionId, $nArchiveId, $nDocumentTypeId)
    {
        $this->strSessionId = $strSessionId;
        $this->nArchiveId = $nArchiveId;
        $this->nDocumentTypeId = $nDocumentTypeId;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return GetDocumentTypeProtocolType
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return int
     */
    public function getNArchiveId()
    {
        return $this->nArchiveId;
    }

    /**
     * @param int $nArchiveId
     * @return GetDocumentTypeProtocolType
     */
    public function withNArchiveId($nArchiveId)
    {
        $new = clone $this;
        $new->nArchiveId = $nArchiveId;

        return $new;
    }

    /**
     * @return int
     */
    public function getNDocumentTypeId()
    {
        return $this->nDocumentTypeId;
    }

    /**
     * @param int $nDocumentTypeId
     * @return GetDocumentTypeProtocolType
     */
    public function withNDocumentTypeId($nDocumentTypeId)
    {
        $new = clone $this;
        $new->nDocumentTypeId = $nDocumentTypeId;

        return $new;
    }


}

