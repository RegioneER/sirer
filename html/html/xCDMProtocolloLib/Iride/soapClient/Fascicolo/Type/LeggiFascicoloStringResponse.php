<?php

namespace IrideWFFascicolo\Type;

class LeggiFascicoloStringResponse
{

    /**
     * @var string
     */
    private $LeggiFascicoloStringResult = null;

    /**
     * @return string
     */
    public function getLeggiFascicoloStringResult()
    {
        return $this->LeggiFascicoloStringResult;
    }

    /**
     * @param string $LeggiFascicoloStringResult
     * @return LeggiFascicoloStringResponse
     */
    public function withLeggiFascicoloStringResult($LeggiFascicoloStringResult)
    {
        $new = clone $this;
        $new->LeggiFascicoloStringResult = $LeggiFascicoloStringResult;

        return $new;
    }


}

