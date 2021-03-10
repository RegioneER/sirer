<?php

namespace IrideWFFascicolo\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CreaFascicoloStringResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $CreaFascicoloStringResult = null;

    /**
     * @return string
     */
    public function getCreaFascicoloStringResult()
    {
        return $this->CreaFascicoloStringResult;
    }

    /**
     * @param string $CreaFascicoloStringResult
     * @return CreaFascicoloStringResponse
     */
    public function withCreaFascicoloStringResult($CreaFascicoloStringResult)
    {
        $new = clone $this;
        $new->CreaFascicoloStringResult = $CreaFascicoloStringResult;

        return $new;
    }


}

