<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocumentInChunkOutput implements RequestInterface
{

    /**
     * @var string
     */
    private $Chunk = null;

    /**
     * @var int
     */
    private $ChunkSize = null;

    /**
     * @var int
     */
    private $FileSize = null;

    /**
     * @var bool
     */
    private $IsLastChunk = null;

    /**
     * Constructor
     *
     * @var string $Chunk
     * @var int $ChunkSize
     * @var int $FileSize
     * @var bool $IsLastChunk
     */
    public function __construct($Chunk, $ChunkSize, $FileSize, $IsLastChunk)
    {
        $this->Chunk = $Chunk;
        $this->ChunkSize = $ChunkSize;
        $this->FileSize = $FileSize;
        $this->IsLastChunk = $IsLastChunk;
    }

    /**
     * @return string
     */
    public function getChunk()
    {
        return $this->Chunk;
    }

    /**
     * @param string $Chunk
     * @return GetCardDocumentInChunkOutput
     */
    public function withChunk($Chunk)
    {
        $new = clone $this;
        $new->Chunk = $Chunk;

        return $new;
    }

    /**
     * @return int
     */
    public function getChunkSize()
    {
        return $this->ChunkSize;
    }

    /**
     * @param int $ChunkSize
     * @return GetCardDocumentInChunkOutput
     */
    public function withChunkSize($ChunkSize)
    {
        $new = clone $this;
        $new->ChunkSize = $ChunkSize;

        return $new;
    }

    /**
     * @return int
     */
    public function getFileSize()
    {
        return $this->FileSize;
    }

    /**
     * @param int $FileSize
     * @return GetCardDocumentInChunkOutput
     */
    public function withFileSize($FileSize)
    {
        $new = clone $this;
        $new->FileSize = $FileSize;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsLastChunk()
    {
        return $this->IsLastChunk;
    }

    /**
     * @param bool $IsLastChunk
     * @return GetCardDocumentInChunkOutput
     */
    public function withIsLastChunk($IsLastChunk)
    {
        $new = clone $this;
        $new->IsLastChunk = $IsLastChunk;

        return $new;
    }


}

