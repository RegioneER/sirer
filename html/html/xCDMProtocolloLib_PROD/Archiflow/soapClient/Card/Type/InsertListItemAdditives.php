<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertListItemAdditives implements RequestInterface
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
     * @var int
     */
    private $docTypeId = null;

    /**
     * @var \ArchiflowWSCard\Type\IdAdditive
     */
    private $additiveId = null;

    /**
     * @var bool
     */
    private $bCheckDuplication = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\ListItem $oListItem
     * @var int $docTypeId
     * @var \ArchiflowWSCard\Type\IdAdditive $additiveId
     * @var bool $bCheckDuplication
     */
    public function __construct($strSessionId, $oListItem, $docTypeId, $additiveId, $bCheckDuplication)
    {
        $this->strSessionId = $strSessionId;
        $this->oListItem = $oListItem;
        $this->docTypeId = $docTypeId;
        $this->additiveId = $additiveId;
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
     * @return InsertListItemAdditives
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
     * @return InsertListItemAdditives
     */
    public function withOListItem($oListItem)
    {
        $new = clone $this;
        $new->oListItem = $oListItem;

        return $new;
    }

    /**
     * @return int
     */
    public function getDocTypeId()
    {
        return $this->docTypeId;
    }

    /**
     * @param int $docTypeId
     * @return InsertListItemAdditives
     */
    public function withDocTypeId($docTypeId)
    {
        $new = clone $this;
        $new->docTypeId = $docTypeId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdAdditive
     */
    public function getAdditiveId()
    {
        return $this->additiveId;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdAdditive $additiveId
     * @return InsertListItemAdditives
     */
    public function withAdditiveId($additiveId)
    {
        $new = clone $this;
        $new->additiveId = $additiveId;

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
     * @return InsertListItemAdditives
     */
    public function withBCheckDuplication($bCheckDuplication)
    {
        $new = clone $this;
        $new->bCheckDuplication = $bCheckDuplication;

        return $new;
    }


}

