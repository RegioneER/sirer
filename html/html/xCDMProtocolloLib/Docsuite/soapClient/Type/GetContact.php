<?php

namespace DocsuiteWS\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetContact implements RequestInterface
{

    /**
     * @var string
     */
    private $contactMailOrCode = null;

    /**
     * @return string
     */
    public function getContactMailOrCode()
    {
        return $this->contactMailOrCode;
    }

    /**
     * @param string $contactMailOrCode
     * @return GetContact
     */
    public function withContactMailOrCode($contactMailOrCode)
    {
        $new = clone $this;
        $new->contactMailOrCode = $contactMailOrCode;

        return $new;
    }


}

