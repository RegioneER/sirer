<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfCard implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Card
     */
    private $Card = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Card $Card
     */
    public function __construct($Card)
    {
        $this->Card = $Card;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Card
     */
    public function getCard()
    {
        return $this->Card;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Card $Card
     * @return ArrayOfCard
     */
    public function withCard($Card)
    {
        $new = clone $this;
        $new->Card = $Card;

        return $new;
    }


}

