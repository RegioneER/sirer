<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetListItemsOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfListItem
     */
    private $IndexItems = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfListItem $IndexItems
     */
    public function __construct($IndexItems)
    {
        $this->IndexItems = $IndexItems;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfListItem
     */
    public function getIndexItems()
    {
        return $this->IndexItems;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfListItem $IndexItems
     * @return GetListItemsOutput
     */
    public function withIndexItems($IndexItems)
    {
        $new = clone $this;
        $new->IndexItems = $IndexItems;

        return $new;
    }


}

