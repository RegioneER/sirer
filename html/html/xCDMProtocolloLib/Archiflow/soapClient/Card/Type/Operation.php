<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Operation implements RequestInterface
{

    /**
     * @var string
     */
    private $Description = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * Constructor
     *
     * @var string $Description
     * @var int $Id
     */
    public function __construct($Description, $Id)
    {
        $this->Description = $Description;
        $this->Id = $Id;
    }

    /**
     * @return string
     */
    public function getDescription()
    {
        return $this->Description;
    }

    /**
     * @param string $Description
     * @return Operation
     */
    public function withDescription($Description)
    {
        $new = clone $this;
        $new->Description = $Description;

        return $new;
    }

    /**
     * @return int
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param int $Id
     * @return Operation
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }


}

