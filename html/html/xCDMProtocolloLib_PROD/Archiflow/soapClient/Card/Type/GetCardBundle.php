<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardBundle implements RequestInterface
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
    private $bDecryptIfSigned = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var bool $bDecryptIfSigned
     */
    public function __construct($strSessionId, $oCardId, $bDecryptIfSigned)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->bDecryptIfSigned = $bDecryptIfSigned;
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
     * @return GetCardBundle
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
     * @return GetCardBundle
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
     * @return GetCardBundle
     */
    public function withBDecryptIfSigned($bDecryptIfSigned)
    {
        $new = clone $this;
        $new->bDecryptIfSigned = $bDecryptIfSigned;

        return $new;
    }


}

