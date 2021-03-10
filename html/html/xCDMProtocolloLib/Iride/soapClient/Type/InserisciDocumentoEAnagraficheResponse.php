<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InserisciDocumentoEAnagraficheResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\ProtocolloOut
     */
    private $InserisciDocumentoEAnagraficheResult = null;

    /**
     * @return \IrideWS\Type\ProtocolloOut
     */
    public function getInserisciDocumentoEAnagraficheResult()
    {
        return $this->InserisciDocumentoEAnagraficheResult;
    }

    /**
     * @param \IrideWS\Type\ProtocolloOut $InserisciDocumentoEAnagraficheResult
     * @return InserisciDocumentoEAnagraficheResponse
     */
    public function withInserisciDocumentoEAnagraficheResult($InserisciDocumentoEAnagraficheResult)
    {
        $new = clone $this;
        $new->InserisciDocumentoEAnagraficheResult = $InserisciDocumentoEAnagraficheResult;

        return $new;
    }


}

