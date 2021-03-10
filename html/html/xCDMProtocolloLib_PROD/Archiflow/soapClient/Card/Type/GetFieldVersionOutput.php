<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetFieldVersionOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfFieldVersion
     */
    private $Fields = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfFieldVersion $Fields
     */
    public function __construct($Fields)
    {
        $this->Fields = $Fields;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfFieldVersion
     */
    public function getFields()
    {
        return $this->Fields;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfFieldVersion $Fields
     * @return GetFieldVersionOutput
     */
    public function withFields($Fields)
    {
        $new = clone $this;
        $new->Fields = $Fields;

        return $new;
    }


}

