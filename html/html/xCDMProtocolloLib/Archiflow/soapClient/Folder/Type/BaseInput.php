<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class BaseInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\SessionInfo
     */
    private $SessionInfo = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\SessionInfo $SessionInfo
     */
    public function __construct($SessionInfo)
    {
        $this->SessionInfo = $SessionInfo;
    }

    /**
     * @return \ArchiflowWSFolder\Type\SessionInfo
     */
    public function getSessionInfo()
    {
        return $this->SessionInfo;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SessionInfo $SessionInfo
     * @return BaseInput
     */
    public function withSessionInfo($SessionInfo)
    {
        $new = clone $this;
        $new->SessionInfo = $SessionInfo;

        return $new;
    }


}

