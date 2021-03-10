<?php

namespace ArchiflowWSLogin\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Logout implements RequestInterface
{

    /**
     * @var \ArchiflowWSLogin\Type\SessionInfo
     */
    private $oSessionInfo = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSLogin\Type\SessionInfo $oSessionInfo
     */
    public function __construct($oSessionInfo)
    {
        $this->oSessionInfo = $oSessionInfo;
    }

    /**
     * @return \ArchiflowWSLogin\Type\SessionInfo
     */
    public function getOSessionInfo()
    {
        return $this->oSessionInfo;
    }

    /**
     * @param \ArchiflowWSLogin\Type\SessionInfo $oSessionInfo
     * @return Logout
     */
    public function withOSessionInfo($oSessionInfo)
    {
        $new = clone $this;
        $new->oSessionInfo = $oSessionInfo;

        return $new;
    }


}

