<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiDocumentoPlusResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $LeggiDocumentoPlusResult = null;

    /**
     * @return string
     */
    public function getLeggiDocumentoPlusResult()
    {
        return $this->LeggiDocumentoPlusResult;
    }

    /**
     * @param string $LeggiDocumentoPlusResult
     * @return LeggiDocumentoPlusResponse
     */
    public function withLeggiDocumentoPlusResult($LeggiDocumentoPlusResult)
    {
        $new = clone $this;
        $new->LeggiDocumentoPlusResult = $LeggiDocumentoPlusResult;

        return $new;
    }


}

