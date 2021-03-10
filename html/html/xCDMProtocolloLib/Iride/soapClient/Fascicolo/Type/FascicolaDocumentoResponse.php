<?php

namespace IrideWFFascicolo\Type;

class FascicolaDocumentoResponse
{

    /**
     * @var \IrideWFFascicolo\Type\EsitoOperazione
     */
    private $FascicolaDocumentoResult = null;

    /**
     * @return \IrideWFFascicolo\Type\EsitoOperazione
     */
    public function getFascicolaDocumentoResult()
    {
        return $this->FascicolaDocumentoResult;
    }

    /**
     * @param \IrideWFFascicolo\Type\EsitoOperazione $FascicolaDocumentoResult
     * @return FascicolaDocumentoResponse
     */
    public function withFascicolaDocumentoResult($FascicolaDocumentoResult)
    {
        $new = clone $this;
        $new->FascicolaDocumentoResult = $FascicolaDocumentoResult;

        return $new;
    }


}

