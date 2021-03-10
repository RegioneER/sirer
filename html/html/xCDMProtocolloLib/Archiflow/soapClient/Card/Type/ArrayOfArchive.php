<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfArchive implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Archive
     */
    private $Archive = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Archive $Archive
     */
    public function __construct($Archive)
    {
        $this->Archive = $Archive;
    }

    /**
     * @return \ArchiflowWSCard\Type\Archive
     */
    public function getArchive()
    {
        return $this->Archive;
    }

    /**
     * @param \ArchiflowWSCard\Type\Archive $Archive
     * @return ArrayOfArchive
     */
    public function withArchive($Archive)
    {
        $new = clone $this;
        $new->Archive = $Archive;

        return $new;
    }


}

