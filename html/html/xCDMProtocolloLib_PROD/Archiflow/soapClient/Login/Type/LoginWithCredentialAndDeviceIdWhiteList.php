<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class LoginWithCredentialAndDeviceIdWhiteList implements RequestInterface
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
    private $strDeviceid = null;

    /**
     * @var \ArchiflowWSLogin\Type\ConnectionInfo
     */
    private $oConnectionInfo = null;

    /**
     * Constructor
     *
     * @var string $strUser
     * @var string $strPassword
     * @var string $strDeviceid
     * @var \ArchiflowWSLogin\Type\ConnectionInfo $oConnectionInfo
     */
    public function __construct($strUser, $strPassword, $strDeviceid, $oConnectionInfo)
    {
        $this->strUser = $strUser;
        $this->strPassword = $strPassword;
        $this->strDeviceid = $strDeviceid;
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
     * @return LoginWithCredentialAndDeviceIdWhiteList
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
     * @return LoginWithCredentialAndDeviceIdWhiteList
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
    public function getStrDeviceid()
    {
        return $this->strDeviceid;
    }

    /**
     * @param string $strDeviceid
     * @return LoginWithCredentialAndDeviceIdWhiteList
     */
    public function withStrDeviceid($strDeviceid)
    {
        $new = clone $this;
        $new->strDeviceid = $strDeviceid;

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
     * @return LoginWithCredentialAndDeviceIdWhiteList
     */
    public function withOConnectionInfo($oConnectionInfo)
    {
        $new = clone $this;
        $new->oConnectionInfo = $oConnectionInfo;

        return $new;
    }


}

