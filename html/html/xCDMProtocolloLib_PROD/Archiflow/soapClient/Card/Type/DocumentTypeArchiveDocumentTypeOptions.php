<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DocumentTypeArchiveDocumentTypeOptions implements RequestInterface
{

    /**
     * @var int
     */
    private $ArchiveID = null;

    /**
     * @var int
     */
    private $CardDuration = null;

    /**
     * @var bool
     */
    private $Preservation = null;

    /**
     * Constructor
     *
     * @var int $ArchiveID
     * @var int $CardDuration
     * @var bool $Preservation
     */
    public function __construct($ArchiveID, $CardDuration, $Preservation)
    {
        $this->ArchiveID = $ArchiveID;
        $this->CardDuration = $CardDuration;
        $this->Preservation = $Preservation;
    }

    /**
     * @return int
     */
    public function getArchiveID()
    {
        return $this->ArchiveID;
    }

    /**
     * @param int $ArchiveID
     * @return DocumentTypeArchiveDocumentTypeOptions
     */
    public function withArchiveID($ArchiveID)
    {
        $new = clone $this;
        $new->ArchiveID = $ArchiveID;

        return $new;
    }

    /**
     * @return int
     */
    public function getCardDuration()
    {
        return $this->CardDuration;
    }

    /**
     * @param int $CardDuration
     * @return DocumentTypeArchiveDocumentTypeOptions
     */
    public function withCardDuration($CardDuration)
    {
        $new = clone $this;
        $new->CardDuration = $CardDuration;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPreservation()
    {
        return $this->Preservation;
    }

    /**
     * @param bool $Preservation
     * @return DocumentTypeArchiveDocumentTypeOptions
     */
    public function withPreservation($Preservation)
    {
        $new = clone $this;
        $new->Preservation = $Preservation;

        return $new;
    }


}

