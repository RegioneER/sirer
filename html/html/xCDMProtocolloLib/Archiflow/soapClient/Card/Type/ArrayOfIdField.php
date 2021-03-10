<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfIdField implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\IdField
     */
    private $IdField = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\IdField $IdField
     */
    public function __construct($IdField)
    {
        $this->IdField = $IdField;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdField
     */
    public function getIdField()
    {
        return $this->IdField;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdField $IdField
     * @return ArrayOfIdField
     */
    public function withIdField($IdField)
    {
        $new = clone $this;
        $new->IdField = $IdField;

        return $new;
    }


}

