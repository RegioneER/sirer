<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAdditive implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Additive
     */
    private $Additive = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Additive $Additive
     */
    public function __construct($Additive)
    {
        $this->Additive = $Additive;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Additive
     */
    public function getAdditive()
    {
        return $this->Additive;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Additive $Additive
     * @return ArrayOfAdditive
     */
    public function withAdditive($Additive)
    {
        $new = clone $this;
        $new->Additive = $Additive;

        return $new;
    }


}

