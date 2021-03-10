<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ProtocolCardResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ProtocolCardOutput
     */
    private $ProtocolCardResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ProtocolCardOutput
     */
    public function getProtocolCardResult()
    {
        return $this->ProtocolCardResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ProtocolCardOutput $ProtocolCardResult
     * @return ProtocolCardResponse
     */
    public function withProtocolCardResult($ProtocolCardResult)
    {
        $new = clone $this;
        $new->ProtocolCardResult = $ProtocolCardResult;

        return $new;
    }


}

