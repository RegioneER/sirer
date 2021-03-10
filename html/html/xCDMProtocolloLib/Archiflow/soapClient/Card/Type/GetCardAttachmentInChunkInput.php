<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardAttachmentInChunkInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $Code = null;

    /**
     * @var int
     */
    private $DimChunk = null;

    /**
     * @var \ArchiflowWSCard\Type\AttachmentContentMode
     */
    private $Mode = null;

    /**
     * @var int
     */
    private $NumChunk = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var int $Code
     * @var int $DimChunk
     * @var \ArchiflowWSCard\Type\AttachmentContentMode $Mode
     * @var int $NumChunk
     */
    public function __construct($CardId, $Code, $DimChunk, $Mode, $NumChunk)
    {
        $this->CardId = $CardId;
        $this->Code = $Code;
        $this->DimChunk = $DimChunk;
        $this->Mode = $Mode;
        $this->NumChunk = $NumChunk;
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
     * @return GetCardAttachmentInChunkInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return int
     */
    public function getCode()
    {
        return $this->Code;
    }

    /**
     * @param int $Code
     * @return GetCardAttachmentInChunkInput
     */
    public function withCode($Code)
    {
        $new = clone $this;
        $new->Code = $Code;

        return $new;
    }

    /**
     * @return int
     */
    public function getDimChunk()
    {
        return $this->DimChunk;
    }

    /**
     * @param int $DimChunk
     * @return GetCardAttachmentInChunkInput
     */
    public function withDimChunk($DimChunk)
    {
        $new = clone $this;
        $new->DimChunk = $DimChunk;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AttachmentContentMode
     */
    public function getMode()
    {
        return $this->Mode;
    }

    /**
     * @param \ArchiflowWSCard\Type\AttachmentContentMode $Mode
     * @return GetCardAttachmentInChunkInput
     */
    public function withMode($Mode)
    {
        $new = clone $this;
        $new->Mode = $Mode;

        return $new;
    }

    /**
     * @return int
     */
    public function getNumChunk()
    {
        return $this->NumChunk;
    }

    /**
     * @param int $NumChunk
     * @return GetCardAttachmentInChunkInput
     */
    public function withNumChunk($NumChunk)
    {
        $new = clone $this;
        $new->NumChunk = $NumChunk;

        return $new;
    }


}

