<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardAttachments implements RequestInterface
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
     * @var bool
     */
    private $bGetContent = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var bool $bGetContent
     */
    public function __construct($strSessionId, $oCardId, $bGetContent)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
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
     * @return GetCardAttachments
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
     * @return GetCardAttachments
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

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
     * @return GetCardAttachments
     */
    public function withBGetContent($bGetContent)
    {
        $new = clone $this;
        $new->bGetContent = $bGetContent;

        return $new;
    }


}

