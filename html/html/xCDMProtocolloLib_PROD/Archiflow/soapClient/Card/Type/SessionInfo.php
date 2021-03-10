<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SessionInfo implements RequestInterface
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
     * @var \ArchiflowWSCard\Type\ArrayOfOfficeChart
     */
    private $ExecutiveOffices = null;

    /**
     * @var \ArchiflowWSCard\Type\Language
     */
    private $Language = null;

    /**
     * @var string
     */
    private $LoginTicketUserId = null;

    /**
     * @var \ArchiflowWSCard\Type\UserLoginType
     */
    private $LoginType = null;

    /**
     * @var string
     */
    private $SessionId = null;

    /**
     * @var string
     */
    private $TokenSess = null;

    /**
     * @var string
     */
    private $VelocisDatabase = null;

    /**
     * @var string
     */
    private $VelocisServer = null;

    /**
     * @var string
     */
    private $WorkflowId = null;

    /**
     * Constructor
     *
     * @var int $ClientType
     * @var string $DateFormat
     * @var int $ExecutiveOfficeCode
     * @var \ArchiflowWSCard\Type\ArrayOfOfficeChart $ExecutiveOffices
     * @var \ArchiflowWSCard\Type\Language $Language
     * @var string $LoginTicketUserId
     * @var \ArchiflowWSCard\Type\UserLoginType $LoginType
     * @var string $SessionId
     * @var string $TokenSess
     * @var string $VelocisDatabase
     * @var string $VelocisServer
     * @var string $WorkflowId
     */
    public function __construct($ClientType, $DateFormat, $ExecutiveOfficeCode, $ExecutiveOffices, $Language, $LoginTicketUserId, $LoginType, $SessionId, $TokenSess, $VelocisDatabase, $VelocisServer, $WorkflowId)
    {
        $this->ClientType = $ClientType;
        $this->DateFormat = $DateFormat;
        $this->ExecutiveOfficeCode = $ExecutiveOfficeCode;
        $this->ExecutiveOffices = $ExecutiveOffices;
        $this->Language = $Language;
        $this->LoginTicketUserId = $LoginTicketUserId;
        $this->LoginType = $LoginType;
        $this->SessionId = $SessionId;
        $this->TokenSess = $TokenSess;
        $this->VelocisDatabase = $VelocisDatabase;
        $this->VelocisServer = $VelocisServer;
        $this->WorkflowId = $WorkflowId;
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
     * @return SessionInfo
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
     * @return SessionInfo
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
     * @return SessionInfo
     */
    public function withExecutiveOfficeCode($ExecutiveOfficeCode)
    {
        $new = clone $this;
        $new->ExecutiveOfficeCode = $ExecutiveOfficeCode;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfOfficeChart
     */
    public function getExecutiveOffices()
    {
        return $this->ExecutiveOffices;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOfficeChart $ExecutiveOffices
     * @return SessionInfo
     */
    public function withExecutiveOffices($ExecutiveOffices)
    {
        $new = clone $this;
        $new->ExecutiveOffices = $ExecutiveOffices;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Language
     */
    public function getLanguage()
    {
        return $this->Language;
    }

    /**
     * @param \ArchiflowWSCard\Type\Language $Language
     * @return SessionInfo
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
    public function getLoginTicketUserId()
    {
        return $this->LoginTicketUserId;
    }

    /**
     * @param string $LoginTicketUserId
     * @return SessionInfo
     */
    public function withLoginTicketUserId($LoginTicketUserId)
    {
        $new = clone $this;
        $new->LoginTicketUserId = $LoginTicketUserId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\UserLoginType
     */
    public function getLoginType()
    {
        return $this->LoginType;
    }

    /**
     * @param \ArchiflowWSCard\Type\UserLoginType $LoginType
     * @return SessionInfo
     */
    public function withLoginType($LoginType)
    {
        $new = clone $this;
        $new->LoginType = $LoginType;

        return $new;
    }

    /**
     * @return string
     */
    public function getSessionId()
    {
        return $this->SessionId;
    }

    /**
     * @param string $SessionId
     * @return SessionInfo
     */
    public function withSessionId($SessionId)
    {
        $new = clone $this;
        $new->SessionId = $SessionId;

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
     * @return SessionInfo
     */
    public function withTokenSess($TokenSess)
    {
        $new = clone $this;
        $new->TokenSess = $TokenSess;

        return $new;
    }

    /**
     * @return string
     */
    public function getVelocisDatabase()
    {
        return $this->VelocisDatabase;
    }

    /**
     * @param string $VelocisDatabase
     * @return SessionInfo
     */
    public function withVelocisDatabase($VelocisDatabase)
    {
        $new = clone $this;
        $new->VelocisDatabase = $VelocisDatabase;

        return $new;
    }

    /**
     * @return string
     */
    public function getVelocisServer()
    {
        return $this->VelocisServer;
    }

    /**
     * @param string $VelocisServer
     * @return SessionInfo
     */
    public function withVelocisServer($VelocisServer)
    {
        $new = clone $this;
        $new->VelocisServer = $VelocisServer;

        return $new;
    }

    /**
     * @return string
     */
    public function getWorkflowId()
    {
        return $this->WorkflowId;
    }

    /**
     * @param string $WorkflowId
     * @return SessionInfo
     */
    public function withWorkflowId($WorkflowId)
    {
        $new = clone $this;
        $new->WorkflowId = $WorkflowId;

        return $new;
    }


}

