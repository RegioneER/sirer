<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ProtocolloOut implements RequestInterface
{

    /**
     * @var int
     */
    private $IdDocumento = null;

    /**
     * @var int
     */
    private $AnnoProtocollo = null;

    /**
     * @var int
     */
    private $NumeroProtocollo = null;

    /**
     * @var \DateTime
     */
    private $DataProtocollo = null;

    /**
     * @var string
     */
    private $Messaggio = null;

    /**
     * @var \IrideWS\Type\ArrayOfRegistroOut
     */
    private $Registri = null;

    /**
     * @var \IrideWS\Type\ArrayOfAllegatoInseritoOut
     */
    private $Allegati = null;

    /**
     * @var string
     */
    private $Errore = null;

    /**
     * Constructor
     *
     * @var int $IdDocumento
     * @var int $AnnoProtocollo
     * @var int $NumeroProtocollo
     * @var \DateTime $DataProtocollo
     * @var string $Messaggio
     * @var \IrideWS\Type\ArrayOfRegistroOut $Registri
     * @var \IrideWS\Type\ArrayOfAllegatoInseritoOut $Allegati
     * @var string $Errore
     */
    public function __construct($IdDocumento, $AnnoProtocollo, $NumeroProtocollo, $DataProtocollo, $Messaggio, $Registri, $Allegati, $Errore)
    {
        $this->IdDocumento = $IdDocumento;
        $this->AnnoProtocollo = $AnnoProtocollo;
        $this->NumeroProtocollo = $NumeroProtocollo;
        $this->DataProtocollo = $DataProtocollo;
        $this->Messaggio = $Messaggio;
        $this->Registri = $Registri;
        $this->Allegati = $Allegati;
        $this->Errore = $Errore;
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
     * @return ProtocolloOut
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
    public function getAnnoProtocollo()
    {
        return $this->AnnoProtocollo;
    }

    /**
     * @param int $AnnoProtocollo
     * @return ProtocolloOut
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
     * @return ProtocolloOut
     */
    public function withNumeroProtocollo($NumeroProtocollo)
    {
        $new = clone $this;
        $new->NumeroProtocollo = $NumeroProtocollo;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDataProtocollo()
    {
        return $this->DataProtocollo;
    }

    /**
     * @param \DateTime $DataProtocollo
     * @return ProtocolloOut
     */
    public function withDataProtocollo($DataProtocollo)
    {
        $new = clone $this;
        $new->DataProtocollo = $DataProtocollo;

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
     * @return ProtocolloOut
     */
    public function withMessaggio($Messaggio)
    {
        $new = clone $this;
        $new->Messaggio = $Messaggio;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfRegistroOut
     */
    public function getRegistri()
    {
        return $this->Registri;
    }

    /**
     * @param \IrideWS\Type\ArrayOfRegistroOut $Registri
     * @return ProtocolloOut
     */
    public function withRegistri($Registri)
    {
        $new = clone $this;
        $new->Registri = $Registri;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfAllegatoInseritoOut
     */
    public function getAllegati()
    {
        return $this->Allegati;
    }

    /**
     * @param \IrideWS\Type\ArrayOfAllegatoInseritoOut $Allegati
     * @return ProtocolloOut
     */
    public function withAllegati($Allegati)
    {
        $new = clone $this;
        $new->Allegati = $Allegati;

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
     * @return ProtocolloOut
     */
    public function withErrore($Errore)
    {
        $new = clone $this;
        $new->Errore = $Errore;

        return $new;
    }


}

