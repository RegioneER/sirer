<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AggiungiAllegati implements RequestInterface
{

    /**
     * @var \IrideWS\Type\NuoviAllegati
     */
    private $NuoviAllegati = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\NuoviAllegati $NuoviAllegati
     */
    public function __construct($NuoviAllegati)
    {
        $this->NuoviAllegati = $NuoviAllegati;
    }

    /**
     * @return \IrideWS\Type\NuoviAllegati
     */
    public function getNuoviAllegati()
    {
        return $this->NuoviAllegati;
    }

    /**
     * @param \IrideWS\Type\NuoviAllegati $NuoviAllegati
     * @return AggiungiAllegati
     */
    public function withNuoviAllegati($NuoviAllegati)
    {
        $new = clone $this;
        $new->NuoviAllegati = $NuoviAllegati;

        return $new;
    }


}

