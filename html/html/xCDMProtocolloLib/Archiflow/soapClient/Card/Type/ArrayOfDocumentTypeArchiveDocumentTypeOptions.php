<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfDocumentTypeArchiveDocumentTypeOptions implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\DocumentTypeArchiveDocumentTypeOptions
     */
    private $DocumentTypeArchiveDocumentTypeOptions = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\DocumentTypeArchiveDocumentTypeOptions
     * $DocumentTypeArchiveDocumentTypeOptions
     */
    public function __construct($DocumentTypeArchiveDocumentTypeOptions)
    {
        $this->DocumentTypeArchiveDocumentTypeOptions = $DocumentTypeArchiveDocumentTypeOptions;
    }

    /**
     * @return \ArchiflowWSCard\Type\DocumentTypeArchiveDocumentTypeOptions
     */
    public function getDocumentTypeArchiveDocumentTypeOptions()
    {
        return $this->DocumentTypeArchiveDocumentTypeOptions;
    }

    /**
     * @param \ArchiflowWSCard\Type\DocumentTypeArchiveDocumentTypeOptions
     * $DocumentTypeArchiveDocumentTypeOptions
     * @return ArrayOfDocumentTypeArchiveDocumentTypeOptions
     */
    public function withDocumentTypeArchiveDocumentTypeOptions($DocumentTypeArchiveDocumentTypeOptions)
    {
        $new = clone $this;
        $new->DocumentTypeArchiveDocumentTypeOptions = $DocumentTypeArchiveDocumentTypeOptions;

        return $new;
    }


}

