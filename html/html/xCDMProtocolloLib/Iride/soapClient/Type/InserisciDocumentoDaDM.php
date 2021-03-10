<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InserisciDocumentoDaDM implements RequestInterface
{

    /**
     * @var \IrideWS\Type\DocumentumIn
     */
    private $DocumentumIn = null;

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
     * @var \IrideWS\Type\DocumentumIn $DocumentumIn
     * @var string $CodiceAmministrazione
     * @var string $CodiceAOO
     */
    public function __construct($DocumentumIn, $CodiceAmministrazione, $CodiceAOO)
    {
        $this->DocumentumIn = $DocumentumIn;
        $this->CodiceAmministrazione = $CodiceAmministrazione;
        $this->CodiceAOO = $CodiceAOO;
    }

    /**
     * @return \IrideWS\Type\DocumentumIn
     */
    public function getDocumentumIn()
    {
        return $this->DocumentumIn;
    }

    /**
     * @param \IrideWS\Type\DocumentumIn $DocumentumIn
     * @return InserisciDocumentoDaDM
     */
    public function withDocumentumIn($DocumentumIn)
    {
        $new = clone $this;
        $new->DocumentumIn = $DocumentumIn;

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
     * @return InserisciDocumentoDaDM
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
     * @return InserisciDocumentoDaDM
     */
    public function withCodiceAOO($CodiceAOO)
    {
        $new = clone $this;
        $new->CodiceAOO = $CodiceAOO;

        return $new;
    }


}

