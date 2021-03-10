<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocumentTypesOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentType
     */
    private $DocumentTypes = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentType $DocumentTypes
     */
    public function __construct($DocumentTypes)
    {
        $this->DocumentTypes = $DocumentTypes;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfDocumentType
     */
    public function getDocumentTypes()
    {
        return $this->DocumentTypes;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfDocumentType $DocumentTypes
     * @return GetDocumentTypesOutput
     */
    public function withDocumentTypes($DocumentTypes)
    {
        $new = clone $this;
        $new->DocumentTypes = $DocumentTypes;

        return $new;
    }


}

