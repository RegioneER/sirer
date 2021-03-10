<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocumentInChunkInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $DimChunk = null;

    /**
     * @var \ArchiflowWSCard\Type\CardContentMode
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
     * @var int $DimChunk
     * @var \ArchiflowWSCard\Type\CardContentMode $Mode
     * @var int $NumChunk
     */
    public function __construct($CardId, $DimChunk, $Mode, $NumChunk)
    {
        $this->CardId = $CardId;
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
     * @return GetCardDocumentInChunkInput
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
    public function getDimChunk()
    {
        return $this->DimChunk;
    }

    /**
     * @param int $DimChunk
     * @return GetCardDocumentInChunkInput
     */
    public function withDimChunk($DimChunk)
    {
        $new = clone $this;
        $new->DimChunk = $DimChunk;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardContentMode
     */
    public function getMode()
    {
        return $this->Mode;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardContentMode $Mode
     * @return GetCardDocumentInChunkInput
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
     * @return GetCardDocumentInChunkInput
     */
    public function withNumChunk($NumChunk)
    {
        $new = clone $this;
        $new->NumChunk = $NumChunk;

        return $new;
    }


}

