<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAttachment implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Attachment
     */
    private $Attachment = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Attachment $Attachment
     */
    public function __construct($Attachment)
    {
        $this->Attachment = $Attachment;
    }

    /**
     * @return \ArchiflowWSCard\Type\Attachment
     */
    public function getAttachment()
    {
        return $this->Attachment;
    }

    /**
     * @param \ArchiflowWSCard\Type\Attachment $Attachment
     * @return ArrayOfAttachment
     */
    public function withAttachment($Attachment)
    {
        $new = clone $this;
        $new->Attachment = $Attachment;

        return $new;
    }


}

