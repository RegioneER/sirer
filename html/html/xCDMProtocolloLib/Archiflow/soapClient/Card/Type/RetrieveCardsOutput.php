<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RetrieveCardsOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfCard
     */
    private $Cards = null;

    /**
     * @var int
     */
    private $HitCount = null;

    /**
     * @var \ArchiflowWSCard\Type\InvoiceMonitor
     */
    private $InvoiceMonitor = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchResult
     */
    private $SearchResult = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfCard $Cards
     * @var int $HitCount
     * @var \ArchiflowWSCard\Type\InvoiceMonitor $InvoiceMonitor
     * @var \ArchiflowWSCard\Type\SearchResult $SearchResult
     */
    public function __construct($Cards, $HitCount, $InvoiceMonitor, $SearchResult)
    {
        $this->Cards = $Cards;
        $this->HitCount = $HitCount;
        $this->InvoiceMonitor = $InvoiceMonitor;
        $this->SearchResult = $SearchResult;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfCard
     */
    public function getCards()
    {
        return $this->Cards;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfCard $Cards
     * @return RetrieveCardsOutput
     */
    public function withCards($Cards)
    {
        $new = clone $this;
        $new->Cards = $Cards;

        return $new;
    }

    /**
     * @return int
     */
    public function getHitCount()
    {
        return $this->HitCount;
    }

    /**
     * @param int $HitCount
     * @return RetrieveCardsOutput
     */
    public function withHitCount($HitCount)
    {
        $new = clone $this;
        $new->HitCount = $HitCount;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\InvoiceMonitor
     */
    public function getInvoiceMonitor()
    {
        return $this->InvoiceMonitor;
    }

    /**
     * @param \ArchiflowWSCard\Type\InvoiceMonitor $InvoiceMonitor
     * @return RetrieveCardsOutput
     */
    public function withInvoiceMonitor($InvoiceMonitor)
    {
        $new = clone $this;
        $new->InvoiceMonitor = $InvoiceMonitor;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchResult
     */
    public function getSearchResult()
    {
        return $this->SearchResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchResult $SearchResult
     * @return RetrieveCardsOutput
     */
    public function withSearchResult($SearchResult)
    {
        $new = clone $this;
        $new->SearchResult = $SearchResult;

        return $new;
    }


}

