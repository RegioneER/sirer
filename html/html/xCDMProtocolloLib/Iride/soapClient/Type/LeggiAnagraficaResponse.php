<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiAnagraficaResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $LeggiAnagraficaResult = null;

    /**
     * @return string
     */
    public function getLeggiAnagraficaResult()
    {
        return $this->LeggiAnagraficaResult;
    }

    /**
     * @param string $LeggiAnagraficaResult
     * @return LeggiAnagraficaResponse
     */
    public function withLeggiAnagraficaResult($LeggiAnagraficaResult)
    {
        $new = clone $this;
        $new->LeggiAnagraficaResult = $LeggiAnagraficaResult;

        return $new;
    }


}

