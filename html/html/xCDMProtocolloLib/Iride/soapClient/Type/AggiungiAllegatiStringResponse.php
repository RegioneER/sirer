<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AggiungiAllegatiStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $AggiungiAllegatiStringResult = null;

    /**
     * @return string
     */
    public function getAggiungiAllegatiStringResult()
    {
        return $this->AggiungiAllegatiStringResult;
    }

    /**
     * @param string $AggiungiAllegatiStringResult
     * @return AggiungiAllegatiStringResponse
     */
    public function withAggiungiAllegatiStringResult($AggiungiAllegatiStringResult)
    {
        $new = clone $this;
        $new->AggiungiAllegatiStringResult = $AggiungiAllegatiStringResult;

        return $new;
    }


}

