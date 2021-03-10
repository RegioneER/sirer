<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RicercaAmministrazioneMultiDBResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $RicercaAmministrazioneMultiDBResult = null;

    /**
     * @return string
     */
    public function getRicercaAmministrazioneMultiDBResult()
    {
        return $this->RicercaAmministrazioneMultiDBResult;
    }

    /**
     * @param string $RicercaAmministrazioneMultiDBResult
     * @return RicercaAmministrazioneMultiDBResponse
     */
    public function withRicercaAmministrazioneMultiDBResult($RicercaAmministrazioneMultiDBResult)
    {
        $new = clone $this;
        $new->RicercaAmministrazioneMultiDBResult = $RicercaAmministrazioneMultiDBResult;

        return $new;
    }


}

