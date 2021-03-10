<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfAgrafCard implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\AgrafCard
     */
    private $AgrafCard = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\AgrafCard $AgrafCard
     */
    public function __construct($AgrafCard)
    {
        $this->AgrafCard = $AgrafCard;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafCard
     */
    public function getAgrafCard()
    {
        return $this->AgrafCard;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafCard $AgrafCard
     * @return ArrayOfAgrafCard
     */
    public function withAgrafCard($AgrafCard)
    {
        $new = clone $this;
        $new->AgrafCard = $AgrafCard;

        return $new;
    }


}

