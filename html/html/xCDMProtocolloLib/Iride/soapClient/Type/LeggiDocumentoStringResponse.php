<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiDocumentoStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $LeggiDocumentoStringResult = null;

    /**
     * @return string
     */
    public function getLeggiDocumentoStringResult()
    {
        return $this->LeggiDocumentoStringResult;
    }

    /**
     * @param string $LeggiDocumentoStringResult
     * @return LeggiDocumentoStringResponse
     */
    public function withLeggiDocumentoStringResult($LeggiDocumentoStringResult)
    {
        $new = clone $this;
        $new->LeggiDocumentoStringResult = $LeggiDocumentoStringResult;

        return $new;
    }


}

