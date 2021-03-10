<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CampoUtente implements RequestInterface
{

    /**
     * @var string
     */
    private $NomeCampo = null;

    /**
     * @var string
     */
    private $TipoCampo = null;

    /**
     * @var string
     */
    private $ValoreCampo = null;

    /**
     * Constructor
     *
     * @var string $NomeCampo
     * @var string $TipoCampo
     * @var string $ValoreCampo
     */
    public function __construct($NomeCampo, $TipoCampo, $ValoreCampo)
    {
        $this->NomeCampo = $NomeCampo;
        $this->TipoCampo = $TipoCampo;
        $this->ValoreCampo = $ValoreCampo;
    }

    /**
     * @return string
     */
    public function getNomeCampo()
    {
        return $this->NomeCampo;
    }

    /**
     * @param string $NomeCampo
     * @return CampoUtente
     */
    public function withNomeCampo($NomeCampo)
    {
        $new = clone $this;
        $new->NomeCampo = $NomeCampo;

        return $new;
    }

    /**
     * @return string
     */
    public function getTipoCampo()
    {
        return $this->TipoCampo;
    }

    /**
     * @param string $TipoCampo
     * @return CampoUtente
     */
    public function withTipoCampo($TipoCampo)
    {
        $new = clone $this;
        $new->TipoCampo = $TipoCampo;

        return $new;
    }

    /**
     * @return string
     */
    public function getValoreCampo()
    {
        return $this->ValoreCampo;
    }

    /**
     * @param string $ValoreCampo
     * @return CampoUtente
     */
    public function withValoreCampo($ValoreCampo)
    {
        $new = clone $this;
        $new->ValoreCampo = $ValoreCampo;

        return $new;
    }


}

