<?php

namespace IrideWFFascicolo\Type;

class CreaSottoFascicoloStringResponse
{

    /**
     * @var string
     */
    private $CreaSottoFascicoloStringResult = null;

    /**
     * @return string
     */
    public function getCreaSottoFascicoloStringResult()
    {
        return $this->CreaSottoFascicoloStringResult;
    }

    /**
     * @param string $CreaSottoFascicoloStringResult
     * @return CreaSottoFascicoloStringResponse
     */
    public function withCreaSottoFascicoloStringResult($CreaSottoFascicoloStringResult)
    {
        $new = clone $this;
        $new->CreaSottoFascicoloStringResult = $CreaSottoFascicoloStringResult;

        return $new;
    }


}

