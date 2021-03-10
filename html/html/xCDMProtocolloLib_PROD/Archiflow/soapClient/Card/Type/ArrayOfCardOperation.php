<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfCardOperation implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CardOperation
     */
    private $CardOperation = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CardOperation $CardOperation
     */
    public function __construct($CardOperation)
    {
        $this->CardOperation = $CardOperation;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardOperation
     */
    public function getCardOperation()
    {
        return $this->CardOperation;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardOperation $CardOperation
     * @return ArrayOfCardOperation
     */
    public function withCardOperation($CardOperation)
    {
        $new = clone $this;
        $new->CardOperation = $CardOperation;

        return $new;
    }


}

