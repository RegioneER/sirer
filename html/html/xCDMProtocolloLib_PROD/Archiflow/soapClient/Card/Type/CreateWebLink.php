<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreateWebLink implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\WebLinkType
     */
    private $wlt = null;

    /**
     * @var string
     */
    private $sitePath = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\WebLinkType $wlt
     * @var string $sitePath
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     */
    public function __construct($oSessionInfo, $wlt, $sitePath, $oCardId)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->wlt = $wlt;
        $this->sitePath = $sitePath;
        $this->oCardId = $oCardId;
    }

    /**
     * @return \ArchiflowWSCard\Type\SessionInfo
     */
    public function getOSessionInfo()
    {
        return $this->oSessionInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @return CreateWebLink
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\WebLinkType
     */
    public function getWlt()
    {
        return $this->wlt;
    }

    /**
     * @param \ArchiflowWSCard\Type\WebLinkType $wlt
     * @return CreateWebLink
     */
    public function withWlt($wlt)
    {
        $new = clone $this;
        $new->wlt = $wlt;

        return $new;
    }

    /**
     * @return string
     */
    public function getSitePath()
    {
        return $this->sitePath;
    }

    /**
     * @param string $sitePath
     * @return CreateWebLink
     */
    public function withSitePath($sitePath)
    {
        $new = clone $this;
        $new->sitePath = $sitePath;

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
     * @return CreateWebLink
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }


}

