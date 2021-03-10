<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CardRightsConfig implements RequestInterface
{

    /**
     * @var bool
     */
    private $RwAggiungerePagine = null;

    /**
     * @var bool
     */
    private $RwAnnullareProtocollo = null;

    /**
     * @var bool
     */
    private $RwCancellaLista = null;

    /**
     * @var bool
     */
    private $RwClassificare = null;

    /**
     * @var bool
     */
    private $RwFascicolare = null;

    /**
     * @var bool
     */
    private $RwFascicolareArch = null;

    /**
     * @var bool
     */
    private $RwModificaAllegati = null;

    /**
     * @var bool
     */
    private $RwModificaAnnotazioni = null;

    /**
     * @var bool
     */
    private $RwModificaDati = null;

    /**
     * @var bool
     */
    private $RwModificaImmagini = null;

    /**
     * @var bool
     */
    private $RwModificaProtocollo = null;

    /**
     * @var bool
     */
    private $RwRispedire = null;

    /**
     * @var bool
     */
    private $RwTogliVisibilita = null;

    /**
     * Constructor
     *
     * @var bool $RwAggiungerePagine
     * @var bool $RwAnnullareProtocollo
     * @var bool $RwCancellaLista
     * @var bool $RwClassificare
     * @var bool $RwFascicolare
     * @var bool $RwFascicolareArch
     * @var bool $RwModificaAllegati
     * @var bool $RwModificaAnnotazioni
     * @var bool $RwModificaDati
     * @var bool $RwModificaImmagini
     * @var bool $RwModificaProtocollo
     * @var bool $RwRispedire
     * @var bool $RwTogliVisibilita
     */
    public function __construct($RwAggiungerePagine, $RwAnnullareProtocollo, $RwCancellaLista, $RwClassificare, $RwFascicolare, $RwFascicolareArch, $RwModificaAllegati, $RwModificaAnnotazioni, $RwModificaDati, $RwModificaImmagini, $RwModificaProtocollo, $RwRispedire, $RwTogliVisibilita)
    {
        $this->RwAggiungerePagine = $RwAggiungerePagine;
        $this->RwAnnullareProtocollo = $RwAnnullareProtocollo;
        $this->RwCancellaLista = $RwCancellaLista;
        $this->RwClassificare = $RwClassificare;
        $this->RwFascicolare = $RwFascicolare;
        $this->RwFascicolareArch = $RwFascicolareArch;
        $this->RwModificaAllegati = $RwModificaAllegati;
        $this->RwModificaAnnotazioni = $RwModificaAnnotazioni;
        $this->RwModificaDati = $RwModificaDati;
        $this->RwModificaImmagini = $RwModificaImmagini;
        $this->RwModificaProtocollo = $RwModificaProtocollo;
        $this->RwRispedire = $RwRispedire;
        $this->RwTogliVisibilita = $RwTogliVisibilita;
    }

    /**
     * @return bool
     */
    public function getRwAggiungerePagine()
    {
        return $this->RwAggiungerePagine;
    }

    /**
     * @param bool $RwAggiungerePagine
     * @return CardRightsConfig
     */
    public function withRwAggiungerePagine($RwAggiungerePagine)
    {
        $new = clone $this;
        $new->RwAggiungerePagine = $RwAggiungerePagine;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwAnnullareProtocollo()
    {
        return $this->RwAnnullareProtocollo;
    }

    /**
     * @param bool $RwAnnullareProtocollo
     * @return CardRightsConfig
     */
    public function withRwAnnullareProtocollo($RwAnnullareProtocollo)
    {
        $new = clone $this;
        $new->RwAnnullareProtocollo = $RwAnnullareProtocollo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwCancellaLista()
    {
        return $this->RwCancellaLista;
    }

    /**
     * @param bool $RwCancellaLista
     * @return CardRightsConfig
     */
    public function withRwCancellaLista($RwCancellaLista)
    {
        $new = clone $this;
        $new->RwCancellaLista = $RwCancellaLista;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwClassificare()
    {
        return $this->RwClassificare;
    }

    /**
     * @param bool $RwClassificare
     * @return CardRightsConfig
     */
    public function withRwClassificare($RwClassificare)
    {
        $new = clone $this;
        $new->RwClassificare = $RwClassificare;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwFascicolare()
    {
        return $this->RwFascicolare;
    }

    /**
     * @param bool $RwFascicolare
     * @return CardRightsConfig
     */
    public function withRwFascicolare($RwFascicolare)
    {
        $new = clone $this;
        $new->RwFascicolare = $RwFascicolare;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwFascicolareArch()
    {
        return $this->RwFascicolareArch;
    }

    /**
     * @param bool $RwFascicolareArch
     * @return CardRightsConfig
     */
    public function withRwFascicolareArch($RwFascicolareArch)
    {
        $new = clone $this;
        $new->RwFascicolareArch = $RwFascicolareArch;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwModificaAllegati()
    {
        return $this->RwModificaAllegati;
    }

    /**
     * @param bool $RwModificaAllegati
     * @return CardRightsConfig
     */
    public function withRwModificaAllegati($RwModificaAllegati)
    {
        $new = clone $this;
        $new->RwModificaAllegati = $RwModificaAllegati;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwModificaAnnotazioni()
    {
        return $this->RwModificaAnnotazioni;
    }

    /**
     * @param bool $RwModificaAnnotazioni
     * @return CardRightsConfig
     */
    public function withRwModificaAnnotazioni($RwModificaAnnotazioni)
    {
        $new = clone $this;
        $new->RwModificaAnnotazioni = $RwModificaAnnotazioni;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwModificaDati()
    {
        return $this->RwModificaDati;
    }

    /**
     * @param bool $RwModificaDati
     * @return CardRightsConfig
     */
    public function withRwModificaDati($RwModificaDati)
    {
        $new = clone $this;
        $new->RwModificaDati = $RwModificaDati;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwModificaImmagini()
    {
        return $this->RwModificaImmagini;
    }

    /**
     * @param bool $RwModificaImmagini
     * @return CardRightsConfig
     */
    public function withRwModificaImmagini($RwModificaImmagini)
    {
        $new = clone $this;
        $new->RwModificaImmagini = $RwModificaImmagini;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwModificaProtocollo()
    {
        return $this->RwModificaProtocollo;
    }

    /**
     * @param bool $RwModificaProtocollo
     * @return CardRightsConfig
     */
    public function withRwModificaProtocollo($RwModificaProtocollo)
    {
        $new = clone $this;
        $new->RwModificaProtocollo = $RwModificaProtocollo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwRispedire()
    {
        return $this->RwRispedire;
    }

    /**
     * @param bool $RwRispedire
     * @return CardRightsConfig
     */
    public function withRwRispedire($RwRispedire)
    {
        $new = clone $this;
        $new->RwRispedire = $RwRispedire;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRwTogliVisibilita()
    {
        return $this->RwTogliVisibilita;
    }

    /**
     * @param bool $RwTogliVisibilita
     * @return CardRightsConfig
     */
    public function withRwTogliVisibilita($RwTogliVisibilita)
    {
        $new = clone $this;
        $new->RwTogliVisibilita = $RwTogliVisibilita;

        return $new;
    }


}

