<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCards2 implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $oCardIds = null;

    /**
     * @var bool
     */
    private $bGetIndexes = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\ArrayOfguid $oCardIds
     * @var bool $bGetIndexes
     */
    public function __construct($oSessionInfo, $oCardIds, $bGetIndexes)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->oCardIds = $oCardIds;
        $this->bGetIndexes = $bGetIndexes;
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
     * @return GetCards2
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

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
     * @return GetCards2
     */
    public function withOCardIds($oCardIds)
    {
        $new = clone $this;
        $new->oCardIds = $oCardIds;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetIndexes()
    {
        return $this->bGetIndexes;
    }

    /**
     * @param bool $bGetIndexes
     * @return GetCards2
     */
    public function withBGetIndexes($bGetIndexes)
    {
        $new = clone $this;
        $new->bGetIndexes = $bGetIndexes;

        return $new;
    }


}

