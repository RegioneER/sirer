<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardsInFolderInput implements RequestInterface
{

    /**
     * @var int
     */
    private $FolderId = null;

    /**
     * @var bool
     */
    private $GetIndexes = null;

    /**
     * @var bool
     */
    private $IsDescending = null;

    /**
     * @var \ArchiflowWSFolder\Type\FieldToOrderBy
     */
    private $OrderFieldId = null;

    /**
     * @var \ArchiflowWSFolder\Type\KeyOrderType
     */
    private $OrderType = null;

    /**
     * @var int
     */
    private $PageIndex = null;

    /**
     * @var int
     */
    private $PageSize = null;

    /**
     * Constructor
     *
     * @var int $FolderId
     * @var bool $GetIndexes
     * @var bool $IsDescending
     * @var \ArchiflowWSFolder\Type\FieldToOrderBy $OrderFieldId
     * @var \ArchiflowWSFolder\Type\KeyOrderType $OrderType
     * @var int $PageIndex
     * @var int $PageSize
     */
    public function __construct($FolderId, $GetIndexes, $IsDescending, $OrderFieldId, $OrderType, $PageIndex, $PageSize)
    {
        $this->FolderId = $FolderId;
        $this->GetIndexes = $GetIndexes;
        $this->IsDescending = $IsDescending;
        $this->OrderFieldId = $OrderFieldId;
        $this->OrderType = $OrderType;
        $this->PageIndex = $PageIndex;
        $this->PageSize = $PageSize;
    }

    /**
     * @return int
     */
    public function getFolderId()
    {
        return $this->FolderId;
    }

    /**
     * @param int $FolderId
     * @return GetCardsInFolderInput
     */
    public function withFolderId($FolderId)
    {
        $new = clone $this;
        $new->FolderId = $FolderId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetIndexes()
    {
        return $this->GetIndexes;
    }

    /**
     * @param bool $GetIndexes
     * @return GetCardsInFolderInput
     */
    public function withGetIndexes($GetIndexes)
    {
        $new = clone $this;
        $new->GetIndexes = $GetIndexes;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsDescending()
    {
        return $this->IsDescending;
    }

    /**
     * @param bool $IsDescending
     * @return GetCardsInFolderInput
     */
    public function withIsDescending($IsDescending)
    {
        $new = clone $this;
        $new->IsDescending = $IsDescending;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\FieldToOrderBy
     */
    public function getOrderFieldId()
    {
        return $this->OrderFieldId;
    }

    /**
     * @param \ArchiflowWSFolder\Type\FieldToOrderBy $OrderFieldId
     * @return GetCardsInFolderInput
     */
    public function withOrderFieldId($OrderFieldId)
    {
        $new = clone $this;
        $new->OrderFieldId = $OrderFieldId;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\KeyOrderType
     */
    public function getOrderType()
    {
        return $this->OrderType;
    }

    /**
     * @param \ArchiflowWSFolder\Type\KeyOrderType $OrderType
     * @return GetCardsInFolderInput
     */
    public function withOrderType($OrderType)
    {
        $new = clone $this;
        $new->OrderType = $OrderType;

        return $new;
    }

    /**
     * @return int
     */
    public function getPageIndex()
    {
        return $this->PageIndex;
    }

    /**
     * @param int $PageIndex
     * @return GetCardsInFolderInput
     */
    public function withPageIndex($PageIndex)
    {
        $new = clone $this;
        $new->PageIndex = $PageIndex;

        return $new;
    }

    /**
     * @return int
     */
    public function getPageSize()
    {
        return $this->PageSize;
    }

    /**
     * @param int $PageSize
     * @return GetCardsInFolderInput
     */
    public function withPageSize($PageSize)
    {
        $new = clone $this;
        $new->PageSize = $PageSize;

        return $new;
    }


}

