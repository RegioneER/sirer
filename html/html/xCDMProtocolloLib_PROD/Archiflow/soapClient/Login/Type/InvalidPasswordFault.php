<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InvalidPasswordFault implements RequestInterface
{

    /**
     * Constructor
     */
    public function __construct()
    {
    }


}

