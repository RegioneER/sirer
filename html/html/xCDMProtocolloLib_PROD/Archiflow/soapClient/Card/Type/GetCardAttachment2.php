<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardAttachment2 implements RequestInterface
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
     * @var bool
     */
    private $bTifToPdf = null;

    /**
     * @var bool
     */
    private $bDecrypt = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var int $nAttachmentCode
     * @var bool $bGetContent
     * @var bool $bTifToPdf
     * @var bool $bDecrypt
     */
    public function __construct($strSessionId, $oCardId, $nAttachmentCode, $bGetContent, $bTifToPdf, $bDecrypt)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->nAttachmentCode = $nAttachmentCode;
        $this->bGetContent = $bGetContent;
        $this->bTifToPdf = $bTifToPdf;
        $this->bDecrypt = $bDecrypt;
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
     * @return GetCardAttachment2
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
     * @return GetCardAttachment2
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
     * @return GetCardAttachment2
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
     * @return GetCardAttachment2
     */
    public function withBGetContent($bGetContent)
    {
        $new = clone $this;
        $new->bGetContent = $bGetContent;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBTifToPdf()
    {
        return $this->bTifToPdf;
    }

    /**
     * @param bool $bTifToPdf
     * @return GetCardAttachment2
     */
    public function withBTifToPdf($bTifToPdf)
    {
        $new = clone $this;
        $new->bTifToPdf = $bTifToPdf;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBDecrypt()
    {
        return $this->bDecrypt;
    }

    /**
     * @param bool $bDecrypt
     * @return GetCardAttachment2
     */
    public function withBDecrypt($bDecrypt)
    {
        $new = clone $this;
        $new->bDecrypt = $bDecrypt;

        return $new;
    }


}

