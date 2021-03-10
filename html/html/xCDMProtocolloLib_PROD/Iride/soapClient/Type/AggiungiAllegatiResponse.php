<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AggiungiAllegatiResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $AggiungiAllegatiResult = null;

    /**
     * @return string
     */
    public function getAggiungiAllegatiResult()
    {
        return $this->AggiungiAllegatiResult;
    }

    /**
     * @param string $AggiungiAllegatiResult
     * @return AggiungiAllegatiResponse
     */
    public function withAggiungiAllegatiResult($AggiungiAllegatiResult)
    {
        $new = clone $this;
        $new->AggiungiAllegatiResult = $AggiungiAllegatiResult;

        return $new;
    }


}

