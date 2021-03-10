<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiDocumentoMultiDBResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\DocumentoOut
     */
    private $LeggiDocumentoMultiDBResult = null;

    /**
     * @return \IrideWS\Type\DocumentoOut
     */
    public function getLeggiDocumentoMultiDBResult()
    {
        return $this->LeggiDocumentoMultiDBResult;
    }

    /**
     * @param \IrideWS\Type\DocumentoOut $LeggiDocumentoMultiDBResult
     * @return LeggiDocumentoMultiDBResponse
     */
    public function withLeggiDocumentoMultiDBResult($LeggiDocumentoMultiDBResult)
    {
        $new = clone $this;
        $new->LeggiDocumentoMultiDBResult = $LeggiDocumentoMultiDBResult;

        return $new;
    }


}

