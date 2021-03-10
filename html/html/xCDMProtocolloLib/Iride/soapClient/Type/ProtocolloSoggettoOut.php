<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ProtocolloSoggettoOut implements RequestInterface
{

    /**
     * @var int
     */
    private $IdDocumento = null;

    /**
     * @var int
     */
    private $NumeroProtocollo = null;

    /**
     * @var string
     */
    private $DataProtocollo = null;

    /**
     * @var int
     */
    private $AnnoProtocollazione = null;

    /**
     * @var string
     */
    private $Origine = null;

    /**
     * @var string
     */
    private $Oggetto = null;

    /**
     * @var string
     */
    private $MittenteDestinatario = null;

    /**
     * @var int
     */
    private $IdSoggetto = null;

    /**
     * @var string
     */
    private $Cognome = null;

    /**
     * @var string
     */
    private $Nome = null;

    /**
     * Constructor
     *
     * @var int $IdDocumento
     * @var int $NumeroProtocollo
     * @var string $DataProtocollo
     * @var int $AnnoProtocollazione
     * @var string $Origine
     * @var string $Oggetto
     * @var string $MittenteDestinatario
     * @var int $IdSoggetto
     * @var string $Cognome
     * @var string $Nome
     */
    public function __construct($IdDocumento, $NumeroProtocollo, $DataProtocollo, $AnnoProtocollazione, $Origine, $Oggetto, $MittenteDestinatario, $IdSoggetto, $Cognome, $Nome)
    {
        $this->IdDocumento = $IdDocumento;
        $this->NumeroProtocollo = $NumeroProtocollo;
        $this->DataProtocollo = $DataProtocollo;
        $this->AnnoProtocollazione = $AnnoProtocollazione;
        $this->Origine = $Origine;
        $this->Oggetto = $Oggetto;
        $this->MittenteDestinatario = $MittenteDestinatario;
        $this->IdSoggetto = $IdSoggetto;
        $this->Cognome = $Cognome;
        $this->Nome = $Nome;
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
     * @return ProtocolloSoggettoOut
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
    public function getNumeroProtocollo()
    {
        return $this->NumeroProtocollo;
    }

    /**
     * @param int $NumeroProtocollo
     * @return ProtocolloSoggettoOut
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
    public function getDataProtocollo()
    {
        return $this->DataProtocollo;
    }

    /**
     * @param string $DataProtocollo
     * @return ProtocolloSoggettoOut
     */
    public function withDataProtocollo($DataProtocollo)
    {
        $new = clone $this;
        $new->DataProtocollo = $DataProtocollo;

        return $new;
    }

    /**
     * @return int
     */
    public function getAnnoProtocollazione()
    {
        return $this->AnnoProtocollazione;
    }

    /**
     * @param int $AnnoProtocollazione
     * @return ProtocolloSoggettoOut
     */
    public function withAnnoProtocollazione($AnnoProtocollazione)
    {
        $new = clone $this;
        $new->AnnoProtocollazione = $AnnoProtocollazione;

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
     * @return ProtocolloSoggettoOut
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
    public function getOggetto()
    {
        return $this->Oggetto;
    }

    /**
     * @param string $Oggetto
     * @return ProtocolloSoggettoOut
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
    public function getMittenteDestinatario()
    {
        return $this->MittenteDestinatario;
    }

    /**
     * @param string $MittenteDestinatario
     * @return ProtocolloSoggettoOut
     */
    public function withMittenteDestinatario($MittenteDestinatario)
    {
        $new = clone $this;
        $new->MittenteDestinatario = $MittenteDestinatario;

        return $new;
    }

    /**
     * @return int
     */
    public function getIdSoggetto()
    {
        return $this->IdSoggetto;
    }

    /**
     * @param int $IdSoggetto
     * @return ProtocolloSoggettoOut
     */
    public function withIdSoggetto($IdSoggetto)
    {
        $new = clone $this;
        $new->IdSoggetto = $IdSoggetto;

        return $new;
    }

    /**
     * @return string
     */
    public function getCognome()
    {
        return $this->Cognome;
    }

    /**
     * @param string $Cognome
     * @return ProtocolloSoggettoOut
     */
    public function withCognome($Cognome)
    {
        $new = clone $this;
        $new->Cognome = $Cognome;

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
     * @return ProtocolloSoggettoOut
     */
    public function withNome($Nome)
    {
        $new = clone $this;
        $new->Nome = $Nome;

        return $new;
    }


}

