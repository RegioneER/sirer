<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RicercaPerCodiceFiscaleString implements RequestInterface
{

    /**
     * @var string
     */
    private $CodiceFiscale = null;

    /**
     * @var string
     */
    private $SoloProtocollo = null;

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
     * @var string $CodiceFiscale
     * @var string $SoloProtocollo
     * @var string $Utente
     * @var string $Ruolo
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($CodiceFiscale, $SoloProtocollo, $Utente, $Ruolo, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->CodiceFiscale = $CodiceFiscale;
        $this->SoloProtocollo = $SoloProtocollo;
        $this->Utente = $Utente;
        $this->Ruolo = $Ruolo;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
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
     * @return RicercaPerCodiceFiscaleString
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
    public function getSoloProtocollo()
    {
        return $this->SoloProtocollo;
    }

    /**
     * @param string $SoloProtocollo
     * @return RicercaPerCodiceFiscaleString
     */
    public function withSoloProtocollo($SoloProtocollo)
    {
        $new = clone $this;
        $new->SoloProtocollo = $SoloProtocollo;

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
     * @return RicercaPerCodiceFiscaleString
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
     * @return RicercaPerCodiceFiscaleString
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
     * @return RicercaPerCodiceFiscaleString
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
     * @return RicercaPerCodiceFiscaleString
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

