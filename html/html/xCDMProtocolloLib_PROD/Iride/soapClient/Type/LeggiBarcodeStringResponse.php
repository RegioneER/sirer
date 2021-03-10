<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class LeggiBarcodeStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $LeggiBarcodeStringResult = null;

    /**
     * @return string
     */
    public function getLeggiBarcodeStringResult()
    {
        return $this->LeggiBarcodeStringResult;
    }

    /**
     * @param string $LeggiBarcodeStringResult
     * @return LeggiBarcodeStringResponse
     */
    public function withLeggiBarcodeStringResult($LeggiBarcodeStringResult)
    {
        $new = clone $this;
        $new->LeggiBarcodeStringResult = $LeggiBarcodeStringResult;

        return $new;
    }


}

