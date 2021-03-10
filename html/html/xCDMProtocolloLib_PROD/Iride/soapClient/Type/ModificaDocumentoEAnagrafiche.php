<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ModificaDocumentoEAnagrafiche implements RequestInterface
{

    /**
     * @var \IrideWS\Type\ModificaProtocolloIn
     */
    private $ProtoIn = null;

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
     * @var \IrideWS\Type\ModificaProtocolloIn $ProtoIn
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($ProtoIn, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->ProtoIn = $ProtoIn;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return \IrideWS\Type\ModificaProtocolloIn
     */
    public function getProtoIn()
    {
        return $this->ProtoIn;
    }

    /**
     * @param \IrideWS\Type\ModificaProtocolloIn $ProtoIn
     * @return ModificaDocumentoEAnagrafiche
     */
    public function withProtoIn($ProtoIn)
    {
        $new = clone $this;
        $new->ProtoIn = $ProtoIn;

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
     * @return ModificaDocumentoEAnagrafiche
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
     * @return ModificaDocumentoEAnagrafiche
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

