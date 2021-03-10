<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AggiungiAllegatiMultiDB implements RequestInterface
{

    /**
     * @var \IrideWS\Type\NuoviAllegati
     */
    private $NuoviAllegati = null;

    /**
     * @var string
     */
    private $CodiceAmministrazione = null;

    /**
     * @var string
     */
    private $CodiceAOO = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\NuoviAllegati $NuoviAllegati
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($NuoviAllegati, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->NuoviAllegati = $NuoviAllegati;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return \IrideWS\Type\NuoviAllegati
     */
    public function getNuoviAllegati()
    {
        return $this->NuoviAllegati;
    }

    /**
     * @param \IrideWS\Type\NuoviAllegati $NuoviAllegati
     * @return AggiungiAllegatiMultiDB
     */
    public function withNuoviAllegati($NuoviAllegati)
    {
        $new = clone $this;
        $new->NuoviAllegati = $NuoviAllegati;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceAmministrazione()
    {
        return $this->CodiceAmministrazione;
    }

    /**
     * @param string $CodiceAmministrazione
     * @return AggiungiAllegatiMultiDB
     */
    public function withCodiceAmministrazione($CodiceAmministrazione)
    {
        $new = clone $this;
        $new->CodiceAmministrazione = $CodiceAmministrazione;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceAOO()
    {
        return $this->CodiceAOO;
    }

    /**
     * @param string $CodiceAOO
     * @return AggiungiAllegatiMultiDB
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

