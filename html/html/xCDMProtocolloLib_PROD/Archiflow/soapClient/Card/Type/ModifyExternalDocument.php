<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ModifyExternalDocument implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\ExternalAttachment
     */
    private $oAttachment = null;

    /**
     * @var bool
     */
    private $bUseSecurity = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\ExternalAttachment $oAttachment
     * @var bool $bUseSecurity
     */
    public function __construct($strSessionId, $oAttachment, $bUseSecurity)
    {
        $this->strSessionId = $strSessionId;
        $this->oAttachment = $oAttachment;
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
     * @return ModifyExternalDocument
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExternalAttachment
     */
    public function getOAttachment()
    {
        return $this->oAttachment;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExternalAttachment $oAttachment
     * @return ModifyExternalDocument
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
    public function getBUseSecurity()
    {
        return $this->bUseSecurity;
    }

    /**
     * @param bool $bUseSecurity
     * @return ModifyExternalDocument
     */
    public function withBUseSecurity($bUseSecurity)
    {
        $new = clone $this;
        $new->bUseSecurity = $bUseSecurity;

        return $new;
    }


}

