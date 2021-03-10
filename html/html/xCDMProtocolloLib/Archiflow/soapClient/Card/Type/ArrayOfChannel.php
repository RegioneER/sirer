<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfChannel implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Channel
     */
    private $Channel = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Channel $Channel
     */
    public function __construct($Channel)
    {
        $this->Channel = $Channel;
    }

    /**
     * @return \ArchiflowWSCard\Type\Channel
     */
    public function getChannel()
    {
        return $this->Channel;
    }

    /**
     * @param \ArchiflowWSCard\Type\Channel $Channel
     * @return ArrayOfChannel
     */
    public function withChannel($Channel)
    {
        $new = clone $this;
        $new->Channel = $Channel;

        return $new;
    }


}

