<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RicercaPerCodiceFiscale implements RequestInterface
{

    /**
     * @var string
     */
    private $CodiceFiscale = null;

    /**
     * @var string
     */
    private $SoloProtocollo = null;

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
     * @var string $CodiceFiscale
     * @var string $SoloProtocollo
     * @var string $Utente
     * @var string $Ruolo
     */
    public function __construct($CodiceFiscale, $SoloProtocollo, $Utente, $Ruolo)
    {
        $this->CodiceFiscale = $CodiceFiscale;
        $this->SoloProtocollo = $SoloProtocollo;
        $this->Utente = $Utente;
        $this->Ruolo = $Ruolo;
    }

    /**
     * @return string
     */
    public function getCodiceFiscale()
    {
        return $this->CodiceFiscale;
    }

    /**
     * @param string $CodiceFiscale
     * @return RicercaPerCodiceFiscale
     */
    public function withCodiceFiscale($CodiceFiscale)
    {
        $new = clone $this;
        $new->CodiceFiscale = $CodiceFiscale;

        return $new;
    }

    /**
     * @return string
     */
    public function getSoloProtocollo()
    {
        return $this->SoloProtocollo;
    }

    /**
     * @param string $SoloProtocollo
     * @return RicercaPerCodiceFiscale
     */
    public function withSoloProtocollo($SoloProtocollo)
    {
        $new = clone $this;
        $new->SoloProtocollo = $SoloProtocollo;

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
     * @return RicercaPerCodiceFiscale
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
     * @return RicercaPerCodiceFiscale
     */
    public function withRuolo($Ruolo)
    {
        $new = clone $this;
        $new->Ruolo = $Ruolo;

        return $new;
    }


}

