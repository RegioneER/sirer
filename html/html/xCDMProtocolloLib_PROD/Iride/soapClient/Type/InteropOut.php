<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InteropOut implements RequestInterface
{

    /**
     * @var string
     */
    private $CodiceAmministrazione = null;

    /**
     * @var string
     */
    private $Denominazione = null;

    /**
     * @var string
     */
    private $CodiceAOO = null;

    /**
     * @var string
     */
    private $AOO = null;

    /**
     * @var string
     */
    private $Indirizzo = null;

    /**
     * @var string
     */
    private $IndirizzoTelematico = null;

    /**
     * @var string
     */
    private $Localizzazione = null;

    /**
     * @var string
     */
    private $Riservato = null;

    /**
     * Constructor
     *
     * @var string $CodiceAmministrazione
     * @var string $Denominazione
     * @var string $CodiceAOO
     * @var string $AOO
     * @var string $Indirizzo
     * @var string $IndirizzoTelematico
     * @var string $Localizzazione
     * @var string $Riservato
     */
    public function __construct($CodiceAmministrazione, $Denominazione, $CodiceAOO, $AOO, $Indirizzo, $IndirizzoTelematico, $Localizzazione, $Riservato)
    {
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->Denominazione = $Denominazione;
        $this->CodiceAOO = $CodiceAOO;
        $this->AOO = $AOO;
        $this->Indirizzo = $Indirizzo;
        $this->IndirizzoTelematico = $IndirizzoTelematico;
        $this->Localizzazione = $Localizzazione;
        $this->Riservato = $Riservato;
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
     * @return InteropOut
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
    public function getDenominazione()
    {
        return $this->Denominazione;
    }

    /**
     * @param string $Denominazione
     * @return InteropOut
     */
    public function withDenominazione($Denominazione)
    {
        $new = clone $this;
        $new->Denominazione = $Denominazione;

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
     * @return InteropOut
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
    public function getAOO()
    {
        return $this->AOO;
    }

    /**
     * @param string $AOO
     * @return InteropOut
     */
    public function withAOO($AOO)
    {
        $new = clone $this;
        $new->AOO = $AOO;

        return $new;
    }

    /**
     * @return string
     */
    public function getIndirizzo()
    {
        return $this->Indirizzo;
    }

    /**
     * @param string $Indirizzo
     * @return InteropOut
     */
    public function withIndirizzo($Indirizzo)
    {
        $new = clone $this;
        $new->Indirizzo = $Indirizzo;

        return $new;
    }

    /**
     * @return string
     */
    public function getIndirizzoTelematico()
    {
        return $this->IndirizzoTelematico;
    }

    /**
     * @param string $IndirizzoTelematico
     * @return InteropOut
     */
    public function withIndirizzoTelematico($IndirizzoTelematico)
    {
        $new = clone $this;
        $new->IndirizzoTelematico = $IndirizzoTelematico;

        return $new;
    }

    /**
     * @return string
     */
    public function getLocalizzazione()
    {
        return $this->Localizzazione;
    }

    /**
     * @param string $Localizzazione
     * @return InteropOut
     */
    public function withLocalizzazione($Localizzazione)
    {
        $new = clone $this;
        $new->Localizzazione = $Localizzazione;

        return $new;
    }

    /**
     * @return string
     */
    public function getRiservato()
    {
        return $this->Riservato;
    }

    /**
     * @param string $Riservato
     * @return InteropOut
     */
    public function withRiservato($Riservato)
    {
        $new = clone $this;
        $new->Riservato = $Riservato;

        return $new;
    }


}

