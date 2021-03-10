<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RecordUtente implements RequestInterface
{

    /**
     * @var int
     */
    private $Progressivo = null;

    /**
     * @var \IrideWS\Type\ArrayOfCampoUtente
     */
    private $Campi = null;

    /**
     * Constructor
     *
     * @var int $Progressivo
     * @var \IrideWS\Type\ArrayOfCampoUtente $Campi
     */
    public function __construct($Progressivo, $Campi)
    {
        $this->Progressivo = $Progressivo;
        $this->Campi = $Campi;
    }

    /**
     * @return int
     */
    public function getProgressivo()
    {
        return $this->Progressivo;
    }

    /**
     * @param int $Progressivo
     * @return RecordUtente
     */
    public function withProgressivo($Progressivo)
    {
        $new = clone $this;
        $new->Progressivo = $Progressivo;

        return $new;
    }

    /**
     * @return \IrideWS\Type\ArrayOfCampoUtente
     */
    public function getCampi()
    {
        return $this->Campi;
    }

    /**
     * @param \IrideWS\Type\ArrayOfCampoUtente $Campi
     * @return RecordUtente
     */
    public function withCampi($Campi)
    {
        $new = clone $this;
        $new->Campi = $Campi;

        return $new;
    }


}

