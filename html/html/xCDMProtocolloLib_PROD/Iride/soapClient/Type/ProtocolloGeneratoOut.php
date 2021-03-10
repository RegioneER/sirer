<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ProtocolloGeneratoOut implements RequestInterface
{

    /**
     * @var string
     */
    private $NumeroRegistrazionePG = null;

    /**
     * @var string
     */
    private $DataRegistrazionePG = null;

    /**
     * @var string
     */
    private $TipoPG = null;

    /**
     * Constructor
     *
     * @var string $NumeroRegistrazionePG
     * @var string $DataRegistrazionePG
     * @var string $TipoPG
     */
    public function __construct($NumeroRegistrazionePG, $DataRegistrazionePG, $TipoPG)
    {
        $this->NumeroRegistrazionePG = $NumeroRegistrazionePG;
        $this->DataRegistrazionePG = $DataRegistrazionePG;
        $this->TipoPG = $TipoPG;
    }

    /**
     * @return string
     */
    public function getNumeroRegistrazionePG()
    {
        return $this->NumeroRegistrazionePG;
    }

    /**
     * @param string $NumeroRegistrazionePG
     * @return ProtocolloGeneratoOut
     */
    public function withNumeroRegistrazionePG($NumeroRegistrazionePG)
    {
        $new = clone $this;
        $new->NumeroRegistrazionePG = $NumeroRegistrazionePG;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataRegistrazionePG()
    {
        return $this->DataRegistrazionePG;
    }

    /**
     * @param string $DataRegistrazionePG
     * @return ProtocolloGeneratoOut
     */
    public function withDataRegistrazionePG($DataRegistrazionePG)
    {
        $new = clone $this;
        $new->DataRegistrazionePG = $DataRegistrazionePG;

        return $new;
    }

    /**
     * @return string
     */
    public function getTipoPG()
    {
        return $this->TipoPG;
    }

    /**
     * @param string $TipoPG
     * @return ProtocolloGeneratoOut
     */
    public function withTipoPG($TipoPG)
    {
        $new = clone $this;
        $new->TipoPG = $TipoPG;

        return $new;
    }


}

