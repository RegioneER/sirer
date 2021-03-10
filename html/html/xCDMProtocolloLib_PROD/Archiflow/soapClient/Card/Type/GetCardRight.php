<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardRight implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * @var \ArchiflowWSCard\Type\RightsRwCard
     */
    private $enRightsRwCard = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\RightsRwCard $enRightsRwCard
     */
    public function __construct($strSessionId, $oCardId, $enRightsRwCard)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->enRightsRwCard = $enRightsRwCard;
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
     * @return GetCardRight
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

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
     * @return GetCardRight
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\RightsRwCard
     */
    public function getEnRightsRwCard()
    {
        return $this->enRightsRwCard;
    }

    /**
     * @param \ArchiflowWSCard\Type\RightsRwCard $enRightsRwCard
     * @return GetCardRight
     */
    public function withEnRightsRwCard($enRightsRwCard)
    {
        $new = clone $this;
        $new->enRightsRwCard = $enRightsRwCard;

        return $new;
    }


}

