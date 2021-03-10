<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfHistory implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\History
     */
    private $History = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\History $History
     */
    public function __construct($History)
    {
        $this->History = $History;
    }

    /**
     * @return \ArchiflowWSCard\Type\History
     */
    public function getHistory()
    {
        return $this->History;
    }

    /**
     * @param \ArchiflowWSCard\Type\History $History
     * @return ArrayOfHistory
     */
    public function withHistory($History)
    {
        $new = clone $this;
        $new->History = $History;

        return $new;
    }


}

