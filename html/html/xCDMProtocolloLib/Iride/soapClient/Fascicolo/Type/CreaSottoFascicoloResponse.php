<?php

namespace IrideWFFascicolo\Type;

class CreaSottoFascicoloResponse
{

    /**
     * @var \IrideWFFascicolo\Type\FascicoloOut
     */
    private $FascicoloOut = null;

    /**
     * @return \IrideWFFascicolo\Type\FascicoloOut
     */
    public function getFascicoloOut()
    {
        return $this->FascicoloOut;
    }

    /**
     * @param \IrideWFFascicolo\Type\FascicoloOut $FascicoloOut
     * @return CreaSottoFascicoloResponse
     */
    public function withFascicoloOut($FascicoloOut)
    {
        $new = clone $this;
        $new->FascicoloOut = $FascicoloOut;

        return $new;
    }


}

