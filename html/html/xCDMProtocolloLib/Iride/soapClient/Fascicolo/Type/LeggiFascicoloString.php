<?php

namespace IrideWFFascicolo\Type;

class LeggiFascicoloString
{

    /**
     * @var string
     */
    private $IDFascicolo = null;

    /**
     * @var string
     */
    private $Anno = null;

    /**
     * @var string
     */
    private $Numero = null;

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
    private $CodiceClassificazione = null;

    /**
     * @return string
     */
    public function getIDFascicolo()
    {
        return $this->IDFascicolo;
    }

    /**
     * @param string $IDFascicolo
     * @return LeggiFascicoloString
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
    public function getAnno()
    {
        return $this->Anno;
    }

    /**
     * @param string $Anno
     * @return LeggiFascicoloString
     */
    public function withAnno($Anno)
    {
        $new = clone $this;
        $new->Anno = $Anno;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumero()
    {
        return $this->Numero;
    }

    /**
     * @param string $Numero
     * @return LeggiFascicoloString
     */
    public function withNumero($Numero)
    {
        $new = clone $this;
        $new->Numero = $Numero;

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
     * @return LeggiFascicoloString
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
     * @return LeggiFascicoloString
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
     * @return LeggiFascicoloString
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
     * @return LeggiFascicoloString
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
    public function getCodiceClassificazione()
    {
        return $this->CodiceClassificazione;
    }

    /**
     * @param string $CodiceClassificazione
     * @return LeggiFascicoloString
     */
    public function withCodiceClassificazione($CodiceClassificazione)
    {
        $new = clone $this;
        $new->CodiceClassificazione = $CodiceClassificazione;

        return $new;
    }


}

