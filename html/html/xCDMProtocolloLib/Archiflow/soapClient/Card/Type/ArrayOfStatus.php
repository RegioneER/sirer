<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfStatus implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Status
     */
    private $Status = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Status $Status
     */
    public function __construct($Status)
    {
        $this->Status = $Status;
    }

    /**
     * @return \ArchiflowWSCard\Type\Status
     */
    public function getStatus()
    {
        return $this->Status;
    }

    /**
     * @param \ArchiflowWSCard\Type\Status $Status
     * @return ArrayOfStatus
     */
    public function withStatus($Status)
    {
        $new = clone $this;
        $new->Status = $Status;

        return $new;
    }


}

