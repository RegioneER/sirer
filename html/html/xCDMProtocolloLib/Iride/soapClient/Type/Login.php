<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Login implements RequestInterface
{

    /**
     * @var string
     */
    private $Utente = null;

    /**
     * @var string
     */
    private $Password = null;

    /**
     * @var string
     */
    private $Ruolo = null;

    /**
     * Constructor
     *
     * @var string $Utente
     * @var string $Password
     * @var string $Ruolo
     */
    public function __construct($Utente, $Password, $Ruolo)
    {
        $this->Utente = $Utente;
        $this->Password = $Password;
        $this->Ruolo = $Ruolo;
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
     * @return Login
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
    public function getPassword()
    {
        return $this->Password;
    }

    /**
     * @param string $Password
     * @return Login
     */
    public function withPassword($Password)
    {
        $new = clone $this;
        $new->Password = $Password;

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
     * @return Login
     */
    public function withRuolo($Ruolo)
    {
        $new = clone $this;
        $new->Ruolo = $Ruolo;

        return $new;
    }


}

