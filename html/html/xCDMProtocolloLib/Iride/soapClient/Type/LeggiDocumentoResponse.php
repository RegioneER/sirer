<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiDocumentoResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\DocumentoOut
     */
    private $LeggiDocumentoResult = null;

    /**
     * @return \IrideWS\Type\DocumentoOut
     */
    public function getLeggiDocumentoResult()
    {
        return $this->LeggiDocumentoResult;
    }

    /**
     * @param \IrideWS\Type\DocumentoOut $LeggiDocumentoResult
     * @return LeggiDocumentoResponse
     */
    public function withLeggiDocumentoResult($LeggiDocumentoResult)
    {
        $new = clone $this;
        $new->LeggiDocumentoResult = $LeggiDocumentoResult;

        return $new;
    }


}

