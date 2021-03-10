<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class UserRightsConfig implements RequestInterface
{

    /**
     * @var bool
     */
    private $UrAggiornamentoListe = null;

    /**
     * @var bool
     */
    private $UrAggiungerePagine = null;

    /**
     * @var bool
     */
    private $UrAnnullareProtocollo = null;

    /**
     * @var bool
     */
    private $UrBloccoDocumento = null;

    /**
     * @var bool
     */
    private $UrCambiaSubnet = null;

    /**
     * @var bool
     */
    private $UrCambioClassFascicolo = null;

    /**
     * @var bool
     */
    private $UrCambioStatoFasc = null;

    /**
     * @var bool
     */
    private $UrCancellaFascicolo = null;

    /**
     * @var bool
     */
    private $UrCancellaLista = null;

    /**
     * @var bool
     */
    private $UrCestinareFascicolo = null;

    /**
     * @var bool
     */
    private $UrClassificare = null;

    /**
     * @var bool
     */
    private $UrConfermareAnnulla = null;

    /**
     * @var bool
     */
    private $UrConfermareRipristino = null;

    /**
     * @var bool
     */
    private $UrCreaArmadiCassetti = null;

    /**
     * @var bool
     */
    private $UrCreaFascicoli = null;

    /**
     * @var bool
     */
    private $UrCreateCompliantCopies = null;

    /**
     * @var bool
     */
    private $UrCreateLinkFascArch = null;

    /**
     * @var bool
     */
    private $UrDisDisconnInattivita = null;

    /**
     * @var bool
     */
    private $UrEliminareFascicolo = null;

    /**
     * @var bool
     */
    private $UrEnableSnaAnonymous = null;

    /**
     * @var bool
     */
    private $UrEnableSnaComplete = null;

    /**
     * @var bool
     */
    private $UrExport = null;

    /**
     * @var bool
     */
    private $UrExportFascicolo = null;

    /**
     * @var bool
     */
    private $UrFascicolare = null;

    /**
     * @var bool
     */
    private $UrFascicolareArch = null;

    /**
     * @var bool
     */
    private $UrFirmare = null;

    /**
     * @var bool
     */
    private $UrGestRegProt = null;

    /**
     * @var bool
     */
    private $UrGestioneAnagrafica = null;

    /**
     * @var bool
     */
    private $UrGestioneCartucce = null;

    /**
     * @var bool
     */
    private $UrGestioneFascicolo = null;

    /**
     * @var bool
     */
    private $UrGestionePrenotazioni = null;

    /**
     * @var bool
     */
    private $UrGestioneTemplTit = null;

    /**
     * @var bool
     */
    private $UrGestioneTipoFasc = null;

    /**
     * @var bool
     */
    private $UrGestioneTitolario = null;

    /**
     * @var bool
     */
    private $UrGestioneUtenti = null;

    /**
     * @var bool
     */
    private $UrGestioneVoceTit = null;

    /**
     * @var bool
     */
    private $UrGestireModScanbatch = null;

    /**
     * @var bool
     */
    private $UrImportEmail = null;

    /**
     * @var bool
     */
    private $UrImportGenerico = null;

    /**
     * @var bool
     */
    private $UrImportSpool = null;

    /**
     * @var bool
     */
    private $UrImpostaDocumenti = null;

    /**
     * @var bool
     */
    private $UrImpostaScadenza = null;

    /**
     * @var bool
     */
    private $UrInsModRecAnagrafica = null;

    /**
     * @var bool
     */
    private $UrInserimentoVuoti = null;

    /**
     * @var bool
     */
    private $UrInserire = null;

    /**
     * @var bool
     */
    private $UrInserireNoteFasc = null;

    /**
     * @var bool
     */
    private $UrInvioMessaggi = null;

    /**
     * @var bool
     */
    private $UrInvioOnLine = null;

    /**
     * @var bool
     */
    private $UrInvioPec = null;

    /**
     * @var bool
     */
    private $UrInvioTelematico = null;

    /**
     * @var bool
     */
    private $UrInvoiceAppRejMailing = null;

    /**
     * @var bool
     */
    private $UrInvoiceChangeMonChannel = null;

    /**
     * @var bool
     */
    private $UrInvoiceDataTransm = null;

    /**
     * @var bool
     */
    private $UrInvoiceManualMailing = null;

    /**
     * @var bool
     */
    private $UrInvoiceManualReMailing = null;

    /**
     * @var bool
     */
    private $UrInvoicePlannedMailing = null;

    /**
     * @var bool
     */
    private $UrManageSharedMailboxData = null;

    /**
     * @var bool
     */
    private $UrMassiveSending = null;

    /**
     * @var bool
     */
    private $UrMettereInSmistamento = null;

    /**
     * @var bool
     */
    private $UrModificaAllegati = null;

    /**
     * @var bool
     */
    private $UrModificaAnnotazioni = null;

    /**
     * @var bool
     */
    private $UrModificaArchDoc = null;

    /**
     * @var bool
     */
    private $UrModificaDati = null;

    /**
     * @var bool
     */
    private $UrModificaDatiFasc = null;

    /**
     * @var bool
     */
    private $UrModificaImmagini = null;

    /**
     * @var bool
     */
    private $UrModificaProtocollo = null;

    /**
     * @var bool
     */
    private $UrMovimentazioneFasc = null;

    /**
     * @var bool
     */
    private $UrOcr = null;

    /**
     * @var bool
     */
    private $UrPartialCancels = null;

    /**
     * @var bool
     */
    private $UrPermalink = null;

    /**
     * @var bool
     */
    private $UrPostaEstesa = null;

    /**
     * @var bool
     */
    private $UrPutInPreservation = null;

    /**
     * @var bool
     */
    private $UrRicercare = null;

    /**
     * @var bool
     */
    private $UrRicezioneTelematica = null;

    /**
     * @var bool
     */
    private $UrRispedire = null;

    /**
     * @var bool
     */
    private $UrSapPublish = null;

    /**
     * @var bool
     */
    private $UrScansione = null;

    /**
     * @var bool
     */
    private $UrSignature = null;

    /**
     * @var bool
     */
    private $UrSmistare = null;

    /**
     * @var bool
     */
    private $UrSpedisciFax = null;

    /**
     * @var bool
     */
    private $UrStampaImgControllata = null;

    /**
     * @var bool
     */
    private $UrStampaImmagini = null;

    /**
     * @var bool
     */
    private $UrStampaRegistro = null;

    /**
     * @var bool
     */
    private $UrTasksCreate = null;

    /**
     * @var bool
     */
    private $UrTasksManage = null;

    /**
     * @var bool
     */
    private $UrTogliVisibilita = null;

    /**
     * @var bool
     */
    private $UrUndefined = null;

    /**
     * @var bool
     */
    private $UrUtilizzoGlifo = null;

    /**
     * @var bool
     */
    private $UrVerificaRicevute = null;

    /**
     * @var bool
     */
    private $UrVisibilitaSoloDoc = null;

    /**
     * @var bool
     */
    private $UrVoceObsoleta = null;

    /**
     * @var bool
     */
    private $UrVuoto1 = null;

    /**
     * @var bool
     */
    private $UrVuoto2 = null;

    /**
     * Constructor
     *
     * @var bool $UrAggiornamentoListe
     * @var bool $UrAggiungerePagine
     * @var bool $UrAnnullareProtocollo
     * @var bool $UrBloccoDocumento
     * @var bool $UrCambiaSubnet
     * @var bool $UrCambioClassFascicolo
     * @var bool $UrCambioStatoFasc
     * @var bool $UrCancellaFascicolo
     * @var bool $UrCancellaLista
     * @var bool $UrCestinareFascicolo
     * @var bool $UrClassificare
     * @var bool $UrConfermareAnnulla
     * @var bool $UrConfermareRipristino
     * @var bool $UrCreaArmadiCassetti
     * @var bool $UrCreaFascicoli
     * @var bool $UrCreateCompliantCopies
     * @var bool $UrCreateLinkFascArch
     * @var bool $UrDisDisconnInattivita
     * @var bool $UrEliminareFascicolo
     * @var bool $UrEnableSnaAnonymous
     * @var bool $UrEnableSnaComplete
     * @var bool $UrExport
     * @var bool $UrExportFascicolo
     * @var bool $UrFascicolare
     * @var bool $UrFascicolareArch
     * @var bool $UrFirmare
     * @var bool $UrGestRegProt
     * @var bool $UrGestioneAnagrafica
     * @var bool $UrGestioneCartucce
     * @var bool $UrGestioneFascicolo
     * @var bool $UrGestionePrenotazioni
     * @var bool $UrGestioneTemplTit
     * @var bool $UrGestioneTipoFasc
     * @var bool $UrGestioneTitolario
     * @var bool $UrGestioneUtenti
     * @var bool $UrGestioneVoceTit
     * @var bool $UrGestireModScanbatch
     * @var bool $UrImportEmail
     * @var bool $UrImportGenerico
     * @var bool $UrImportSpool
     * @var bool $UrImpostaDocumenti
     * @var bool $UrImpostaScadenza
     * @var bool $UrInsModRecAnagrafica
     * @var bool $UrInserimentoVuoti
     * @var bool $UrInserire
     * @var bool $UrInserireNoteFasc
     * @var bool $UrInvioMessaggi
     * @var bool $UrInvioOnLine
     * @var bool $UrInvioPec
     * @var bool $UrInvioTelematico
     * @var bool $UrInvoiceAppRejMailing
     * @var bool $UrInvoiceChangeMonChannel
     * @var bool $UrInvoiceDataTransm
     * @var bool $UrInvoiceManualMailing
     * @var bool $UrInvoiceManualReMailing
     * @var bool $UrInvoicePlannedMailing
     * @var bool $UrManageSharedMailboxData
     * @var bool $UrMassiveSending
     * @var bool $UrMettereInSmistamento
     * @var bool $UrModificaAllegati
     * @var bool $UrModificaAnnotazioni
     * @var bool $UrModificaArchDoc
     * @var bool $UrModificaDati
     * @var bool $UrModificaDatiFasc
     * @var bool $UrModificaImmagini
     * @var bool $UrModificaProtocollo
     * @var bool $UrMovimentazioneFasc
     * @var bool $UrOcr
     * @var bool $UrPartialCancels
     * @var bool $UrPermalink
     * @var bool $UrPostaEstesa
     * @var bool $UrPutInPreservation
     * @var bool $UrRicercare
     * @var bool $UrRicezioneTelematica
     * @var bool $UrRispedire
     * @var bool $UrSapPublish
     * @var bool $UrScansione
     * @var bool $UrSignature
     * @var bool $UrSmistare
     * @var bool $UrSpedisciFax
     * @var bool $UrStampaImgControllata
     * @var bool $UrStampaImmagini
     * @var bool $UrStampaRegistro
     * @var bool $UrTasksCreate
     * @var bool $UrTasksManage
     * @var bool $UrTogliVisibilita
     * @var bool $UrUndefined
     * @var bool $UrUtilizzoGlifo
     * @var bool $UrVerificaRicevute
     * @var bool $UrVisibilitaSoloDoc
     * @var bool $UrVoceObsoleta
     * @var bool $UrVuoto1
     * @var bool $UrVuoto2
     */
    public function __construct($UrAggiornamentoListe, $UrAggiungerePagine, $UrAnnullareProtocollo, $UrBloccoDocumento, $UrCambiaSubnet, $UrCambioClassFascicolo, $UrCambioStatoFasc, $UrCancellaFascicolo, $UrCancellaLista, $UrCestinareFascicolo, $UrClassificare, $UrConfermareAnnulla, $UrConfermareRipristino, $UrCreaArmadiCassetti, $UrCreaFascicoli, $UrCreateCompliantCopies, $UrCreateLinkFascArch, $UrDisDisconnInattivita, $UrEliminareFascicolo, $UrEnableSnaAnonymous, $UrEnableSnaComplete, $UrExport, $UrExportFascicolo, $UrFascicolare, $UrFascicolareArch, $UrFirmare, $UrGestRegProt, $UrGestioneAnagrafica, $UrGestioneCartucce, $UrGestioneFascicolo, $UrGestionePrenotazioni, $UrGestioneTemplTit, $UrGestioneTipoFasc, $UrGestioneTitolario, $UrGestioneUtenti, $UrGestioneVoceTit, $UrGestireModScanbatch, $UrImportEmail, $UrImportGenerico, $UrImportSpool, $UrImpostaDocumenti, $UrImpostaScadenza, $UrInsModRecAnagrafica, $UrInserimentoVuoti, $UrInserire, $UrInserireNoteFasc, $UrInvioMessaggi, $UrInvioOnLine, $UrInvioPec, $UrInvioTelematico, $UrInvoiceAppRejMailing, $UrInvoiceChangeMonChannel, $UrInvoiceDataTransm, $UrInvoiceManualMailing, $UrInvoiceManualReMailing, $UrInvoicePlannedMailing, $UrManageSharedMailboxData, $UrMassiveSending, $UrMettereInSmistamento, $UrModificaAllegati, $UrModificaAnnotazioni, $UrModificaArchDoc, $UrModificaDati, $UrModificaDatiFasc, $UrModificaImmagini, $UrModificaProtocollo, $UrMovimentazioneFasc, $UrOcr, $UrPartialCancels, $UrPermalink, $UrPostaEstesa, $UrPutInPreservation, $UrRicercare, $UrRicezioneTelematica, $UrRispedire, $UrSapPublish, $UrScansione, $UrSignature, $UrSmistare, $UrSpedisciFax, $UrStampaImgControllata, $UrStampaImmagini, $UrStampaRegistro, $UrTasksCreate, $UrTasksManage, $UrTogliVisibilita, $UrUndefined, $UrUtilizzoGlifo, $UrVerificaRicevute, $UrVisibilitaSoloDoc, $UrVoceObsoleta, $UrVuoto1, $UrVuoto2)
    {
        $this->UrAggiornamentoListe = $UrAggiornamentoListe;
        $this->UrAggiungerePagine = $UrAggiungerePagine;
        $this->UrAnnullareProtocollo = $UrAnnullareProtocollo;
        $this->UrBloccoDocumento = $UrBloccoDocumento;
        $this->UrCambiaSubnet = $UrCambiaSubnet;
        $this->UrCambioClassFascicolo = $UrCambioClassFascicolo;
        $this->UrCambioStatoFasc = $UrCambioStatoFasc;
        $this->UrCancellaFascicolo = $UrCancellaFascicolo;
        $this->UrCancellaLista = $UrCancellaLista;
        $this->UrCestinareFascicolo = $UrCestinareFascicolo;
        $this->UrClassificare = $UrClassificare;
        $this->UrConfermareAnnulla = $UrConfermareAnnulla;
        $this->UrConfermareRipristino = $UrConfermareRipristino;
        $this->UrCreaArmadiCassetti = $UrCreaArmadiCassetti;
        $this->UrCreaFascicoli = $UrCreaFascicoli;
        $this->UrCreateCompliantCopies = $UrCreateCompliantCopies;
        $this->UrCreateLinkFascArch = $UrCreateLinkFascArch;
        $this->UrDisDisconnInattivita = $UrDisDisconnInattivita;
        $this->UrEliminareFascicolo = $UrEliminareFascicolo;
        $this->UrEnableSnaAnonymous = $UrEnableSnaAnonymous;
        $this->UrEnableSnaComplete = $UrEnableSnaComplete;
        $this->UrExport = $UrExport;
        $this->UrExportFascicolo = $UrExportFascicolo;
        $this->UrFascicolare = $UrFascicolare;
        $this->UrFascicolareArch = $UrFascicolareArch;
        $this->UrFirmare = $UrFirmare;
        $this->UrGestRegProt = $UrGestRegProt;
        $this->UrGestioneAnagrafica = $UrGestioneAnagrafica;
        $this->UrGestioneCartucce = $UrGestioneCartucce;
        $this->UrGestioneFascicolo = $UrGestioneFascicolo;
        $this->UrGestionePrenotazioni = $UrGestionePrenotazioni;
        $this->UrGestioneTemplTit = $UrGestioneTemplTit;
        $this->UrGestioneTipoFasc = $UrGestioneTipoFasc;
        $this->UrGestioneTitolario = $UrGestioneTitolario;
        $this->UrGestioneUtenti = $UrGestioneUtenti;
        $this->UrGestioneVoceTit = $UrGestioneVoceTit;
        $this->UrGestireModScanbatch = $UrGestireModScanbatch;
        $this->UrImportEmail = $UrImportEmail;
        $this->UrImportGenerico = $UrImportGenerico;
        $this->UrImportSpool = $UrImportSpool;
        $this->UrImpostaDocumenti = $UrImpostaDocumenti;
        $this->UrImpostaScadenza = $UrImpostaScadenza;
        $this->UrInsModRecAnagrafica = $UrInsModRecAnagrafica;
        $this->UrInserimentoVuoti = $UrInserimentoVuoti;
        $this->UrInserire = $UrInserire;
        $this->UrInserireNoteFasc = $UrInserireNoteFasc;
        $this->UrInvioMessaggi = $UrInvioMessaggi;
        $this->UrInvioOnLine = $UrInvioOnLine;
        $this->UrInvioPec = $UrInvioPec;
        $this->UrInvioTelematico = $UrInvioTelematico;
        $this->UrInvoiceAppRejMailing = $UrInvoiceAppRejMailing;
        $this->UrInvoiceChangeMonChannel = $UrInvoiceChangeMonChannel;
        $this->UrInvoiceDataTransm = $UrInvoiceDataTransm;
        $this->UrInvoiceManualMailing = $UrInvoiceManualMailing;
        $this->UrInvoiceManualReMailing = $UrInvoiceManualReMailing;
        $this->UrInvoicePlannedMailing = $UrInvoicePlannedMailing;
        $this->UrManageSharedMailboxData = $UrManageSharedMailboxData;
        $this->UrMassiveSending = $UrMassiveSending;
        $this->UrMettereInSmistamento = $UrMettereInSmistamento;
        $this->UrModificaAllegati = $UrModificaAllegati;
        $this->UrModificaAnnotazioni = $UrModificaAnnotazioni;
        $this->UrModificaArchDoc = $UrModificaArchDoc;
        $this->UrModificaDati = $UrModificaDati;
        $this->UrModificaDatiFasc = $UrModificaDatiFasc;
        $this->UrModificaImmagini = $UrModificaImmagini;
        $this->UrModificaProtocollo = $UrModificaProtocollo;
        $this->UrMovimentazioneFasc = $UrMovimentazioneFasc;
        $this->UrOcr = $UrOcr;
        $this->UrPartialCancels = $UrPartialCancels;
        $this->UrPermalink = $UrPermalink;
        $this->UrPostaEstesa = $UrPostaEstesa;
        $this->UrPutInPreservation = $UrPutInPreservation;
        $this->UrRicercare = $UrRicercare;
        $this->UrRicezioneTelematica = $UrRicezioneTelematica;
        $this->UrRispedire = $UrRispedire;
        $this->UrSapPublish = $UrSapPublish;
        $this->UrScansione = $UrScansione;
        $this->UrSignature = $UrSignature;
        $this->UrSmistare = $UrSmistare;
        $this->UrSpedisciFax = $UrSpedisciFax;
        $this->UrStampaImgControllata = $UrStampaImgControllata;
        $this->UrStampaImmagini = $UrStampaImmagini;
        $this->UrStampaRegistro = $UrStampaRegistro;
        $this->UrTasksCreate = $UrTasksCreate;
        $this->UrTasksManage = $UrTasksManage;
        $this->UrTogliVisibilita = $UrTogliVisibilita;
        $this->UrUndefined = $UrUndefined;
        $this->UrUtilizzoGlifo = $UrUtilizzoGlifo;
        $this->UrVerificaRicevute = $UrVerificaRicevute;
        $this->UrVisibilitaSoloDoc = $UrVisibilitaSoloDoc;
        $this->UrVoceObsoleta = $UrVoceObsoleta;
        $this->UrVuoto1 = $UrVuoto1;
        $this->UrVuoto2 = $UrVuoto2;
    }

    /**
     * @return bool
     */
    public function getUrAggiornamentoListe()
    {
        return $this->UrAggiornamentoListe;
    }

    /**
     * @param bool $UrAggiornamentoListe
     * @return UserRightsConfig
     */
    public function withUrAggiornamentoListe($UrAggiornamentoListe)
    {
        $new = clone $this;
        $new->UrAggiornamentoListe = $UrAggiornamentoListe;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrAggiungerePagine()
    {
        return $this->UrAggiungerePagine;
    }

    /**
     * @param bool $UrAggiungerePagine
     * @return UserRightsConfig
     */
    public function withUrAggiungerePagine($UrAggiungerePagine)
    {
        $new = clone $this;
        $new->UrAggiungerePagine = $UrAggiungerePagine;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrAnnullareProtocollo()
    {
        return $this->UrAnnullareProtocollo;
    }

    /**
     * @param bool $UrAnnullareProtocollo
     * @return UserRightsConfig
     */
    public function withUrAnnullareProtocollo($UrAnnullareProtocollo)
    {
        $new = clone $this;
        $new->UrAnnullareProtocollo = $UrAnnullareProtocollo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrBloccoDocumento()
    {
        return $this->UrBloccoDocumento;
    }

    /**
     * @param bool $UrBloccoDocumento
     * @return UserRightsConfig
     */
    public function withUrBloccoDocumento($UrBloccoDocumento)
    {
        $new = clone $this;
        $new->UrBloccoDocumento = $UrBloccoDocumento;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCambiaSubnet()
    {
        return $this->UrCambiaSubnet;
    }

    /**
     * @param bool $UrCambiaSubnet
     * @return UserRightsConfig
     */
    public function withUrCambiaSubnet($UrCambiaSubnet)
    {
        $new = clone $this;
        $new->UrCambiaSubnet = $UrCambiaSubnet;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCambioClassFascicolo()
    {
        return $this->UrCambioClassFascicolo;
    }

    /**
     * @param bool $UrCambioClassFascicolo
     * @return UserRightsConfig
     */
    public function withUrCambioClassFascicolo($UrCambioClassFascicolo)
    {
        $new = clone $this;
        $new->UrCambioClassFascicolo = $UrCambioClassFascicolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCambioStatoFasc()
    {
        return $this->UrCambioStatoFasc;
    }

    /**
     * @param bool $UrCambioStatoFasc
     * @return UserRightsConfig
     */
    public function withUrCambioStatoFasc($UrCambioStatoFasc)
    {
        $new = clone $this;
        $new->UrCambioStatoFasc = $UrCambioStatoFasc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCancellaFascicolo()
    {
        return $this->UrCancellaFascicolo;
    }

    /**
     * @param bool $UrCancellaFascicolo
     * @return UserRightsConfig
     */
    public function withUrCancellaFascicolo($UrCancellaFascicolo)
    {
        $new = clone $this;
        $new->UrCancellaFascicolo = $UrCancellaFascicolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCancellaLista()
    {
        return $this->UrCancellaLista;
    }

    /**
     * @param bool $UrCancellaLista
     * @return UserRightsConfig
     */
    public function withUrCancellaLista($UrCancellaLista)
    {
        $new = clone $this;
        $new->UrCancellaLista = $UrCancellaLista;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCestinareFascicolo()
    {
        return $this->UrCestinareFascicolo;
    }

    /**
     * @param bool $UrCestinareFascicolo
     * @return UserRightsConfig
     */
    public function withUrCestinareFascicolo($UrCestinareFascicolo)
    {
        $new = clone $this;
        $new->UrCestinareFascicolo = $UrCestinareFascicolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrClassificare()
    {
        return $this->UrClassificare;
    }

    /**
     * @param bool $UrClassificare
     * @return UserRightsConfig
     */
    public function withUrClassificare($UrClassificare)
    {
        $new = clone $this;
        $new->UrClassificare = $UrClassificare;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrConfermareAnnulla()
    {
        return $this->UrConfermareAnnulla;
    }

    /**
     * @param bool $UrConfermareAnnulla
     * @return UserRightsConfig
     */
    public function withUrConfermareAnnulla($UrConfermareAnnulla)
    {
        $new = clone $this;
        $new->UrConfermareAnnulla = $UrConfermareAnnulla;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrConfermareRipristino()
    {
        return $this->UrConfermareRipristino;
    }

    /**
     * @param bool $UrConfermareRipristino
     * @return UserRightsConfig
     */
    public function withUrConfermareRipristino($UrConfermareRipristino)
    {
        $new = clone $this;
        $new->UrConfermareRipristino = $UrConfermareRipristino;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCreaArmadiCassetti()
    {
        return $this->UrCreaArmadiCassetti;
    }

    /**
     * @param bool $UrCreaArmadiCassetti
     * @return UserRightsConfig
     */
    public function withUrCreaArmadiCassetti($UrCreaArmadiCassetti)
    {
        $new = clone $this;
        $new->UrCreaArmadiCassetti = $UrCreaArmadiCassetti;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCreaFascicoli()
    {
        return $this->UrCreaFascicoli;
    }

    /**
     * @param bool $UrCreaFascicoli
     * @return UserRightsConfig
     */
    public function withUrCreaFascicoli($UrCreaFascicoli)
    {
        $new = clone $this;
        $new->UrCreaFascicoli = $UrCreaFascicoli;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCreateCompliantCopies()
    {
        return $this->UrCreateCompliantCopies;
    }

    /**
     * @param bool $UrCreateCompliantCopies
     * @return UserRightsConfig
     */
    public function withUrCreateCompliantCopies($UrCreateCompliantCopies)
    {
        $new = clone $this;
        $new->UrCreateCompliantCopies = $UrCreateCompliantCopies;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrCreateLinkFascArch()
    {
        return $this->UrCreateLinkFascArch;
    }

    /**
     * @param bool $UrCreateLinkFascArch
     * @return UserRightsConfig
     */
    public function withUrCreateLinkFascArch($UrCreateLinkFascArch)
    {
        $new = clone $this;
        $new->UrCreateLinkFascArch = $UrCreateLinkFascArch;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrDisDisconnInattivita()
    {
        return $this->UrDisDisconnInattivita;
    }

    /**
     * @param bool $UrDisDisconnInattivita
     * @return UserRightsConfig
     */
    public function withUrDisDisconnInattivita($UrDisDisconnInattivita)
    {
        $new = clone $this;
        $new->UrDisDisconnInattivita = $UrDisDisconnInattivita;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrEliminareFascicolo()
    {
        return $this->UrEliminareFascicolo;
    }

    /**
     * @param bool $UrEliminareFascicolo
     * @return UserRightsConfig
     */
    public function withUrEliminareFascicolo($UrEliminareFascicolo)
    {
        $new = clone $this;
        $new->UrEliminareFascicolo = $UrEliminareFascicolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrEnableSnaAnonymous()
    {
        return $this->UrEnableSnaAnonymous;
    }

    /**
     * @param bool $UrEnableSnaAnonymous
     * @return UserRightsConfig
     */
    public function withUrEnableSnaAnonymous($UrEnableSnaAnonymous)
    {
        $new = clone $this;
        $new->UrEnableSnaAnonymous = $UrEnableSnaAnonymous;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrEnableSnaComplete()
    {
        return $this->UrEnableSnaComplete;
    }

    /**
     * @param bool $UrEnableSnaComplete
     * @return UserRightsConfig
     */
    public function withUrEnableSnaComplete($UrEnableSnaComplete)
    {
        $new = clone $this;
        $new->UrEnableSnaComplete = $UrEnableSnaComplete;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrExport()
    {
        return $this->UrExport;
    }

    /**
     * @param bool $UrExport
     * @return UserRightsConfig
     */
    public function withUrExport($UrExport)
    {
        $new = clone $this;
        $new->UrExport = $UrExport;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrExportFascicolo()
    {
        return $this->UrExportFascicolo;
    }

    /**
     * @param bool $UrExportFascicolo
     * @return UserRightsConfig
     */
    public function withUrExportFascicolo($UrExportFascicolo)
    {
        $new = clone $this;
        $new->UrExportFascicolo = $UrExportFascicolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrFascicolare()
    {
        return $this->UrFascicolare;
    }

    /**
     * @param bool $UrFascicolare
     * @return UserRightsConfig
     */
    public function withUrFascicolare($UrFascicolare)
    {
        $new = clone $this;
        $new->UrFascicolare = $UrFascicolare;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrFascicolareArch()
    {
        return $this->UrFascicolareArch;
    }

    /**
     * @param bool $UrFascicolareArch
     * @return UserRightsConfig
     */
    public function withUrFascicolareArch($UrFascicolareArch)
    {
        $new = clone $this;
        $new->UrFascicolareArch = $UrFascicolareArch;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrFirmare()
    {
        return $this->UrFirmare;
    }

    /**
     * @param bool $UrFirmare
     * @return UserRightsConfig
     */
    public function withUrFirmare($UrFirmare)
    {
        $new = clone $this;
        $new->UrFirmare = $UrFirmare;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestRegProt()
    {
        return $this->UrGestRegProt;
    }

    /**
     * @param bool $UrGestRegProt
     * @return UserRightsConfig
     */
    public function withUrGestRegProt($UrGestRegProt)
    {
        $new = clone $this;
        $new->UrGestRegProt = $UrGestRegProt;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestioneAnagrafica()
    {
        return $this->UrGestioneAnagrafica;
    }

    /**
     * @param bool $UrGestioneAnagrafica
     * @return UserRightsConfig
     */
    public function withUrGestioneAnagrafica($UrGestioneAnagrafica)
    {
        $new = clone $this;
        $new->UrGestioneAnagrafica = $UrGestioneAnagrafica;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestioneCartucce()
    {
        return $this->UrGestioneCartucce;
    }

    /**
     * @param bool $UrGestioneCartucce
     * @return UserRightsConfig
     */
    public function withUrGestioneCartucce($UrGestioneCartucce)
    {
        $new = clone $this;
        $new->UrGestioneCartucce = $UrGestioneCartucce;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestioneFascicolo()
    {
        return $this->UrGestioneFascicolo;
    }

    /**
     * @param bool $UrGestioneFascicolo
     * @return UserRightsConfig
     */
    public function withUrGestioneFascicolo($UrGestioneFascicolo)
    {
        $new = clone $this;
        $new->UrGestioneFascicolo = $UrGestioneFascicolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestionePrenotazioni()
    {
        return $this->UrGestionePrenotazioni;
    }

    /**
     * @param bool $UrGestionePrenotazioni
     * @return UserRightsConfig
     */
    public function withUrGestionePrenotazioni($UrGestionePrenotazioni)
    {
        $new = clone $this;
        $new->UrGestionePrenotazioni = $UrGestionePrenotazioni;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestioneTemplTit()
    {
        return $this->UrGestioneTemplTit;
    }

    /**
     * @param bool $UrGestioneTemplTit
     * @return UserRightsConfig
     */
    public function withUrGestioneTemplTit($UrGestioneTemplTit)
    {
        $new = clone $this;
        $new->UrGestioneTemplTit = $UrGestioneTemplTit;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestioneTipoFasc()
    {
        return $this->UrGestioneTipoFasc;
    }

    /**
     * @param bool $UrGestioneTipoFasc
     * @return UserRightsConfig
     */
    public function withUrGestioneTipoFasc($UrGestioneTipoFasc)
    {
        $new = clone $this;
        $new->UrGestioneTipoFasc = $UrGestioneTipoFasc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestioneTitolario()
    {
        return $this->UrGestioneTitolario;
    }

    /**
     * @param bool $UrGestioneTitolario
     * @return UserRightsConfig
     */
    public function withUrGestioneTitolario($UrGestioneTitolario)
    {
        $new = clone $this;
        $new->UrGestioneTitolario = $UrGestioneTitolario;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestioneUtenti()
    {
        return $this->UrGestioneUtenti;
    }

    /**
     * @param bool $UrGestioneUtenti
     * @return UserRightsConfig
     */
    public function withUrGestioneUtenti($UrGestioneUtenti)
    {
        $new = clone $this;
        $new->UrGestioneUtenti = $UrGestioneUtenti;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestioneVoceTit()
    {
        return $this->UrGestioneVoceTit;
    }

    /**
     * @param bool $UrGestioneVoceTit
     * @return UserRightsConfig
     */
    public function withUrGestioneVoceTit($UrGestioneVoceTit)
    {
        $new = clone $this;
        $new->UrGestioneVoceTit = $UrGestioneVoceTit;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrGestireModScanbatch()
    {
        return $this->UrGestireModScanbatch;
    }

    /**
     * @param bool $UrGestireModScanbatch
     * @return UserRightsConfig
     */
    public function withUrGestireModScanbatch($UrGestireModScanbatch)
    {
        $new = clone $this;
        $new->UrGestireModScanbatch = $UrGestireModScanbatch;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrImportEmail()
    {
        return $this->UrImportEmail;
    }

    /**
     * @param bool $UrImportEmail
     * @return UserRightsConfig
     */
    public function withUrImportEmail($UrImportEmail)
    {
        $new = clone $this;
        $new->UrImportEmail = $UrImportEmail;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrImportGenerico()
    {
        return $this->UrImportGenerico;
    }

    /**
     * @param bool $UrImportGenerico
     * @return UserRightsConfig
     */
    public function withUrImportGenerico($UrImportGenerico)
    {
        $new = clone $this;
        $new->UrImportGenerico = $UrImportGenerico;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrImportSpool()
    {
        return $this->UrImportSpool;
    }

    /**
     * @param bool $UrImportSpool
     * @return UserRightsConfig
     */
    public function withUrImportSpool($UrImportSpool)
    {
        $new = clone $this;
        $new->UrImportSpool = $UrImportSpool;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrImpostaDocumenti()
    {
        return $this->UrImpostaDocumenti;
    }

    /**
     * @param bool $UrImpostaDocumenti
     * @return UserRightsConfig
     */
    public function withUrImpostaDocumenti($UrImpostaDocumenti)
    {
        $new = clone $this;
        $new->UrImpostaDocumenti = $UrImpostaDocumenti;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrImpostaScadenza()
    {
        return $this->UrImpostaScadenza;
    }

    /**
     * @param bool $UrImpostaScadenza
     * @return UserRightsConfig
     */
    public function withUrImpostaScadenza($UrImpostaScadenza)
    {
        $new = clone $this;
        $new->UrImpostaScadenza = $UrImpostaScadenza;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInsModRecAnagrafica()
    {
        return $this->UrInsModRecAnagrafica;
    }

    /**
     * @param bool $UrInsModRecAnagrafica
     * @return UserRightsConfig
     */
    public function withUrInsModRecAnagrafica($UrInsModRecAnagrafica)
    {
        $new = clone $this;
        $new->UrInsModRecAnagrafica = $UrInsModRecAnagrafica;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInserimentoVuoti()
    {
        return $this->UrInserimentoVuoti;
    }

    /**
     * @param bool $UrInserimentoVuoti
     * @return UserRightsConfig
     */
    public function withUrInserimentoVuoti($UrInserimentoVuoti)
    {
        $new = clone $this;
        $new->UrInserimentoVuoti = $UrInserimentoVuoti;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInserire()
    {
        return $this->UrInserire;
    }

    /**
     * @param bool $UrInserire
     * @return UserRightsConfig
     */
    public function withUrInserire($UrInserire)
    {
        $new = clone $this;
        $new->UrInserire = $UrInserire;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInserireNoteFasc()
    {
        return $this->UrInserireNoteFasc;
    }

    /**
     * @param bool $UrInserireNoteFasc
     * @return UserRightsConfig
     */
    public function withUrInserireNoteFasc($UrInserireNoteFasc)
    {
        $new = clone $this;
        $new->UrInserireNoteFasc = $UrInserireNoteFasc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvioMessaggi()
    {
        return $this->UrInvioMessaggi;
    }

    /**
     * @param bool $UrInvioMessaggi
     * @return UserRightsConfig
     */
    public function withUrInvioMessaggi($UrInvioMessaggi)
    {
        $new = clone $this;
        $new->UrInvioMessaggi = $UrInvioMessaggi;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvioOnLine()
    {
        return $this->UrInvioOnLine;
    }

    /**
     * @param bool $UrInvioOnLine
     * @return UserRightsConfig
     */
    public function withUrInvioOnLine($UrInvioOnLine)
    {
        $new = clone $this;
        $new->UrInvioOnLine = $UrInvioOnLine;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvioPec()
    {
        return $this->UrInvioPec;
    }

    /**
     * @param bool $UrInvioPec
     * @return UserRightsConfig
     */
    public function withUrInvioPec($UrInvioPec)
    {
        $new = clone $this;
        $new->UrInvioPec = $UrInvioPec;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvioTelematico()
    {
        return $this->UrInvioTelematico;
    }

    /**
     * @param bool $UrInvioTelematico
     * @return UserRightsConfig
     */
    public function withUrInvioTelematico($UrInvioTelematico)
    {
        $new = clone $this;
        $new->UrInvioTelematico = $UrInvioTelematico;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvoiceAppRejMailing()
    {
        return $this->UrInvoiceAppRejMailing;
    }

    /**
     * @param bool $UrInvoiceAppRejMailing
     * @return UserRightsConfig
     */
    public function withUrInvoiceAppRejMailing($UrInvoiceAppRejMailing)
    {
        $new = clone $this;
        $new->UrInvoiceAppRejMailing = $UrInvoiceAppRejMailing;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvoiceChangeMonChannel()
    {
        return $this->UrInvoiceChangeMonChannel;
    }

    /**
     * @param bool $UrInvoiceChangeMonChannel
     * @return UserRightsConfig
     */
    public function withUrInvoiceChangeMonChannel($UrInvoiceChangeMonChannel)
    {
        $new = clone $this;
        $new->UrInvoiceChangeMonChannel = $UrInvoiceChangeMonChannel;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvoiceDataTransm()
    {
        return $this->UrInvoiceDataTransm;
    }

    /**
     * @param bool $UrInvoiceDataTransm
     * @return UserRightsConfig
     */
    public function withUrInvoiceDataTransm($UrInvoiceDataTransm)
    {
        $new = clone $this;
        $new->UrInvoiceDataTransm = $UrInvoiceDataTransm;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvoiceManualMailing()
    {
        return $this->UrInvoiceManualMailing;
    }

    /**
     * @param bool $UrInvoiceManualMailing
     * @return UserRightsConfig
     */
    public function withUrInvoiceManualMailing($UrInvoiceManualMailing)
    {
        $new = clone $this;
        $new->UrInvoiceManualMailing = $UrInvoiceManualMailing;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvoiceManualReMailing()
    {
        return $this->UrInvoiceManualReMailing;
    }

    /**
     * @param bool $UrInvoiceManualReMailing
     * @return UserRightsConfig
     */
    public function withUrInvoiceManualReMailing($UrInvoiceManualReMailing)
    {
        $new = clone $this;
        $new->UrInvoiceManualReMailing = $UrInvoiceManualReMailing;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrInvoicePlannedMailing()
    {
        return $this->UrInvoicePlannedMailing;
    }

    /**
     * @param bool $UrInvoicePlannedMailing
     * @return UserRightsConfig
     */
    public function withUrInvoicePlannedMailing($UrInvoicePlannedMailing)
    {
        $new = clone $this;
        $new->UrInvoicePlannedMailing = $UrInvoicePlannedMailing;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrManageSharedMailboxData()
    {
        return $this->UrManageSharedMailboxData;
    }

    /**
     * @param bool $UrManageSharedMailboxData
     * @return UserRightsConfig
     */
    public function withUrManageSharedMailboxData($UrManageSharedMailboxData)
    {
        $new = clone $this;
        $new->UrManageSharedMailboxData = $UrManageSharedMailboxData;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrMassiveSending()
    {
        return $this->UrMassiveSending;
    }

    /**
     * @param bool $UrMassiveSending
     * @return UserRightsConfig
     */
    public function withUrMassiveSending($UrMassiveSending)
    {
        $new = clone $this;
        $new->UrMassiveSending = $UrMassiveSending;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrMettereInSmistamento()
    {
        return $this->UrMettereInSmistamento;
    }

    /**
     * @param bool $UrMettereInSmistamento
     * @return UserRightsConfig
     */
    public function withUrMettereInSmistamento($UrMettereInSmistamento)
    {
        $new = clone $this;
        $new->UrMettereInSmistamento = $UrMettereInSmistamento;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrModificaAllegati()
    {
        return $this->UrModificaAllegati;
    }

    /**
     * @param bool $UrModificaAllegati
     * @return UserRightsConfig
     */
    public function withUrModificaAllegati($UrModificaAllegati)
    {
        $new = clone $this;
        $new->UrModificaAllegati = $UrModificaAllegati;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrModificaAnnotazioni()
    {
        return $this->UrModificaAnnotazioni;
    }

    /**
     * @param bool $UrModificaAnnotazioni
     * @return UserRightsConfig
     */
    public function withUrModificaAnnotazioni($UrModificaAnnotazioni)
    {
        $new = clone $this;
        $new->UrModificaAnnotazioni = $UrModificaAnnotazioni;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrModificaArchDoc()
    {
        return $this->UrModificaArchDoc;
    }

    /**
     * @param bool $UrModificaArchDoc
     * @return UserRightsConfig
     */
    public function withUrModificaArchDoc($UrModificaArchDoc)
    {
        $new = clone $this;
        $new->UrModificaArchDoc = $UrModificaArchDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrModificaDati()
    {
        return $this->UrModificaDati;
    }

    /**
     * @param bool $UrModificaDati
     * @return UserRightsConfig
     */
    public function withUrModificaDati($UrModificaDati)
    {
        $new = clone $this;
        $new->UrModificaDati = $UrModificaDati;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrModificaDatiFasc()
    {
        return $this->UrModificaDatiFasc;
    }

    /**
     * @param bool $UrModificaDatiFasc
     * @return UserRightsConfig
     */
    public function withUrModificaDatiFasc($UrModificaDatiFasc)
    {
        $new = clone $this;
        $new->UrModificaDatiFasc = $UrModificaDatiFasc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrModificaImmagini()
    {
        return $this->UrModificaImmagini;
    }

    /**
     * @param bool $UrModificaImmagini
     * @return UserRightsConfig
     */
    public function withUrModificaImmagini($UrModificaImmagini)
    {
        $new = clone $this;
        $new->UrModificaImmagini = $UrModificaImmagini;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrModificaProtocollo()
    {
        return $this->UrModificaProtocollo;
    }

    /**
     * @param bool $UrModificaProtocollo
     * @return UserRightsConfig
     */
    public function withUrModificaProtocollo($UrModificaProtocollo)
    {
        $new = clone $this;
        $new->UrModificaProtocollo = $UrModificaProtocollo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrMovimentazioneFasc()
    {
        return $this->UrMovimentazioneFasc;
    }

    /**
     * @param bool $UrMovimentazioneFasc
     * @return UserRightsConfig
     */
    public function withUrMovimentazioneFasc($UrMovimentazioneFasc)
    {
        $new = clone $this;
        $new->UrMovimentazioneFasc = $UrMovimentazioneFasc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrOcr()
    {
        return $this->UrOcr;
    }

    /**
     * @param bool $UrOcr
     * @return UserRightsConfig
     */
    public function withUrOcr($UrOcr)
    {
        $new = clone $this;
        $new->UrOcr = $UrOcr;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrPartialCancels()
    {
        return $this->UrPartialCancels;
    }

    /**
     * @param bool $UrPartialCancels
     * @return UserRightsConfig
     */
    public function withUrPartialCancels($UrPartialCancels)
    {
        $new = clone $this;
        $new->UrPartialCancels = $UrPartialCancels;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrPermalink()
    {
        return $this->UrPermalink;
    }

    /**
     * @param bool $UrPermalink
     * @return UserRightsConfig
     */
    public function withUrPermalink($UrPermalink)
    {
        $new = clone $this;
        $new->UrPermalink = $UrPermalink;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrPostaEstesa()
    {
        return $this->UrPostaEstesa;
    }

    /**
     * @param bool $UrPostaEstesa
     * @return UserRightsConfig
     */
    public function withUrPostaEstesa($UrPostaEstesa)
    {
        $new = clone $this;
        $new->UrPostaEstesa = $UrPostaEstesa;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrPutInPreservation()
    {
        return $this->UrPutInPreservation;
    }

    /**
     * @param bool $UrPutInPreservation
     * @return UserRightsConfig
     */
    public function withUrPutInPreservation($UrPutInPreservation)
    {
        $new = clone $this;
        $new->UrPutInPreservation = $UrPutInPreservation;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrRicercare()
    {
        return $this->UrRicercare;
    }

    /**
     * @param bool $UrRicercare
     * @return UserRightsConfig
     */
    public function withUrRicercare($UrRicercare)
    {
        $new = clone $this;
        $new->UrRicercare = $UrRicercare;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrRicezioneTelematica()
    {
        return $this->UrRicezioneTelematica;
    }

    /**
     * @param bool $UrRicezioneTelematica
     * @return UserRightsConfig
     */
    public function withUrRicezioneTelematica($UrRicezioneTelematica)
    {
        $new = clone $this;
        $new->UrRicezioneTelematica = $UrRicezioneTelematica;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrRispedire()
    {
        return $this->UrRispedire;
    }

    /**
     * @param bool $UrRispedire
     * @return UserRightsConfig
     */
    public function withUrRispedire($UrRispedire)
    {
        $new = clone $this;
        $new->UrRispedire = $UrRispedire;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrSapPublish()
    {
        return $this->UrSapPublish;
    }

    /**
     * @param bool $UrSapPublish
     * @return UserRightsConfig
     */
    public function withUrSapPublish($UrSapPublish)
    {
        $new = clone $this;
        $new->UrSapPublish = $UrSapPublish;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrScansione()
    {
        return $this->UrScansione;
    }

    /**
     * @param bool $UrScansione
     * @return UserRightsConfig
     */
    public function withUrScansione($UrScansione)
    {
        $new = clone $this;
        $new->UrScansione = $UrScansione;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrSignature()
    {
        return $this->UrSignature;
    }

    /**
     * @param bool $UrSignature
     * @return UserRightsConfig
     */
    public function withUrSignature($UrSignature)
    {
        $new = clone $this;
        $new->UrSignature = $UrSignature;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrSmistare()
    {
        return $this->UrSmistare;
    }

    /**
     * @param bool $UrSmistare
     * @return UserRightsConfig
     */
    public function withUrSmistare($UrSmistare)
    {
        $new = clone $this;
        $new->UrSmistare = $UrSmistare;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrSpedisciFax()
    {
        return $this->UrSpedisciFax;
    }

    /**
     * @param bool $UrSpedisciFax
     * @return UserRightsConfig
     */
    public function withUrSpedisciFax($UrSpedisciFax)
    {
        $new = clone $this;
        $new->UrSpedisciFax = $UrSpedisciFax;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrStampaImgControllata()
    {
        return $this->UrStampaImgControllata;
    }

    /**
     * @param bool $UrStampaImgControllata
     * @return UserRightsConfig
     */
    public function withUrStampaImgControllata($UrStampaImgControllata)
    {
        $new = clone $this;
        $new->UrStampaImgControllata = $UrStampaImgControllata;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrStampaImmagini()
    {
        return $this->UrStampaImmagini;
    }

    /**
     * @param bool $UrStampaImmagini
     * @return UserRightsConfig
     */
    public function withUrStampaImmagini($UrStampaImmagini)
    {
        $new = clone $this;
        $new->UrStampaImmagini = $UrStampaImmagini;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrStampaRegistro()
    {
        return $this->UrStampaRegistro;
    }

    /**
     * @param bool $UrStampaRegistro
     * @return UserRightsConfig
     */
    public function withUrStampaRegistro($UrStampaRegistro)
    {
        $new = clone $this;
        $new->UrStampaRegistro = $UrStampaRegistro;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrTasksCreate()
    {
        return $this->UrTasksCreate;
    }

    /**
     * @param bool $UrTasksCreate
     * @return UserRightsConfig
     */
    public function withUrTasksCreate($UrTasksCreate)
    {
        $new = clone $this;
        $new->UrTasksCreate = $UrTasksCreate;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrTasksManage()
    {
        return $this->UrTasksManage;
    }

    /**
     * @param bool $UrTasksManage
     * @return UserRightsConfig
     */
    public function withUrTasksManage($UrTasksManage)
    {
        $new = clone $this;
        $new->UrTasksManage = $UrTasksManage;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrTogliVisibilita()
    {
        return $this->UrTogliVisibilita;
    }

    /**
     * @param bool $UrTogliVisibilita
     * @return UserRightsConfig
     */
    public function withUrTogliVisibilita($UrTogliVisibilita)
    {
        $new = clone $this;
        $new->UrTogliVisibilita = $UrTogliVisibilita;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrUndefined()
    {
        return $this->UrUndefined;
    }

    /**
     * @param bool $UrUndefined
     * @return UserRightsConfig
     */
    public function withUrUndefined($UrUndefined)
    {
        $new = clone $this;
        $new->UrUndefined = $UrUndefined;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrUtilizzoGlifo()
    {
        return $this->UrUtilizzoGlifo;
    }

    /**
     * @param bool $UrUtilizzoGlifo
     * @return UserRightsConfig
     */
    public function withUrUtilizzoGlifo($UrUtilizzoGlifo)
    {
        $new = clone $this;
        $new->UrUtilizzoGlifo = $UrUtilizzoGlifo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrVerificaRicevute()
    {
        return $this->UrVerificaRicevute;
    }

    /**
     * @param bool $UrVerificaRicevute
     * @return UserRightsConfig
     */
    public function withUrVerificaRicevute($UrVerificaRicevute)
    {
        $new = clone $this;
        $new->UrVerificaRicevute = $UrVerificaRicevute;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrVisibilitaSoloDoc()
    {
        return $this->UrVisibilitaSoloDoc;
    }

    /**
     * @param bool $UrVisibilitaSoloDoc
     * @return UserRightsConfig
     */
    public function withUrVisibilitaSoloDoc($UrVisibilitaSoloDoc)
    {
        $new = clone $this;
        $new->UrVisibilitaSoloDoc = $UrVisibilitaSoloDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrVoceObsoleta()
    {
        return $this->UrVoceObsoleta;
    }

    /**
     * @param bool $UrVoceObsoleta
     * @return UserRightsConfig
     */
    public function withUrVoceObsoleta($UrVoceObsoleta)
    {
        $new = clone $this;
        $new->UrVoceObsoleta = $UrVoceObsoleta;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrVuoto1()
    {
        return $this->UrVuoto1;
    }

    /**
     * @param bool $UrVuoto1
     * @return UserRightsConfig
     */
    public function withUrVuoto1($UrVuoto1)
    {
        $new = clone $this;
        $new->UrVuoto1 = $UrVuoto1;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUrVuoto2()
    {
        return $this->UrVuoto2;
    }

    /**
     * @param bool $UrVuoto2
     * @return UserRightsConfig
     */
    public function withUrVuoto2($UrVuoto2)
    {
        $new = clone $this;
        $new->UrVuoto2 = $UrVuoto2;

        return $new;
    }


}

