<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InserisciDatiUtente implements RequestInterface
{

    /**
     * @var string
     */
    private $Appartenenza = null;

    /**
     * @var int
     */
    private $Identificativo = null;

    /**
     * @var string
     */
    private $DatiUtente = null;

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
     * @var string $Appartenenza
     * @var int $Identificativo
     * @var string $DatiUtente
     * @var string $Utente
     * @var string $Ruolo
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($Appartenenza, $Identificativo, $DatiUtente, $Utente, $Ruolo, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->Appartenenza = $Appartenenza;
        $this->Identificativo = $Identificativo;
        $this->DatiUtente = $DatiUtente;
        $this->Utente = $Utente;
        $this->Ruolo = $Ruolo;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getAppartenenza()
    {
        return $this->Appartenenza;
    }

    /**
     * @param string $Appartenenza
     * @return InserisciDatiUtente
     */
    public function withAppartenenza($Appartenenza)
    {
        $new = clone $this;
        $new->Appartenenza = $Appartenenza;

        return $new;
    }

    /**
     * @return int
     */
    public function getIdentificativo()
    {
        return $this->Identificativo;
    }

    /**
     * @param int $Identificativo
     * @return InserisciDatiUtente
     */
    public function withIdentificativo($Identificativo)
    {
        $new = clone $this;
        $new->Identificativo = $Identificativo;

        return $new;
    }

    /**
     * @return string
     */
    public function getDatiUtente()
    {
        return $this->DatiUtente;
    }

    /**
     * @param string $DatiUtente
     * @return InserisciDatiUtente
     */
    public function withDatiUtente($DatiUtente)
    {
        $new = clone $this;
        $new->DatiUtente = $DatiUtente;

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
     * @return InserisciDatiUtente
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
     * @return InserisciDatiUtente
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
     * @return InserisciDatiUtente
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
     * @return InserisciDatiUtente
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

