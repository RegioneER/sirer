<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfGroup implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Group
     */
    private $Group = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Group $Group
     */
    public function __construct($Group)
    {
        $this->Group = $Group;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Group
     */
    public function getGroup()
    {
        return $this->Group;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Group $Group
     * @return ArrayOfGroup
     */
    public function withGroup($Group)
    {
        $new = clone $this;
        $new->Group = $Group;

        return $new;
    }


}

