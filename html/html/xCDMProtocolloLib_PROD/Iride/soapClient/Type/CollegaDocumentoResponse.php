<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class CollegaDocumentoResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $CollegaDocumentoResult = null;

    /**
     * @return string
     */
    public function getCollegaDocumentoResult()
    {
        return $this->CollegaDocumentoResult;
    }

    /**
     * @param string $CollegaDocumentoResult
     * @return CollegaDocumentoResponse
     */
    public function withCollegaDocumentoResult($CollegaDocumentoResult)
    {
        $new = clone $this;
        $new->CollegaDocumentoResult = $CollegaDocumentoResult;

        return $new;
    }


}

