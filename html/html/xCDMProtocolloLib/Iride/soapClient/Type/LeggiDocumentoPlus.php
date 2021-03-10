<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class LeggiDocumentoPlus implements RequestInterface
{

    /**
     * @var string
     */
    private $FiltroDocumento = null;

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
     * @var string $FiltroDocumento
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($FiltroDocumento, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->FiltroDocumento = $FiltroDocumento;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getFiltroDocumento()
    {
        return $this->FiltroDocumento;
    }

    /**
     * @param string $FiltroDocumento
     * @return LeggiDocumentoPlus
     */
    public function withFiltroDocumento($FiltroDocumento)
    {
        $new = clone $this;
        $new->FiltroDocumento = $FiltroDocumento;

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
     * @return LeggiDocumentoPlus
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
     * @return LeggiDocumentoPlus
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

