<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AggiungiAllegatiMultiDBResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $AggiungiAllegatiMultiDBResult = null;

    /**
     * @return string
     */
    public function getAggiungiAllegatiMultiDBResult()
    {
        return $this->AggiungiAllegatiMultiDBResult;
    }

    /**
     * @param string $AggiungiAllegatiMultiDBResult
     * @return AggiungiAllegatiMultiDBResponse
     */
    public function withAggiungiAllegatiMultiDBResult($AggiungiAllegatiMultiDBResult)
    {
        $new = clone $this;
        $new->AggiungiAllegatiMultiDBResult = $AggiungiAllegatiMultiDBResult;

        return $new;
    }


}

