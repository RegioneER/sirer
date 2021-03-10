<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardHistoryPerPage implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

    /**
     * @var int
     */
    private $PageIndex = null;

    /**
     * @var int
     */
    private $PageSize = null;

    /**
     * @var bool
     */
    private $DescendingOrder = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var int $PageIndex
     * @var int $PageSize
     * @var bool $DescendingOrder
     */
    public function __construct($strSessionId, $oCardId, $PageIndex, $PageSize, $DescendingOrder)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->PageIndex = $PageIndex;
        $this->PageSize = $PageSize;
        $this->DescendingOrder = $DescendingOrder;
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
     * @return GetCardHistoryPerPage
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getOCardId()
    {
        return $this->oCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $oCardId
     * @return GetCardHistoryPerPage
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

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
     * @return GetCardHistoryPerPage
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
     * @return GetCardHistoryPerPage
     */
    public function withPageSize($PageSize)
    {
        $new = clone $this;
        $new->PageSize = $PageSize;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDescendingOrder()
    {
        return $this->DescendingOrder;
    }

    /**
     * @param bool $DescendingOrder
     * @return GetCardHistoryPerPage
     */
    public function withDescendingOrder($DescendingOrder)
    {
        $new = clone $this;
        $new->DescendingOrder = $DescendingOrder;

        return $new;
    }


}

