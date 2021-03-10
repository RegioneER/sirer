<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardsOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfCard
     */
    private $Cards = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfCard $Cards
     */
    public function __construct($Cards)
    {
        $this->Cards = $Cards;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfCard
     */
    public function getCards()
    {
        return $this->Cards;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfCard $Cards
     * @return GetCardsOutput
     */
    public function withCards($Cards)
    {
        $new = clone $this;
        $new->Cards = $Cards;

        return $new;
    }


}

