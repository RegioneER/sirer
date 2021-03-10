<?php

namespace IrideWFFascicolo\Type;

class FascicoloOut
{

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var int
     */
    private $Anno = null;

    /**
     * @var string
     */
    private $Numero = null;

    /**
     * @var string
     */
    private $NumeroSenzaClassifica = null;

    /**
     * @var string
     */
    private $Oggetto = null;

    /**
     * @var \DateTime
     */
    private $Data = null;

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
    private $AltriDati = null;

    /**
     * @var string
     */
    private $Archiviata = null;

    /**
     * @var int
     */
    private $AnnoArchiviazione = null;

    /**
     * @var int
     */
    private $NumeroArchiviazione = null;

    /**
     * @var string
     */
    private $UtenteDiInserimento = null;

    /**
     * @var string
     */
    private $RuoloDiInserimento = null;

    /**
     * @var \DateTime
     */
    private $DataDiInserimento = null;

    /**
     * @var \DateTime
     */
    private $DataDiChiusura = null;

    /**
     * @var bool
     */
    private $PraticaChiusa = null;

    /**
     * @var \DateTime
     */
    private $DataDiScarto = null;

    /**
     * @var int
     */
    private $PraticaRiservata = null;

    /**
     * @var \IrideWFFascicolo\Type\ArrayOfDocumentoFascicoloOut
     */
    private $DocumentiFascicolo = null;

    /**
     * @var string
     */
    private $FormatoData = null;

    /**
     * @var string
     */
    private $LivelloDiSicurezza = null;

    /**
     * @var bool
     */
    private $PraticaScartabile = null;

    /**
     * @var int
     */
    private $NumeroDocumentiPratica = null;

    /**
     * @var int
     */
    private $IterAttivo = null;

    /**
     * @var string
     */
    private $ACL = null;

    /**
     * @var string
     */
    private $ErrDescription = null;

    /**
     * @var \DateTime
     */
    private $DataDiAnnullo = null;

    /**
     * @var bool
     */
    private $PraticaAnnullata = null;

    /**
     * @var string
     */
    private $AnnullamentoNote = null;

    /**
     * @var string
     */
    private $AnnullamentoUtente = null;

    /**
     * @var string
     */
    private $Padre = null;

    /**
     * @var string
     */
    private $Key = null;

    /**
     * @var string
     */
    private $SottoFascicolo = null;

    /**
     * @var bool
     */
    private $IsSottofascicolo = null;

    /**
     * @var bool
     */
    private $HasSottofascicolo = null;

    /**
     * @var bool
     */
    private $HasDocumenti = null;

    /**
     * @var bool
     */
    private $HasDocumentiConIter = null;

    /**
     * @var string
     */
    private $Messaggio = null;

    /**
     * @var string
     */
    private $Errore = null;

    /**
     * @var bool
     */
    private $Eterogeneo = null;

    /**
     * @return int
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param int $Id
     * @return FascicoloOut
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }

    /**
     * @return int
     */
    public function getAnno()
    {
        return $this->Anno;
    }

    /**
     * @param int $Anno
     * @return FascicoloOut
     */
    public function withAnno($Anno)
    {
        $new = clone $this;
        $new->Anno = $Anno;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumero()
    {
        return $this->Numero;
    }

    /**
     * @param string $Numero
     * @return FascicoloOut
     */
    public function withNumero($Numero)
    {
        $new = clone $this;
        $new->Numero = $Numero;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroSenzaClassifica()
    {
        return $this->NumeroSenzaClassifica;
    }

    /**
     * @param string $NumeroSenzaClassifica
     * @return FascicoloOut
     */
    public function withNumeroSenzaClassifica($NumeroSenzaClassifica)
    {
        $new = clone $this;
        $new->NumeroSenzaClassifica = $NumeroSenzaClassifica;

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
     * @return FascicoloOut
     */
    public function withOggetto($Oggetto)
    {
        $new = clone $this;
        $new->Oggetto = $Oggetto;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getData()
    {
        return $this->Data;
    }

    /**
     * @param \DateTime $Data
     * @return FascicoloOut
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
     * @return FascicoloOut
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
     * @return FascicoloOut
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
    public function getAltriDati()
    {
        return $this->AltriDati;
    }

    /**
     * @param string $AltriDati
     * @return FascicoloOut
     */
    public function withAltriDati($AltriDati)
    {
        $new = clone $this;
        $new->AltriDati = $AltriDati;

        return $new;
    }

    /**
     * @return string
     */
    public function getArchiviata()
    {
        return $this->Archiviata;
    }

    /**
     * @param string $Archiviata
     * @return FascicoloOut
     */
    public function withArchiviata($Archiviata)
    {
        $new = clone $this;
        $new->Archiviata = $Archiviata;

        return $new;
    }

    /**
     * @return int
     */
    public function getAnnoArchiviazione()
    {
        return $this->AnnoArchiviazione;
    }

    /**
     * @param int $AnnoArchiviazione
     * @return FascicoloOut
     */
    public function withAnnoArchiviazione($AnnoArchiviazione)
    {
        $new = clone $this;
        $new->AnnoArchiviazione = $AnnoArchiviazione;

        return $new;
    }

    /**
     * @return int
     */
    public function getNumeroArchiviazione()
    {
        return $this->NumeroArchiviazione;
    }

    /**
     * @param int $NumeroArchiviazione
     * @return FascicoloOut
     */
    public function withNumeroArchiviazione($NumeroArchiviazione)
    {
        $new = clone $this;
        $new->NumeroArchiviazione = $NumeroArchiviazione;

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
     * @return FascicoloOut
     */
    public function withUtenteDiInserimento($UtenteDiInserimento)
    {
        $new = clone $this;
        $new->UtenteDiInserimento = $UtenteDiInserimento;

        return $new;
    }

    /**
     * @return string
     */
    public function getRuoloDiInserimento()
    {
        return $this->RuoloDiInserimento;
    }

    /**
     * @param string $RuoloDiInserimento
     * @return FascicoloOut
     */
    public function withRuoloDiInserimento($RuoloDiInserimento)
    {
        $new = clone $this;
        $new->RuoloDiInserimento = $RuoloDiInserimento;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataDiInserimento()
    {
        return $this->DataDiInserimento;
    }

    /**
     * @param \DateTime $DataDiInserimento
     * @return FascicoloOut
     */
    public function withDataDiInserimento($DataDiInserimento)
    {
        $new = clone $this;
        $new->DataDiInserimento = $DataDiInserimento;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataDiChiusura()
    {
        return $this->DataDiChiusura;
    }

    /**
     * @param \DateTime $DataDiChiusura
     * @return FascicoloOut
     */
    public function withDataDiChiusura($DataDiChiusura)
    {
        $new = clone $this;
        $new->DataDiChiusura = $DataDiChiusura;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPraticaChiusa()
    {
        return $this->PraticaChiusa;
    }

    /**
     * @param bool $PraticaChiusa
     * @return FascicoloOut
     */
    public function withPraticaChiusa($PraticaChiusa)
    {
        $new = clone $this;
        $new->PraticaChiusa = $PraticaChiusa;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataDiScarto()
    {
        return $this->DataDiScarto;
    }

    /**
     * @param \DateTime $DataDiScarto
     * @return FascicoloOut
     */
    public function withDataDiScarto($DataDiScarto)
    {
        $new = clone $this;
        $new->DataDiScarto = $DataDiScarto;

        return $new;
    }

    /**
     * @return int
     */
    public function getPraticaRiservata()
    {
        return $this->PraticaRiservata;
    }

    /**
     * @param int $PraticaRiservata
     * @return FascicoloOut
     */
    public function withPraticaRiservata($PraticaRiservata)
    {
        $new = clone $this;
        $new->PraticaRiservata = $PraticaRiservata;

        return $new;
    }

    /**
     * @return \IrideWFFascicolo\Type\ArrayOfDocumentoFascicoloOut
     */
    public function getDocumentiFascicolo()
    {
        return $this->DocumentiFascicolo;
    }

    /**
     * @param \IrideWFFascicolo\Type\ArrayOfDocumentoFascicoloOut $DocumentiFascicolo
     * @return FascicoloOut
     */
    public function withDocumentiFascicolo($DocumentiFascicolo)
    {
        $new = clone $this;
        $new->DocumentiFascicolo = $DocumentiFascicolo;

        return $new;
    }

    /**
     * @return string
     */
    public function getFormatoData()
    {
        return $this->FormatoData;
    }

    /**
     * @param string $FormatoData
     * @return FascicoloOut
     */
    public function withFormatoData($FormatoData)
    {
        $new = clone $this;
        $new->FormatoData = $FormatoData;

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
     * @return FascicoloOut
     */
    public function withLivelloDiSicurezza($LivelloDiSicurezza)
    {
        $new = clone $this;
        $new->LivelloDiSicurezza = $LivelloDiSicurezza;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPraticaScartabile()
    {
        return $this->PraticaScartabile;
    }

    /**
     * @param bool $PraticaScartabile
     * @return FascicoloOut
     */
    public function withPraticaScartabile($PraticaScartabile)
    {
        $new = clone $this;
        $new->PraticaScartabile = $PraticaScartabile;

        return $new;
    }

    /**
     * @return int
     */
    public function getNumeroDocumentiPratica()
    {
        return $this->NumeroDocumentiPratica;
    }

    /**
     * @param int $NumeroDocumentiPratica
     * @return FascicoloOut
     */
    public function withNumeroDocumentiPratica($NumeroDocumentiPratica)
    {
        $new = clone $this;
        $new->NumeroDocumentiPratica = $NumeroDocumentiPratica;

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
     * @return FascicoloOut
     */
    public function withIterAttivo($IterAttivo)
    {
        $new = clone $this;
        $new->IterAttivo = $IterAttivo;

        return $new;
    }

    /**
     * @return string
     */
    public function getACL()
    {
        return $this->ACL;
    }

    /**
     * @param string $ACL
     * @return FascicoloOut
     */
    public function withACL($ACL)
    {
        $new = clone $this;
        $new->ACL = $ACL;

        return $new;
    }

    /**
     * @return string
     */
    public function getErrDescription()
    {
        return $this->ErrDescription;
    }

    /**
     * @param string $ErrDescription
     * @return FascicoloOut
     */
    public function withErrDescription($ErrDescription)
    {
        $new = clone $this;
        $new->ErrDescription = $ErrDescription;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataDiAnnullo()
    {
        return $this->DataDiAnnullo;
    }

    /**
     * @param \DateTime $DataDiAnnullo
     * @return FascicoloOut
     */
    public function withDataDiAnnullo($DataDiAnnullo)
    {
        $new = clone $this;
        $new->DataDiAnnullo = $DataDiAnnullo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getPraticaAnnullata()
    {
        return $this->PraticaAnnullata;
    }

    /**
     * @param bool $PraticaAnnullata
     * @return FascicoloOut
     */
    public function withPraticaAnnullata($PraticaAnnullata)
    {
        $new = clone $this;
        $new->PraticaAnnullata = $PraticaAnnullata;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnnullamentoNote()
    {
        return $this->AnnullamentoNote;
    }

    /**
     * @param string $AnnullamentoNote
     * @return FascicoloOut
     */
    public function withAnnullamentoNote($AnnullamentoNote)
    {
        $new = clone $this;
        $new->AnnullamentoNote = $AnnullamentoNote;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnnullamentoUtente()
    {
        return $this->AnnullamentoUtente;
    }

    /**
     * @param string $AnnullamentoUtente
     * @return FascicoloOut
     */
    public function withAnnullamentoUtente($AnnullamentoUtente)
    {
        $new = clone $this;
        $new->AnnullamentoUtente = $AnnullamentoUtente;

        return $new;
    }

    /**
     * @return string
     */
    public function getPadre()
    {
        return $this->Padre;
    }

    /**
     * @param string $Padre
     * @return FascicoloOut
     */
    public function withPadre($Padre)
    {
        $new = clone $this;
        $new->Padre = $Padre;

        return $new;
    }

    /**
     * @return string
     */
    public function getKey()
    {
        return $this->Key;
    }

    /**
     * @param string $Key
     * @return FascicoloOut
     */
    public function withKey($Key)
    {
        $new = clone $this;
        $new->Key = $Key;

        return $new;
    }

    /**
     * @return string
     */
    public function getSottoFascicolo()
    {
        return $this->SottoFascicolo;
    }

    /**
     * @param string $SottoFascicolo
     * @return FascicoloOut
     */
    public function withSottoFascicolo($SottoFascicolo)
    {
        $new = clone $this;
        $new->SottoFascicolo = $SottoFascicolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsSottofascicolo()
    {
        return $this->IsSottofascicolo;
    }

    /**
     * @param bool $IsSottofascicolo
     * @return FascicoloOut
     */
    public function withIsSottofascicolo($IsSottofascicolo)
    {
        $new = clone $this;
        $new->IsSottofascicolo = $IsSottofascicolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasSottofascicolo()
    {
        return $this->HasSottofascicolo;
    }

    /**
     * @param bool $HasSottofascicolo
     * @return FascicoloOut
     */
    public function withHasSottofascicolo($HasSottofascicolo)
    {
        $new = clone $this;
        $new->HasSottofascicolo = $HasSottofascicolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasDocumenti()
    {
        return $this->HasDocumenti;
    }

    /**
     * @param bool $HasDocumenti
     * @return FascicoloOut
     */
    public function withHasDocumenti($HasDocumenti)
    {
        $new = clone $this;
        $new->HasDocumenti = $HasDocumenti;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasDocumentiConIter()
    {
        return $this->HasDocumentiConIter;
    }

    /**
     * @param bool $HasDocumentiConIter
     * @return FascicoloOut
     */
    public function withHasDocumentiConIter($HasDocumentiConIter)
    {
        $new = clone $this;
        $new->HasDocumentiConIter = $HasDocumentiConIter;

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
     * @return FascicoloOut
     */
    public function withMessaggio($Messaggio)
    {
        $new = clone $this;
        $new->Messaggio = $Messaggio;

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
     * @return FascicoloOut
     */
    public function withErrore($Errore)
    {
        $new = clone $this;
        $new->Errore = $Errore;

        return $new;
    }

    /**
     * @return bool
     */
    public function getEterogeneo()
    {
        return $this->Eterogeneo;
    }

    /**
     * @param bool $Eterogeneo
     * @return FascicoloOut
     */
    public function withEterogeneo($Eterogeneo)
    {
        $new = clone $this;
        $new->Eterogeneo = $Eterogeneo;

        return $new;
    }


}

