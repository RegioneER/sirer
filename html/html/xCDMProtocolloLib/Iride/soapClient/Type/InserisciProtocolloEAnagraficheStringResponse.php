<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InserisciProtocolloEAnagraficheStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $InserisciProtocolloEAnagraficheStringResult = null;

    /**
     * @return string
     */
    public function getInserisciProtocolloEAnagraficheStringResult()
    {
        return $this->InserisciProtocolloEAnagraficheStringResult;
    }

    /**
     * @param string $InserisciProtocolloEAnagraficheStringResult
     * @return InserisciProtocolloEAnagraficheStringResponse
     */
    public function withInserisciProtocolloEAnagraficheStringResult($InserisciProtocolloEAnagraficheStringResult)
    {
        $new = clone $this;
        $new->InserisciProtocolloEAnagraficheStringResult = $InserisciProtocolloEAnagraficheStringResult;

        return $new;
    }


}

