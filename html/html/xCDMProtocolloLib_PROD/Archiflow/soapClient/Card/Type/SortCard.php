<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SortCard implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\CardBundle
     */
    private $oCard = null;

    /**
     * @var bool
     */
    private $bIsAutomaticProtocol = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\CardBundle $oCard
     * @var bool $bIsAutomaticProtocol
     */
    public function __construct($strSessionId, $oCard, $bIsAutomaticProtocol)
    {
        $this->strSessionId = $strSessionId;
        $this->oCard = $oCard;
        $this->bIsAutomaticProtocol = $bIsAutomaticProtocol;
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
     * @return SortCard
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardBundle
     */
    public function getOCard()
    {
        return $this->oCard;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardBundle $oCard
     * @return SortCard
     */
    public function withOCard($oCard)
    {
        $new = clone $this;
        $new->oCard = $oCard;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBIsAutomaticProtocol()
    {
        return $this->bIsAutomaticProtocol;
    }

    /**
     * @param bool $bIsAutomaticProtocol
     * @return SortCard
     */
    public function withBIsAutomaticProtocol($bIsAutomaticProtocol)
    {
        $new = clone $this;
        $new->bIsAutomaticProtocol = $bIsAutomaticProtocol;

        return $new;
    }


}

