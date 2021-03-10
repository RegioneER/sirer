<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardBundle2 implements RequestInterface
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
     * @var bool
     */
    private $bDecryptIfSigned = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $oSessionInfo
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var bool $bDecryptIfSigned
     */
    public function __construct($oSessionInfo, $oCardId, $bDecryptIfSigned)
    {
        $this->oSessionInfo = $oSessionInfo;
        $this->oCardId = $oCardId;
        $this->bDecryptIfSigned = $bDecryptIfSigned;
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
     * @return GetCardBundle2
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
     * @return GetCardBundle2
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
    public function getBDecryptIfSigned()
    {
        return $this->bDecryptIfSigned;
    }

    /**
     * @param bool $bDecryptIfSigned
     * @return GetCardBundle2
     */
    public function withBDecryptIfSigned($bDecryptIfSigned)
    {
        $new = clone $this;
        $new->bDecryptIfSigned = $bDecryptIfSigned;

        return $new;
    }


}

