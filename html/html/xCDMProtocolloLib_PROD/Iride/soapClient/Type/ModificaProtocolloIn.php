<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ModificaProtocolloIn implements RequestInterface
{

    /**
     * @var string
     */
    private $IdDocumento = null;

    /**
     * @var string
     */
    private $AnnoProtocollo = null;

    /**
     * @var string
     */
    private $NumeroProtocollo = null;

    /**
     * @var string
     */
    private $Data = null;

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
    private $Utente = null;

    /**
     * @var string
     */
    private $Ruolo = null;

    /**
     * Constructor
     *
     * @var string $IdDocumento
     * @var string $AnnoProtocollo
     * @var string $NumeroProtocollo
     * @var string $Data
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
     * @var string $Utente
     * @var string $Ruolo
     */
    public function __construct($IdDocumento, $AnnoProtocollo, $NumeroProtocollo, $Data, $Classifica, $TipoDocumento, $Oggetto, $OggettoBilingue, $Origine, $MittenteInterno, $MittentiDestinatari, $AggiornaAnagrafiche, $InCaricoA, $AnnoPratica, $NumeroPratica, $DataDocumento, $NumeroDocumento, $NumeroAllegati, $DataEvid, $Utente, $Ruolo)
    {
        $this->IdDocumento = $IdDocumento;
        $this->AnnoProtocollo = $AnnoProtocollo;
        $this->NumeroProtocollo = $NumeroProtocollo;
        $this->Data = $Data;
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
        $this->Utente = $Utente;
        $this->Ruolo = $Ruolo;
    }

    /**
     * @return string
     */
    public function getIdDocumento()
    {
        return $this->IdDocumento;
    }

    /**
     * @param string $IdDocumento
     * @return ModificaProtocolloIn
     */
    public function withIdDocumento($IdDocumento)
    {
        $new = clone $this;
        $new->IdDocumento = $IdDocumento;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnnoProtocollo()
    {
        return $this->AnnoProtocollo;
    }

    /**
     * @param string $AnnoProtocollo
     * @return ModificaProtocolloIn
     */
    public function withAnnoProtocollo($AnnoProtocollo)
    {
        $new = clone $this;
        $new->AnnoProtocollo = $AnnoProtocollo;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroProtocollo()
    {
        return $this->NumeroProtocollo;
    }

    /**
     * @param string $NumeroProtocollo
     * @return ModificaProtocolloIn
     */
    public function withNumeroProtocollo($NumeroProtocollo)
    {
        $new = clone $this;
        $new->NumeroProtocollo = $NumeroProtocollo;

        return $new;
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
     * @return ModificaProtocolloIn
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
    public function getClassifica()
    {
        return $this->Classifica;
    }

    /**
     * @param string $Classifica
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
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
    public function getUtente()
    {
        return $this->Utente;
    }

    /**
     * @param string $Utente
     * @return ModificaProtocolloIn
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
     * @return ModificaProtocolloIn
     */
    public function withRuolo($Ruolo)
    {
        $new = clone $this;
        $new->Ruolo = $Ruolo;

        return $new;
    }


}

