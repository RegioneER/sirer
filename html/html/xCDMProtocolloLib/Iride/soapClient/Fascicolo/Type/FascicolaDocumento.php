<?php

namespace IrideWFFascicolo\Type;

class FascicolaDocumento
{

    /**
     * @var int
     */
    private $IDFascicolo = null;

    /**
     * @var int
     */
    private $IDDocumento = null;

    /**
     * @var string
     */
    private $AggiornaClassifica = null;

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
    private $Principale = null;

    /**
     * @return int
     */
    public function getIDFascicolo()
    {
        return $this->IDFascicolo;
    }

    /**
     * @param int $IDFascicolo
     * @return FascicolaDocumento
     */
    public function withIDFascicolo($IDFascicolo)
    {
        $new = clone $this;
        $new->IDFascicolo = $IDFascicolo;

        return $new;
    }

    /**
     * @return int
     */
    public function getIDDocumento()
    {
        return $this->IDDocumento;
    }

    /**
     * @param int $IDDocumento
     * @return FascicolaDocumento
     */
    public function withIDDocumento($IDDocumento)
    {
        $new = clone $this;
        $new->IDDocumento = $IDDocumento;

        return $new;
    }

    /**
     * @return string
     */
    public function getAggiornaClassifica()
    {
        return $this->AggiornaClassifica;
    }

    /**
     * @param string $AggiornaClassifica
     * @return FascicolaDocumento
     */
    public function withAggiornaClassifica($AggiornaClassifica)
    {
        $new = clone $this;
        $new->AggiornaClassifica = $AggiornaClassifica;

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
     * @return FascicolaDocumento
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
     * @return FascicolaDocumento
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
     * @return FascicolaDocumento
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
     * @return FascicolaDocumento
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
    public function getPrincipale()
    {
        return $this->Principale;
    }

    /**
     * @param string $Principale
     * @return FascicolaDocumento
     */
    public function withPrincipale($Principale)
    {
        $new = clone $this;
        $new->Principale = $Principale;

        return $new;
    }


}

