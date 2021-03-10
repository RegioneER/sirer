<?php

namespace IrideWFFascicolo\Type;

class CreaFascicolo
{

    /**
     * @var \IrideWFFascicolo\Type\FascicoloIn
     */
    private $FascicoloIn = null;

    /**
     * @var string
     */
    private $CodiceAmministrazione = null;

    /**
     * @var string
     */
    private $CodiceAOO = null;

    /**
     * @return \IrideWFFascicolo\Type\FascicoloIn
     */
    public function getFascicoloIn()
    {
        return $this->FascicoloIn;
    }

    /**
     * @param \IrideWFFascicolo\Type\FascicoloIn $FascicoloIn
     * @return CreaFascicolo
     */
    public function withFascicoloIn($FascicoloIn)
    {
        $new = clone $this;
        $new->FascicoloIn = $FascicoloIn;

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
     * @return CreaFascicolo
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
     * @return CreaFascicolo
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

