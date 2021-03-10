<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AnnullaDocumentoResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $AnnullaDocumentoResult = null;

    /**
     * @return string
     */
    public function getAnnullaDocumentoResult()
    {
        return $this->AnnullaDocumentoResult;
    }

    /**
     * @param string $AnnullaDocumentoResult
     * @return AnnullaDocumentoResponse
     */
    public function withAnnullaDocumentoResult($AnnullaDocumentoResult)
    {
        $new = clone $this;
        $new->AnnullaDocumentoResult = $AnnullaDocumentoResult;

        return $new;
    }


}

