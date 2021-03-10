<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RicercaPerCodiceFiscaleMultiDBResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\ProtocolliSoggettoOut
     */
    private $RicercaPerCodiceFiscaleMultiDBResult = null;

    /**
     * @return \IrideWS\Type\ProtocolliSoggettoOut
     */
    public function getRicercaPerCodiceFiscaleMultiDBResult()
    {
        return $this->RicercaPerCodiceFiscaleMultiDBResult;
    }

    /**
     * @param \IrideWS\Type\ProtocolliSoggettoOut $RicercaPerCodiceFiscaleMultiDBResult
     * @return RicercaPerCodiceFiscaleMultiDBResponse
     */
    public function withRicercaPerCodiceFiscaleMultiDBResult($RicercaPerCodiceFiscaleMultiDBResult)
    {
        $new = clone $this;
        $new->RicercaPerCodiceFiscaleMultiDBResult = $RicercaPerCodiceFiscaleMultiDBResult;

        return $new;
    }


}

