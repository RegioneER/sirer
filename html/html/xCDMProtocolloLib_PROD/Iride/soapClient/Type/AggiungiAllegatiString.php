<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AggiungiAllegatiString implements RequestInterface
{

    /**
     * @var string
     */
    private $NuoviAllegatiStr = null;

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
     * @var string $NuoviAllegatiStr
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($NuoviAllegatiStr, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->NuoviAllegatiStr = $NuoviAllegatiStr;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getNuoviAllegatiStr()
    {
        return $this->NuoviAllegatiStr;
    }

    /**
     * @param string $NuoviAllegatiStr
     * @return AggiungiAllegatiString
     */
    public function withNuoviAllegatiStr($NuoviAllegatiStr)
    {
        $new = clone $this;
        $new->NuoviAllegatiStr = $NuoviAllegatiStr;

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
     * @return AggiungiAllegatiString
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
     * @return AggiungiAllegatiString
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

