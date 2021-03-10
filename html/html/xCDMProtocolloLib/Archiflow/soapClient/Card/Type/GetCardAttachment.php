<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardAttachment implements RequestInterface
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
     * @var int
     */
    private $nAttachmentCode = null;

    /**
     * @var bool
     */
    private $bGetContent = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var int $nAttachmentCode
     * @var bool $bGetContent
     */
    public function __construct($strSessionId, $oCardId, $nAttachmentCode, $bGetContent)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->nAttachmentCode = $nAttachmentCode;
        $this->bGetContent = $bGetContent;
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
     * @return GetCardAttachment
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
     * @return GetCardAttachment
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return int
     */
    public function getNAttachmentCode()
    {
        return $this->nAttachmentCode;
    }

    /**
     * @param int $nAttachmentCode
     * @return GetCardAttachment
     */
    public function withNAttachmentCode($nAttachmentCode)
    {
        $new = clone $this;
        $new->nAttachmentCode = $nAttachmentCode;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetContent()
    {
        return $this->bGetContent;
    }

    /**
     * @param bool $bGetContent
     * @return GetCardAttachment
     */
    public function withBGetContent($bGetContent)
    {
        $new = clone $this;
        $new->bGetContent = $bGetContent;

        return $new;
    }


}

