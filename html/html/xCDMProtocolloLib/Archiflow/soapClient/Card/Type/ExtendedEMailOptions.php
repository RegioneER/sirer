<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ExtendedEMailOptions implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $AttachmentsIds = null;

    /**
     * @var bool
     */
    private $SendAdditionalData = null;

    /**
     * @var bool
     */
    private $SendAnnotations = null;

    /**
     * @var bool
     */
    private $SendExtAttachments = null;

    /**
     * @var bool
     */
    private $SendIndexes = null;

    /**
     * @var bool
     */
    private $SendIntAttachments = null;

    /**
     * @var bool
     */
    private $SendMainDocument = null;

    /**
     * @var bool
     */
    private $SendTif2Pdf = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfint $AttachmentsIds
     * @var bool $SendAdditionalData
     * @var bool $SendAnnotations
     * @var bool $SendExtAttachments
     * @var bool $SendIndexes
     * @var bool $SendIntAttachments
     * @var bool $SendMainDocument
     * @var bool $SendTif2Pdf
     */
    public function __construct($AttachmentsIds, $SendAdditionalData, $SendAnnotations, $SendExtAttachments, $SendIndexes, $SendIntAttachments, $SendMainDocument, $SendTif2Pdf)
    {
        $this->AttachmentsIds = $AttachmentsIds;
        $this->SendAdditionalData = $SendAdditionalData;
        $this->SendAnnotations = $SendAnnotations;
        $this->SendExtAttachments = $SendExtAttachments;
        $this->SendIndexes = $SendIndexes;
        $this->SendIntAttachments = $SendIntAttachments;
        $this->SendMainDocument = $SendMainDocument;
        $this->SendTif2Pdf = $SendTif2Pdf;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getAttachmentsIds()
    {
        return $this->AttachmentsIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $AttachmentsIds
     * @return ExtendedEMailOptions
     */
    public function withAttachmentsIds($AttachmentsIds)
    {
        $new = clone $this;
        $new->AttachmentsIds = $AttachmentsIds;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendAdditionalData()
    {
        return $this->SendAdditionalData;
    }

    /**
     * @param bool $SendAdditionalData
     * @return ExtendedEMailOptions
     */
    public function withSendAdditionalData($SendAdditionalData)
    {
        $new = clone $this;
        $new->SendAdditionalData = $SendAdditionalData;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendAnnotations()
    {
        return $this->SendAnnotations;
    }

    /**
     * @param bool $SendAnnotations
     * @return ExtendedEMailOptions
     */
    public function withSendAnnotations($SendAnnotations)
    {
        $new = clone $this;
        $new->SendAnnotations = $SendAnnotations;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendExtAttachments()
    {
        return $this->SendExtAttachments;
    }

    /**
     * @param bool $SendExtAttachments
     * @return ExtendedEMailOptions
     */
    public function withSendExtAttachments($SendExtAttachments)
    {
        $new = clone $this;
        $new->SendExtAttachments = $SendExtAttachments;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendIndexes()
    {
        return $this->SendIndexes;
    }

    /**
     * @param bool $SendIndexes
     * @return ExtendedEMailOptions
     */
    public function withSendIndexes($SendIndexes)
    {
        $new = clone $this;
        $new->SendIndexes = $SendIndexes;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendIntAttachments()
    {
        return $this->SendIntAttachments;
    }

    /**
     * @param bool $SendIntAttachments
     * @return ExtendedEMailOptions
     */
    public function withSendIntAttachments($SendIntAttachments)
    {
        $new = clone $this;
        $new->SendIntAttachments = $SendIntAttachments;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendMainDocument()
    {
        return $this->SendMainDocument;
    }

    /**
     * @param bool $SendMainDocument
     * @return ExtendedEMailOptions
     */
    public function withSendMainDocument($SendMainDocument)
    {
        $new = clone $this;
        $new->SendMainDocument = $SendMainDocument;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendTif2Pdf()
    {
        return $this->SendTif2Pdf;
    }

    /**
     * @param bool $SendTif2Pdf
     * @return ExtendedEMailOptions
     */
    public function withSendTif2Pdf($SendTif2Pdf)
    {
        $new = clone $this;
        $new->SendTif2Pdf = $SendTif2Pdf;

        return $new;
    }


}

