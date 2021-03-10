<?php

namespace IrideWFFascicolo\Type;

class LeggiFascicolo
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
     * @return LeggiFascicolo
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
     * @return LeggiFascicolo
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
     * @return LeggiFascicolo
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
     * @return LeggiFascicolo
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
     * @return LeggiFascicolo
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
     * @return LeggiFascicolo
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
     * @return LeggiFascicolo
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
     * @return LeggiFascicolo
     */
    public function withCodiceClassificazione($CodiceClassificazione)
    {
        $new = clone $this;
        $new->CodiceClassificazione = $CodiceClassificazione;

        return $new;
    }


}

