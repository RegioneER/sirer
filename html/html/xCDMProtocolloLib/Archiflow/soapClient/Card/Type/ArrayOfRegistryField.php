<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfRegistryField implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\RegistryField
     */
    private $RegistryField = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\RegistryField $RegistryField
     */
    public function __construct($RegistryField)
    {
        $this->RegistryField = $RegistryField;
    }

    /**
     * @return \ArchiflowWSCard\Type\RegistryField
     */
    public function getRegistryField()
    {
        return $this->RegistryField;
    }

    /**
     * @param \ArchiflowWSCard\Type\RegistryField $RegistryField
     * @return ArrayOfRegistryField
     */
    public function withRegistryField($RegistryField)
    {
        $new = clone $this;
        $new->RegistryField = $RegistryField;

        return $new;
    }


}

