<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InserisciDocumentoEAnagraficheStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $InserisciDocumentoEAnagraficheStringResult = null;

    /**
     * @return string
     */
    public function getInserisciDocumentoEAnagraficheStringResult()
    {
        return $this->InserisciDocumentoEAnagraficheStringResult;
    }

    /**
     * @param string $InserisciDocumentoEAnagraficheStringResult
     * @return InserisciDocumentoEAnagraficheStringResponse
     */
    public function withInserisciDocumentoEAnagraficheStringResult($InserisciDocumentoEAnagraficheStringResult)
    {
        $new = clone $this;
        $new->InserisciDocumentoEAnagraficheStringResult = $InserisciDocumentoEAnagraficheStringResult;

        return $new;
    }


}

