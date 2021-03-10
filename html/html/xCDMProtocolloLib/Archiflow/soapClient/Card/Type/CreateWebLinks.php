<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreateWebLinks implements RequestInterface
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
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $oCardIds = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\WebLinkType $wlt
     * @var string $sitePath
     * @var \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     */
    public function __construct($oSessionInfo, $wlt, $sitePath, $oCardIds)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->wlt = $wlt;
        $this->sitePath = $sitePath;
        $this->oCardIds = $oCardIds;
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
     * @return CreateWebLinks
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
     * @return CreateWebLinks
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
     * @return CreateWebLinks
     */
    public function withSitePath($sitePath)
    {
        $new = clone $this;
        $new->sitePath = $sitePath;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getOCardIds()
    {
        return $this->oCardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     * @return CreateWebLinks
     */
    public function withOCardIds($oCardIds)
    {
        $new = clone $this;
        $new->oCardIds = $oCardIds;

        return $new;
    }


}

