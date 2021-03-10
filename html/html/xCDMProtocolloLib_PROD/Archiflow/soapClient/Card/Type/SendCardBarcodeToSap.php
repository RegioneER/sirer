<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendCardBarcodeToSap implements RequestInterface
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
    private $guidCard = null;

    /**
     * @var string
     */
    private $barcode = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $sessionInfo
     * @var string $contRep
     * @var string $guidCard
     * @var string $barcode
     */
    public function __construct($sessionInfo, $contRep, $guidCard, $barcode)
    {
        $this->sessionInfo = $sessionInfo;
        $this->contRep = $contRep;
        $this->guidCard = $guidCard;
        $this->barcode = $barcode;
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
     * @return SendCardBarcodeToSap
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
     * @return SendCardBarcodeToSap
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
    public function getGuidCard()
    {
        return $this->guidCard;
    }

    /**
     * @param string $guidCard
     * @return SendCardBarcodeToSap
     */
    public function withGuidCard($guidCard)
    {
        $new = clone $this;
        $new->guidCard = $guidCard;

        return $new;
    }

    /**
     * @return string
     */
    public function getBarcode()
    {
        return $this->barcode;
    }

    /**
     * @param string $barcode
     * @return SendCardBarcodeToSap
     */
    public function withBarcode($barcode)
    {
        $new = clone $this;
        $new->barcode = $barcode;

        return $new;
    }


}

