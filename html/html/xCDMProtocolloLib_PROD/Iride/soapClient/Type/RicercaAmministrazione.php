<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RicercaAmministrazione implements RequestInterface
{

    /**
     * @var string
     */
    private $CodiceAmmSoggetto = null;

    /**
     * @var string
     */
    private $CodiceAOOSoggetto = null;

    /**
     * Constructor
     *
     * @var string $CodiceAmmSoggetto
     * @var string $CodiceAOOSoggetto
     */
    public function __construct($CodiceAmmSoggetto, $CodiceAOOSoggetto)
    {
        $this->CodiceAmmSoggetto = $CodiceAmmSoggetto;
        $this->CodiceAOOSoggetto = $CodiceAOOSoggetto;
    }

    /**
     * @return string
     */
    public function getCodiceAmmSoggetto()
    {
        return $this->CodiceAmmSoggetto;
    }

    /**
     * @param string $CodiceAmmSoggetto
     * @return RicercaAmministrazione
     */
    public function withCodiceAmmSoggetto($CodiceAmmSoggetto)
    {
        $new = clone $this;
        $new->CodiceAmmSoggetto = $CodiceAmmSoggetto;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceAOOSoggetto()
    {
        return $this->CodiceAOOSoggetto;
    }

    /**
     * @param string $CodiceAOOSoggetto
     * @return RicercaAmministrazione
     */
    public function withCodiceAOOSoggetto($CodiceAOOSoggetto)
    {
        $new = clone $this;
        $new->CodiceAOOSoggetto = $CodiceAOOSoggetto;

        return $new;
    }


}

