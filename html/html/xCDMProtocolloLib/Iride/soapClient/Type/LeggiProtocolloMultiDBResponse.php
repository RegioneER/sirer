<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiProtocolloMultiDBResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\DocumentoOut
     */
    private $LeggiProtocolloMultiDBResult = null;

    /**
     * @return \IrideWS\Type\DocumentoOut
     */
    public function getLeggiProtocolloMultiDBResult()
    {
        return $this->LeggiProtocolloMultiDBResult;
    }

    /**
     * @param \IrideWS\Type\DocumentoOut $LeggiProtocolloMultiDBResult
     * @return LeggiProtocolloMultiDBResponse
     */
    public function withLeggiProtocolloMultiDBResult($LeggiProtocolloMultiDBResult)
    {
        $new = clone $this;
        $new->LeggiProtocolloMultiDBResult = $LeggiProtocolloMultiDBResult;

        return $new;
    }


}

