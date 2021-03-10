<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InserisciDatiUtenteResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\EsitoOperazione
     */
    private $InserisciDatiUtenteResult = null;

    /**
     * @return \IrideWS\Type\EsitoOperazione
     */
    public function getInserisciDatiUtenteResult()
    {
        return $this->InserisciDatiUtenteResult;
    }

    /**
     * @param \IrideWS\Type\EsitoOperazione $InserisciDatiUtenteResult
     * @return InserisciDatiUtenteResponse
     */
    public function withInserisciDatiUtenteResult($InserisciDatiUtenteResult)
    {
        $new = clone $this;
        $new->InserisciDatiUtenteResult = $InserisciDatiUtenteResult;

        return $new;
    }


}

