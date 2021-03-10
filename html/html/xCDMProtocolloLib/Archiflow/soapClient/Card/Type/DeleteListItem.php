<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DeleteListItem implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\ListItem
     */
    private $oListItem = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\ListItem $oListItem
     */
    public function __construct($strSessionId, $oListItem)
    {
        $this->strSessionId = $strSessionId;
        $this->oListItem = $oListItem;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return DeleteListItem
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ListItem
     */
    public function getOListItem()
    {
        return $this->oListItem;
    }

    /**
     * @param \ArchiflowWSCard\Type\ListItem $oListItem
     * @return DeleteListItem
     */
    public function withOListItem($oListItem)
    {
        $new = clone $this;
        $new->oListItem = $oListItem;

        return $new;
    }


}

