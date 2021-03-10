<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocumentSignaturesInfoOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CryptographicEnvelope
     */
    private $CryptographicEnvelope = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CryptographicEnvelope $CryptographicEnvelope
     */
    public function __construct($CryptographicEnvelope)
    {
        $this->CryptographicEnvelope = $CryptographicEnvelope;
    }

    /**
     * @return \ArchiflowWSCard\Type\CryptographicEnvelope
     */
    public function getCryptographicEnvelope()
    {
        return $this->CryptographicEnvelope;
    }

    /**
     * @param \ArchiflowWSCard\Type\CryptographicEnvelope $CryptographicEnvelope
     * @return GetCardDocumentSignaturesInfoOutput
     */
    public function withCryptographicEnvelope($CryptographicEnvelope)
    {
        $new = clone $this;
        $new->CryptographicEnvelope = $CryptographicEnvelope;

        return $new;
    }


}

