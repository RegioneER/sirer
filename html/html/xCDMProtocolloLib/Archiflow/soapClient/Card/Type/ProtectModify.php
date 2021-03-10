<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ProtectModify implements RequestInterface
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
    private $bProtect = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var bool $bProtect
     */
    public function __construct($strSessionId, $oCardId, $bProtect)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->bProtect = $bProtect;
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
     * @return ProtectModify
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
     * @return ProtectModify
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
    public function getBProtect()
    {
        return $this->bProtect;
    }

    /**
     * @param bool $bProtect
     * @return ProtectModify
     */
    public function withBProtect($bProtect)
    {
        $new = clone $this;
        $new->bProtect = $bProtect;

        return $new;
    }


}

