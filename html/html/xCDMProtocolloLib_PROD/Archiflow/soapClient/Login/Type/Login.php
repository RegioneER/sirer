<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Login implements RequestInterface
{

    /**
     * @var string
     */
    private $strUser = null;

    /**
     * @var string
     */
    private $strPassword = null;

    /**
     * @var \ArchiflowWSLogin\Type\ConnectionInfo
     */
    private $oConnectionInfo = null;

    /**
     * Constructor
     *
     * @var string $strUser
     * @var string $strPassword
     * @var \ArchiflowWSLogin\Type\ConnectionInfo $oConnectionInfo
     */
    public function __construct($strUser, $strPassword, $oConnectionInfo)
    {
        $this->strUser = $strUser;
        $this->strPassword = $strPassword;
        $this->oConnectionInfo = $oConnectionInfo;
    }

    /**
     * @return string
     */
    public function getStrUser()
    {
        return $this->strUser;
    }

    /**
     * @param string $strUser
     * @return Login
     */
    public function withStrUser($strUser)
    {
        $new = clone $this;
        $new->strUser = $strUser;

        return $new;
    }

    /**
     * @return string
     */
    public function getStrPassword()
    {
        return $this->strPassword;
    }

    /**
     * @param string $strPassword
     * @return Login
     */
    public function withStrPassword($strPassword)
    {
        $new = clone $this;
        $new->strPassword = $strPassword;

        return $new;
    }

    /**
     * @return \ArchiflowWSLogin\Type\ConnectionInfo
     */
    public function getOConnectionInfo()
    {
        return $this->oConnectionInfo;
    }

    /**
     * @param \ArchiflowWSLogin\Type\ConnectionInfo $oConnectionInfo
     * @return Login
     */
    public function withOConnectionInfo($oConnectionInfo)
    {
        $new = clone $this;
        $new->oConnectionInfo = $oConnectionInfo;

        return $new;
    }


}

