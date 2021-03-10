<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SearchFoldersByParam implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\SearchFoldersByParamInput
     */
    private $paramIn = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\SearchFoldersByParamInput $paramIn
     */
    public function __construct($paramIn)
    {
        $this->paramIn = $paramIn;
    }

    /**
     * @return \ArchiflowWSFolder\Type\SearchFoldersByParamInput
     */
    public function getParamIn()
    {
        return $this->paramIn;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SearchFoldersByParamInput $paramIn
     * @return SearchFoldersByParam
     */
    public function withParamIn($paramIn)
    {
        $new = clone $this;
        $new->paramIn = $paramIn;

        return $new;
    }


}

