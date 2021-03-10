<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AttachPressMark implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AttachPressMarkInput
     */
    private $input = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AttachPressMarkInput $input
     */
    public function __construct($input)
    {
        $this->input = $input;
    }

    /**
     * @return \ArchiflowWSCard\Type\AttachPressMarkInput
     */
    public function getInput()
    {
        return $this->input;
    }

    /**
     * @param \ArchiflowWSCard\Type\AttachPressMarkInput $input
     * @return AttachPressMark
     */
    public function withInput($input)
    {
        $new = clone $this;
        $new->input = $input;

        return $new;
    }


}

