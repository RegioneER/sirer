<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ModificaDocumentoEAnagraficheResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\ModificaProtocolloOut
     */
    private $ModificaDocumentoEAnagraficheResult = null;

    /**
     * @return \IrideWS\Type\ModificaProtocolloOut
     */
    public function getModificaDocumentoEAnagraficheResult()
    {
        return $this->ModificaDocumentoEAnagraficheResult;
    }

    /**
     * @param \IrideWS\Type\ModificaProtocolloOut $ModificaDocumentoEAnagraficheResult
     * @return ModificaDocumentoEAnagraficheResponse
     */
    public function withModificaDocumentoEAnagraficheResult($ModificaDocumentoEAnagraficheResult)
    {
        $new = clone $this;
        $new->ModificaDocumentoEAnagraficheResult = $ModificaDocumentoEAnagraficheResult;

        return $new;
    }


}

