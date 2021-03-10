<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvalidPasswordFormatFault implements RequestInterface
{

    /**
     * Constructor
     */
    public function __construct()
    {
    }


}

