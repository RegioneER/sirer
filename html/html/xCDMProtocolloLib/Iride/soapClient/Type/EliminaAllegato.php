<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class EliminaAllegato implements RequestInterface
{

    /**
     * @var string
     */
    private $EliminaAllegatoIn = null;

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
     * @var string $EliminaAllegatoIn
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($EliminaAllegatoIn, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->EliminaAllegatoIn = $EliminaAllegatoIn;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getEliminaAllegatoIn()
    {
        return $this->EliminaAllegatoIn;
    }

    /**
     * @param string $EliminaAllegatoIn
     * @return EliminaAllegato
     */
    public function withEliminaAllegatoIn($EliminaAllegatoIn)
    {
        $new = clone $this;
        $new->EliminaAllegatoIn = $EliminaAllegatoIn;

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
     * @return EliminaAllegato
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
     * @return EliminaAllegato
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

