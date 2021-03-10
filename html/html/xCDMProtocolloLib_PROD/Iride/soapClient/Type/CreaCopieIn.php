<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreaCopieIn implements RequestInterface
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
    private $FascicolaConOriginale = null;

    /**
     * @var \IrideWS\Type\ArrayOfUODestinataria
     */
    private $UODestinatarie = null;

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
     * @var string $FascicolaConOriginale
     * @var \IrideWS\Type\ArrayOfUODestinataria $UODestinatarie
     * @var string $Utente
     * @var string $Ruolo
     */
    public function __construct($IdDocumento, $AnnoProtocollo, $NumeroProtocollo, $FascicolaConOriginale, $UODestinatarie, $Utente, $Ruolo)
    {
        $this->IdDocumento = $IdDocumento;
        $this->AnnoProtocollo = $AnnoProtocollo;
        $this->NumeroProtocollo = $NumeroProtocollo;
        $this->FascicolaConOriginale = $FascicolaConOriginale;
        $this->UODestinatarie = $UODestinatarie;
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
     * @return CreaCopieIn
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
     * @return CreaCopieIn
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
     * @return CreaCopieIn
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
    public function getFascicolaConOriginale()
    {
        return $this->FascicolaConOriginale;
    }

    /**
     * @param string $FascicolaConOriginale
     * @return CreaCopieIn
     */
    public function withFascicolaConOriginale($FascicolaConOriginale)
    {
        $new = clone $this;
        $new->FascicolaConOriginale = $FascicolaConOriginale;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfUODestinataria
     */
    public function getUODestinatarie()
    {
        return $this->UODestinatarie;
    }

    /**
     * @param \IrideWS\Type\ArrayOfUODestinataria $UODestinatarie
     * @return CreaCopieIn
     */
    public function withUODestinatarie($UODestinatarie)
    {
        $new = clone $this;
        $new->UODestinatarie = $UODestinatarie;

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
     * @return CreaCopieIn
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
     * @return CreaCopieIn
     */
    public function withRuolo($Ruolo)
    {
        $new = clone $this;
        $new->Ruolo = $Ruolo;

        return $new;
    }


}

