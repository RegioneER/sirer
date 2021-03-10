<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfKeyVersion implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\KeyVersion
     */
    private $KeyVersion = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\KeyVersion $KeyVersion
     */
    public function __construct($KeyVersion)
    {
        $this->KeyVersion = $KeyVersion;
    }

    /**
     * @return \ArchiflowWSCard\Type\KeyVersion
     */
    public function getKeyVersion()
    {
        return $this->KeyVersion;
    }

    /**
     * @param \ArchiflowWSCard\Type\KeyVersion $KeyVersion
     * @return ArrayOfKeyVersion
     */
    public function withKeyVersion($KeyVersion)
    {
        $new = clone $this;
        $new->KeyVersion = $KeyVersion;

        return $new;
    }


}

