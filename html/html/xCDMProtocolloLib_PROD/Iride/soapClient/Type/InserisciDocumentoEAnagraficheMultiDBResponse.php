<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InserisciDocumentoEAnagraficheMultiDBResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\ProtocolloOut
     */
    private $InserisciDocumentoEAnagraficheMultiDBResult = null;

    /**
     * @return \IrideWS\Type\ProtocolloOut
     */
    public function getInserisciDocumentoEAnagraficheMultiDBResult()
    {
        return $this->InserisciDocumentoEAnagraficheMultiDBResult;
    }

    /**
     * @param \IrideWS\Type\ProtocolloOut $InserisciDocumentoEAnagraficheMultiDBResult
     * @return InserisciDocumentoEAnagraficheMultiDBResponse
     */
    public function withInserisciDocumentoEAnagraficheMultiDBResult($InserisciDocumentoEAnagraficheMultiDBResult)
    {
        $new = clone $this;
        $new->InserisciDocumentoEAnagraficheMultiDBResult = $InserisciDocumentoEAnagraficheMultiDBResult;

        return $new;
    }


}

