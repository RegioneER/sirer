<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetPressMarkInfoOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfPressMarkModelInfo
     */
    private $Models = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfPressMarkModelInfo $Models
     */
    public function __construct($Models)
    {
        $this->Models = $Models;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfPressMarkModelInfo
     */
    public function getModels()
    {
        return $this->Models;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfPressMarkModelInfo $Models
     * @return GetPressMarkInfoOutput
     */
    public function withModels($Models)
    {
        $new = clone $this;
        $new->Models = $Models;

        return $new;
    }


}

