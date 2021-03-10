<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfEnvelopeInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\EnvelopeInfo
     */
    private $EnvelopeInfo = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\EnvelopeInfo $EnvelopeInfo
     */
    public function __construct($EnvelopeInfo)
    {
        $this->EnvelopeInfo = $EnvelopeInfo;
    }

    /**
     * @return \ArchiflowWSCard\Type\EnvelopeInfo
     */
    public function getEnvelopeInfo()
    {
        return $this->EnvelopeInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\EnvelopeInfo $EnvelopeInfo
     * @return ArrayOfEnvelopeInfo
     */
    public function withEnvelopeInfo($EnvelopeInfo)
    {
        $new = clone $this;
        $new->EnvelopeInfo = $EnvelopeInfo;

        return $new;
    }


}

