<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetGraphometricSignatureTemplateOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Base64Binary
     */
    private $Fct = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Base64Binary $Fct
     */
    public function __construct($Fct)
    {
        $this->Fct = $Fct;
    }

    /**
     * @return \ArchiflowWSCard\Type\Base64Binary
     */
    public function getFct()
    {
        return $this->Fct;
    }

    /**
     * @param \ArchiflowWSCard\Type\Base64Binary $Fct
     * @return GetGraphometricSignatureTemplateOutput
     */
    public function withFct($Fct)
    {
        $new = clone $this;
        $new->Fct = $Fct;

        return $new;
    }


}

