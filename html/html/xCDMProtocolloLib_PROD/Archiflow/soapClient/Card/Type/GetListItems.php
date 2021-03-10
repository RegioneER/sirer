<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetListItems implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $nListId = null;

    /**
     * @var int
     */
    private $nParentItemId = null;

    /**
     * @var string
     */
    private $strParentItemValue = null;

    /**
     * @var int
     */
    private $nDocumentType = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $nListId
     * @var int $nParentItemId
     * @var string $strParentItemValue
     * @var int $nDocumentType
     */
    public function __construct($strSessionId, $nListId, $nParentItemId, $strParentItemValue, $nDocumentType)
    {
        $this->strSessionId = $strSessionId;
        $this->nListId = $nListId;
        $this->nParentItemId = $nParentItemId;
        $this->strParentItemValue = $strParentItemValue;
        $this->nDocumentType = $nDocumentType;
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
     * @return GetListItems
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return int
     */
    public function getNListId()
    {
        return $this->nListId;
    }

    /**
     * @param int $nListId
     * @return GetListItems
     */
    public function withNListId($nListId)
    {
        $new = clone $this;
        $new->nListId = $nListId;

        return $new;
    }

    /**
     * @return int
     */
    public function getNParentItemId()
    {
        return $this->nParentItemId;
    }

    /**
     * @param int $nParentItemId
     * @return GetListItems
     */
    public function withNParentItemId($nParentItemId)
    {
        $new = clone $this;
        $new->nParentItemId = $nParentItemId;

        return $new;
    }

    /**
     * @return string
     */
    public function getStrParentItemValue()
    {
        return $this->strParentItemValue;
    }

    /**
     * @param string $strParentItemValue
     * @return GetListItems
     */
    public function withStrParentItemValue($strParentItemValue)
    {
        $new = clone $this;
        $new->strParentItemValue = $strParentItemValue;

        return $new;
    }

    /**
     * @return int
     */
    public function getNDocumentType()
    {
        return $this->nDocumentType;
    }

    /**
     * @param int $nDocumentType
     * @return GetListItems
     */
    public function withNDocumentType($nDocumentType)
    {
        $new = clone $this;
        $new->nDocumentType = $nDocumentType;

        return $new;
    }


}

