<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ProtocolliSoggettoOut implements RequestInterface
{

    /**
     * @var \IrideWS\Type\ArrayOfProtocolloSoggettoOut
     */
    private $Protocolli = null;

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
     * @var \IrideWS\Type\ArrayOfProtocolloSoggettoOut $Protocolli
     * @var string $Messaggio
     * @var string $Errore
     */
    public function __construct($Protocolli, $Messaggio, $Errore)
    {
        $this->Protocolli = $Protocolli;
        $this->Messaggio = $Messaggio;
        $this->Errore = $Errore;
    }

    /**
     * @return \IrideWS\Type\ArrayOfProtocolloSoggettoOut
     */
    public function getProtocolli()
    {
        return $this->Protocolli;
    }

    /**
     * @param \IrideWS\Type\ArrayOfProtocolloSoggettoOut $Protocolli
     * @return ProtocolliSoggettoOut
     */
    public function withProtocolli($Protocolli)
    {
        $new = clone $this;
        $new->Protocolli = $Protocolli;

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
     * @return ProtocolliSoggettoOut
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
     * @return ProtocolliSoggettoOut
     */
    public function withErrore($Errore)
    {
        $new = clone $this;
        $new->Errore = $Errore;

        return $new;
    }


}

