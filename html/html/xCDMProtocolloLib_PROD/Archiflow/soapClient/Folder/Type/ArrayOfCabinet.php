<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfCabinet implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Cabinet
     */
    private $Cabinet = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Cabinet $Cabinet
     */
    public function __construct($Cabinet)
    {
        $this->Cabinet = $Cabinet;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Cabinet
     */
    public function getCabinet()
    {
        return $this->Cabinet;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Cabinet $Cabinet
     * @return ArrayOfCabinet
     */
    public function withCabinet($Cabinet)
    {
        $new = clone $this;
        $new->Cabinet = $Cabinet;

        return $new;
    }


}

