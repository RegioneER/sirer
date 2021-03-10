<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfPhase implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Phase
     */
    private $Phase = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Phase $Phase
     */
    public function __construct($Phase)
    {
        $this->Phase = $Phase;
    }

    /**
     * @return \ArchiflowWSCard\Type\Phase
     */
    public function getPhase()
    {
        return $this->Phase;
    }

    /**
     * @param \ArchiflowWSCard\Type\Phase $Phase
     * @return ArrayOfPhase
     */
    public function withPhase($Phase)
    {
        $new = clone $this;
        $new->Phase = $Phase;

        return $new;
    }


}

