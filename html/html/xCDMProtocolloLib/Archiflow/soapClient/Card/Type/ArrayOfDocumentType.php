<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfDocumentType implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\DocumentType
     */
    private $DocumentType = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\DocumentType $DocumentType
     */
    public function __construct($DocumentType)
    {
        $this->DocumentType = $DocumentType;
    }

    /**
     * @return \ArchiflowWSCard\Type\DocumentType
     */
    public function getDocumentType()
    {
        return $this->DocumentType;
    }

    /**
     * @param \ArchiflowWSCard\Type\DocumentType $DocumentType
     * @return ArrayOfDocumentType
     */
    public function withDocumentType($DocumentType)
    {
        $new = clone $this;
        $new->DocumentType = $DocumentType;

        return $new;
    }


}

