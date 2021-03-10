<?php

namespace IrideWFFascicolo\Type;

class ModificaFascicolo
{

    /**
     * @var string
     */
    private $FascicoloInStr = null;

    /**
     * @var string
     */
    private $CodiceAmministrazione = null;

    /**
     * @var string
     */
    private $CodiceAOO = null;

    /**
     * @return string
     */
    public function getFascicoloInStr()
    {
        return $this->FascicoloInStr;
    }

    /**
     * @param string $FascicoloInStr
     * @return ModificaFascicolo
     */
    public function withFascicoloInStr($FascicoloInStr)
    {
        $new = clone $this;
        $new->FascicoloInStr = $FascicoloInStr;

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
     * @return ModificaFascicolo
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
     * @return ModificaFascicolo
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

