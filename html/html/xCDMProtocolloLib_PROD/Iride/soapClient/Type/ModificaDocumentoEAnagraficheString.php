<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ModificaDocumentoEAnagraficheString implements RequestInterface
{

    /**
     * @var string
     */
    private $ProtocolloInStr = null;

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
     * @var string $ProtocolloInStr
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($ProtocolloInStr, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->ProtocolloInStr = $ProtocolloInStr;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return string
     */
    public function getProtocolloInStr()
    {
        return $this->ProtocolloInStr;
    }

    /**
     * @param string $ProtocolloInStr
     * @return ModificaDocumentoEAnagraficheString
     */
    public function withProtocolloInStr($ProtocolloInStr)
    {
        $new = clone $this;
        $new->ProtocolloInStr = $ProtocolloInStr;

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
     * @return ModificaDocumentoEAnagraficheString
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
     * @return ModificaDocumentoEAnagraficheString
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

