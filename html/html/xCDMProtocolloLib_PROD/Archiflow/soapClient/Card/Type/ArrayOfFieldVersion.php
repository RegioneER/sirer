<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfFieldVersion implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\FieldVersion
     */
    private $FieldVersion = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\FieldVersion $FieldVersion
     */
    public function __construct($FieldVersion)
    {
        $this->FieldVersion = $FieldVersion;
    }

    /**
     * @return \ArchiflowWSCard\Type\FieldVersion
     */
    public function getFieldVersion()
    {
        return $this->FieldVersion;
    }

    /**
     * @param \ArchiflowWSCard\Type\FieldVersion $FieldVersion
     * @return ArrayOfFieldVersion
     */
    public function withFieldVersion($FieldVersion)
    {
        $new = clone $this;
        $new->FieldVersion = $FieldVersion;

        return $new;
    }


}

