<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfUser implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\User
     */
    private $User = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\User $User
     */
    public function __construct($User)
    {
        $this->User = $User;
    }

    /**
     * @return \ArchiflowWSFolder\Type\User
     */
    public function getUser()
    {
        return $this->User;
    }

    /**
     * @param \ArchiflowWSFolder\Type\User $User
     * @return ArrayOfUser
     */
    public function withUser($User)
    {
        $new = clone $this;
        $new->User = $User;

        return $new;
    }


}

