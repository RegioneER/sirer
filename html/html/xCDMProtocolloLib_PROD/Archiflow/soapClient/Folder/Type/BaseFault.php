<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class BaseFault implements RequestInterface
{

    /**
     * @var int
     */
    private $InternalCode = null;

    /**
     * @var bool
     */
    private $IsComErrorInternalCode = null;

    /**
     * @var string
     */
    private $Message = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * Constructor
     *
     * @var int $InternalCode
     * @var bool $IsComErrorInternalCode
     * @var string $Message
     * @var string $Name
     */
    public function __construct($InternalCode, $IsComErrorInternalCode, $Message, $Name)
    {
        $this->InternalCode = $InternalCode;
        $this->IsComErrorInternalCode = $IsComErrorInternalCode;
        $this->Message = $Message;
        $this->Name = $Name;
    }

    /**
     * @return int
     */
    public function getInternalCode()
    {
        return $this->InternalCode;
    }

    /**
     * @param int $InternalCode
     * @return BaseFault
     */
    public function withInternalCode($InternalCode)
    {
        $new = clone $this;
        $new->InternalCode = $InternalCode;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsComErrorInternalCode()
    {
        return $this->IsComErrorInternalCode;
    }

    /**
     * @param bool $IsComErrorInternalCode
     * @return BaseFault
     */
    public function withIsComErrorInternalCode($IsComErrorInternalCode)
    {
        $new = clone $this;
        $new->IsComErrorInternalCode = $IsComErrorInternalCode;

        return $new;
    }

    /**
     * @return string
     */
    public function getMessage()
    {
        return $this->Message;
    }

    /**
     * @param string $Message
     * @return BaseFault
     */
    public function withMessage($Message)
    {
        $new = clone $this;
        $new->Message = $Message;

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
     * @return BaseFault
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }


}

