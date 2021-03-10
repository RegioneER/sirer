<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class EsitoOperazione implements RequestInterface
{

    /**
     * @var bool
     */
    private $Esito = null;

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
     * @var bool $Esito
     * @var string $Messaggio
     * @var string $Errore
     */
    public function __construct($Esito, $Messaggio, $Errore)
    {
        $this->Esito = $Esito;
        $this->Messaggio = $Messaggio;
        $this->Errore = $Errore;
    }

    /**
     * @return bool
     */
    public function getEsito()
    {
        return $this->Esito;
    }

    /**
     * @param bool $Esito
     * @return EsitoOperazione
     */
    public function withEsito($Esito)
    {
        $new = clone $this;
        $new->Esito = $Esito;

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
     * @return EsitoOperazione
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
     * @return EsitoOperazione
     */
    public function withErrore($Errore)
    {
        $new = clone $this;
        $new->Errore = $Errore;

        return $new;
    }


}

