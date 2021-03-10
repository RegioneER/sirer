<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DocumentumIn implements RequestInterface
{

    /**
     * @var string
     */
    private $ObjecID = null;

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
    private $Origine = null;

    /**
     * @var string
     */
    private $MittenteInterno = null;

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
     * @var string $ObjecID
     * @var string $TipoDocumento
     * @var string $Oggetto
     * @var string $Origine
     * @var string $MittenteInterno
     * @var string $Utente
     * @var string $Ruolo
     */
    public function __construct($ObjecID, $TipoDocumento, $Oggetto, $Origine, $MittenteInterno, $Utente, $Ruolo)
    {
        $this->ObjecID = $ObjecID;
        $this->TipoDocumento = $TipoDocumento;
        $this->Oggetto = $Oggetto;
        $this->Origine = $Origine;
        $this->MittenteInterno = $MittenteInterno;
        $this->Utente = $Utente;
        $this->Ruolo = $Ruolo;
    }

    /**
     * @return string
     */
    public function getObjecID()
    {
        return $this->ObjecID;
    }

    /**
     * @param string $ObjecID
     * @return DocumentumIn
     */
    public function withObjecID($ObjecID)
    {
        $new = clone $this;
        $new->ObjecID = $ObjecID;

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
     * @return DocumentumIn
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
     * @return DocumentumIn
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
    public function getOrigine()
    {
        return $this->Origine;
    }

    /**
     * @param string $Origine
     * @return DocumentumIn
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
     * @return DocumentumIn
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
    public function getUtente()
    {
        return $this->Utente;
    }

    /**
     * @param string $Utente
     * @return DocumentumIn
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
     * @return DocumentumIn
     */
    public function withRuolo($Ruolo)
    {
        $new = clone $this;
        $new->Ruolo = $Ruolo;

        return $new;
    }


}

