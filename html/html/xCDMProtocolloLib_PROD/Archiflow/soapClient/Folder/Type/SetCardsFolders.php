<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardsFolders implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\SetCardsFoldersInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\SetCardsFoldersInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSFolder\Type\SetCardsFoldersInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SetCardsFoldersInput $paramIn
     * @return SetCardsFolders
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

