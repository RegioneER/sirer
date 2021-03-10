<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RicercaPerCodiceFiscaleStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $RicercaPerCodiceFiscaleStringResult = null;

    /**
     * @return string
     */
    public function getRicercaPerCodiceFiscaleStringResult()
    {
        return $this->RicercaPerCodiceFiscaleStringResult;
    }

    /**
     * @param string $RicercaPerCodiceFiscaleStringResult
     * @return RicercaPerCodiceFiscaleStringResponse
     */
    public function withRicercaPerCodiceFiscaleStringResult($RicercaPerCodiceFiscaleStringResult)
    {
        $new = clone $this;
        $new->RicercaPerCodiceFiscaleStringResult = $RicercaPerCodiceFiscaleStringResult;

        return $new;
    }


}

