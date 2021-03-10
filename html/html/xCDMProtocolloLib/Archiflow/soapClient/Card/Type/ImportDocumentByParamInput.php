<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ImportDocumentByParamInput implements RequestInterface
{

    /**
     * @var bool
     */
    private $AutoCheckIn = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var bool
     */
    private $ConcatDocument = null;

    /**
     * @var \ArchiflowWSCard\Type\Document
     */
    private $Document = null;

    /**
     * @var bool
     */
    private $OverridePrevious = null;

    /**
     * @var string
     */
    private $PressMarkModel = null;

    /**
     * Constructor
     *
     * @var bool $AutoCheckIn
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var bool $ConcatDocument
     * @var \ArchiflowWSCard\Type\Document $Document
     * @var bool $OverridePrevious
     * @var string $PressMarkModel
     */
    public function __construct($AutoCheckIn, $CardId, $ConcatDocument, $Document, $OverridePrevious, $PressMarkModel)
    {
        $this->AutoCheckIn = $AutoCheckIn;
        $this->CardId = $CardId;
        $this->ConcatDocument = $ConcatDocument;
        $this->Document = $Document;
        $this->OverridePrevious = $OverridePrevious;
        $this->PressMarkModel = $PressMarkModel;
    }

    /**
     * @return bool
     */
    public function getAutoCheckIn()
    {
        return $this->AutoCheckIn;
    }

    /**
     * @param bool $AutoCheckIn
     * @return ImportDocumentByParamInput
     */
    public function withAutoCheckIn($AutoCheckIn)
    {
        $new = clone $this;
        $new->AutoCheckIn = $AutoCheckIn;

        return $new;
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
     * @return ImportDocumentByParamInput
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
    public function getConcatDocument()
    {
        return $this->ConcatDocument;
    }

    /**
     * @param bool $ConcatDocument
     * @return ImportDocumentByParamInput
     */
    public function withConcatDocument($ConcatDocument)
    {
        $new = clone $this;
        $new->ConcatDocument = $ConcatDocument;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Document
     */
    public function getDocument()
    {
        return $this->Document;
    }

    /**
     * @param \ArchiflowWSCard\Type\Document $Document
     * @return ImportDocumentByParamInput
     */
    public function withDocument($Document)
    {
        $new = clone $this;
        $new->Document = $Document;

        return $new;
    }

    /**
     * @return bool
     */
    public function getOverridePrevious()
    {
        return $this->OverridePrevious;
    }

    /**
     * @param bool $OverridePrevious
     * @return ImportDocumentByParamInput
     */
    public function withOverridePrevious($OverridePrevious)
    {
        $new = clone $this;
        $new->OverridePrevious = $OverridePrevious;

        return $new;
    }

    /**
     * @return string
     */
    public function getPressMarkModel()
    {
        return $this->PressMarkModel;
    }

    /**
     * @param string $PressMarkModel
     * @return ImportDocumentByParamInput
     */
    public function withPressMarkModel($PressMarkModel)
    {
        $new = clone $this;
        $new->PressMarkModel = $PressMarkModel;

        return $new;
    }


}

