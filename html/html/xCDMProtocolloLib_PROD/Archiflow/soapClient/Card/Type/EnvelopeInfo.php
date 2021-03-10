<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class EnvelopeInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SignatureInfo
     */
    private $Signature = null;

    /**
     * @var \ArchiflowWSCard\Type\TimeStampInfo
     */
    private $TimeStamp = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SignatureInfo $Signature
     * @var \ArchiflowWSCard\Type\TimeStampInfo $TimeStamp
     */
    public function __construct($Signature, $TimeStamp)
    {
        $this->Signature = $Signature;
        $this->TimeStamp = $TimeStamp;
    }

    /**
     * @return \ArchiflowWSCard\Type\SignatureInfo
     */
    public function getSignature()
    {
        return $this->Signature;
    }

    /**
     * @param \ArchiflowWSCard\Type\SignatureInfo $Signature
     * @return EnvelopeInfo
     */
    public function withSignature($Signature)
    {
        $new = clone $this;
        $new->Signature = $Signature;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\TimeStampInfo
     */
    public function getTimeStamp()
    {
        return $this->TimeStamp;
    }

    /**
     * @param \ArchiflowWSCard\Type\TimeStampInfo $TimeStamp
     * @return EnvelopeInfo
     */
    public function withTimeStamp($TimeStamp)
    {
        $new = clone $this;
        $new->TimeStamp = $TimeStamp;

        return $new;
    }


}

