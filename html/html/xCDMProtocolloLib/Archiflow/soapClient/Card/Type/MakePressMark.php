<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class MakePressMark implements RequestInterface
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
     * @var string
     */
    private $strModelName = null;

    /**
     * @var bool
     */
    private $bSigned = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var string $strModelName
     * @var bool $bSigned
     */
    public function __construct($strSessionId, $oCardId, $strModelName, $bSigned)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->strModelName = $strModelName;
        $this->bSigned = $bSigned;
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
     * @return MakePressMark
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
     * @return MakePressMark
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

        return $new;
    }

    /**
     * @return string
     */
    public function getStrModelName()
    {
        return $this->strModelName;
    }

    /**
     * @param string $strModelName
     * @return MakePressMark
     */
    public function withStrModelName($strModelName)
    {
        $new = clone $this;
        $new->strModelName = $strModelName;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBSigned()
    {
        return $this->bSigned;
    }

    /**
     * @param bool $bSigned
     * @return MakePressMark
     */
    public function withBSigned($bSigned)
    {
        $new = clone $this;
        $new->bSigned = $bSigned;

        return $new;
    }


}

