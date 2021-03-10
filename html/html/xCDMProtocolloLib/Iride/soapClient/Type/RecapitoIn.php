<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RecapitoIn implements RequestInterface
{

    /**
     * @var string
     */
    private $TipoRecapito = null;

    /**
     * @var string
     */
    private $ValoreRecapito = null;

    /**
     * Constructor
     *
     * @var string $TipoRecapito
     * @var string $ValoreRecapito
     */
    public function __construct($TipoRecapito, $ValoreRecapito)
    {
        $this->TipoRecapito = $TipoRecapito;
        $this->ValoreRecapito = $ValoreRecapito;
    }

    /**
     * @return string
     */
    public function getTipoRecapito()
    {
        return $this->TipoRecapito;
    }

    /**
     * @param string $TipoRecapito
     * @return RecapitoIn
     */
    public function withTipoRecapito($TipoRecapito)
    {
        $new = clone $this;
        $new->TipoRecapito = $TipoRecapito;

        return $new;
    }

    /**
     * @return string
     */
    public function getValoreRecapito()
    {
        return $this->ValoreRecapito;
    }

    /**
     * @param string $ValoreRecapito
     * @return RecapitoIn
     */
    public function withValoreRecapito($ValoreRecapito)
    {
        $new = clone $this;
        $new->ValoreRecapito = $ValoreRecapito;

        return $new;
    }


}

