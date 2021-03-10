<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArchiflowServiceExceptionDetail implements RequestInterface
{

    /**
     * @var int
     */
    private $Code = null;

    /**
     * @var int
     */
    private $HResultCode = null;

    /**
     * @var string
     */
    private $Message = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var \ArchiflowWSCard\Type\ArchiflowExceptionSeverity
     */
    private $Severity = null;

    /**
     * Constructor
     *
     * @var int $Code
     * @var int $HResultCode
     * @var string $Message
     * @var string $Name
     * @var \ArchiflowWSCard\Type\ArchiflowExceptionSeverity $Severity
     */
    public function __construct($Code, $HResultCode, $Message, $Name, $Severity)
    {
        $this->Code = $Code;
        $this->HResultCode = $HResultCode;
        $this->Message = $Message;
        $this->Name = $Name;
        $this->Severity = $Severity;
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
     * @return ArchiflowServiceExceptionDetail
     */
    public function withCode($Code)
    {
        $new = clone $this;
        $new->Code = $Code;

        return $new;
    }

    /**
     * @return int
     */
    public function getHResultCode()
    {
        return $this->HResultCode;
    }

    /**
     * @param int $HResultCode
     * @return ArchiflowServiceExceptionDetail
     */
    public function withHResultCode($HResultCode)
    {
        $new = clone $this;
        $new->HResultCode = $HResultCode;

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
     * @return ArchiflowServiceExceptionDetail
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
     * @return ArchiflowServiceExceptionDetail
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArchiflowExceptionSeverity
     */
    public function getSeverity()
    {
        return $this->Severity;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArchiflowExceptionSeverity $Severity
     * @return ArchiflowServiceExceptionDetail
     */
    public function withSeverity($Severity)
    {
        $new = clone $this;
        $new->Severity = $Severity;

        return $new;
    }


}

