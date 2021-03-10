<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RicercaAmministrazioneResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $RicercaAmministrazioneResult = null;

    /**
     * @return string
     */
    public function getRicercaAmministrazioneResult()
    {
        return $this->RicercaAmministrazioneResult;
    }

    /**
     * @param string $RicercaAmministrazioneResult
     * @return RicercaAmministrazioneResponse
     */
    public function withRicercaAmministrazioneResult($RicercaAmministrazioneResult)
    {
        $new = clone $this;
        $new->RicercaAmministrazioneResult = $RicercaAmministrazioneResult;

        return $new;
    }


}

