<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvalidSessionFault implements RequestInterface
{

    /**
     * Constructor
     */
    public function __construct()
    {
    }


}

