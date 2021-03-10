<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfRecord implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Record
     */
    private $Record = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Record $Record
     */
    public function __construct($Record)
    {
        $this->Record = $Record;
    }

    /**
     * @return \ArchiflowWSCard\Type\Record
     */
    public function getRecord()
    {
        return $this->Record;
    }

    /**
     * @param \ArchiflowWSCard\Type\Record $Record
     * @return ArrayOfRecord
     */
    public function withRecord($Record)
    {
        $new = clone $this;
        $new->Record = $Record;

        return $new;
    }


}

