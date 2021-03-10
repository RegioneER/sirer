<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class MittenteDestinatarioIn implements RequestInterface
{

    /**
     * @var string
     */
    private $CodiceFiscale = null;

    /**
     * @var string
     */
    private $CognomeNome = null;

    /**
     * @var string
     */
    private $Nome = null;

    /**
     * @var string
     */
    private $Indirizzo = null;

    /**
     * @var string
     */
    private $Localita = null;

    /**
     * @var string
     */
    private $CodiceComuneResidenza = null;

    /**
     * @var string
     */
    private $DataNascita = null;

    /**
     * @var string
     */
    private $CodiceComuneNascita = null;

    /**
     * @var string
     */
    private $Nazionalita = null;

    /**
     * @var string
     */
    private $DataInvio_DataProt = null;

    /**
     * @var string
     */
    private $Spese_NProt = null;

    /**
     * @var string
     */
    private $Mezzo = null;

    /**
     * @var string
     */
    private $DataRicevimento = null;

    /**
     * @var string
     */
    private $TipoSogg = null;

    /**
     * @var string
     */
    private $TipoPersona = null;

    /**
     * @var \IrideWS\Type\ArrayOfRecapitoIn
     */
    private $Recapiti = null;

    /**
     * Constructor
     *
     * @var string $CodiceFiscale
     * @var string $CognomeNome
     * @var string $Nome
     * @var string $Indirizzo
     * @var string $Localita
     * @var string $CodiceComuneResidenza
     * @var string $DataNascita
     * @var string $CodiceComuneNascita
     * @var string $Nazionalita
     * @var string $DataInvio_DataProt
     * @var string $Spese_NProt
     * @var string $Mezzo
     * @var string $DataRicevimento
     * @var string $TipoSogg
     * @var string $TipoPersona
     * @var \IrideWS\Type\ArrayOfRecapitoIn $Recapiti
     */
    public function __construct($CodiceFiscale, $CognomeNome, $Nome, $Indirizzo, $Localita, $CodiceComuneResidenza, $DataNascita, $CodiceComuneNascita, $Nazionalita, $DataInvio_DataProt, $Spese_NProt, $Mezzo, $DataRicevimento, $TipoSogg, $TipoPersona, $Recapiti)
    {
        $this->CodiceFiscale = $CodiceFiscale;
        $this->CognomeNome = $CognomeNome;
        $this->Nome = $Nome;
        $this->Indirizzo = $Indirizzo;
        $this->Localita = $Localita;
        $this->CodiceComuneResidenza = $CodiceComuneResidenza;
        $this->DataNascita = $DataNascita;
        $this->CodiceComuneNascita = $CodiceComuneNascita;
        $this->Nazionalita = $Nazionalita;
        $this->DataInvio_DataProt = $DataInvio_DataProt;
        $this->Spese_NProt = $Spese_NProt;
        $this->Mezzo = $Mezzo;
        $this->DataRicevimento = $DataRicevimento;
        $this->TipoSogg = $TipoSogg;
        $this->TipoPersona = $TipoPersona;
        $this->Recapiti = $Recapiti;
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
     * @return MittenteDestinatarioIn
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
    public function getCognomeNome()
    {
        return $this->CognomeNome;
    }

    /**
     * @param string $CognomeNome
     * @return MittenteDestinatarioIn
     */
    public function withCognomeNome($CognomeNome)
    {
        $new = clone $this;
        $new->CognomeNome = $CognomeNome;

        return $new;
    }

    /**
     * @return string
     */
    public function getNome()
    {
        return $this->Nome;
    }

    /**
     * @param string $Nome
     * @return MittenteDestinatarioIn
     */
    public function withNome($Nome)
    {
        $new = clone $this;
        $new->Nome = $Nome;

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
     * @return MittenteDestinatarioIn
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
    public function getLocalita()
    {
        return $this->Localita;
    }

    /**
     * @param string $Localita
     * @return MittenteDestinatarioIn
     */
    public function withLocalita($Localita)
    {
        $new = clone $this;
        $new->Localita = $Localita;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceComuneResidenza()
    {
        return $this->CodiceComuneResidenza;
    }

    /**
     * @param string $CodiceComuneResidenza
     * @return MittenteDestinatarioIn
     */
    public function withCodiceComuneResidenza($CodiceComuneResidenza)
    {
        $new = clone $this;
        $new->CodiceComuneResidenza = $CodiceComuneResidenza;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataNascita()
    {
        return $this->DataNascita;
    }

    /**
     * @param string $DataNascita
     * @return MittenteDestinatarioIn
     */
    public function withDataNascita($DataNascita)
    {
        $new = clone $this;
        $new->DataNascita = $DataNascita;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceComuneNascita()
    {
        return $this->CodiceComuneNascita;
    }

    /**
     * @param string $CodiceComuneNascita
     * @return MittenteDestinatarioIn
     */
    public function withCodiceComuneNascita($CodiceComuneNascita)
    {
        $new = clone $this;
        $new->CodiceComuneNascita = $CodiceComuneNascita;

        return $new;
    }

    /**
     * @return string
     */
    public function getNazionalita()
    {
        return $this->Nazionalita;
    }

    /**
     * @param string $Nazionalita
     * @return MittenteDestinatarioIn
     */
    public function withNazionalita($Nazionalita)
    {
        $new = clone $this;
        $new->Nazionalita = $Nazionalita;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataInvio_DataProt()
    {
        return $this->DataInvio_DataProt;
    }

    /**
     * @param string $DataInvio_DataProt
     * @return MittenteDestinatarioIn
     */
    public function withDataInvio_DataProt($DataInvio_DataProt)
    {
        $new = clone $this;
        $new->DataInvio_DataProt = $DataInvio_DataProt;

        return $new;
    }

    /**
     * @return string
     */
    public function getSpese_NProt()
    {
        return $this->Spese_NProt;
    }

    /**
     * @param string $Spese_NProt
     * @return MittenteDestinatarioIn
     */
    public function withSpese_NProt($Spese_NProt)
    {
        $new = clone $this;
        $new->Spese_NProt = $Spese_NProt;

        return $new;
    }

    /**
     * @return string
     */
    public function getMezzo()
    {
        return $this->Mezzo;
    }

    /**
     * @param string $Mezzo
     * @return MittenteDestinatarioIn
     */
    public function withMezzo($Mezzo)
    {
        $new = clone $this;
        $new->Mezzo = $Mezzo;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataRicevimento()
    {
        return $this->DataRicevimento;
    }

    /**
     * @param string $DataRicevimento
     * @return MittenteDestinatarioIn
     */
    public function withDataRicevimento($DataRicevimento)
    {
        $new = clone $this;
        $new->DataRicevimento = $DataRicevimento;

        return $new;
    }

    /**
     * @return string
     */
    public function getTipoSogg()
    {
        return $this->TipoSogg;
    }

    /**
     * @param string $TipoSogg
     * @return MittenteDestinatarioIn
     */
    public function withTipoSogg($TipoSogg)
    {
        $new = clone $this;
        $new->TipoSogg = $TipoSogg;

        return $new;
    }

    /**
     * @return string
     */
    public function getTipoPersona()
    {
        return $this->TipoPersona;
    }

    /**
     * @param string $TipoPersona
     * @return MittenteDestinatarioIn
     */
    public function withTipoPersona($TipoPersona)
    {
        $new = clone $this;
        $new->TipoPersona = $TipoPersona;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfRecapitoIn
     */
    public function getRecapiti()
    {
        return $this->Recapiti;
    }

    /**
     * @param \IrideWS\Type\ArrayOfRecapitoIn $Recapiti
     * @return MittenteDestinatarioIn
     */
    public function withRecapiti($Recapiti)
    {
        $new = clone $this;
        $new->Recapiti = $Recapiti;

        return $new;
    }


}

