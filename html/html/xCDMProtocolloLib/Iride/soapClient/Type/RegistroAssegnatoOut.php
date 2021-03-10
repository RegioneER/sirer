<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RegistroAssegnatoOut implements RequestInterface
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
     * @var string
     */
    private $DataRegistro = null;

    /**
     * Constructor
     *
     * @var string $TipoRegistro
     * @var int $AnnoRegistro
     * @var int $NumeroRegistro
     * @var string $DataRegistro
     */
    public function __construct($TipoRegistro, $AnnoRegistro, $NumeroRegistro, $DataRegistro)
    {
        $this->TipoRegistro = $TipoRegistro;
        $this->AnnoRegistro = $AnnoRegistro;
        $this->NumeroRegistro = $NumeroRegistro;
        $this->DataRegistro = $DataRegistro;
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
     * @return RegistroAssegnatoOut
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
     * @return RegistroAssegnatoOut
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
     * @return RegistroAssegnatoOut
     */
    public function withNumeroRegistro($NumeroRegistro)
    {
        $new = clone $this;
        $new->NumeroRegistro = $NumeroRegistro;

        return $new;
    }

    /**
     * @return string
     */
    public function getDataRegistro()
    {
        return $this->DataRegistro;
    }

    /**
     * @param string $DataRegistro
     * @return RegistroAssegnatoOut
     */
    public function withDataRegistro($DataRegistro)
    {
        $new = clone $this;
        $new->DataRegistro = $DataRegistro;

        return $new;
    }


}

