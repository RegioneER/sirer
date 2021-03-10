<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class MoveCardDocAndAttachments implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\MoveCardDocAndAttachmentsInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\MoveCardDocAndAttachmentsInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSCard\Type\MoveCardDocAndAttachmentsInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSCard\Type\MoveCardDocAndAttachmentsInput $paramIn
     * @return MoveCardDocAndAttachments
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

