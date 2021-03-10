<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AttachDocument implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * @var \ArchiflowWSCard\Type\Attachment
     */
    private $oAttachment = null;

    /**
     * @var bool
     */
    private $bCircular = null;

    /**
     * @var bool
     */
    private $bUseSecurity = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\Attachment $oAttachment
     * @var bool $bCircular
     * @var bool $bUseSecurity
     */
    public function __construct($strSessionId, $oCardId, $oAttachment, $bCircular, $bUseSecurity)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->oAttachment = $oAttachment;
        $this->bCircular = $bCircular;
        $this->bUseSecurity = $bUseSecurity;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return AttachDocument
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getOCardId()
    {
        return $this->oCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $oCardId
     * @return AttachDocument
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Attachment
     */
    public function getOAttachment()
    {
        return $this->oAttachment;
    }

    /**
     * @param \ArchiflowWSCard\Type\Attachment $oAttachment
     * @return AttachDocument
     */
    public function withOAttachment($oAttachment)
    {
        $new = clone $this;
        $new->oAttachment = $oAttachment;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBCircular()
    {
        return $this->bCircular;
    }

    /**
     * @param bool $bCircular
     * @return AttachDocument
     */
    public function withBCircular($bCircular)
    {
        $new = clone $this;
        $new->bCircular = $bCircular;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBUseSecurity()
    {
        return $this->bUseSecurity;
    }

    /**
     * @param bool $bUseSecurity
     * @return AttachDocument
     */
    public function withBUseSecurity($bUseSecurity)
    {
        $new = clone $this;
        $new->bUseSecurity = $bUseSecurity;

        return $new;
    }


}

