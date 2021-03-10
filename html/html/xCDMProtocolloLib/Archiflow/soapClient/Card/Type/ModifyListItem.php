<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ModifyListItem implements RequestInterface
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
     * @var bool
     */
    private $bCheckDuplication = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\ListItem $oListItem
     * @var bool $bCheckDuplication
     */
    public function __construct($strSessionId, $oListItem, $bCheckDuplication)
    {
        $this->strSessionId = $strSessionId;
        $this->oListItem = $oListItem;
        $this->bCheckDuplication = $bCheckDuplication;
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
     * @return ModifyListItem
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
     * @return ModifyListItem
     */
    public function withOListItem($oListItem)
    {
        $new = clone $this;
        $new->oListItem = $oListItem;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBCheckDuplication()
    {
        return $this->bCheckDuplication;
    }

    /**
     * @param bool $bCheckDuplication
     * @return ModifyListItem
     */
    public function withBCheckDuplication($bCheckDuplication)
    {
        $new = clone $this;
        $new->bCheckDuplication = $bCheckDuplication;

        return $new;
    }


}

