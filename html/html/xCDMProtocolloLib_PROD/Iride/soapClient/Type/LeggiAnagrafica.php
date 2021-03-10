<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class LeggiAnagrafica implements RequestInterface
{

    /**
     * @var string
     */
    private $IdSoggetto = null;

    /**
     * @var string
     */
    private $CodiceFiscale = null;

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
     * Constructor
     *
     * @var string $IdSoggetto
     * @var string $CodiceFiscale
     * @var string $Utente
     * @var string $Ruolo
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($IdSoggetto, $CodiceFiscale, $Utente, $Ruolo, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->IdSoggetto = $IdSoggetto;
        $this->CodiceFiscale = $CodiceFiscale;
        $this->Utente = $Utente;
        $this->Ruolo = $Ruolo;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getIdSoggetto()
    {
        return $this->IdSoggetto;
    }

    /**
     * @param string $IdSoggetto
     * @return LeggiAnagrafica
     */
    public function withIdSoggetto($IdSoggetto)
    {
        $new = clone $this;
        $new->IdSoggetto = $IdSoggetto;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceFiscale()
    {
        return $this->CodiceFiscale;
    }

    /**
     * @param string $CodiceFiscale
     * @return LeggiAnagrafica
     */
    public function withCodiceFiscale($CodiceFiscale)
    {
        $new = clone $this;
        $new->CodiceFiscale = $CodiceFiscale;

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
     * @return LeggiAnagrafica
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
     * @return LeggiAnagrafica
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
     * @return LeggiAnagrafica
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
     * @return LeggiAnagrafica
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

