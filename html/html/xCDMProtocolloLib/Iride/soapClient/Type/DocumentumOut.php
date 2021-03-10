<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DocumentumOut implements RequestInterface
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
     * @var \IrideWS\Type\ArrayOfRegistroOut
     */
    private $Registri = null;

    /**
     * @var string
     */
    private $Messaggio = null;

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
     * @var \IrideWS\Type\ArrayOfRegistroOut $Registri
     * @var string $Messaggio
     * @var string $Errore
     */
    public function __construct($IdDocumento, $AnnoProtocollo, $NumeroProtocollo, $DataProtocollo, $Registri, $Messaggio, $Errore)
    {
        $this->IdDocumento = $IdDocumento;
        $this->AnnoProtocollo = $AnnoProtocollo;
        $this->NumeroProtocollo = $NumeroProtocollo;
        $this->DataProtocollo = $DataProtocollo;
        $this->Registri = $Registri;
        $this->Messaggio = $Messaggio;
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
     * @return DocumentumOut
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
     * @return DocumentumOut
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
     * @return DocumentumOut
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
     * @return DocumentumOut
     */
    public function withDataProtocollo($DataProtocollo)
    {
        $new = clone $this;
        $new->DataProtocollo = $DataProtocollo;

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
     * @return DocumentumOut
     */
    public function withRegistri($Registri)
    {
        $new = clone $this;
        $new->Registri = $Registri;

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
     * @return DocumentumOut
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
     * @return DocumentumOut
     */
    public function withErrore($Errore)
    {
        $new = clone $this;
        $new->Errore = $Errore;

        return $new;
    }


}

