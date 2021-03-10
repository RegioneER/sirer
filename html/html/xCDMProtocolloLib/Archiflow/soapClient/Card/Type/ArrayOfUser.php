<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfUser implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\User
     */
    private $User = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\User $User
     */
    public function __construct($User)
    {
        $this->User = $User;
    }

    /**
     * @return \ArchiflowWSCard\Type\User
     */
    public function getUser()
    {
        return $this->User;
    }

    /**
     * @param \ArchiflowWSCard\Type\User $User
     * @return ArrayOfUser
     */
    public function withUser($User)
    {
        $new = clone $this;
        $new->User = $User;

        return $new;
    }


}

