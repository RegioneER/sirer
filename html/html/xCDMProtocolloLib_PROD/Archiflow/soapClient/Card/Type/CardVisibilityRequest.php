<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CardVisibilityRequest implements RequestInterface
{

    /**
     * @var int
     */
    private $ArchiveId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $ClassIds = null;

    /**
     * @var int
     */
    private $DocumentTypeId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfField
     */
    private $Fields = null;

    /**
     * Constructor
     *
     * @var int $ArchiveId
     * @var \ArchiflowWSCard\Type\ArrayOfint $ClassIds
     * @var int $DocumentTypeId
     * @var \ArchiflowWSCard\Type\ArrayOfField $Fields
     */
    public function __construct($ArchiveId, $ClassIds, $DocumentTypeId, $Fields)
    {
        $this->ArchiveId = $ArchiveId;
        $this->ClassIds = $ClassIds;
        $this->DocumentTypeId = $DocumentTypeId;
        $this->Fields = $Fields;
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
     * @return CardVisibilityRequest
     */
    public function withArchiveId($ArchiveId)
    {
        $new = clone $this;
        $new->ArchiveId = $ArchiveId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getClassIds()
    {
        return $this->ClassIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $ClassIds
     * @return CardVisibilityRequest
     */
    public function withClassIds($ClassIds)
    {
        $new = clone $this;
        $new->ClassIds = $ClassIds;

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
     * @return CardVisibilityRequest
     */
    public function withDocumentTypeId($DocumentTypeId)
    {
        $new = clone $this;
        $new->DocumentTypeId = $DocumentTypeId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfField
     */
    public function getFields()
    {
        return $this->Fields;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfField $Fields
     * @return CardVisibilityRequest
     */
    public function withFields($Fields)
    {
        $new = clone $this;
        $new->Fields = $Fields;

        return $new;
    }


}

