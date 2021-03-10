<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfguid implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Guid
     */
    private $guid = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Guid $guid
     */
    public function __construct($guid)
    {
        $this->guid = $guid;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Guid
     */
    public function getGuid()
    {
        return $this->guid;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Guid $guid
     * @return ArrayOfguid
     */
    public function withGuid($guid)
    {
        $new = clone $this;
        $new->guid = $guid;

        return $new;
    }


}

