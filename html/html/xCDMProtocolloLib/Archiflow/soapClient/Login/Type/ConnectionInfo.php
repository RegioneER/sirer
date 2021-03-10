<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ConnectionInfo implements RequestInterface
{

    /**
     * @var int
     */
    private $ClientType = null;

    /**
     * @var string
     */
    private $DateFormat = null;

    /**
     * @var int
     */
    private $ExecutiveOfficeCode = null;

    /**
     * @var \ArchiflowWSLogin\Type\Language
     */
    private $Language = null;

    /**
     * @var string
     */
    private $LoginTicket = null;

    /**
     * @var \ArchiflowWSLogin\Type\LoginMode
     */
    private $Mode = null;

    /**
     * @var string
     */
    private $NewPassword = null;

    /**
     * @var string
     */
    private $SecurityToken = null;

    /**
     * @var string
     */
    private $SystemDomain = null;

    /**
     * @var string
     */
    private $TokenSess = null;

    /**
     * @var bool
     */
    private $UseSystemUser = null;

    /**
     * @var string
     */
    private $WorkflowDomain = null;


    /*
    public enum Language : int {

        [System.Runtime.Serialization.EnumMemberAttribute()]
        Unknown = -1,

        [System.Runtime.Serialization.EnumMemberAttribute()]
        Italian = 0,

        [System.Runtime.Serialization.EnumMemberAttribute()]
        English = 1,

        [System.Runtime.Serialization.EnumMemberAttribute()]
        German = 2,

        [System.Runtime.Serialization.EnumMemberAttribute()]
        French = 3,

        [System.Runtime.Serialization.EnumMemberAttribute()]
        Spanish = 4,

        [System.Runtime.Serialization.EnumMemberAttribute()]
        Portuguese = 5,

        [System.Runtime.Serialization.EnumMemberAttribute()]
        Brasilian = 6,

        [System.Runtime.Serialization.EnumMemberAttribute()]
        Romanian = 7,
    }
    */

    /**
     * Constructor
     *
     * @var int $ClientType
     * @var string $DateFormat
     * @var int $ExecutiveOfficeCode
     * @var \ArchiflowWSLogin\Type\Language $Language
     * @var string $LoginTicket
     * @var \ArchiflowWSLogin\Type\LoginMode $Mode
     * @var string $NewPassword
     * @var string $SecurityToken
     * @var string $SystemDomain
     * @var string $TokenSess
     * @var bool $UseSystemUser
     * @var string $WorkflowDomain
     */
    public function __construct($ClientType, $DateFormat, $ExecutiveOfficeCode, $Language, $LoginTicket, $Mode, $NewPassword, $SecurityToken, $SystemDomain, $TokenSess, $UseSystemUser, $WorkflowDomain)
    {
        $this->ClientType = $ClientType;
        $this->DateFormat = $DateFormat;
        $this->ExecutiveOfficeCode = $ExecutiveOfficeCode;
        $this->Language = $Language;
        $this->LoginTicket = $LoginTicket;
        $this->Mode = $Mode;
        $this->NewPassword = $NewPassword;
        $this->SecurityToken = $SecurityToken;
        $this->SystemDomain = $SystemDomain;
        $this->TokenSess = $TokenSess;
        $this->UseSystemUser = $UseSystemUser;
        $this->WorkflowDomain = $WorkflowDomain;
    }

    /**
     * @return int
     */
    public function getClientType()
    {
        return $this->ClientType;
    }

    /**
     * @param int $ClientType
     * @return ConnectionInfo
     */
    public function withClientType($ClientType)
    {
        $new = clone $this;
        $new->ClientType = $ClientType;

        return $new;
    }

    /**
     * @return string
     */
    public function getDateFormat()
    {
        return $this->DateFormat;
    }

    /**
     * @param string $DateFormat
     * @return ConnectionInfo
     */
    public function withDateFormat($DateFormat)
    {
        $new = clone $this;
        $new->DateFormat = $DateFormat;

        return $new;
    }

    /**
     * @return int
     */
    public function getExecutiveOfficeCode()
    {
        return $this->ExecutiveOfficeCode;
    }

    /**
     * @param int $ExecutiveOfficeCode
     * @return ConnectionInfo
     */
    public function withExecutiveOfficeCode($ExecutiveOfficeCode)
    {
        $new = clone $this;
        $new->ExecutiveOfficeCode = $ExecutiveOfficeCode;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\Language
     */
    public function getLanguage()
    {
        return $this->Language;
    }

    /**
     * @param \ArchiflowWSLogin\Type\Language $Language
     * @return ConnectionInfo
     */
    public function withLanguage($Language)
    {
        $new = clone $this;
        $new->Language = $Language;

        return $new;
    }

    /**
     * @return string
     */
    public function getLoginTicket()
    {
        return $this->LoginTicket;
    }

    /**
     * @param string $LoginTicket
     * @return ConnectionInfo
     */
    public function withLoginTicket($LoginTicket)
    {
        $new = clone $this;
        $new->LoginTicket = $LoginTicket;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\LoginMode
     */
    public function getMode()
    {
        return $this->Mode;
    }

    /**
     * @param \ArchiflowWSLogin\Type\LoginMode $Mode
     * @return ConnectionInfo
     */
    public function withMode($Mode)
    {
        $new = clone $this;
        $new->Mode = $Mode;

        return $new;
    }

    /**
     * @return string
     */
    public function getNewPassword()
    {
        return $this->NewPassword;
    }

    /**
     * @param string $NewPassword
     * @return ConnectionInfo
     */
    public function withNewPassword($NewPassword)
    {
        $new = clone $this;
        $new->NewPassword = $NewPassword;

        return $new;
    }

    /**
     * @return string
     */
    public function getSecurityToken()
    {
        return $this->SecurityToken;
    }

    /**
     * @param string $SecurityToken
     * @return ConnectionInfo
     */
    public function withSecurityToken($SecurityToken)
    {
        $new = clone $this;
        $new->SecurityToken = $SecurityToken;

        return $new;
    }

    /**
     * @return string
     */
    public function getSystemDomain()
    {
        return $this->SystemDomain;
    }

    /**
     * @param string $SystemDomain
     * @return ConnectionInfo
     */
    public function withSystemDomain($SystemDomain)
    {
        $new = clone $this;
        $new->SystemDomain = $SystemDomain;

        return $new;
    }

    /**
     * @return string
     */
    public function getTokenSess()
    {
        return $this->TokenSess;
    }

    /**
     * @param string $TokenSess
     * @return ConnectionInfo
     */
    public function withTokenSess($TokenSess)
    {
        $new = clone $this;
        $new->TokenSess = $TokenSess;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUseSystemUser()
    {
        return $this->UseSystemUser;
    }

    /**
     * @param bool $UseSystemUser
     * @return ConnectionInfo
     */
    public function withUseSystemUser($UseSystemUser)
    {
        $new = clone $this;
        $new->UseSystemUser = $UseSystemUser;

        return $new;
    }

    /**
     * @return string
     */
    public function getWorkflowDomain()
    {
        return $this->WorkflowDomain;
    }

    /**
     * @param string $WorkflowDomain
     * @return ConnectionInfo
     */
    public function withWorkflowDomain($WorkflowDomain)
    {
        $new = clone $this;
        $new->WorkflowDomain = $WorkflowDomain;

        return $new;
    }


}

