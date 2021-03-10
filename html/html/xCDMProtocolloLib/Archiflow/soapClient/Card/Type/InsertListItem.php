<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertListItem implements RequestInterface
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
     * @var \ArchiflowWSCard\Type\IdField
     */
    private $fieldId = null;

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
     * @var \ArchiflowWSCard\Type\IdField $fieldId
     * @var bool $bCheckDuplication
     */
    public function __construct($strSessionId, $oListItem, $docTypeId, $fieldId, $bCheckDuplication)
    {
        $this->strSessionId = $strSessionId;
        $this->oListItem = $oListItem;
        $this->docTypeId = $docTypeId;
        $this->fieldId = $fieldId;
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
     * @return InsertListItem
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
     * @return InsertListItem
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
     * @return InsertListItem
     */
    public function withDocTypeId($docTypeId)
    {
        $new = clone $this;
        $new->docTypeId = $docTypeId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdField
     */
    public function getFieldId()
    {
        return $this->fieldId;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdField $fieldId
     * @return InsertListItem
     */
    public function withFieldId($fieldId)
    {
        $new = clone $this;
        $new->fieldId = $fieldId;

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
     * @return InsertListItem
     */
    public function withBCheckDuplication($bCheckDuplication)
    {
        $new = clone $this;
        $new->bCheckDuplication = $bCheckDuplication;

        return $new;
    }


}

