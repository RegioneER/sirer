<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InternalAttachment implements RequestInterface
{

    /**
     * @var int
     */
    private $ArchiveId = null;

    /**
     * @var \ArchiflowWSCard\Type\InternalAttachType
     */
    private $AttachType = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $AttachmentCardId = null;

    /**
     * @var string
     */
    private $InternalNote = null;

    /**
     * Constructor
     *
     * @var int $ArchiveId
     * @var \ArchiflowWSCard\Type\InternalAttachType $AttachType
     * @var \ArchiflowWSCard\Type\Guid $AttachmentCardId
     * @var string $InternalNote
     */
    public function __construct($ArchiveId, $AttachType, $AttachmentCardId, $InternalNote)
    {
        $this->ArchiveId = $ArchiveId;
        $this->AttachType = $AttachType;
        $this->AttachmentCardId = $AttachmentCardId;
        $this->InternalNote = $InternalNote;
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
     * @return InternalAttachment
     */
    public function withArchiveId($ArchiveId)
    {
        $new = clone $this;
        $new->ArchiveId = $ArchiveId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\InternalAttachType
     */
    public function getAttachType()
    {
        return $this->AttachType;
    }

    /**
     * @param \ArchiflowWSCard\Type\InternalAttachType $AttachType
     * @return InternalAttachment
     */
    public function withAttachType($AttachType)
    {
        $new = clone $this;
        $new->AttachType = $AttachType;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getAttachmentCardId()
    {
        return $this->AttachmentCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $AttachmentCardId
     * @return InternalAttachment
     */
    public function withAttachmentCardId($AttachmentCardId)
    {
        $new = clone $this;
        $new->AttachmentCardId = $AttachmentCardId;

        return $new;
    }

    /**
     * @return string
     */
    public function getInternalNote()
    {
        return $this->InternalNote;
    }

    /**
     * @param string $InternalNote
     * @return InternalAttachment
     */
    public function withInternalNote($InternalNote)
    {
        $new = clone $this;
        $new->InternalNote = $InternalNote;

        return $new;
    }


}

