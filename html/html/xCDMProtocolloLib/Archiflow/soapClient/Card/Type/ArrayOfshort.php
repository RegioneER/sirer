<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfshort implements RequestInterface
{

    /**
     * @var int
     */
    private $short = null;

    /**
     * Constructor
     *
     * @var int $short
     */
    public function __construct($short)
    {
        $this->short = $short;
    }

    /**
     * @return int
     */
    public function getShort()
    {
        return $this->short;
    }

    /**
     * @param int $short
     * @return ArrayOfshort
     */
    public function withShort($short)
    {
        $new = clone $this;
        $new->short = $short;

        return $new;
    }


}

