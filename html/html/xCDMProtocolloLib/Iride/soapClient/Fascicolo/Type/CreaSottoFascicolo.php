<?php

namespace IrideWFFascicolo\Type;

class CreaSottoFascicolo
{

    /**
     * @var int
     */
    private $IDFascicolo = null;

    /**
     * @var string
     */
    private $Utente = null;

    /**
     * @var string
     */
    private $Ruolo = null;

    /**
     * @var string
     */
    private $CodiceAmministrazione = null;

    /**
     * @var string
     */
    private $CodiceAOO = null;

    /**
     * @var \IrideWFFascicolo\Type\FascicoloIn
     */
    private $FascicoloIn = null;

    /**
     * @return int
     */
    public function getIDFascicolo()
    {
        return $this->IDFascicolo;
    }

    /**
     * @param int $IDFascicolo
     * @return CreaSottoFascicolo
     */
    public function withIDFascicolo($IDFascicolo)
    {
        $new = clone $this;
        $new->IDFascicolo = $IDFascicolo;

        return $new;
    }

    /**
     * @return string
     */
    public function getUtente()
    {
        return $this->Utente;
    }

    /**
     * @param string $Utente
     * @return CreaSottoFascicolo
     */
    public function withUtente($Utente)
    {
        $new = clone $this;
        $new->Utente = $Utente;

        return $new;
    }

    /**
     * @return string
     */
    public function getRuolo()
    {
        return $this->Ruolo;
    }

    /**
     * @param string $Ruolo
     * @return CreaSottoFascicolo
     */
    public function withRuolo($Ruolo)
    {
        $new = clone $this;
        $new->Ruolo = $Ruolo;

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
     * @return CreaSottoFascicolo
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
     * @return CreaSottoFascicolo
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }

    /**
     * @return \IrideWFFascicolo\Type\FascicoloIn
     */
    public function getFascicoloIn()
    {
        return $this->FascicoloIn;
    }

    /**
     * @param \IrideWFFascicolo\Type\FascicoloIn $FascicoloIn
     * @return CreaSottoFascicolo
     */
    public function withFascicoloIn($FascicoloIn)
    {
        $new = clone $this;
        $new->FascicoloIn = $FascicoloIn;

        return $new;
    }


}

