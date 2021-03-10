<?php

namespace IrideWFFascicolo\Type;

class ModificaFascicoloResponse
{

    /**
     * @var \IrideWFFascicolo\Type\EsitoOperazione
     */
    private $ModificaFascicoloResult = null;

    /**
     * @return \IrideWFFascicolo\Type\EsitoOperazione
     */
    public function getModificaFascicoloResult()
    {
        return $this->ModificaFascicoloResult;
    }

    /**
     * @param \IrideWFFascicolo\Type\EsitoOperazione $ModificaFascicoloResult
     * @return ModificaFascicoloResponse
     */
    public function withModificaFascicoloResult($ModificaFascicoloResult)
    {
        $new = clone $this;
        $new->ModificaFascicoloResult = $ModificaFascicoloResult;

        return $new;
    }


}

