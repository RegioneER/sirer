<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ResetCardInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var bool
     */
    private $ExternalAttachments = null;

    /**
     * @var bool
     */
    private $InternalAttachments = null;

    /**
     * @var bool
     */
    private $MainDocument = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var bool $ExternalAttachments
     * @var bool $InternalAttachments
     * @var bool $MainDocument
     */
    public function __construct($CardId, $ExternalAttachments, $InternalAttachments, $MainDocument)
    {
        $this->CardId = $CardId;
        $this->ExternalAttachments = $ExternalAttachments;
        $this->InternalAttachments = $InternalAttachments;
        $this->MainDocument = $MainDocument;
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
     * @return ResetCardInput
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
    public function getExternalAttachments()
    {
        return $this->ExternalAttachments;
    }

    /**
     * @param bool $ExternalAttachments
     * @return ResetCardInput
     */
    public function withExternalAttachments($ExternalAttachments)
    {
        $new = clone $this;
        $new->ExternalAttachments = $ExternalAttachments;

        return $new;
    }

    /**
     * @return bool
     */
    public function getInternalAttachments()
    {
        return $this->InternalAttachments;
    }

    /**
     * @param bool $InternalAttachments
     * @return ResetCardInput
     */
    public function withInternalAttachments($InternalAttachments)
    {
        $new = clone $this;
        $new->InternalAttachments = $InternalAttachments;

        return $new;
    }

    /**
     * @return bool
     */
    public function getMainDocument()
    {
        return $this->MainDocument;
    }

    /**
     * @param bool $MainDocument
     * @return ResetCardInput
     */
    public function withMainDocument($MainDocument)
    {
        $new = clone $this;
        $new->MainDocument = $MainDocument;

        return $new;
    }


}

