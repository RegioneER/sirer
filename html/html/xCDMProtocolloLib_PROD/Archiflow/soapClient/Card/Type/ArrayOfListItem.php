<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfListItem implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ListItem
     */
    private $ListItem = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ListItem $ListItem
     */
    public function __construct($ListItem)
    {
        $this->ListItem = $ListItem;
    }

    /**
     * @return \ArchiflowWSCard\Type\ListItem
     */
    public function getListItem()
    {
        return $this->ListItem;
    }

    /**
     * @param \ArchiflowWSCard\Type\ListItem $ListItem
     * @return ArrayOfListItem
     */
    public function withListItem($ListItem)
    {
        $new = clone $this;
        $new->ListItem = $ListItem;

        return $new;
    }


}

