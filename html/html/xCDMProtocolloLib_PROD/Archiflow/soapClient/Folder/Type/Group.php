<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Group implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfUser
     */
    private $Users = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $Users
     */
    public function __construct($Users)
    {
        $this->Users = $Users;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfUser
     */
    public function getUsers()
    {
        return $this->Users;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfUser $Users
     * @return Group
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }


}

