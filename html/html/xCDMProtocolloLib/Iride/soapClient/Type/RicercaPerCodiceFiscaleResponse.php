<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RicercaPerCodiceFiscaleResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\ProtocolliSoggettoOut
     */
    private $RicercaPerCodiceFiscaleResult = null;

    /**
     * @return \IrideWS\Type\ProtocolliSoggettoOut
     */
    public function getRicercaPerCodiceFiscaleResult()
    {
        return $this->RicercaPerCodiceFiscaleResult;
    }

    /**
     * @param \IrideWS\Type\ProtocolliSoggettoOut $RicercaPerCodiceFiscaleResult
     * @return RicercaPerCodiceFiscaleResponse
     */
    public function withRicercaPerCodiceFiscaleResult($RicercaPerCodiceFiscaleResult)
    {
        $new = clone $this;
        $new->RicercaPerCodiceFiscaleResult = $RicercaPerCodiceFiscaleResult;

        return $new;
    }


}

