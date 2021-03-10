<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class BaseInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\SessionInfo
     */
    private $SessionInfo = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\SessionInfo $SessionInfo
     */
    public function __construct($SessionInfo)
    {
        $this->SessionInfo = $SessionInfo;
    }

    /**
     * @return \ArchiflowWSCard\Type\SessionInfo
     */
    public function getSessionInfo()
    {
        return $this->SessionInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\SessionInfo $SessionInfo
     * @return BaseInput
     */
    public function withSessionInfo($SessionInfo)
    {
        $new = clone $this;
        $new->SessionInfo = $SessionInfo;

        return $new;
    }


}

