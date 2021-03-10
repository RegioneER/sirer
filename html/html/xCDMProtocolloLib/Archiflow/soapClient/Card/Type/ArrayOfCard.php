<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfCard implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Card
     */
    private $Card = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Card $Card
     */
    public function __construct($Card)
    {
        $this->Card = $Card;
    }

    /**
     * @return \ArchiflowWSCard\Type\Card
     */
    public function getCard()
    {
        return $this->Card;
    }

    /**
     * @param \ArchiflowWSCard\Type\Card $Card
     * @return ArrayOfCard
     */
    public function withCard($Card)
    {
        $new = clone $this;
        $new->Card = $Card;

        return $new;
    }


}

