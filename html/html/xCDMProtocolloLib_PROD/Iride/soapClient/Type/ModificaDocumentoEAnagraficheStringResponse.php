<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ModificaDocumentoEAnagraficheStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $ModificaDocumentoEAnagraficheStringResult = null;

    /**
     * @return string
     */
    public function getModificaDocumentoEAnagraficheStringResult()
    {
        return $this->ModificaDocumentoEAnagraficheStringResult;
    }

    /**
     * @param string $ModificaDocumentoEAnagraficheStringResult
     * @return ModificaDocumentoEAnagraficheStringResponse
     */
    public function withModificaDocumentoEAnagraficheStringResult($ModificaDocumentoEAnagraficheStringResult)
    {
        $new = clone $this;
        $new->ModificaDocumentoEAnagraficheStringResult = $ModificaDocumentoEAnagraficheStringResult;

        return $new;
    }


}

