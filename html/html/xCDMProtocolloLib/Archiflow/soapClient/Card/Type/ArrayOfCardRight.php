<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfCardRight implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CardRight
     */
    private $CardRight = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CardRight $CardRight
     */
    public function __construct($CardRight)
    {
        $this->CardRight = $CardRight;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardRight
     */
    public function getCardRight()
    {
        return $this->CardRight;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardRight $CardRight
     * @return ArrayOfCardRight
     */
    public function withCardRight($CardRight)
    {
        $new = clone $this;
        $new->CardRight = $CardRight;

        return $new;
    }


}

