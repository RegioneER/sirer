<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class LoginOut implements RequestInterface
{

    /**
     * @var string
     */
    private $Utente = null;

    /**
     * @var string
     */
    private $Ruolo = null;

    /**
     * @var bool
     */
    private $Autenticato = null;

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
     * @var string $Utente
     * @var string $Ruolo
     * @var bool $Autenticato
     * @var string $Messaggio
     * @var string $Errore
     */
    public function __construct($Utente, $Ruolo, $Autenticato, $Messaggio, $Errore)
    {
        $this->Utente = $Utente;
        $this->Ruolo = $Ruolo;
        $this->Autenticato = $Autenticato;
        $this->Messaggio = $Messaggio;
        $this->Errore = $Errore;
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
     * @return LoginOut
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
     * @return LoginOut
     */
    public function withRuolo($Ruolo)
    {
        $new = clone $this;
        $new->Ruolo = $Ruolo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getAutenticato()
    {
        return $this->Autenticato;
    }

    /**
     * @param bool $Autenticato
     * @return LoginOut
     */
    public function withAutenticato($Autenticato)
    {
        $new = clone $this;
        $new->Autenticato = $Autenticato;

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
     * @return LoginOut
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
     * @return LoginOut
     */
    public function withErrore($Errore)
    {
        $new = clone $this;
        $new->Errore = $Errore;

        return $new;
    }


}

