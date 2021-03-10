<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiCopieResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $LeggiCopieResult = null;

    /**
     * @return string
     */
    public function getLeggiCopieResult()
    {
        return $this->LeggiCopieResult;
    }

    /**
     * @param string $LeggiCopieResult
     * @return LeggiCopieResponse
     */
    public function withLeggiCopieResult($LeggiCopieResult)
    {
        $new = clone $this;
        $new->LeggiCopieResult = $LeggiCopieResult;

        return $new;
    }


}

