<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CreaCopieStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $CreaCopieStringResult = null;

    /**
     * @return string
     */
    public function getCreaCopieStringResult()
    {
        return $this->CreaCopieStringResult;
    }

    /**
     * @param string $CreaCopieStringResult
     * @return CreaCopieStringResponse
     */
    public function withCreaCopieStringResult($CreaCopieStringResult)
    {
        $new = clone $this;
        $new->CreaCopieStringResult = $CreaCopieStringResult;

        return $new;
    }


}

