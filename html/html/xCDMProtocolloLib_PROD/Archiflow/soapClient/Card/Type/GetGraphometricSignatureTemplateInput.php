<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetGraphometricSignatureTemplateInput implements RequestInterface
{

    /**
     * @var int
     */
    private $DocumentType = null;

    /**
     * Constructor
     *
     * @var int $DocumentType
     */
    public function __construct($DocumentType)
    {
        $this->DocumentType = $DocumentType;
    }

    /**
     * @return int
     */
    public function getDocumentType()
    {
        return $this->DocumentType;
    }

    /**
     * @param int $DocumentType
     * @return GetGraphometricSignatureTemplateInput
     */
    public function withDocumentType($DocumentType)
    {
        $new = clone $this;
        $new->DocumentType = $DocumentType;

        return $new;
    }


}

