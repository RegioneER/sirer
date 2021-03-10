<?php

namespace IrideWFFascicolo\Type;

class FascicoloIn
{

    /**
     * @var string
     */
    private $Anno = null;

    /**
     * @var string
     */
    private $Numero = null;

    /**
     * @var string
     */
    private $Data = null;

    /**
     * @var string
     */
    private $Oggetto = null;

    /**
     * @var string
     */
    private $Classifica = null;

    /**
     * @var string
     */
    private $AltriDati = null;

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
    private $Eterogeneo = null;

    /**
     * @var string
     */
    private $DataChiusura = null;

    /**
     * @var string
     */
    private $DatiAggiuntivi = null;

    /**
     * @var string
     */
    private $Applicazione = null;

    /**
     * @var string
     */
    private $Aggiornamento = null;

    /**
     * @var string
     */
    private $AnagraficaCf = null;

    /**
     * @var string
     */
    private $AnagraficaPiva = null;

    /**
     * @return string
     */
    public function getAnno()
    {
        return $this->Anno;
    }

    /**
     * @param string $Anno
     * @return FascicoloIn
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
     * @return FascicoloIn
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
    public function getData()
    {
        return $this->Data;
    }

    /**
     * @param string $Data
     * @return FascicoloIn
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
    public function getOggetto()
    {
        return $this->Oggetto;
    }

    /**
     * @param string $Oggetto
     * @return FascicoloIn
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
    public function getClassifica()
    {
        return $this->Classifica;
    }

    /**
     * @param string $Classifica
     * @return FascicoloIn
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
    public function getAltriDati()
    {
        return $this->AltriDati;
    }

    /**
     * @param string $AltriDati
     * @return FascicoloIn
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
    public function getUtente()
    {
        return $this->Utente;
    }

    /**
     * @param string $Utente
     * @return FascicoloIn
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
     * @return FascicoloIn
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
    public function getEterogeneo()
    {
        return $this->Eterogeneo;
    }

    /**
     * @param string $Eterogeneo
     * @return FascicoloIn
     */
    public function withEterogeneo($Eterogeneo)
    {
        $new = clone $this;
        $new->Eterogeneo = $Eterogeneo;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataChiusura()
    {
        return $this->DataChiusura;
    }

    /**
     * @param string $DataChiusura
     * @return FascicoloIn
     */
    public function withDataChiusura($DataChiusura)
    {
        $new = clone $this;
        $new->DataChiusura = $DataChiusura;

        return $new;
    }

    /**
     * @return string
     */
    public function getDatiAggiuntivi()
    {
        return $this->DatiAggiuntivi;
    }

    /**
     * @param string $DatiAggiuntivi
     * @return FascicoloIn
     */
    public function withDatiAggiuntivi($DatiAggiuntivi)
    {
        $new = clone $this;
        $new->DatiAggiuntivi = $DatiAggiuntivi;

        return $new;
    }

    /**
     * @return string
     */
    public function getApplicazione()
    {
        return $this->Applicazione;
    }

    /**
     * @param string $Applicazione
     * @return FascicoloIn
     */
    public function withApplicazione($Applicazione)
    {
        $new = clone $this;
        $new->Applicazione = $Applicazione;

        return $new;
    }

    /**
     * @return string
     */
    public function getAggiornamento()
    {
        return $this->Aggiornamento;
    }

    /**
     * @param string $Aggiornamento
     * @return FascicoloIn
     */
    public function withAggiornamento($Aggiornamento)
    {
        $new = clone $this;
        $new->Aggiornamento = $Aggiornamento;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnagraficaCf()
    {
        return $this->AnagraficaCf;
    }

    /**
     * @param string $AnagraficaCf
     * @return FascicoloIn
     */
    public function withAnagraficaCf($AnagraficaCf)
    {
        $new = clone $this;
        $new->AnagraficaCf = $AnagraficaCf;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnagraficaPiva()
    {
        return $this->AnagraficaPiva;
    }

    /**
     * @param string $AnagraficaPiva
     * @return FascicoloIn
     */
    public function withAnagraficaPiva($AnagraficaPiva)
    {
        $new = clone $this;
        $new->AnagraficaPiva = $AnagraficaPiva;

        return $new;
    }


}

