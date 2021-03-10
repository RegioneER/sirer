<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RispostaAlProtocolloOut implements RequestInterface
{

    /**
     * @var string
     */
    private $NumeroRegistrazioneRP = null;

    /**
     * @var string
     */
    private $DataRegistrazioneRP = null;

    /**
     * @var string
     */
    private $TipoRP = null;

    /**
     * Constructor
     *
     * @var string $NumeroRegistrazioneRP
     * @var string $DataRegistrazioneRP
     * @var string $TipoRP
     */
    public function __construct($NumeroRegistrazioneRP, $DataRegistrazioneRP, $TipoRP)
    {
        $this->NumeroRegistrazioneRP = $NumeroRegistrazioneRP;
        $this->DataRegistrazioneRP = $DataRegistrazioneRP;
        $this->TipoRP = $TipoRP;
    }

    /**
     * @return string
     */
    public function getNumeroRegistrazioneRP()
    {
        return $this->NumeroRegistrazioneRP;
    }

    /**
     * @param string $NumeroRegistrazioneRP
     * @return RispostaAlProtocolloOut
     */
    public function withNumeroRegistrazioneRP($NumeroRegistrazioneRP)
    {
        $new = clone $this;
        $new->NumeroRegistrazioneRP = $NumeroRegistrazioneRP;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataRegistrazioneRP()
    {
        return $this->DataRegistrazioneRP;
    }

    /**
     * @param string $DataRegistrazioneRP
     * @return RispostaAlProtocolloOut
     */
    public function withDataRegistrazioneRP($DataRegistrazioneRP)
    {
        $new = clone $this;
        $new->DataRegistrazioneRP = $DataRegistrazioneRP;

        return $new;
    }

    /**
     * @return string
     */
    public function getTipoRP()
    {
        return $this->TipoRP;
    }

    /**
     * @param string $TipoRP
     * @return RispostaAlProtocolloOut
     */
    public function withTipoRP($TipoRP)
    {
        $new = clone $this;
        $new->TipoRP = $TipoRP;

        return $new;
    }


}

