<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAdditive implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Additive
     */
    private $Additive = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Additive $Additive
     */
    public function __construct($Additive)
    {
        $this->Additive = $Additive;
    }

    /**
     * @return \ArchiflowWSCard\Type\Additive
     */
    public function getAdditive()
    {
        return $this->Additive;
    }

    /**
     * @param \ArchiflowWSCard\Type\Additive $Additive
     * @return ArrayOfAdditive
     */
    public function withAdditive($Additive)
    {
        $new = clone $this;
        $new->Additive = $Additive;

        return $new;
    }


}

