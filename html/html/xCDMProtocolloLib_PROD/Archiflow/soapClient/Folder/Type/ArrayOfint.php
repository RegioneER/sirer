<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfint implements RequestInterface
{

    /**
     * @var int
     */
    private $int = null;

    /**
     * Constructor
     *
     * @var int $int
     */
    public function __construct($int)
    {
        $this->int = $int;
    }

    /**
     * @return int
     */
    public function getInt()
    {
        return $this->int;
    }

    /**
     * @param int $int
     * @return ArrayOfint
     */
    public function withInt($int)
    {
        $new = clone $this;
        $new->int = $int;

        return $new;
    }


}

