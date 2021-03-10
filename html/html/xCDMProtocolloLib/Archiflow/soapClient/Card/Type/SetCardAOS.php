<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardAOS implements RequestInterface
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
     * @var bool
     */
    private $bAOS = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var bool $bAOS
     */
    public function __construct($strSessionId, $oCardId, $bAOS)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->bAOS = $bAOS;
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
     * @return SetCardAOS
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
     * @return SetCardAOS
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
    public function getBAOS()
    {
        return $this->bAOS;
    }

    /**
     * @param bool $bAOS
     * @return SetCardAOS
     */
    public function withBAOS($bAOS)
    {
        $new = clone $this;
        $new->bAOS = $bAOS;

        return $new;
    }


}

