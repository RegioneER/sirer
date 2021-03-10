<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocument2 implements RequestInterface
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
     * @var bool
     */
    private $bTifToPdf = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var bool $bDecryptIfSigned
     * @var bool $bTifToPdf
     */
    public function __construct($strSessionId, $oCardId, $bDecryptIfSigned, $bTifToPdf)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->bDecryptIfSigned = $bDecryptIfSigned;
        $this->bTifToPdf = $bTifToPdf;
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
     * @return GetCardDocument2
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
     * @return GetCardDocument2
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
     * @return GetCardDocument2
     */
    public function withBDecryptIfSigned($bDecryptIfSigned)
    {
        $new = clone $this;
        $new->bDecryptIfSigned = $bDecryptIfSigned;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBTifToPdf()
    {
        return $this->bTifToPdf;
    }

    /**
     * @param bool $bTifToPdf
     * @return GetCardDocument2
     */
    public function withBTifToPdf($bTifToPdf)
    {
        $new = clone $this;
        $new->bTifToPdf = $bTifToPdf;

        return $new;
    }


}

