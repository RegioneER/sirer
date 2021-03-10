<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendCardOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SendingOutValues
     */
    private $SendingValues = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SendingOutValues $SendingValues
     */
    public function __construct($SendingValues)
    {
        $this->SendingValues = $SendingValues;
    }

    /**
     * @return \ArchiflowWSCard\Type\SendingOutValues
     */
    public function getSendingValues()
    {
        return $this->SendingValues;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendingOutValues $SendingValues
     * @return SendCardOutput
     */
    public function withSendingValues($SendingValues)
    {
        $new = clone $this;
        $new->SendingValues = $SendingValues;

        return $new;
    }


}

