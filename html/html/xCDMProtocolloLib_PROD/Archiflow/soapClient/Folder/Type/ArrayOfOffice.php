<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfOffice implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Office
     */
    private $Office = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Office $Office
     */
    public function __construct($Office)
    {
        $this->Office = $Office;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Office
     */
    public function getOffice()
    {
        return $this->Office;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Office $Office
     * @return ArrayOfOffice
     */
    public function withOffice($Office)
    {
        $new = clone $this;
        $new->Office = $Office;

        return $new;
    }


}

