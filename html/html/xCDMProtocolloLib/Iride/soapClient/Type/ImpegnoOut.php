<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ImpegnoOut implements RequestInterface
{

    /**
     * @var int
     */
    private $AnnoImpegno = null;

    /**
     * @var string
     */
    private $NumeroImpegno = null;

    /**
     * @var string
     */
    private $CapitoloImpegno = null;

    /**
     * @var string
     */
    private $ArticoloImpegno = null;

    /**
     * @var string
     */
    private $CodSiopeImpegno = null;

    /**
     * @var float
     */
    private $ImportoImpegno = null;

    /**
     * @var float
     */
    private $SoggettoImpegno = null;

    /**
     * Constructor
     *
     * @var int $AnnoImpegno
     * @var string $NumeroImpegno
     * @var string $CapitoloImpegno
     * @var string $ArticoloImpegno
     * @var string $CodSiopeImpegno
     * @var float $ImportoImpegno
     * @var float $SoggettoImpegno
     */
    public function __construct($AnnoImpegno, $NumeroImpegno, $CapitoloImpegno, $ArticoloImpegno, $CodSiopeImpegno, $ImportoImpegno, $SoggettoImpegno)
    {
        $this->AnnoImpegno = $AnnoImpegno;
        $this->NumeroImpegno = $NumeroImpegno;
        $this->CapitoloImpegno = $CapitoloImpegno;
        $this->ArticoloImpegno = $ArticoloImpegno;
        $this->CodSiopeImpegno = $CodSiopeImpegno;
        $this->ImportoImpegno = $ImportoImpegno;
        $this->SoggettoImpegno = $SoggettoImpegno;
    }

    /**
     * @return int
     */
    public function getAnnoImpegno()
    {
        return $this->AnnoImpegno;
    }

    /**
     * @param int $AnnoImpegno
     * @return ImpegnoOut
     */
    public function withAnnoImpegno($AnnoImpegno)
    {
        $new = clone $this;
        $new->AnnoImpegno = $AnnoImpegno;

        return $new;
    }

    /**
     * @return string
     */
    public function getNumeroImpegno()
    {
        return $this->NumeroImpegno;
    }

    /**
     * @param string $NumeroImpegno
     * @return ImpegnoOut
     */
    public function withNumeroImpegno($NumeroImpegno)
    {
        $new = clone $this;
        $new->NumeroImpegno = $NumeroImpegno;

        return $new;
    }

    /**
     * @return string
     */
    public function getCapitoloImpegno()
    {
        return $this->CapitoloImpegno;
    }

    /**
     * @param string $CapitoloImpegno
     * @return ImpegnoOut
     */
    public function withCapitoloImpegno($CapitoloImpegno)
    {
        $new = clone $this;
        $new->CapitoloImpegno = $CapitoloImpegno;

        return $new;
    }

    /**
     * @return string
     */
    public function getArticoloImpegno()
    {
        return $this->ArticoloImpegno;
    }

    /**
     * @param string $ArticoloImpegno
     * @return ImpegnoOut
     */
    public function withArticoloImpegno($ArticoloImpegno)
    {
        $new = clone $this;
        $new->ArticoloImpegno = $ArticoloImpegno;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodSiopeImpegno()
    {
        return $this->CodSiopeImpegno;
    }

    /**
     * @param string $CodSiopeImpegno
     * @return ImpegnoOut
     */
    public function withCodSiopeImpegno($CodSiopeImpegno)
    {
        $new = clone $this;
        $new->CodSiopeImpegno = $CodSiopeImpegno;

        return $new;
    }

    /**
     * @return float
     */
    public function getImportoImpegno()
    {
        return $this->ImportoImpegno;
    }

    /**
     * @param float $ImportoImpegno
     * @return ImpegnoOut
     */
    public function withImportoImpegno($ImportoImpegno)
    {
        $new = clone $this;
        $new->ImportoImpegno = $ImportoImpegno;

        return $new;
    }

    /**
     * @return float
     */
    public function getSoggettoImpegno()
    {
        return $this->SoggettoImpegno;
    }

    /**
     * @param float $SoggettoImpegno
     * @return ImpegnoOut
     */
    public function withSoggettoImpegno($SoggettoImpegno)
    {
        $new = clone $this;
        $new->SoggettoImpegno = $SoggettoImpegno;

        return $new;
    }


}

