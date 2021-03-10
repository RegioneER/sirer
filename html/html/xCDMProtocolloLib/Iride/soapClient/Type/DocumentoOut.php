<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DocumentoOut implements RequestInterface
{

    /**
     * @var int
     */
    private $IdDocumento = null;

    /**
     * @var int
     */
    private $AnnoProtocollo = null;

    /**
     * @var int
     */
    private $NumeroProtocollo = null;

    /**
     * @var \DateTime
     */
    private $DataProtocollo = null;

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
    private $Classifica = null;

    /**
     * @var string
     */
    private $Classifica_Descrizione = null;

    /**
     * @var string
     */
    private $TipoDocumento = null;

    /**
     * @var string
     */
    private $TipoDocumento_Descrizione = null;

    /**
     * @var string
     */
    private $MittenteInterno = null;

    /**
     * @var string
     */
    private $MittenteInterno_Descrizione = null;

    /**
     * @var \IrideWS\Type\ArrayOfMittenteDestinatarioOut
     */
    private $MittentiDestinatari = null;

    /**
     * @var \DateTime
     */
    private $DataDocumento = null;

    /**
     * @var string
     */
    private $NumeroDocumento = null;

    /**
     * @var string
     */
    private $InCaricoA = null;

    /**
     * @var string
     */
    private $InCaricoA_Descrizione = null;

    /**
     * @var string
     */
    private $AnnoNumeroData = null;

    /**
     * @var int
     */
    private $AnnoPratica = null;

    /**
     * @var string
     */
    private $NumeroPratica = null;

    /**
     * @var string
     */
    private $AnnoNumeroPratica = null;

    /**
     * @var string
     */
    private $LivelloDiSicurezza = null;

    /**
     * @var \DateTime
     */
    private $DataEvidenza = null;

    /**
     * @var string
     */
    private $DocAllegati = null;

    /**
     * @var bool
     */
    private $DocumentoRiservato = null;

    /**
     * @var int
     */
    private $IterAttivo = null;

    /**
     * @var \DateTime
     */
    private $DataDiCarico = null;

    /**
     * @var string
     */
    private $UtenteDiInserimento = null;

    /**
     * @var \DateTime
     */
    private $DataInserimento = null;

    /**
     * @var string
     */
    private $Messaggio = null;

    /**
     * @var \IrideWS\Type\ArrayOfAllegatoOut
     */
    private $Allegati = null;

    /**
     * @var \IrideWS\Type\ArrayOfImpegnoOut
     */
    private $Impegni = null;

    /**
     * @var \IrideWS\Type\ArrayOfAccertamentoOut
     */
    private $Accertamenti = null;

    /**
     * @var \IrideWS\Type\ArrayOfCentriDiCostoOut
     */
    private $CentriDiCosto = null;

    /**
     * @var \IrideWS\Type\ArrayOfRegistroAssegnatoOut
     */
    private $Registri = null;

    /**
     * @var \IrideWS\Type\InteropOut
     */
    private $Interop = null;

    /**
     * @var \IrideWS\Type\RispostaAlProtocolloOut
     */
    private $RispostaAlProtocollo = null;

    /**
     * @var \IrideWS\Type\ArrayOfProtocolloGeneratoOut
     */
    private $ProtocolliGenerati = null;

    /**
     * @var \IrideWS\Type\ArrayOfCorrispondenteOut
     */
    private $Corrispondenti = null;

    /**
     * @var string
     */
    private $Errore = null;

    /**
     * @var int
     */
    private $IdPratica = null;

    /**
     * @var \DateTime
     */
    private $DataInizioPubblicazione = null;

    /**
     * @var \DateTime
     */
    private $DataFinePubblicazione = null;

    /**
     * @var \IrideWS\Type\ArrayOfTabellaUtente
     */
    private $DatiUtente = null;

    /**
     * Constructor
     *
     * @var int $IdDocumento
     * @var int $AnnoProtocollo
     * @var int $NumeroProtocollo
     * @var \DateTime $DataProtocollo
     * @var string $Oggetto
     * @var string $OggettoBilingue
     * @var string $Origine
     * @var string $Classifica
     * @var string $Classifica_Descrizione
     * @var string $TipoDocumento
     * @var string $TipoDocumento_Descrizione
     * @var string $MittenteInterno
     * @var string $MittenteInterno_Descrizione
     * @var \IrideWS\Type\ArrayOfMittenteDestinatarioOut $MittentiDestinatari
     * @var \DateTime $DataDocumento
     * @var string $NumeroDocumento
     * @var string $InCaricoA
     * @var string $InCaricoA_Descrizione
     * @var string $AnnoNumeroData
     * @var int $AnnoPratica
     * @var string $NumeroPratica
     * @var string $AnnoNumeroPratica
     * @var string $LivelloDiSicurezza
     * @var \DateTime $DataEvidenza
     * @var string $DocAllegati
     * @var bool $DocumentoRiservato
     * @var int $IterAttivo
     * @var \DateTime $DataDiCarico
     * @var string $UtenteDiInserimento
     * @var \DateTime $DataInserimento
     * @var string $Messaggio
     * @var \IrideWS\Type\ArrayOfAllegatoOut $Allegati
     * @var \IrideWS\Type\ArrayOfImpegnoOut $Impegni
     * @var \IrideWS\Type\ArrayOfAccertamentoOut $Accertamenti
     * @var \IrideWS\Type\ArrayOfCentriDiCostoOut $CentriDiCosto
     * @var \IrideWS\Type\ArrayOfRegistroAssegnatoOut $Registri
     * @var \IrideWS\Type\InteropOut $Interop
     * @var \IrideWS\Type\RispostaAlProtocolloOut $RispostaAlProtocollo
     * @var \IrideWS\Type\ArrayOfProtocolloGeneratoOut $ProtocolliGenerati
     * @var \IrideWS\Type\ArrayOfCorrispondenteOut $Corrispondenti
     * @var string $Errore
     * @var int $IdPratica
     * @var \DateTime $DataInizioPubblicazione
     * @var \DateTime $DataFinePubblicazione
     * @var \IrideWS\Type\ArrayOfTabellaUtente $DatiUtente
     */
    public function __construct($IdDocumento, $AnnoProtocollo, $NumeroProtocollo, $DataProtocollo, $Oggetto, $OggettoBilingue, $Origine, $Classifica, $Classifica_Descrizione, $TipoDocumento, $TipoDocumento_Descrizione, $MittenteInterno, $MittenteInterno_Descrizione, $MittentiDestinatari, $DataDocumento, $NumeroDocumento, $InCaricoA, $InCaricoA_Descrizione, $AnnoNumeroData, $AnnoPratica, $NumeroPratica, $AnnoNumeroPratica, $LivelloDiSicurezza, $DataEvidenza, $DocAllegati, $DocumentoRiservato, $IterAttivo, $DataDiCarico, $UtenteDiInserimento, $DataInserimento, $Messaggio, $Allegati, $Impegni, $Accertamenti, $CentriDiCosto, $Registri, $Interop, $RispostaAlProtocollo, $ProtocolliGenerati, $Corrispondenti, $Errore, $IdPratica, $DataInizioPubblicazione, $DataFinePubblicazione, $DatiUtente)
    {
        $this->IdDocumento = $IdDocumento;
        $this->AnnoProtocollo = $AnnoProtocollo;
        $this->NumeroProtocollo = $NumeroProtocollo;
        $this->DataProtocollo = $DataProtocollo;
        $this->Oggetto = $Oggetto;
        $this->OggettoBilingue = $OggettoBilingue;
        $this->Origine = $Origine;
        $this->Classifica = $Classifica;
        $this->Classifica_Descrizione = $Classifica_Descrizione;
        $this->TipoDocumento = $TipoDocumento;
        $this->TipoDocumento_Descrizione = $TipoDocumento_Descrizione;
        $this->MittenteInterno = $MittenteInterno;
        $this->MittenteInterno_Descrizione = $MittenteInterno_Descrizione;
        $this->MittentiDestinatari = $MittentiDestinatari;
        $this->DataDocumento = $DataDocumento;
        $this->NumeroDocumento = $NumeroDocumento;
        $this->InCaricoA = $InCaricoA;
        $this->InCaricoA_Descrizione = $InCaricoA_Descrizione;
        $this->AnnoNumeroData = $AnnoNumeroData;
        $this->AnnoPratica = $AnnoPratica;
        $this->NumeroPratica = $NumeroPratica;
        $this->AnnoNumeroPratica = $AnnoNumeroPratica;
        $this->LivelloDiSicurezza = $LivelloDiSicurezza;
        $this->DataEvidenza = $DataEvidenza;
        $this->DocAllegati = $DocAllegati;
        $this->DocumentoRiservato = $DocumentoRiservato;
        $this->IterAttivo = $IterAttivo;
        $this->DataDiCarico = $DataDiCarico;
        $this->UtenteDiInserimento = $UtenteDiInserimento;
        $this->DataInserimento = $DataInserimento;
        $this->Messaggio = $Messaggio;
        $this->Allegati = $Allegati;
        $this->Impegni = $Impegni;
        $this->Accertamenti = $Accertamenti;
        $this->CentriDiCosto = $CentriDiCosto;
        $this->Registri = $Registri;
        $this->Interop = $Interop;
        $this->RispostaAlProtocollo = $RispostaAlProtocollo;
        $this->ProtocolliGenerati = $ProtocolliGenerati;
        $this->Corrispondenti = $Corrispondenti;
        $this->Errore = $Errore;
        $this->IdPratica = $IdPratica;
        $this->DataInizioPubblicazione = $DataInizioPubblicazione;
        $this->DataFinePubblicazione = $DataFinePubblicazione;
        $this->DatiUtente = $DatiUtente;
    }

    /**
     * @return int
     */
    public function getIdDocumento()
    {
        return $this->IdDocumento;
    }

    /**
     * @param int $IdDocumento
     * @return DocumentoOut
     */
    public function withIdDocumento($IdDocumento)
    {
        $new = clone $this;
        $new->IdDocumento = $IdDocumento;

        return $new;
    }

    /**
     * @return int
     */
    public function getAnnoProtocollo()
    {
        return $this->AnnoProtocollo;
    }

    /**
     * @param int $AnnoProtocollo
     * @return DocumentoOut
     */
    public function withAnnoProtocollo($AnnoProtocollo)
    {
        $new = clone $this;
        $new->AnnoProtocollo = $AnnoProtocollo;

        return $new;
    }

    /**
     * @return int
     */
    public function getNumeroProtocollo()
    {
        return $this->NumeroProtocollo;
    }

    /**
     * @param int $NumeroProtocollo
     * @return DocumentoOut
     */
    public function withNumeroProtocollo($NumeroProtocollo)
    {
        $new = clone $this;
        $new->NumeroProtocollo = $NumeroProtocollo;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataProtocollo()
    {
        return $this->DataProtocollo;
    }

    /**
     * @param \DateTime $DataProtocollo
     * @return DocumentoOut
     */
    public function withDataProtocollo($DataProtocollo)
    {
        $new = clone $this;
        $new->DataProtocollo = $DataProtocollo;

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
     * @return DocumentoOut
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
     * @return DocumentoOut
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
     * @return DocumentoOut
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
    public function getClassifica()
    {
        return $this->Classifica;
    }

    /**
     * @param string $Classifica
     * @return DocumentoOut
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
    public function getClassifica_Descrizione()
    {
        return $this->Classifica_Descrizione;
    }

    /**
     * @param string $Classifica_Descrizione
     * @return DocumentoOut
     */
    public function withClassifica_Descrizione($Classifica_Descrizione)
    {
        $new = clone $this;
        $new->Classifica_Descrizione = $Classifica_Descrizione;

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
     * @return DocumentoOut
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
    public function getTipoDocumento_Descrizione()
    {
        return $this->TipoDocumento_Descrizione;
    }

    /**
     * @param string $TipoDocumento_Descrizione
     * @return DocumentoOut
     */
    public function withTipoDocumento_Descrizione($TipoDocumento_Descrizione)
    {
        $new = clone $this;
        $new->TipoDocumento_Descrizione = $TipoDocumento_Descrizione;

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
     * @return DocumentoOut
     */
    public function withMittenteInterno($MittenteInterno)
    {
        $new = clone $this;
        $new->MittenteInterno = $MittenteInterno;

        return $new;
    }

    /**
     * @return string
     */
    public function getMittenteInterno_Descrizione()
    {
        return $this->MittenteInterno_Descrizione;
    }

    /**
     * @param string $MittenteInterno_Descrizione
     * @return DocumentoOut
     */
    public function withMittenteInterno_Descrizione($MittenteInterno_Descrizione)
    {
        $new = clone $this;
        $new->MittenteInterno_Descrizione = $MittenteInterno_Descrizione;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfMittenteDestinatarioOut
     */
    public function getMittentiDestinatari()
    {
        return $this->MittentiDestinatari;
    }

    /**
     * @param \IrideWS\Type\ArrayOfMittenteDestinatarioOut $MittentiDestinatari
     * @return DocumentoOut
     */
    public function withMittentiDestinatari($MittentiDestinatari)
    {
        $new = clone $this;
        $new->MittentiDestinatari = $MittentiDestinatari;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataDocumento()
    {
        return $this->DataDocumento;
    }

    /**
     * @param \DateTime $DataDocumento
     * @return DocumentoOut
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
     * @return DocumentoOut
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
    public function getInCaricoA()
    {
        return $this->InCaricoA;
    }

    /**
     * @param string $InCaricoA
     * @return DocumentoOut
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
    public function getInCaricoA_Descrizione()
    {
        return $this->InCaricoA_Descrizione;
    }

    /**
     * @param string $InCaricoA_Descrizione
     * @return DocumentoOut
     */
    public function withInCaricoA_Descrizione($InCaricoA_Descrizione)
    {
        $new = clone $this;
        $new->InCaricoA_Descrizione = $InCaricoA_Descrizione;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnnoNumeroData()
    {
        return $this->AnnoNumeroData;
    }

    /**
     * @param string $AnnoNumeroData
     * @return DocumentoOut
     */
    public function withAnnoNumeroData($AnnoNumeroData)
    {
        $new = clone $this;
        $new->AnnoNumeroData = $AnnoNumeroData;

        return $new;
    }

    /**
     * @return int
     */
    public function getAnnoPratica()
    {
        return $this->AnnoPratica;
    }

    /**
     * @param int $AnnoPratica
     * @return DocumentoOut
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
     * @return DocumentoOut
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
    public function getAnnoNumeroPratica()
    {
        return $this->AnnoNumeroPratica;
    }

    /**
     * @param string $AnnoNumeroPratica
     * @return DocumentoOut
     */
    public function withAnnoNumeroPratica($AnnoNumeroPratica)
    {
        $new = clone $this;
        $new->AnnoNumeroPratica = $AnnoNumeroPratica;

        return $new;
    }

    /**
     * @return string
     */
    public function getLivelloDiSicurezza()
    {
        return $this->LivelloDiSicurezza;
    }

    /**
     * @param string $LivelloDiSicurezza
     * @return DocumentoOut
     */
    public function withLivelloDiSicurezza($LivelloDiSicurezza)
    {
        $new = clone $this;
        $new->LivelloDiSicurezza = $LivelloDiSicurezza;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataEvidenza()
    {
        return $this->DataEvidenza;
    }

    /**
     * @param \DateTime $DataEvidenza
     * @return DocumentoOut
     */
    public function withDataEvidenza($DataEvidenza)
    {
        $new = clone $this;
        $new->DataEvidenza = $DataEvidenza;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocAllegati()
    {
        return $this->DocAllegati;
    }

    /**
     * @param string $DocAllegati
     * @return DocumentoOut
     */
    public function withDocAllegati($DocAllegati)
    {
        $new = clone $this;
        $new->DocAllegati = $DocAllegati;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDocumentoRiservato()
    {
        return $this->DocumentoRiservato;
    }

    /**
     * @param bool $DocumentoRiservato
     * @return DocumentoOut
     */
    public function withDocumentoRiservato($DocumentoRiservato)
    {
        $new = clone $this;
        $new->DocumentoRiservato = $DocumentoRiservato;

        return $new;
    }

    /**
     * @return int
     */
    public function getIterAttivo()
    {
        return $this->IterAttivo;
    }

    /**
     * @param int $IterAttivo
     * @return DocumentoOut
     */
    public function withIterAttivo($IterAttivo)
    {
        $new = clone $this;
        $new->IterAttivo = $IterAttivo;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataDiCarico()
    {
        return $this->DataDiCarico;
    }

    /**
     * @param \DateTime $DataDiCarico
     * @return DocumentoOut
     */
    public function withDataDiCarico($DataDiCarico)
    {
        $new = clone $this;
        $new->DataDiCarico = $DataDiCarico;

        return $new;
    }

    /**
     * @return string
     */
    public function getUtenteDiInserimento()
    {
        return $this->UtenteDiInserimento;
    }

    /**
     * @param string $UtenteDiInserimento
     * @return DocumentoOut
     */
    public function withUtenteDiInserimento($UtenteDiInserimento)
    {
        $new = clone $this;
        $new->UtenteDiInserimento = $UtenteDiInserimento;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataInserimento()
    {
        return $this->DataInserimento;
    }

    /**
     * @param \DateTime $DataInserimento
     * @return DocumentoOut
     */
    public function withDataInserimento($DataInserimento)
    {
        $new = clone $this;
        $new->DataInserimento = $DataInserimento;

        return $new;
    }

    /**
     * @return string
     */
    public function getMessaggio()
    {
        return $this->Messaggio;
    }

    /**
     * @param string $Messaggio
     * @return DocumentoOut
     */
    public function withMessaggio($Messaggio)
    {
        $new = clone $this;
        $new->Messaggio = $Messaggio;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfAllegatoOut
     */
    public function getAllegati()
    {
        return $this->Allegati;
    }

    /**
     * @param \IrideWS\Type\ArrayOfAllegatoOut $Allegati
     * @return DocumentoOut
     */
    public function withAllegati($Allegati)
    {
        $new = clone $this;
        $new->Allegati = $Allegati;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfImpegnoOut
     */
    public function getImpegni()
    {
        return $this->Impegni;
    }

    /**
     * @param \IrideWS\Type\ArrayOfImpegnoOut $Impegni
     * @return DocumentoOut
     */
    public function withImpegni($Impegni)
    {
        $new = clone $this;
        $new->Impegni = $Impegni;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfAccertamentoOut
     */
    public function getAccertamenti()
    {
        return $this->Accertamenti;
    }

    /**
     * @param \IrideWS\Type\ArrayOfAccertamentoOut $Accertamenti
     * @return DocumentoOut
     */
    public function withAccertamenti($Accertamenti)
    {
        $new = clone $this;
        $new->Accertamenti = $Accertamenti;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfCentriDiCostoOut
     */
    public function getCentriDiCosto()
    {
        return $this->CentriDiCosto;
    }

    /**
     * @param \IrideWS\Type\ArrayOfCentriDiCostoOut $CentriDiCosto
     * @return DocumentoOut
     */
    public function withCentriDiCosto($CentriDiCosto)
    {
        $new = clone $this;
        $new->CentriDiCosto = $CentriDiCosto;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfRegistroAssegnatoOut
     */
    public function getRegistri()
    {
        return $this->Registri;
    }

    /**
     * @param \IrideWS\Type\ArrayOfRegistroAssegnatoOut $Registri
     * @return DocumentoOut
     */
    public function withRegistri($Registri)
    {
        $new = clone $this;
        $new->Registri = $Registri;

        return $new;
    }

    /**
     * @return \IrideWS\Type\InteropOut
     */
    public function getInterop()
    {
        return $this->Interop;
    }

    /**
     * @param \IrideWS\Type\InteropOut $Interop
     * @return DocumentoOut
     */
    public function withInterop($Interop)
    {
        $new = clone $this;
        $new->Interop = $Interop;

        return $new;
    }

    /**
     * @return \IrideWS\Type\RispostaAlProtocolloOut
     */
    public function getRispostaAlProtocollo()
    {
        return $this->RispostaAlProtocollo;
    }

    /**
     * @param \IrideWS\Type\RispostaAlProtocolloOut $RispostaAlProtocollo
     * @return DocumentoOut
     */
    public function withRispostaAlProtocollo($RispostaAlProtocollo)
    {
        $new = clone $this;
        $new->RispostaAlProtocollo = $RispostaAlProtocollo;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfProtocolloGeneratoOut
     */
    public function getProtocolliGenerati()
    {
        return $this->ProtocolliGenerati;
    }

    /**
     * @param \IrideWS\Type\ArrayOfProtocolloGeneratoOut $ProtocolliGenerati
     * @return DocumentoOut
     */
    public function withProtocolliGenerati($ProtocolliGenerati)
    {
        $new = clone $this;
        $new->ProtocolliGenerati = $ProtocolliGenerati;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfCorrispondenteOut
     */
    public function getCorrispondenti()
    {
        return $this->Corrispondenti;
    }

    /**
     * @param \IrideWS\Type\ArrayOfCorrispondenteOut $Corrispondenti
     * @return DocumentoOut
     */
    public function withCorrispondenti($Corrispondenti)
    {
        $new = clone $this;
        $new->Corrispondenti = $Corrispondenti;

        return $new;
    }

    /**
     * @return string
     */
    public function getErrore()
    {
        return $this->Errore;
    }

    /**
     * @param string $Errore
     * @return DocumentoOut
     */
    public function withErrore($Errore)
    {
        $new = clone $this;
        $new->Errore = $Errore;

        return $new;
    }

    /**
     * @return int
     */
    public function getIdPratica()
    {
        return $this->IdPratica;
    }

    /**
     * @param int $IdPratica
     * @return DocumentoOut
     */
    public function withIdPratica($IdPratica)
    {
        $new = clone $this;
        $new->IdPratica = $IdPratica;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataInizioPubblicazione()
    {
        return $this->DataInizioPubblicazione;
    }

    /**
     * @param \DateTime $DataInizioPubblicazione
     * @return DocumentoOut
     */
    public function withDataInizioPubblicazione($DataInizioPubblicazione)
    {
        $new = clone $this;
        $new->DataInizioPubblicazione = $DataInizioPubblicazione;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataFinePubblicazione()
    {
        return $this->DataFinePubblicazione;
    }

    /**
     * @param \DateTime $DataFinePubblicazione
     * @return DocumentoOut
     */
    public function withDataFinePubblicazione($DataFinePubblicazione)
    {
        $new = clone $this;
        $new->DataFinePubblicazione = $DataFinePubblicazione;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfTabellaUtente
     */
    public function getDatiUtente()
    {
        return $this->DatiUtente;
    }

    /**
     * @param \IrideWS\Type\ArrayOfTabellaUtente $DatiUtente
     * @return DocumentoOut
     */
    public function withDatiUtente($DatiUtente)
    {
        $new = clone $this;
        $new->DatiUtente = $DatiUtente;

        return $new;
    }


}

