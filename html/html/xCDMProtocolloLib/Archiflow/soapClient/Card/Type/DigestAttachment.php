<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DigestAttachment implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Attachment
     */
    private $oAttachment = null;

    /**
     * @var int
     */
    private $UserSecurity = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Attachment $oAttachment
     * @var int $UserSecurity
     */
    public function __construct($strSessionId, $oAttachment, $UserSecurity)
    {
        $this->strSessionId = $strSessionId;
        $this->oAttachment = $oAttachment;
        $this->UserSecurity = $UserSecurity;
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
     * @return DigestAttachment
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

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
     * @return DigestAttachment
     */
    public function withOAttachment($oAttachment)
    {
        $new = clone $this;
        $new->oAttachment = $oAttachment;

        return $new;
    }

    /**
     * @return int
     */
    public function getUserSecurity()
    {
        return $this->UserSecurity;
    }

    /**
     * @param int $UserSecurity
     * @return DigestAttachment
     */
    public function withUserSecurity($UserSecurity)
    {
        $new = clone $this;
        $new->UserSecurity = $UserSecurity;

        return $new;
    }


}

