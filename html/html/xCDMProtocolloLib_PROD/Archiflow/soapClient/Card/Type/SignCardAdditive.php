<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SignCardAdditive implements RequestInterface
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
     * @var \ArchiflowWSCard\Type\Additive
     */
    private $oAdditive = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\Additive $oAdditive
     */
    public function __construct($oSessionInfo, $oCardId, $oAdditive)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->oCardId = $oCardId;
        $this->oAdditive = $oAdditive;
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
     * @return SignCardAdditive
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
     * @return SignCardAdditive
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Additive
     */
    public function getOAdditive()
    {
        return $this->oAdditive;
    }

    /**
     * @param \ArchiflowWSCard\Type\Additive $oAdditive
     * @return SignCardAdditive
     */
    public function withOAdditive($oAdditive)
    {
        $new = clone $this;
        $new->oAdditive = $oAdditive;

        return $new;
    }


}

