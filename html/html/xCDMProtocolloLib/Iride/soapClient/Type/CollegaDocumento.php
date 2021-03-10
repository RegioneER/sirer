<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CollegaDocumento implements RequestInterface
{

    /**
     * @var string
     */
    private $CollegaDocumentoIn = null;

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
     * @var string $CollegaDocumentoIn
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($CollegaDocumentoIn, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->CollegaDocumentoIn = $CollegaDocumentoIn;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getCollegaDocumentoIn()
    {
        return $this->CollegaDocumentoIn;
    }

    /**
     * @param string $CollegaDocumentoIn
     * @return CollegaDocumento
     */
    public function withCollegaDocumentoIn($CollegaDocumentoIn)
    {
        $new = clone $this;
        $new->CollegaDocumentoIn = $CollegaDocumentoIn;

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
     * @return CollegaDocumento
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
     * @return CollegaDocumento
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

