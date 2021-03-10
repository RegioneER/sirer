<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DuplicateInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $CopyAttachmentsById = null;

    /**
     * @var bool
     */
    private $CopyExternalAttachment = null;

    /**
     * @var bool
     */
    private $CopyInternalAttachment = null;

    /**
     * @var bool
     */
    private $CopyMainDocument = null;

    /**
     * @var bool
     */
    private $CopyRegistry = null;

    /**
     * @var bool
     */
    private $DualAttachmentParentCard = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $ParentCardId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfint $CopyAttachmentsById
     * @var bool $CopyExternalAttachment
     * @var bool $CopyInternalAttachment
     * @var bool $CopyMainDocument
     * @var bool $CopyRegistry
     * @var bool $DualAttachmentParentCard
     * @var \ArchiflowWSCard\Type\Guid $ParentCardId
     */
    public function __construct($CopyAttachmentsById, $CopyExternalAttachment, $CopyInternalAttachment, $CopyMainDocument, $CopyRegistry, $DualAttachmentParentCard, $ParentCardId)
    {
        $this->CopyAttachmentsById = $CopyAttachmentsById;
        $this->CopyExternalAttachment = $CopyExternalAttachment;
        $this->CopyInternalAttachment = $CopyInternalAttachment;
        $this->CopyMainDocument = $CopyMainDocument;
        $this->CopyRegistry = $CopyRegistry;
        $this->DualAttachmentParentCard = $DualAttachmentParentCard;
        $this->ParentCardId = $ParentCardId;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getCopyAttachmentsById()
    {
        return $this->CopyAttachmentsById;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $CopyAttachmentsById
     * @return DuplicateInfo
     */
    public function withCopyAttachmentsById($CopyAttachmentsById)
    {
        $new = clone $this;
        $new->CopyAttachmentsById = $CopyAttachmentsById;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCopyExternalAttachment()
    {
        return $this->CopyExternalAttachment;
    }

    /**
     * @param bool $CopyExternalAttachment
     * @return DuplicateInfo
     */
    public function withCopyExternalAttachment($CopyExternalAttachment)
    {
        $new = clone $this;
        $new->CopyExternalAttachment = $CopyExternalAttachment;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCopyInternalAttachment()
    {
        return $this->CopyInternalAttachment;
    }

    /**
     * @param bool $CopyInternalAttachment
     * @return DuplicateInfo
     */
    public function withCopyInternalAttachment($CopyInternalAttachment)
    {
        $new = clone $this;
        $new->CopyInternalAttachment = $CopyInternalAttachment;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCopyMainDocument()
    {
        return $this->CopyMainDocument;
    }

    /**
     * @param bool $CopyMainDocument
     * @return DuplicateInfo
     */
    public function withCopyMainDocument($CopyMainDocument)
    {
        $new = clone $this;
        $new->CopyMainDocument = $CopyMainDocument;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCopyRegistry()
    {
        return $this->CopyRegistry;
    }

    /**
     * @param bool $CopyRegistry
     * @return DuplicateInfo
     */
    public function withCopyRegistry($CopyRegistry)
    {
        $new = clone $this;
        $new->CopyRegistry = $CopyRegistry;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDualAttachmentParentCard()
    {
        return $this->DualAttachmentParentCard;
    }

    /**
     * @param bool $DualAttachmentParentCard
     * @return DuplicateInfo
     */
    public function withDualAttachmentParentCard($DualAttachmentParentCard)
    {
        $new = clone $this;
        $new->DualAttachmentParentCard = $DualAttachmentParentCard;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getParentCardId()
    {
        return $this->ParentCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $ParentCardId
     * @return DuplicateInfo
     */
    public function withParentCardId($ParentCardId)
    {
        $new = clone $this;
        $new->ParentCardId = $ParentCardId;

        return $new;
    }


}

