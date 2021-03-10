<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardsInFolder implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\GetCardsInFolderInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\GetCardsInFolderInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSFolder\Type\GetCardsInFolderInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSFolder\Type\GetCardsInFolderInput $paramIn
     * @return GetCardsInFolder
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

