<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InserisciProtocolloEAnagraficheResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\ProtocolloOut
     */
    private $InserisciProtocolloEAnagraficheResult = null;

    /**
     * @return \IrideWS\Type\ProtocolloOut
     */
    public function getInserisciProtocolloEAnagraficheResult()
    {
        return $this->InserisciProtocolloEAnagraficheResult;
    }

    /**
     * @param \IrideWS\Type\ProtocolloOut $InserisciProtocolloEAnagraficheResult
     * @return InserisciProtocolloEAnagraficheResponse
     */
    public function withInserisciProtocolloEAnagraficheResult($InserisciProtocolloEAnagraficheResult)
    {
        $new = clone $this;
        $new->InserisciProtocolloEAnagraficheResult = $InserisciProtocolloEAnagraficheResult;

        return $new;
    }


}

