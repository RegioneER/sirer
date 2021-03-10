<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CopiaCreata implements RequestInterface
{

    /**
     * @var int
     */
    private $IdDocumentoCopia = null;

    /**
     * @var string
     */
    private $Carico = null;

    /**
     * Constructor
     *
     * @var int $IdDocumentoCopia
     * @var string $Carico
     */
    public function __construct($IdDocumentoCopia, $Carico)
    {
        $this->IdDocumentoCopia = $IdDocumentoCopia;
        $this->Carico = $Carico;
    }

    /**
     * @return int
     */
    public function getIdDocumentoCopia()
    {
        return $this->IdDocumentoCopia;
    }

    /**
     * @param int $IdDocumentoCopia
     * @return CopiaCreata
     */
    public function withIdDocumentoCopia($IdDocumentoCopia)
    {
        $new = clone $this;
        $new->IdDocumentoCopia = $IdDocumentoCopia;

        return $new;
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
     * @return CopiaCreata
     */
    public function withCarico($Carico)
    {
        $new = clone $this;
        $new->Carico = $Carico;

        return $new;
    }


}

