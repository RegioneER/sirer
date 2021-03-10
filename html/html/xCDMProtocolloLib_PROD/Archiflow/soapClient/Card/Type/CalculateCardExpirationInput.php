<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CalculateCardExpirationInput implements RequestInterface
{

    /**
     * @var int
     */
    private $ArchiveId = null;

    /**
     * @var int
     */
    private $DocumentTypeId = null;

    /**
     * @var int
     */
    private $Duration = null;

    /**
     * @var \ArchiflowWSCard\Type\ExpirationMethodType
     */
    private $ExpirationMethod = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $TitolarioItemIds = null;

    /**
     * Constructor
     *
     * @var int $ArchiveId
     * @var int $DocumentTypeId
     * @var int $Duration
     * @var \ArchiflowWSCard\Type\ExpirationMethodType $ExpirationMethod
     * @var \ArchiflowWSCard\Type\ArrayOfint $TitolarioItemIds
     */
    public function __construct($ArchiveId, $DocumentTypeId, $Duration, $ExpirationMethod, $TitolarioItemIds)
    {
        $this->ArchiveId = $ArchiveId;
        $this->DocumentTypeId = $DocumentTypeId;
        $this->Duration = $Duration;
        $this->ExpirationMethod = $ExpirationMethod;
        $this->TitolarioItemIds = $TitolarioItemIds;
    }

    /**
     * @return int
     */
    public function getArchiveId()
    {
        return $this->ArchiveId;
    }

    /**
     * @param int $ArchiveId
     * @return CalculateCardExpirationInput
     */
    public function withArchiveId($ArchiveId)
    {
        $new = clone $this;
        $new->ArchiveId = $ArchiveId;

        return $new;
    }

    /**
     * @return int
     */
    public function getDocumentTypeId()
    {
        return $this->DocumentTypeId;
    }

    /**
     * @param int $DocumentTypeId
     * @return CalculateCardExpirationInput
     */
    public function withDocumentTypeId($DocumentTypeId)
    {
        $new = clone $this;
        $new->DocumentTypeId = $DocumentTypeId;

        return $new;
    }

    /**
     * @return int
     */
    public function getDuration()
    {
        return $this->Duration;
    }

    /**
     * @param int $Duration
     * @return CalculateCardExpirationInput
     */
    public function withDuration($Duration)
    {
        $new = clone $this;
        $new->Duration = $Duration;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExpirationMethodType
     */
    public function getExpirationMethod()
    {
        return $this->ExpirationMethod;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExpirationMethodType $ExpirationMethod
     * @return CalculateCardExpirationInput
     */
    public function withExpirationMethod($ExpirationMethod)
    {
        $new = clone $this;
        $new->ExpirationMethod = $ExpirationMethod;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getTitolarioItemIds()
    {
        return $this->TitolarioItemIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $TitolarioItemIds
     * @return CalculateCardExpirationInput
     */
    public function withTitolarioItemIds($TitolarioItemIds)
    {
        $new = clone $this;
        $new->TitolarioItemIds = $TitolarioItemIds;

        return $new;
    }


}

