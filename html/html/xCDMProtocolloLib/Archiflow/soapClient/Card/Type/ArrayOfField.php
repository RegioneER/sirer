<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfField implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Field
     */
    private $Field = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Field $Field
     */
    /*
    public function __construct($Field)
    {
        $this->Field = $Field;
    }
    */
    /**
     * Constructor
     */
    public function __construct()
    {
        $this->Field = array();
    }

    /**
     * @return \ArchiflowWSCard\Type\Field
     */
    public function getField()
    {
        return $this->Field;
    }

    /**
     * @param \ArchiflowWSCard\Type\Field $Field
     * @return ArrayOfField
     */
    public function withField($Field)
    {
        $new = clone $this;
        $new->Field = $Field;

        return $new;
    }

    /**
     * @param Field $Field
     */
    public function setField(Field $Field)
    {
        $this->Field = $Field;
    }
    public function setFieldArray(Field $Field)
    {
        if (!is_array($this->Field)){
            $cField = $this->Field;
            $this->Field = array();
            if (is_object($cField)){
                $this->Field[] = $cField;
            }
        }
        $this->Field[] = $Field;
    }



}

