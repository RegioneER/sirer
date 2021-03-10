<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreaCopieOut implements RequestInterface
{

    /**
     * @var string
     */
    private $Messaggio = null;

    /**
     * @var string
     */
    private $Errore = null;

    /**
     * @var int
     */
    private $IdDocumentoSorgente = null;

    /**
     * @var \IrideWS\Type\ArrayOfCopiaCreata
     */
    private $CopieCreate = null;

    /**
     * Constructor
     *
     * @var string $Messaggio
     * @var string $Errore
     * @var int $IdDocumentoSorgente
     * @var \IrideWS\Type\ArrayOfCopiaCreata $CopieCreate
     */
    public function __construct($Messaggio, $Errore, $IdDocumentoSorgente, $CopieCreate)
    {
        $this->Messaggio = $Messaggio;
        $this->Errore = $Errore;
        $this->IdDocumentoSorgente = $IdDocumentoSorgente;
        $this->CopieCreate = $CopieCreate;
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
     * @return CreaCopieOut
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
     * @return CreaCopieOut
     */
    public function withErrore($Errore)
    {
        $new = clone $this;
        $new->Errore = $Errore;

        return $new;
    }

    /**
     * @return int
     */
    public function getIdDocumentoSorgente()
    {
        return $this->IdDocumentoSorgente;
    }

    /**
     * @param int $IdDocumentoSorgente
     * @return CreaCopieOut
     */
    public function withIdDocumentoSorgente($IdDocumentoSorgente)
    {
        $new = clone $this;
        $new->IdDocumentoSorgente = $IdDocumentoSorgente;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfCopiaCreata
     */
    public function getCopieCreate()
    {
        return $this->CopieCreate;
    }

    /**
     * @param \IrideWS\Type\ArrayOfCopiaCreata $CopieCreate
     * @return CreaCopieOut
     */
    public function withCopieCreate($CopieCreate)
    {
        $new = clone $this;
        $new->CopieCreate = $CopieCreate;

        return $new;
    }


}

