<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InserisciDocumentoDaDMResponse implements ResultInterface
{

    /**
     * @var \IrideWS\Type\DocumentumOut
     */
    private $DocumentumOut = null;

    /**
     * @return \IrideWS\Type\DocumentumOut
     */
    public function getDocumentumOut()
    {
        return $this->DocumentumOut;
    }

    /**
     * @param \IrideWS\Type\DocumentumOut $DocumentumOut
     * @return InserisciDocumentoDaDMResponse
     */
    public function withDocumentumOut($DocumentumOut)
    {
        $new = clone $this;
        $new->DocumentumOut = $DocumentumOut;

        return $new;
    }


}

