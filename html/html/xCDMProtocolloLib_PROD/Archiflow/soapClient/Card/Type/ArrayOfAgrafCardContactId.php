<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAgrafCardContactId implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AgrafCardContactId
     */
    private $AgrafCardContactId = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AgrafCardContactId $AgrafCardContactId
     */
    public function __construct($AgrafCardContactId)
    {
        $this->AgrafCardContactId = $AgrafCardContactId;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafCardContactId
     */
    public function getAgrafCardContactId()
    {
        return $this->AgrafCardContactId;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafCardContactId $AgrafCardContactId
     * @return ArrayOfAgrafCardContactId
     */
    public function withAgrafCardContactId($AgrafCardContactId)
    {
        $new = clone $this;
        $new->AgrafCardContactId = $AgrafCardContactId;

        return $new;
    }


}

