<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiProtocolloResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\DocumentoOut
     */
    private $LeggiProtocolloResult = null;

    /**
     * @return \IrideWS\Type\DocumentoOut
     */
    public function getLeggiProtocolloResult()
    {
        return $this->LeggiProtocolloResult;
    }

    /**
     * @param \IrideWS\Type\DocumentoOut $LeggiProtocolloResult
     * @return LeggiProtocolloResponse
     */
    public function withLeggiProtocolloResult($LeggiProtocolloResult)
    {
        $new = clone $this;
        $new->LeggiProtocolloResult = $LeggiProtocolloResult;

        return $new;
    }


}

