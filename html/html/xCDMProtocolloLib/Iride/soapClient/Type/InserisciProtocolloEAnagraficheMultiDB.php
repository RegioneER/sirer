<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InserisciProtocolloEAnagraficheMultiDB implements RequestInterface
{

    /**
     * @var \IrideWS\Type\ProtocolloIn
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
     * @var \IrideWS\Type\ProtocolloIn $ProtoIn
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
     * @return \IrideWS\Type\ProtocolloIn
     */
    public function getProtoIn()
    {
        return $this->ProtoIn;
    }

    /**
     * @param \IrideWS\Type\ProtocolloIn $ProtoIn
     * @return InserisciProtocolloEAnagraficheMultiDB
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
     * @return InserisciProtocolloEAnagraficheMultiDB
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
     * @return InserisciProtocolloEAnagraficheMultiDB
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

