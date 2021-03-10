<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class UODestinataria implements RequestInterface
{

    /**
     * @var string
     */
    private $Carico = null;

    /**
     * @var string
     */
    private $TipoUO = null;

    /**
     * @var string
     */
    private $Data = null;

    /**
     * @var string
     */
    private $NumeroCopie = null;

    /**
     * Constructor
     *
     * @var string $Carico
     * @var string $TipoUO
     * @var string $Data
     * @var string $NumeroCopie
     */
    public function __construct($Carico, $TipoUO, $Data, $NumeroCopie)
    {
        $this->Carico = $Carico;
        $this->TipoUO = $TipoUO;
        $this->Data = $Data;
        $this->NumeroCopie = $NumeroCopie;
    }

    /**
     * @return string
     */
    public function getCarico()
    {
        return $this->Carico;
    }

    /**
     * @param string $Carico
     * @return UODestinataria
     */
    public function withCarico($Carico)
    {
        $new = clone $this;
        $new->Carico = $Carico;

        return $new;
    }

    /**
     * @return string
     */
    public function getTipoUO()
    {
        return $this->TipoUO;
    }

    /**
     * @param string $TipoUO
     * @return UODestinataria
     */
    public function withTipoUO($TipoUO)
    {
        $new = clone $this;
        $new->TipoUO = $TipoUO;

        return $new;
    }

    /**
     * @return string
     */
    public function getData()
    {
        return $this->Data;
    }

    /**
     * @param string $Data
     * @return UODestinataria
     */
    public function withData($Data)
    {
        $new = clone $this;
        $new->Data = $Data;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroCopie()
    {
        return $this->NumeroCopie;
    }

    /**
     * @param string $NumeroCopie
     * @return UODestinataria
     */
    public function withNumeroCopie($NumeroCopie)
    {
        $new = clone $this;
        $new->NumeroCopie = $NumeroCopie;

        return $new;
    }


}

