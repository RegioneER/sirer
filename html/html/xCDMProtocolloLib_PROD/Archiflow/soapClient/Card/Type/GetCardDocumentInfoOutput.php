<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardDocumentInfoOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Document
     */
    private $Document = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Document $Document
     */
    public function __construct($Document)
    {
        $this->Document = $Document;
    }

    /**
     * @return \ArchiflowWSCard\Type\Document
     */
    public function getDocument()
    {
        return $this->Document;
    }

    /**
     * @param \ArchiflowWSCard\Type\Document $Document
     * @return GetCardDocumentInfoOutput
     */
    public function withDocument($Document)
    {
        $new = clone $this;
        $new->Document = $Document;

        return $new;
    }


}

