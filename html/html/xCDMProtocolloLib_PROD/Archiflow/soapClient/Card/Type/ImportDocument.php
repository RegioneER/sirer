<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ImportDocument implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * @var \ArchiflowWSCard\Type\Document
     */
    private $oDocument = null;

    /**
     * @var bool
     */
    private $bOverridePrevious = null;

    /**
     * @var bool
     */
    private $bConcatDocument = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\Document $oDocument
     * @var bool $bOverridePrevious
     * @var bool $bConcatDocument
     */
    public function __construct($strSessionId, $oCardId, $oDocument, $bOverridePrevious, $bConcatDocument)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->oDocument = $oDocument;
        $this->bOverridePrevious = $bOverridePrevious;
        $this->bConcatDocument = $bConcatDocument;
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
     * @return ImportDocument
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getOCardId()
    {
        return $this->oCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $oCardId
     * @return ImportDocument
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Document
     */
    public function getODocument()
    {
        return $this->oDocument;
    }

    /**
     * @param \ArchiflowWSCard\Type\Document $oDocument
     * @return ImportDocument
     */
    public function withODocument($oDocument)
    {
        $new = clone $this;
        $new->oDocument = $oDocument;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBOverridePrevious()
    {
        return $this->bOverridePrevious;
    }

    /**
     * @param bool $bOverridePrevious
     * @return ImportDocument
     */
    public function withBOverridePrevious($bOverridePrevious)
    {
        $new = clone $this;
        $new->bOverridePrevious = $bOverridePrevious;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBConcatDocument()
    {
        return $this->bConcatDocument;
    }

    /**
     * @param bool $bConcatDocument
     * @return ImportDocument
     */
    public function withBConcatDocument($bConcatDocument)
    {
        $new = clone $this;
        $new->bConcatDocument = $bConcatDocument;

        return $new;
    }


}

