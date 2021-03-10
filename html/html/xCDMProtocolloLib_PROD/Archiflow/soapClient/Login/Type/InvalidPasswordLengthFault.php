<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvalidPasswordLengthFault implements RequestInterface
{

    /**
     * Constructor
     */
    public function __construct()
    {
    }


}

