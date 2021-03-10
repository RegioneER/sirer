<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendFolderByParam implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\SendFolderInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\SendFolderInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSFolder\Type\SendFolderInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SendFolderInput $paramIn
     * @return SendFolderByParam
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

