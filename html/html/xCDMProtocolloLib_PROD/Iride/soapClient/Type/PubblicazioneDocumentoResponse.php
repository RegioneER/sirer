<?php

namespace IrideWS\Type;

use Phpro\SoapClient\Type\ResultInterface;

class PubblicazioneDocumentoResponse implements ResultInterface
{

    /**
     * @var string
     */
    private $PubblicazioneDocumentoResult = null;

    /**
     * @return string
     */
    public function getPubblicazioneDocumentoResult()
    {
        return $this->PubblicazioneDocumentoResult;
    }

    /**
     * @param string $PubblicazioneDocumentoResult
     * @return PubblicazioneDocumentoResponse
     */
    public function withPubblicazioneDocumentoResult($PubblicazioneDocumentoResult)
    {
        $new = clone $this;
        $new->PubblicazioneDocumentoResult = $PubblicazioneDocumentoResult;

        return $new;
    }


}

