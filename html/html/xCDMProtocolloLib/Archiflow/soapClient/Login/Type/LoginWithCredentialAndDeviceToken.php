<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class LoginWithCredentialAndDeviceToken implements RequestInterface
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
     * @var string
     */
    private $strDeviceToken = null;

    /**
     * @var bool
     */
    private $bSave = null;

    /**
     * @var \ArchiflowWSLogin\Type\ConnectionInfo
     */
    private $oConnectionInfo = null;

    /**
     * Constructor
     *
     * @var string $strUser
     * @var string $strPassword
     * @var string $strDeviceToken
     * @var bool $bSave
     * @var \ArchiflowWSLogin\Type\ConnectionInfo $oConnectionInfo
     */
    public function __construct($strUser, $strPassword, $strDeviceToken, $bSave, $oConnectionInfo)
    {
        $this->strUser = $strUser;
        $this->strPassword = $strPassword;
        $this->strDeviceToken = $strDeviceToken;
        $this->bSave = $bSave;
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
     * @return LoginWithCredentialAndDeviceToken
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
     * @return LoginWithCredentialAndDeviceToken
     */
    public function withStrPassword($strPassword)
    {
        $new = clone $this;
        $new->strPassword = $strPassword;

        return $new;
    }

    /**
     * @return string
     */
    public function getStrDeviceToken()
    {
        return $this->strDeviceToken;
    }

    /**
     * @param string $strDeviceToken
     * @return LoginWithCredentialAndDeviceToken
     */
    public function withStrDeviceToken($strDeviceToken)
    {
        $new = clone $this;
        $new->strDeviceToken = $strDeviceToken;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBSave()
    {
        return $this->bSave;
    }

    /**
     * @param bool $bSave
     * @return LoginWithCredentialAndDeviceToken
     */
    public function withBSave($bSave)
    {
        $new = clone $this;
        $new->bSave = $bSave;

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
     * @return LoginWithCredentialAndDeviceToken
     */
    public function withOConnectionInfo($oConnectionInfo)
    {
        $new = clone $this;
        $new->oConnectionInfo = $oConnectionInfo;

        return $new;
    }


}

