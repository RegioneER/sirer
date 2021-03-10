<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardsInFolderOutput implements RequestInterface
{

    /**
     * @var int
     */
    private $HitCount = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfCard
     */
    private $cards = null;

    /**
     * Constructor
     *
     * @var int $HitCount
     * @var \ArchiflowWSFolder\Type\ArrayOfCard $cards
     */
    public function __construct($HitCount, $cards)
    {
        $this->HitCount = $HitCount;
        $this->cards = $cards;
    }

    /**
     * @return int
     */
    public function getHitCount()
    {
        return $this->HitCount;
    }

    /**
     * @param int $HitCount
     * @return GetCardsInFolderOutput
     */
    public function withHitCount($HitCount)
    {
        $new = clone $this;
        $new->HitCount = $HitCount;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfCard
     */
    public function getCards()
    {
        return $this->cards;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfCard $cards
     * @return GetCardsInFolderOutput
     */
    public function withCards($cards)
    {
        $new = clone $this;
        $new->cards = $cards;

        return $new;
    }


}

