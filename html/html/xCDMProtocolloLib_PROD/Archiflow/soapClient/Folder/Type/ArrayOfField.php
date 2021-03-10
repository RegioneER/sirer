<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfField implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Field
     */
    private $Field = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Field $Field
     */
    public function __construct($Field)
    {
        $this->Field = $Field;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Field
     */
    public function getField()
    {
        return $this->Field;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Field $Field
     * @return ArrayOfField
     */
    public function withField($Field)
    {
        $new = clone $this;
        $new->Field = $Field;

        return $new;
    }


}

