<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Entity implements RequestInterface
{

    /**
     * @var bool
     */
    private $CCVisibility = null;

    /**
     * @var int
     */
    private $Code = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var bool
     */
    private $NormalVisibility = null;

    /**
     * @var bool
     */
    private $SendMail = null;

    /**
     * Constructor
     *
     * @var bool $CCVisibility
     * @var int $Code
     * @var string $Name
     * @var bool $NormalVisibility
     * @var bool $SendMail
     */
    public function __construct($CCVisibility, $Code, $Name, $NormalVisibility, $SendMail)
    {
        $this->CCVisibility = $CCVisibility;
        $this->Code = $Code;
        $this->Name = $Name;
        $this->NormalVisibility = $NormalVisibility;
        $this->SendMail = $SendMail;
    }

    /**
     * @return bool
     */
    public function getCCVisibility()
    {
        return $this->CCVisibility;
    }

    /**
     * @param bool $CCVisibility
     * @return Entity
     */
    public function withCCVisibility($CCVisibility)
    {
        $new = clone $this;
        $new->CCVisibility = $CCVisibility;

        return $new;
    }

    /**
     * @return int
     */
    public function getCode()
    {
        return $this->Code;
    }

    /**
     * @param int $Code
     * @return Entity
     */
    public function withCode($Code)
    {
        $new = clone $this;
        $new->Code = $Code;

        return $new;
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
     * @return Entity
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return bool
     */
    public function getNormalVisibility()
    {
        return $this->NormalVisibility;
    }

    /**
     * @param bool $NormalVisibility
     * @return Entity
     */
    public function withNormalVisibility($NormalVisibility)
    {
        $new = clone $this;
        $new->NormalVisibility = $NormalVisibility;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSendMail()
    {
        return $this->SendMail;
    }

    /**
     * @param bool $SendMail
     * @return Entity
     */
    public function withSendMail($SendMail)
    {
        $new = clone $this;
        $new->SendMail = $SendMail;

        return $new;
    }


}

