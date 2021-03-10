<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RegistroOut implements RequestInterface
{

    /**
     * @var string
     */
    private $TipoRegistro = null;

    /**
     * @var int
     */
    private $AnnoRegistro = null;

    /**
     * @var int
     */
    private $NumeroRegistro = null;

    /**
     * Constructor
     *
     * @var string $TipoRegistro
     * @var int $AnnoRegistro
     * @var int $NumeroRegistro
     */
    public function __construct($TipoRegistro, $AnnoRegistro, $NumeroRegistro)
    {
        $this->TipoRegistro = $TipoRegistro;
        $this->AnnoRegistro = $AnnoRegistro;
        $this->NumeroRegistro = $NumeroRegistro;
    }

    /**
     * @return string
     */
    public function getTipoRegistro()
    {
        return $this->TipoRegistro;
    }

    /**
     * @param string $TipoRegistro
     * @return RegistroOut
     */
    public function withTipoRegistro($TipoRegistro)
    {
        $new = clone $this;
        $new->TipoRegistro = $TipoRegistro;

        return $new;
    }

    /**
     * @return int
     */
    public function getAnnoRegistro()
    {
        return $this->AnnoRegistro;
    }

    /**
     * @param int $AnnoRegistro
     * @return RegistroOut
     */
    public function withAnnoRegistro($AnnoRegistro)
    {
        $new = clone $this;
        $new->AnnoRegistro = $AnnoRegistro;

        return $new;
    }

    /**
     * @return int
     */
    public function getNumeroRegistro()
    {
        return $this->NumeroRegistro;
    }

    /**
     * @param int $NumeroRegistro
     * @return RegistroOut
     */
    public function withNumeroRegistro($NumeroRegistro)
    {
        $new = clone $this;
        $new->NumeroRegistro = $NumeroRegistro;

        return $new;
    }


}

