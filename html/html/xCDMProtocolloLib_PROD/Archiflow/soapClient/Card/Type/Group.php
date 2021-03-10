<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Group implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $Users = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfUser $Users
     */
    public function __construct($Users)
    {
        $this->Users = $Users;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfUser
     */
    public function getUsers()
    {
        return $this->Users;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfUser $Users
     * @return Group
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }


}

