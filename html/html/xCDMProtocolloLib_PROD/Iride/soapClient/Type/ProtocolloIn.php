<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ProtocolloIn implements RequestInterface
{

    /**
     * @var string
     */
    private $Data = null;

    /**
     * @var string
     */
    private $DataProt = null;

    /**
     * @var string
     */
    private $NumProt = null;

    /**
     * @var string
     */
    private $Classifica = null;

    /**
     * @var string
     */
    private $TipoDocumento = null;

    /**
     * @var string
     */
    private $Oggetto = null;

    /**
     * @var string
     */
    private $OggettoBilingue = null;

    /**
     * @var string
     */
    private $Origine = null;

    /**
     * @var string
     */
    private $MittenteInterno = null;

    /**
     * @var \IrideWS\Type\ArrayOfMittenteDestinatarioIn
     */
    private $MittentiDestinatari = null;

    /**
     * @var string
     */
    private $AggiornaAnagrafiche = null;

    /**
     * @var string
     */
    private $InCaricoA = null;

    /**
     * @var string
     */
    private $AnnoPratica = null;

    /**
     * @var string
     */
    private $NumeroPratica = null;

    /**
     * @var string
     */
    private $DataDocumento = null;

    /**
     * @var string
     */
    private $NumeroDocumento = null;

    /**
     * @var string
     */
    private $NumeroAllegati = null;

    /**
     * @var string
     */
    private $DataEvid = null;

    /**
     * @var string
     */
    private $OggettoStandard = null;

    /**
     * @var string
     */
    private $Utente = null;

    /**
     * @var string
     */
    private $Ruolo = null;

    /**
     * @var \IrideWS\Type\ArrayOfAllegatoIn
     */
    private $Allegati = null;

    /**
     * Constructor
     *
     * @var string $Data
     * @var string $DataProt
     * @var string $NumProt
     * @var string $Classifica
     * @var string $TipoDocumento
     * @var string $Oggetto
     * @var string $OggettoBilingue
     * @var string $Origine
     * @var string $MittenteInterno
     * @var \IrideWS\Type\ArrayOfMittenteDestinatarioIn $MittentiDestinatari
     * @var string $AggiornaAnagrafiche
     * @var string $InCaricoA
     * @var string $AnnoPratica
     * @var string $NumeroPratica
     * @var string $DataDocumento
     * @var string $NumeroDocumento
     * @var string $NumeroAllegati
     * @var string $DataEvid
     * @var string $OggettoStandard
     * @var string $Utente
     * @var string $Ruolo
     * @var \IrideWS\Type\ArrayOfAllegatoIn $Allegati
     */
    public function __construct($Data, $DataProt, $NumProt, $Classifica, $TipoDocumento, $Oggetto, $OggettoBilingue, $Origine, $MittenteInterno, $MittentiDestinatari, $AggiornaAnagrafiche, $InCaricoA, $AnnoPratica, $NumeroPratica, $DataDocumento, $NumeroDocumento, $NumeroAllegati, $DataEvid, $OggettoStandard, $Utente, $Ruolo, $Allegati)
    {
        $this->Data = $Data;
        $this->DataProt = $DataProt;
        $this->NumProt = $NumProt;
        $this->Classifica = $Classifica;
        $this->TipoDocumento = $TipoDocumento;
        $this->Oggetto = $Oggetto;
        $this->OggettoBilingue = $OggettoBilingue;
        $this->Origine = $Origine;
        $this->MittenteInterno = $MittenteInterno;
        $this->MittentiDestinatari = $MittentiDestinatari;
        $this->AggiornaAnagrafiche = $AggiornaAnagrafiche;
        $this->InCaricoA = $InCaricoA;
        $this->AnnoPratica = $AnnoPratica;
        $this->NumeroPratica = $NumeroPratica;
        $this->DataDocumento = $DataDocumento;
        $this->NumeroDocumento = $NumeroDocumento;
        $this->NumeroAllegati = $NumeroAllegati;
        $this->DataEvid = $DataEvid;
        $this->OggettoStandard = $OggettoStandard;
        $this->Utente = $Utente;
        $this->Ruolo = $Ruolo;
        $this->Allegati = $Allegati;
    }

    /**
     * @return string
     */
    public function getData()
    {
        return $this->Data;
    }

    /**
     * @param string $Data
     * @return ProtocolloIn
     */
    public function withData($Data)
    {
        $new = clone $this;
        $new->Data = $Data;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataProt()
    {
        return $this->DataProt;
    }

    /**
     * @param string $DataProt
     * @return ProtocolloIn
     */
    public function withDataProt($DataProt)
    {
        $new = clone $this;
        $new->DataProt = $DataProt;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumProt()
    {
        return $this->NumProt;
    }

    /**
     * @param string $NumProt
     * @return ProtocolloIn
     */
    public function withNumProt($NumProt)
    {
        $new = clone $this;
        $new->NumProt = $NumProt;

        return $new;
    }

    /**
     * @return string
     */
    public function getClassifica()
    {
        return $this->Classifica;
    }

    /**
     * @param string $Classifica
     * @return ProtocolloIn
     */
    public function withClassifica($Classifica)
    {
        $new = clone $this;
        $new->Classifica = $Classifica;

        return $new;
    }

    /**
     * @return string
     */
    public function getTipoDocumento()
    {
        return $this->TipoDocumento;
    }

    /**
     * @param string $TipoDocumento
     * @return ProtocolloIn
     */
    public function withTipoDocumento($TipoDocumento)
    {
        $new = clone $this;
        $new->TipoDocumento = $TipoDocumento;

        return $new;
    }

    /**
     * @return string
     */
    public function getOggetto()
    {
        return $this->Oggetto;
    }

    /**
     * @param string $Oggetto
     * @return ProtocolloIn
     */
    public function withOggetto($Oggetto)
    {
        $new = clone $this;
        $new->Oggetto = $Oggetto;

        return $new;
    }

    /**
     * @return string
     */
    public function getOggettoBilingue()
    {
        return $this->OggettoBilingue;
    }

    /**
     * @param string $OggettoBilingue
     * @return ProtocolloIn
     */
    public function withOggettoBilingue($OggettoBilingue)
    {
        $new = clone $this;
        $new->OggettoBilingue = $OggettoBilingue;

        return $new;
    }

    /**
     * @return string
     */
    public function getOrigine()
    {
        return $this->Origine;
    }

    /**
     * @param string $Origine
     * @return ProtocolloIn
     */
    public function withOrigine($Origine)
    {
        $new = clone $this;
        $new->Origine = $Origine;

        return $new;
    }

    /**
     * @return string
     */
    public function getMittenteInterno()
    {
        return $this->MittenteInterno;
    }

    /**
     * @param string $MittenteInterno
     * @return ProtocolloIn
     */
    public function withMittenteInterno($MittenteInterno)
    {
        $new = clone $this;
        $new->MittenteInterno = $MittenteInterno;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfMittenteDestinatarioIn
     */
    public function getMittentiDestinatari()
    {
        return $this->MittentiDestinatari;
    }

    /**
     * @param \IrideWS\Type\ArrayOfMittenteDestinatarioIn $MittentiDestinatari
     * @return ProtocolloIn
     */
    public function withMittentiDestinatari($MittentiDestinatari)
    {
        $new = clone $this;
        $new->MittentiDestinatari = $MittentiDestinatari;

        return $new;
    }

    /**
     * @return string
     */
    public function getAggiornaAnagrafiche()
    {
        return $this->AggiornaAnagrafiche;
    }

    /**
     * @param string $AggiornaAnagrafiche
     * @return ProtocolloIn
     */
    public function withAggiornaAnagrafiche($AggiornaAnagrafiche)
    {
        $new = clone $this;
        $new->AggiornaAnagrafiche = $AggiornaAnagrafiche;

        return $new;
    }

    /**
     * @return string
     */
    public function getInCaricoA()
    {
        return $this->InCaricoA;
    }

    /**
     * @param string $InCaricoA
     * @return ProtocolloIn
     */
    public function withInCaricoA($InCaricoA)
    {
        $new = clone $this;
        $new->InCaricoA = $InCaricoA;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnnoPratica()
    {
        return $this->AnnoPratica;
    }

    /**
     * @param string $AnnoPratica
     * @return ProtocolloIn
     */
    public function withAnnoPratica($AnnoPratica)
    {
        $new = clone $this;
        $new->AnnoPratica = $AnnoPratica;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroPratica()
    {
        return $this->NumeroPratica;
    }

    /**
     * @param string $NumeroPratica
     * @return ProtocolloIn
     */
    public function withNumeroPratica($NumeroPratica)
    {
        $new = clone $this;
        $new->NumeroPratica = $NumeroPratica;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataDocumento()
    {
        return $this->DataDocumento;
    }

    /**
     * @param string $DataDocumento
     * @return ProtocolloIn
     */
    public function withDataDocumento($DataDocumento)
    {
        $new = clone $this;
        $new->DataDocumento = $DataDocumento;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroDocumento()
    {
        return $this->NumeroDocumento;
    }

    /**
     * @param string $NumeroDocumento
     * @return ProtocolloIn
     */
    public function withNumeroDocumento($NumeroDocumento)
    {
        $new = clone $this;
        $new->NumeroDocumento = $NumeroDocumento;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroAllegati()
    {
        return $this->NumeroAllegati;
    }

    /**
     * @param string $NumeroAllegati
     * @return ProtocolloIn
     */
    public function withNumeroAllegati($NumeroAllegati)
    {
        $new = clone $this;
        $new->NumeroAllegati = $NumeroAllegati;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataEvid()
    {
        return $this->DataEvid;
    }

    /**
     * @param string $DataEvid
     * @return ProtocolloIn
     */
    public function withDataEvid($DataEvid)
    {
        $new = clone $this;
        $new->DataEvid = $DataEvid;

        return $new;
    }

    /**
     * @return string
     */
    public function getOggettoStandard()
    {
        return $this->OggettoStandard;
    }

    /**
     * @param string $OggettoStandard
     * @return ProtocolloIn
     */
    public function withOggettoStandard($OggettoStandard)
    {
        $new = clone $this;
        $new->OggettoStandard = $OggettoStandard;

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
     * @return ProtocolloIn
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
     * @return ProtocolloIn
     */
    public function withRuolo($Ruolo)
    {
        $new = clone $this;
        $new->Ruolo = $Ruolo;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfAllegatoIn
     */
    public function getAllegati()
    {
        return $this->Allegati;
    }

    /**
     * @param \IrideWS\Type\ArrayOfAllegatoIn $Allegati
     * @return ProtocolloIn
     */
    public function withAllegati($Allegati)
    {
        $new = clone $this;
        $new->Allegati = $Allegati;

        return $new;
    }


}

