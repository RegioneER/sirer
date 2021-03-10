<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiProtocolloStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $LeggiProtocolloStringResult = null;

    /**
     * @return string
     */
    public function getLeggiProtocolloStringResult()
    {
        return $this->LeggiProtocolloStringResult;
    }

    /**
     * @param string $LeggiProtocolloStringResult
     * @return LeggiProtocolloStringResponse
     */
    public function withLeggiProtocolloStringResult($LeggiProtocolloStringResult)
    {
        $new = clone $this;
        $new->LeggiProtocolloStringResult = $LeggiProtocolloStringResult;

        return $new;
    }


}

