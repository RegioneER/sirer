<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardAdditives1 implements RequestInterface
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
     * @var \ArchiflowWSCard\Type\ArrayOfAdditive
     */
    private $oAdditives = null;

    /**
     * @var bool
     */
    private $bSyncWF = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\ArrayOfAdditive $oAdditives
     * @var bool $bSyncWF
     */
    public function __construct($oSessionInfo, $oCardId, $oAdditives, $bSyncWF)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->oCardId = $oCardId;
        $this->oAdditives = $oAdditives;
        $this->bSyncWF = $bSyncWF;
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
     * @return SetCardAdditives1
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
     * @return SetCardAdditives1
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAdditive
     */
    public function getOAdditives()
    {
        return $this->oAdditives;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAdditive $oAdditives
     * @return SetCardAdditives1
     */
    public function withOAdditives($oAdditives)
    {
        $new = clone $this;
        $new->oAdditives = $oAdditives;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBSyncWF()
    {
        return $this->bSyncWF;
    }

    /**
     * @param bool $bSyncWF
     * @return SetCardAdditives1
     */
    public function withBSyncWF($bSyncWF)
    {
        $new = clone $this;
        $new->bSyncWF = $bSyncWF;

        return $new;
    }


}

