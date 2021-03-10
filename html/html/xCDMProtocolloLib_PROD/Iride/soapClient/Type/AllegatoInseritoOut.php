<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AllegatoInseritoOut implements RequestInterface
{

    /**
     * @var int
     */
    private $Serial = null;

    /**
     * @var int
     */
    private $IDBase = null;

    /**
     * @var int
     */
    private $Versione = null;

    /**
     * Constructor
     *
     * @var int $Serial
     * @var int $IDBase
     * @var int $Versione
     */
    public function __construct($Serial, $IDBase, $Versione)
    {
        $this->Serial = $Serial;
        $this->IDBase = $IDBase;
        $this->Versione = $Versione;
    }

    /**
     * @return int
     */
    public function getSerial()
    {
        return $this->Serial;
    }

    /**
     * @param int $Serial
     * @return AllegatoInseritoOut
     */
    public function withSerial($Serial)
    {
        $new = clone $this;
        $new->Serial = $Serial;

        return $new;
    }

    /**
     * @return int
     */
    public function getIDBase()
    {
        return $this->IDBase;
    }

    /**
     * @param int $IDBase
     * @return AllegatoInseritoOut
     */
    public function withIDBase($IDBase)
    {
        $new = clone $this;
        $new->IDBase = $IDBase;

        return $new;
    }

    /**
     * @return int
     */
    public function getVersione()
    {
        return $this->Versione;
    }

    /**
     * @param int $Versione
     * @return AllegatoInseritoOut
     */
    public function withVersione($Versione)
    {
        $new = clone $this;
        $new->Versione = $Versione;

        return $new;
    }


}

