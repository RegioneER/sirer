<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class NuoviAllegati implements RequestInterface
{

    /**
     * @var string
     */
    private $idDoc = null;

    /**
     * @var string
     */
    private $annoProt = null;

    /**
     * @var string
     */
    private $numProt = null;

    /**
     * @var string
     */
    private $utente = null;

    /**
     * @var string
     */
    private $ruolo = null;

    /**
     * @var \IrideWS\Type\ArrayOfAllegatoIn
     */
    private $Allegati = null;

    /**
     * Constructor
     *
     * @var string $idDoc
     * @var string $annoProt
     * @var string $numProt
     * @var string $utente
     * @var string $ruolo
     * @var \IrideWS\Type\ArrayOfAllegatoIn $Allegati
     */
    public function __construct($idDoc, $annoProt, $numProt, $utente, $ruolo, $Allegati)
    {
        $this->idDoc = $idDoc;
        $this->annoProt = $annoProt;
        $this->numProt = $numProt;
        $this->utente = $utente;
        $this->ruolo = $ruolo;
        $this->Allegati = $Allegati;
    }

    /**
     * @return string
     */
    public function getIdDoc()
    {
        return $this->idDoc;
    }

    /**
     * @param string $idDoc
     * @return NuoviAllegati
     */
    public function withIdDoc($idDoc)
    {
        $new = clone $this;
        $new->idDoc = $idDoc;

        return $new;
    }

    /**
     * @return string
     */
    public function getAnnoProt()
    {
        return $this->annoProt;
    }

    /**
     * @param string $annoProt
     * @return NuoviAllegati
     */
    public function withAnnoProt($annoProt)
    {
        $new = clone $this;
        $new->annoProt = $annoProt;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumProt()
    {
        return $this->numProt;
    }

    /**
     * @param string $numProt
     * @return NuoviAllegati
     */
    public function withNumProt($numProt)
    {
        $new = clone $this;
        $new->numProt = $numProt;

        return $new;
    }

    /**
     * @return string
     */
    public function getUtente()
    {
        return $this->utente;
    }

    /**
     * @param string $utente
     * @return NuoviAllegati
     */
    public function withUtente($utente)
    {
        $new = clone $this;
        $new->utente = $utente;

        return $new;
    }

    /**
     * @return string
     */
    public function getRuolo()
    {
        return $this->ruolo;
    }

    /**
     * @param string $ruolo
     * @return NuoviAllegati
     */
    public function withRuolo($ruolo)
    {
        $new = clone $this;
        $new->ruolo = $ruolo;

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
     * @return NuoviAllegati
     */
    public function withAllegati($Allegati)
    {
        $new = clone $this;
        $new->Allegati = $Allegati;

        return $new;
    }


}

