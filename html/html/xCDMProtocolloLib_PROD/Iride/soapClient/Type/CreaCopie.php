<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreaCopie implements RequestInterface
{

    /**
     * @var \IrideWS\Type\CreaCopieIn
     */
    private $CreaCopieIn = null;

    /**
     * @var string
     */
    private $CodiceAmministrazione = null;

    /**
     * @var string
     */
    private $CodiceAOO = null;

    /**
     * Constructor
     *
     * @var \IrideWS\Type\CreaCopieIn $CreaCopieIn
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($CreaCopieIn, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->CreaCopieIn = $CreaCopieIn;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return \IrideWS\Type\CreaCopieIn
     */
    public function getCreaCopieIn()
    {
        return $this->CreaCopieIn;
    }

    /**
     * @param \IrideWS\Type\CreaCopieIn $CreaCopieIn
     * @return CreaCopie
     */
    public function withCreaCopieIn($CreaCopieIn)
    {
        $new = clone $this;
        $new->CreaCopieIn = $CreaCopieIn;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceAmministrazione()
    {
        return $this->CodiceAmministrazione;
    }

    /**
     * @param string $CodiceAmministrazione
     * @return CreaCopie
     */
    public function withCodiceAmministrazione($CodiceAmministrazione)
    {
        $new = clone $this;
        $new->CodiceAmministrazione = $CodiceAmministrazione;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodiceAOO()
    {
        return $this->CodiceAOO;
    }

    /**
     * @param string $CodiceAOO
     * @return CreaCopie
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

