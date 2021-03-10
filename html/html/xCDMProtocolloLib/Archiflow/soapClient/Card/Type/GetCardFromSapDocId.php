<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardFromSapDocId implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $sessionInfo = null;

    /**
     * @var string
     */
    private $contRep = null;

    /**
     * @var string
     */
    private $docId = null;

    /**
     * @var string
     */
    private $compId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @var string $contRep
     * @var string $docId
     * @var string $compId
     */
    public function __construct($sessionInfo, $contRep, $docId, $compId)
    {
        $this->sessionInfo = $sessionInfo;
        $this->contRep = $contRep;
        $this->docId = $docId;
        $this->compId = $compId;
    }

    /**
     * @return \ArchiflowWSCard\Type\SessionInfo
     */
    public function getSessionInfo()
    {
        return $this->sessionInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @return GetCardFromSapDocId
     */
    public function withSessionInfo($sessionInfo)
    {
        $new = clone $this;
        $new->sessionInfo = $sessionInfo;

        return $new;
    }

    /**
     * @return string
     */
    public function getContRep()
    {
        return $this->contRep;
    }

    /**
     * @param string $contRep
     * @return GetCardFromSapDocId
     */
    public function withContRep($contRep)
    {
        $new = clone $this;
        $new->contRep = $contRep;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocId()
    {
        return $this->docId;
    }

    /**
     * @param string $docId
     * @return GetCardFromSapDocId
     */
    public function withDocId($docId)
    {
        $new = clone $this;
        $new->docId = $docId;

        return $new;
    }

    /**
     * @return string
     */
    public function getCompId()
    {
        return $this->compId;
    }

    /**
     * @param string $compId
     * @return GetCardFromSapDocId
     */
    public function withCompId($compId)
    {
        $new = clone $this;
        $new->compId = $compId;

        return $new;
    }


}

