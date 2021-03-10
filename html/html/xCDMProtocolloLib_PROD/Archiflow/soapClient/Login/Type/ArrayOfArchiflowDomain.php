<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfArchiflowDomain implements RequestInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\ArchiflowDomain
     */
    private $ArchiflowDomain = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSLogin\Type\ArchiflowDomain $ArchiflowDomain
     */
    public function __construct($ArchiflowDomain)
    {
        $this->ArchiflowDomain = $ArchiflowDomain;
    }

    /**
     * @return \ArchiflowWSLogin\Type\ArchiflowDomain
     */
    public function getArchiflowDomain()
    {
        return $this->ArchiflowDomain;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ArchiflowDomain $ArchiflowDomain
     * @return ArrayOfArchiflowDomain
     */
    public function withArchiflowDomain($ArchiflowDomain)
    {
        $new = clone $this;
        $new->ArchiflowDomain = $ArchiflowDomain;

        return $new;
    }


}

