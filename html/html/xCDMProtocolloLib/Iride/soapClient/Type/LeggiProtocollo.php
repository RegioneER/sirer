<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class LeggiProtocollo implements RequestInterface
{

    /**
     * @var int
     */
    private $AnnoProtocollo = null;

    /**
     * @var int
     */
    private $NumeroProtocollo = null;

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
     * @var int $AnnoProtocollo
     * @var int $NumeroProtocollo
     * @var string $Utente
     * @var string $Ruolo
     */
    public function __construct($AnnoProtocollo, $NumeroProtocollo, $Utente, $Ruolo)
    {
        $this->AnnoProtocollo = $AnnoProtocollo;
        $this->NumeroProtocollo = $NumeroProtocollo;
        $this->Utente = $Utente;
        $this->Ruolo = $Ruolo;
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
     * @return LeggiProtocollo
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
     * @return LeggiProtocollo
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
    public function getUtente()
    {
        return $this->Utente;
    }

    /**
     * @param string $Utente
     * @return LeggiProtocollo
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
     * @return LeggiProtocollo
     */
    public function withRuolo($Ruolo)
    {
        $new = clone $this;
        $new->Ruolo = $Ruolo;

        return $new;
    }


}

