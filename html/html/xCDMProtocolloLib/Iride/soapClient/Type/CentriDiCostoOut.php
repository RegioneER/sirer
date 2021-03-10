<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CentriDiCostoOut implements RequestInterface
{

    /**
     * @var string
     */
    private $Tipo = null;

    /**
     * @var string
     */
    private $Voce = null;

    /**
     * @var string
     */
    private $CdC_provento = null;

    /**
     * @var string
     */
    private $Propon_ammor = null;

    /**
     * @var float
     */
    private $Importo = null;

    /**
     * Constructor
     *
     * @var string $Tipo
     * @var string $Voce
     * @var string $CdC_provento
     * @var string $Propon_ammor
     * @var float $Importo
     */
    public function __construct($Tipo, $Voce, $CdC_provento, $Propon_ammor, $Importo)
    {
        $this->Tipo = $Tipo;
        $this->Voce = $Voce;
        $this->CdC_provento = $CdC_provento;
        $this->Propon_ammor = $Propon_ammor;
        $this->Importo = $Importo;
    }

    /**
     * @return string
     */
    public function getTipo()
    {
        return $this->Tipo;
    }

    /**
     * @param string $Tipo
     * @return CentriDiCostoOut
     */
    public function withTipo($Tipo)
    {
        $new = clone $this;
        $new->Tipo = $Tipo;

        return $new;
    }

    /**
     * @return string
     */
    public function getVoce()
    {
        return $this->Voce;
    }

    /**
     * @param string $Voce
     * @return CentriDiCostoOut
     */
    public function withVoce($Voce)
    {
        $new = clone $this;
        $new->Voce = $Voce;

        return $new;
    }

    /**
     * @return string
     */
    public function getCdC_provento()
    {
        return $this->CdC_provento;
    }

    /**
     * @param string $CdC_provento
     * @return CentriDiCostoOut
     */
    public function withCdC_provento($CdC_provento)
    {
        $new = clone $this;
        $new->CdC_provento = $CdC_provento;

        return $new;
    }

    /**
     * @return string
     */
    public function getPropon_ammor()
    {
        return $this->Propon_ammor;
    }

    /**
     * @param string $Propon_ammor
     * @return CentriDiCostoOut
     */
    public function withPropon_ammor($Propon_ammor)
    {
        $new = clone $this;
        $new->Propon_ammor = $Propon_ammor;

        return $new;
    }

    /**
     * @return float
     */
    public function getImporto()
    {
        return $this->Importo;
    }

    /**
     * @param float $Importo
     * @return CentriDiCostoOut
     */
    public function withImporto($Importo)
    {
        $new = clone $this;
        $new->Importo = $Importo;

        return $new;
    }


}

