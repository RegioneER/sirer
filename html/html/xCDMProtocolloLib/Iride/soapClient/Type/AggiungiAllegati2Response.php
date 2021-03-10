<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AggiungiAllegati2Response implements ResultInterface
{

    /**
     * @var \IrideWS\Type\AllegatiInseritiOut
     */
    private $AggiungiAllegati2Result = null;

    /**
     * @return \IrideWS\Type\AllegatiInseritiOut
     */
    public function getAggiungiAllegati2Result()
    {
        return $this->AggiungiAllegati2Result;
    }

    /**
     * @param \IrideWS\Type\AllegatiInseritiOut $AggiungiAllegati2Result
     * @return AggiungiAllegati2Response
     */
    public function withAggiungiAllegati2Result($AggiungiAllegati2Result)
    {
        $new = clone $this;
        $new->AggiungiAllegati2Result = $AggiungiAllegati2Result;

        return $new;
    }


}

