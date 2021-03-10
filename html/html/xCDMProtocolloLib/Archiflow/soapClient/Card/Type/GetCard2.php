<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCard2 implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     */
    public function __construct($oSessionInfo, $oCardId)
    {
        $this->oSessionInfo = $oSessionInfo;
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
     * @return GetCard2
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

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
     * @return GetCard2
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }


}

