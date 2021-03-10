<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CardOperationsOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CardOperations
     */
    private $Operations = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CardOperations $Operations
     */
    public function __construct($Operations)
    {
        $this->Operations = $Operations;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardOperations
     */
    public function getOperations()
    {
        return $this->Operations;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardOperations $Operations
     * @return CardOperationsOutput
     */
    public function withOperations($Operations)
    {
        $new = clone $this;
        $new->Operations = $Operations;

        return $new;
    }


}

