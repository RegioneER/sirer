<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CorrispondenteOut implements RequestInterface
{

    /**
     * @var int
     */
    private $IdSoggetto = null;

    /**
     * @var string
     */
    private $Denominazione = null;

    /**
     * @var bool
     */
    private $FlagAmministrazione = null;

    /**
     * @var string
     */
    private $CodiceAmministrazione = null;

    /**
     * @var string
     */
    private $AOO = null;

    /**
     * @var string
     */
    private $CodiceAOO = null;

    /**
     * @var string
     */
    private $UnitaOrganizzativa = null;

    /**
     * @var string
     */
    private $NumeroRegistrazione = null;

    /**
     * @var string
     */
    private $DataRegistrazione = null;

    /**
     * Constructor
     *
     * @var int $IdSoggetto
     * @var string $Denominazione
     * @var bool $FlagAmministrazione
     * @var string $CodiceAmministrazione
     * @var string $AOO
     * @var string $CodiceAOO
     * @var string $UnitaOrganizzativa
     * @var string $NumeroRegistrazione
     * @var string $DataRegistrazione
     */
    public function __construct($IdSoggetto, $Denominazione, $FlagAmministrazione, $CodiceAmministrazione, $AOO, $CodiceAOO, $UnitaOrganizzativa, $NumeroRegistrazione, $DataRegistrazione)
    {
        $this->IdSoggetto = $IdSoggetto;
        $this->Denominazione = $Denominazione;
        $this->FlagAmministrazione = $FlagAmministrazione;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->AOO = $AOO;
        $this->CodiceAOO = $CodiceAOO;
        $this->UnitaOrganizzativa = $UnitaOrganizzativa;
        $this->NumeroRegistrazione = $NumeroRegistrazione;
        $this->DataRegistrazione = $DataRegistrazione;
    }

    /**
     * @return int
     */
    public function getIdSoggetto()
    {
        return $this->IdSoggetto;
    }

    /**
     * @param int $IdSoggetto
     * @return CorrispondenteOut
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
    public function getDenominazione()
    {
        return $this->Denominazione;
    }

    /**
     * @param string $Denominazione
     * @return CorrispondenteOut
     */
    public function withDenominazione($Denominazione)
    {
        $new = clone $this;
        $new->Denominazione = $Denominazione;

        return $new;
    }

    /**
     * @return bool
     */
    public function getFlagAmministrazione()
    {
        return $this->FlagAmministrazione;
    }

    /**
     * @param bool $FlagAmministrazione
     * @return CorrispondenteOut
     */
    public function withFlagAmministrazione($FlagAmministrazione)
    {
        $new = clone $this;
        $new->FlagAmministrazione = $FlagAmministrazione;

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
     * @return CorrispondenteOut
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
    public function getAOO()
    {
        return $this->AOO;
    }

    /**
     * @param string $AOO
     * @return CorrispondenteOut
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
    public function getCodiceAOO()
    {
        return $this->CodiceAOO;
    }

    /**
     * @param string $CodiceAOO
     * @return CorrispondenteOut
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
    public function getUnitaOrganizzativa()
    {
        return $this->UnitaOrganizzativa;
    }

    /**
     * @param string $UnitaOrganizzativa
     * @return CorrispondenteOut
     */
    public function withUnitaOrganizzativa($UnitaOrganizzativa)
    {
        $new = clone $this;
        $new->UnitaOrganizzativa = $UnitaOrganizzativa;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroRegistrazione()
    {
        return $this->NumeroRegistrazione;
    }

    /**
     * @param string $NumeroRegistrazione
     * @return CorrispondenteOut
     */
    public function withNumeroRegistrazione($NumeroRegistrazione)
    {
        $new = clone $this;
        $new->NumeroRegistrazione = $NumeroRegistrazione;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataRegistrazione()
    {
        return $this->DataRegistrazione;
    }

    /**
     * @param string $DataRegistrazione
     * @return CorrispondenteOut
     */
    public function withDataRegistrazione($DataRegistrazione)
    {
        $new = clone $this;
        $new->DataRegistrazione = $DataRegistrazione;

        return $new;
    }


}

