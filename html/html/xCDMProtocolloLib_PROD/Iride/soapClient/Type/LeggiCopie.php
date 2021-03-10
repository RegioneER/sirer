<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class LeggiCopie implements RequestInterface
{

    /**
     * @var string
     */
    private $LeggiCopieIn = null;

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
     * @var string $LeggiCopieIn
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($LeggiCopieIn, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->LeggiCopieIn = $LeggiCopieIn;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getLeggiCopieIn()
    {
        return $this->LeggiCopieIn;
    }

    /**
     * @param string $LeggiCopieIn
     * @return LeggiCopie
     */
    public function withLeggiCopieIn($LeggiCopieIn)
    {
        $new = clone $this;
        $new->LeggiCopieIn = $LeggiCopieIn;

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
     * @return LeggiCopie
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
     * @return LeggiCopie
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

