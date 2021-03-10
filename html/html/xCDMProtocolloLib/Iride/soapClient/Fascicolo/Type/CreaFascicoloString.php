<?php

namespace IrideWFFascicolo\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreaFascicoloString  implements RequestInterface
{


    public function __construct($FascicoloInStr, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->FascicoloInStr = $FascicoloInStr;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }
    /**
     * @var string
     */
    private $FascicoloInStr = null;

    /**
     * @var string
     */
    private $CodiceAmministrazione = null;

    /**
     * @var string
     */
    private $CodiceAOO = null;

    /**
     * @return string
     */
    public function getFascicoloInStr()
    {
        return $this->FascicoloInStr;
    }

    /**
     * @param string $FascicoloInStr
     * @return CreaFascicoloString
     */
    public function withFascicoloInStr($FascicoloInStr)
    {
        $new = clone $this;
        $new->FascicoloInStr = $FascicoloInStr;

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
     * @return CreaFascicoloString
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
     * @return CreaFascicoloString
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

