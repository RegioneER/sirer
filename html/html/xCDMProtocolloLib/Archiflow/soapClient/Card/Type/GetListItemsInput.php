<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetListItemsInput implements RequestInterface
{

    /**
     * @var int
     */
    private $DocumentType = null;

    /**
     * @var int
     */
    private $ListId = null;

    /**
     * @var int
     */
    private $ParentItemId = null;

    /**
     * @var string
     */
    private $ParentItemValue = null;

    /**
     * @var bool
     */
    private $Search = null;

    /**
     * @var string
     */
    private $SessionId = null;

    /**
     * Constructor
     *
     * @var int $DocumentType
     * @var int $ListId
     * @var int $ParentItemId
     * @var string $ParentItemValue
     * @var bool $Search
     * @var string $SessionId
     */
    public function __construct($DocumentType, $ListId, $ParentItemId, $ParentItemValue, $Search, $SessionId)
    {
        $this->DocumentType = $DocumentType;
        $this->ListId = $ListId;
        $this->ParentItemId = $ParentItemId;
        $this->ParentItemValue = $ParentItemValue;
        $this->Search = $Search;
        $this->SessionId = $SessionId;
    }

    /**
     * @return int
     */
    public function getDocumentType()
    {
        return $this->DocumentType;
    }

    /**
     * @param int $DocumentType
     * @return GetListItemsInput
     */
    public function withDocumentType($DocumentType)
    {
        $new = clone $this;
        $new->DocumentType = $DocumentType;

        return $new;
    }

    /**
     * @return int
     */
    public function getListId()
    {
        return $this->ListId;
    }

    /**
     * @param int $ListId
     * @return GetListItemsInput
     */
    public function withListId($ListId)
    {
        $new = clone $this;
        $new->ListId = $ListId;

        return $new;
    }

    /**
     * @return int
     */
    public function getParentItemId()
    {
        return $this->ParentItemId;
    }

    /**
     * @param int $ParentItemId
     * @return GetListItemsInput
     */
    public function withParentItemId($ParentItemId)
    {
        $new = clone $this;
        $new->ParentItemId = $ParentItemId;

        return $new;
    }

    /**
     * @return string
     */
    public function getParentItemValue()
    {
        return $this->ParentItemValue;
    }

    /**
     * @param string $ParentItemValue
     * @return GetListItemsInput
     */
    public function withParentItemValue($ParentItemValue)
    {
        $new = clone $this;
        $new->ParentItemValue = $ParentItemValue;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSearch()
    {
        return $this->Search;
    }

    /**
     * @param bool $Search
     * @return GetListItemsInput
     */
    public function withSearch($Search)
    {
        $new = clone $this;
        $new->Search = $Search;

        return $new;
    }

    /**
     * @return string
     */
    public function getSessionId()
    {
        return $this->SessionId;
    }

    /**
     * @param string $SessionId
     * @return GetListItemsInput
     */
    public function withSessionId($SessionId)
    {
        $new = clone $this;
        $new->SessionId = $SessionId;

        return $new;
    }


}

