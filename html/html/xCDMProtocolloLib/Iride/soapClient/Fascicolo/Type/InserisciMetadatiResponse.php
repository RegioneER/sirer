<?php

namespace IrideWFFascicolo\Type;

class InserisciMetadatiResponse
{

    /**
     * @var \IrideWFFascicolo\Type\EsitoOperazione
     */
    private $InserisciMetadatiResult = null;

    /**
     * @return \IrideWFFascicolo\Type\EsitoOperazione
     */
    public function getInserisciMetadatiResult()
    {
        return $this->InserisciMetadatiResult;
    }

    /**
     * @param \IrideWFFascicolo\Type\EsitoOperazione $InserisciMetadatiResult
     * @return InserisciMetadatiResponse
     */
    public function withInserisciMetadatiResult($InserisciMetadatiResult)
    {
        $new = clone $this;
        $new->InserisciMetadatiResult = $InserisciMetadatiResult;

        return $new;
    }


}

