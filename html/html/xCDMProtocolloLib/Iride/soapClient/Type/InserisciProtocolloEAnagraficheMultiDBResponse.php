<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InserisciProtocolloEAnagraficheMultiDBResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\ProtocolloOut
     */
    private $InserisciProtocolloEAnagraficheMultiDBResult = null;

    /**
     * @return \IrideWS\Type\ProtocolloOut
     */
    public function getInserisciProtocolloEAnagraficheMultiDBResult()
    {
        return $this->InserisciProtocolloEAnagraficheMultiDBResult;
    }

    /**
     * @param \IrideWS\Type\ProtocolloOut $InserisciProtocolloEAnagraficheMultiDBResult
     * @return InserisciProtocolloEAnagraficheMultiDBResponse
     */
    public function withInserisciProtocolloEAnagraficheMultiDBResult($InserisciProtocolloEAnagraficheMultiDBResult)
    {
        $new = clone $this;
        $new->InserisciProtocolloEAnagraficheMultiDBResult = $InserisciProtocolloEAnagraficheMultiDBResult;

        return $new;
    }


}

