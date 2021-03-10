<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class LoginWithDeviceId implements RequestInterface
{

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
     * @var string $strDeviceid
     * @var \ArchiflowWSLogin\Type\ConnectionInfo $oConnectionInfo
     */
    public function __construct($strDeviceid, $oConnectionInfo)
    {
        $this->strDeviceid = $strDeviceid;
        $this->oConnectionInfo = $oConnectionInfo;
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
     * @return LoginWithDeviceId
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
     * @return LoginWithDeviceId
     */
    public function withOConnectionInfo($oConnectionInfo)
    {
        $new = clone $this;
        $new->oConnectionInfo = $oConnectionInfo;

        return $new;
    }


}

