<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfOffice implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Office
     */
    private $Office = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Office $Office
     */
    public function __construct($Office)
    {
        $this->Office = $Office;
    }

    /**
     * @return \ArchiflowWSCard\Type\Office
     */
    public function getOffice()
    {
        return $this->Office;
    }

    /**
     * @param \ArchiflowWSCard\Type\Office $Office
     * @return ArrayOfOffice
     */
    public function withOffice($Office)
    {
        $new = clone $this;
        $new->Office = $Office;

        return $new;
    }


}

