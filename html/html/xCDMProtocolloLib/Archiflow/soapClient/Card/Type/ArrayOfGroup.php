<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfGroup implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Group
     */
    private $Group = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Group $Group
     */
    public function __construct($Group)
    {
        $this->Group = $Group;
    }

    /**
     * @return \ArchiflowWSCard\Type\Group
     */
    public function getGroup()
    {
        return $this->Group;
    }

    /**
     * @param \ArchiflowWSCard\Type\Group $Group
     * @return ArrayOfGroup
     */
    public function withGroup($Group)
    {
        $new = clone $this;
        $new->Group = $Group;

        return $new;
    }


}

