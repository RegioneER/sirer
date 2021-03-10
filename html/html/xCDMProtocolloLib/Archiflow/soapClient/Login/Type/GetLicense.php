<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetLicense implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     */
    public function __construct($strSessionId)
    {
        $this->strSessionId = $strSessionId;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return GetLicense
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }


}

