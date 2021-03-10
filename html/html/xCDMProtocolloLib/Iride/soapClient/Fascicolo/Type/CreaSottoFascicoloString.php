<?php

namespace IrideWFFascicolo\Type;

class CreaSottoFascicoloString
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
     * @var string
     */
    private $FascicoloInStr = null;

    /**
     * @return int
     */
    public function getIDFascicolo()
    {
        return $this->IDFascicolo;
    }

    /**
     * @param int $IDFascicolo
     * @return CreaSottoFascicoloString
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
     * @return CreaSottoFascicoloString
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
     * @return CreaSottoFascicoloString
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
     * @return CreaSottoFascicoloString
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
     * @return CreaSottoFascicoloString
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }

    /**
     * @return string
     */
    public function getFascicoloInStr()
    {
        return $this->FascicoloInStr;
    }

    /**
     * @param string $FascicoloInStr
     * @return CreaSottoFascicoloString
     */
    public function withFascicoloInStr($FascicoloInStr)
    {
        $new = clone $this;
        $new->FascicoloInStr = $FascicoloInStr;

        return $new;
    }


}

