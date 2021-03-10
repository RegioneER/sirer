<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAnnotation implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Annotation
     */
    private $Annotation = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Annotation $Annotation
     */
    public function __construct($Annotation)
    {
        $this->Annotation = $Annotation;
    }

    /**
     * @return \ArchiflowWSCard\Type\Annotation
     */
    public function getAnnotation()
    {
        return $this->Annotation;
    }

    /**
     * @param \ArchiflowWSCard\Type\Annotation $Annotation
     * @return ArrayOfAnnotation
     */
    public function withAnnotation($Annotation)
    {
        $new = clone $this;
        $new->Annotation = $Annotation;

        return $new;
    }


}

