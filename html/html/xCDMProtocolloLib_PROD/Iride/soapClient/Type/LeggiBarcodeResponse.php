<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiBarcodeResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\DocumentoOut
     */
    private $LeggiBarcodeResult = null;

    /**
     * @return \IrideWS\Type\DocumentoOut
     */
    public function getLeggiBarcodeResult()
    {
        return $this->LeggiBarcodeResult;
    }

    /**
     * @param \IrideWS\Type\DocumentoOut $LeggiBarcodeResult
     * @return LeggiBarcodeResponse
     */
    public function withLeggiBarcodeResult($LeggiBarcodeResult)
    {
        $new = clone $this;
        $new->LeggiBarcodeResult = $LeggiBarcodeResult;

        return $new;
    }


}

