<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CreaCopieString implements RequestInterface
{

    /**
     * @var string
     */
    private $CreaCopieInStr = null;

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
     * @var string $CreaCopieInStr
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($CreaCopieInStr, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->CreaCopieInStr = $CreaCopieInStr;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getCreaCopieInStr()
    {
        return $this->CreaCopieInStr;
    }

    /**
     * @param string $CreaCopieInStr
     * @return CreaCopieString
     */
    public function withCreaCopieInStr($CreaCopieInStr)
    {
        $new = clone $this;
        $new->CreaCopieInStr = $CreaCopieInStr;

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
     * @return CreaCopieString
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
     * @return CreaCopieString
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

