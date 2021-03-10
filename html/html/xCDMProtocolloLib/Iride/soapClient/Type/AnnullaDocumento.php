<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AnnullaDocumento implements RequestInterface
{

    /**
     * @var string
     */
    private $AnnullaDocumentoIn = null;

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
     * @var string $AnnullaDocumentoIn
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($AnnullaDocumentoIn, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->AnnullaDocumentoIn = $AnnullaDocumentoIn;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getAnnullaDocumentoIn()
    {
        return $this->AnnullaDocumentoIn;
    }

    /**
     * @param string $AnnullaDocumentoIn
     * @return AnnullaDocumento
     */
    public function withAnnullaDocumentoIn($AnnullaDocumentoIn)
    {
        $new = clone $this;
        $new->AnnullaDocumentoIn = $AnnullaDocumentoIn;

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
     * @return AnnullaDocumento
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
     * @return AnnullaDocumento
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

