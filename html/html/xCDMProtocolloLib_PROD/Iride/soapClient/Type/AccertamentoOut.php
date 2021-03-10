<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AccertamentoOut implements RequestInterface
{

    /**
     * @var int
     */
    private $AnnoAccertamento = null;

    /**
     * @var string
     */
    private $NumeroAccertamento = null;

    /**
     * @var string
     */
    private $CapitoloAccertamento = null;

    /**
     * @var string
     */
    private $ArticoloAccertamento = null;

    /**
     * @var string
     */
    private $CodSiopeAccertamento = null;

    /**
     * @var float
     */
    private $ImportoAccertamento = null;

    /**
     * @var float
     */
    private $SoggettoAccertamento = null;

    /**
     * Constructor
     *
     * @var int $AnnoAccertamento
     * @var string $NumeroAccertamento
     * @var string $CapitoloAccertamento
     * @var string $ArticoloAccertamento
     * @var string $CodSiopeAccertamento
     * @var float $ImportoAccertamento
     * @var float $SoggettoAccertamento
     */
    public function __construct($AnnoAccertamento, $NumeroAccertamento, $CapitoloAccertamento, $ArticoloAccertamento, $CodSiopeAccertamento, $ImportoAccertamento, $SoggettoAccertamento)
    {
        $this->AnnoAccertamento = $AnnoAccertamento;
        $this->NumeroAccertamento = $NumeroAccertamento;
        $this->CapitoloAccertamento = $CapitoloAccertamento;
        $this->ArticoloAccertamento = $ArticoloAccertamento;
        $this->CodSiopeAccertamento = $CodSiopeAccertamento;
        $this->ImportoAccertamento = $ImportoAccertamento;
        $this->SoggettoAccertamento = $SoggettoAccertamento;
    }

    /**
     * @return int
     */
    public function getAnnoAccertamento()
    {
        return $this->AnnoAccertamento;
    }

    /**
     * @param int $AnnoAccertamento
     * @return AccertamentoOut
     */
    public function withAnnoAccertamento($AnnoAccertamento)
    {
        $new = clone $this;
        $new->AnnoAccertamento = $AnnoAccertamento;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroAccertamento()
    {
        return $this->NumeroAccertamento;
    }

    /**
     * @param string $NumeroAccertamento
     * @return AccertamentoOut
     */
    public function withNumeroAccertamento($NumeroAccertamento)
    {
        $new = clone $this;
        $new->NumeroAccertamento = $NumeroAccertamento;

        return $new;
    }

    /**
     * @return string
     */
    public function getCapitoloAccertamento()
    {
        return $this->CapitoloAccertamento;
    }

    /**
     * @param string $CapitoloAccertamento
     * @return AccertamentoOut
     */
    public function withCapitoloAccertamento($CapitoloAccertamento)
    {
        $new = clone $this;
        $new->CapitoloAccertamento = $CapitoloAccertamento;

        return $new;
    }

    /**
     * @return string
     */
    public function getArticoloAccertamento()
    {
        return $this->ArticoloAccertamento;
    }

    /**
     * @param string $ArticoloAccertamento
     * @return AccertamentoOut
     */
    public function withArticoloAccertamento($ArticoloAccertamento)
    {
        $new = clone $this;
        $new->ArticoloAccertamento = $ArticoloAccertamento;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodSiopeAccertamento()
    {
        return $this->CodSiopeAccertamento;
    }

    /**
     * @param string $CodSiopeAccertamento
     * @return AccertamentoOut
     */
    public function withCodSiopeAccertamento($CodSiopeAccertamento)
    {
        $new = clone $this;
        $new->CodSiopeAccertamento = $CodSiopeAccertamento;

        return $new;
    }

    /**
     * @return float
     */
    public function getImportoAccertamento()
    {
        return $this->ImportoAccertamento;
    }

    /**
     * @param float $ImportoAccertamento
     * @return AccertamentoOut
     */
    public function withImportoAccertamento($ImportoAccertamento)
    {
        $new = clone $this;
        $new->ImportoAccertamento = $ImportoAccertamento;

        return $new;
    }

    /**
     * @return float
     */
    public function getSoggettoAccertamento()
    {
        return $this->SoggettoAccertamento;
    }

    /**
     * @param float $SoggettoAccertamento
     * @return AccertamentoOut
     */
    public function withSoggettoAccertamento($SoggettoAccertamento)
    {
        $new = clone $this;
        $new->SoggettoAccertamento = $SoggettoAccertamento;

        return $new;
    }


}

