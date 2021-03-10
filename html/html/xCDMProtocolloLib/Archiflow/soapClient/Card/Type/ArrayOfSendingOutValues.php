<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfSendingOutValues implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SendingOutValues
     */
    private $SendingOutValues = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SendingOutValues $SendingOutValues
     */
    public function __construct($SendingOutValues)
    {
        $this->SendingOutValues = $SendingOutValues;
    }

    /**
     * @return \ArchiflowWSCard\Type\SendingOutValues
     */
    public function getSendingOutValues()
    {
        return $this->SendingOutValues;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendingOutValues $SendingOutValues
     * @return ArrayOfSendingOutValues
     */
    public function withSendingOutValues($SendingOutValues)
    {
        $new = clone $this;
        $new->SendingOutValues = $SendingOutValues;

        return $new;
    }


}

