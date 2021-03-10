<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CreaCopieResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\CreaCopieOut
     */
    private $CreaCopieResult = null;

    /**
     * @return \IrideWS\Type\CreaCopieOut
     */
    public function getCreaCopieResult()
    {
        return $this->CreaCopieResult;
    }

    /**
     * @param \IrideWS\Type\CreaCopieOut $CreaCopieResult
     * @return CreaCopieResponse
     */
    public function withCreaCopieResult($CreaCopieResult)
    {
        $new = clone $this;
        $new->CreaCopieResult = $CreaCopieResult;

        return $new;
    }


}

