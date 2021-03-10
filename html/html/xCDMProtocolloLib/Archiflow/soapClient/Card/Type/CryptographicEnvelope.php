<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CryptographicEnvelope implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfEnvelopeInfo
     */
    private $Items = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfEnvelopeInfo $Items
     */
    public function __construct($Items)
    {
        $this->Items = $Items;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfEnvelopeInfo
     */
    public function getItems()
    {
        return $this->Items;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfEnvelopeInfo $Items
     * @return CryptographicEnvelope
     */
    public function withItems($Items)
    {
        $new = clone $this;
        $new->Items = $Items;

        return $new;
    }


}

