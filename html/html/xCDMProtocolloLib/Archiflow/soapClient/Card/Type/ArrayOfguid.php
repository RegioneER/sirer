<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfguid implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $guid = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $guid
     */
    public function __construct($guid)
    {
        $this->guid = $guid;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getGuid()
    {
        return $this->guid;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $guid
     * @return ArrayOfguid
     */
    public function withGuid($guid)
    {
        $new = clone $this;
        $new->guid = $guid;

        return $new;
    }


}

