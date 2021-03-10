<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class EliminaAllegatoResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $EliminaAllegatoResult = null;

    /**
     * @return string
     */
    public function getEliminaAllegatoResult()
    {
        return $this->EliminaAllegatoResult;
    }

    /**
     * @param string $EliminaAllegatoResult
     * @return EliminaAllegatoResponse
     */
    public function withEliminaAllegatoResult($EliminaAllegatoResult)
    {
        $new = clone $this;
        $new->EliminaAllegatoResult = $EliminaAllegatoResult;

        return $new;
    }


}

