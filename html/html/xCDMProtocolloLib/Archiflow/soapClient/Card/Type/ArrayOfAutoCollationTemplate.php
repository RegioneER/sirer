<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAutoCollationTemplate implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AutoCollationTemplate
     */
    private $AutoCollationTemplate = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AutoCollationTemplate $AutoCollationTemplate
     */
    public function __construct($AutoCollationTemplate)
    {
        $this->AutoCollationTemplate = $AutoCollationTemplate;
    }

    /**
     * @return \ArchiflowWSCard\Type\AutoCollationTemplate
     */
    public function getAutoCollationTemplate()
    {
        return $this->AutoCollationTemplate;
    }

    /**
     * @param \ArchiflowWSCard\Type\AutoCollationTemplate $AutoCollationTemplate
     * @return ArrayOfAutoCollationTemplate
     */
    public function withAutoCollationTemplate($AutoCollationTemplate)
    {
        $new = clone $this;
        $new->AutoCollationTemplate = $AutoCollationTemplate;

        return $new;
    }


}

