<?php

namespace IrideWFFascicolo\Type;

class EsitoOperazione
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

