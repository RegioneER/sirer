<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArchiflowDomain implements RequestInterface
{

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var \ArchiflowWSLogin\Type\DomainType
     */
    private $Type = null;

    /**
     * Constructor
     *
     * @var string $Name
     * @var \ArchiflowWSLogin\Type\DomainType $Type
     */
    public function __construct($Name, $Type)
    {
        $this->Name = $Name;
        $this->Type = $Type;
    }

    /**
     * @return string
     */
    public function getName()
    {
        return $this->Name;
    }

    /**
     * @param string $Name
     * @return ArchiflowDomain
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\DomainType
     */
    public function getType()
    {
        return $this->Type;
    }

    /**
     * @param \ArchiflowWSLogin\Type\DomainType $Type
     * @return ArchiflowDomain
     */
    public function withType($Type)
    {
        $new = clone $this;
        $new->Type = $Type;

        return $new;
    }


}

