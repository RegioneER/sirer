<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetPressMarkInfo implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetPressMarkInfoInput
     */
    private $input = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\GetPressMarkInfoInput $input
     */
    public function __construct($input)
    {
        $this->input = $input;
    }

    /**
     * @return \ArchiflowWSCard\Type\GetPressMarkInfoInput
     */
    public function getInput()
    {
        return $this->input;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetPressMarkInfoInput $input
     * @return GetPressMarkInfo
     */
    public function withInput($input)
    {
        $new = clone $this;
        $new->input = $input;

        return $new;
    }


}

