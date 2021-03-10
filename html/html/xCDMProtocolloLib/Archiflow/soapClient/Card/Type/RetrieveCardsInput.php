<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RetrieveCardsInput implements RequestInterface
{

    /**
     * @var bool
     */
    private $GetAdditives = null;

    /**
     * @var bool
     */
    private $GetIndexes = null;

    /**
     * @var bool
     */
    private $GetInvoice = null;

    /**
     * @var bool
     */
    private $GetInvoicesMonitor = null;

    /**
     * @var int
     */
    private $PageNumber = null;

    /**
     * @var int
     */
    private $PageSize = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchCriteria
     */
    private $SearchCriteria = null;

    /**
     * Constructor
     *
     * @var bool $GetAdditives
     * @var bool $GetIndexes
     * @var bool $GetInvoice
     * @var bool $GetInvoicesMonitor
     * @var int $PageNumber
     * @var int $PageSize
     * @var \ArchiflowWSCard\Type\SearchCriteria $SearchCriteria
     */
    public function __construct($GetAdditives, $GetIndexes, $GetInvoice, $GetInvoicesMonitor, $PageNumber, $PageSize, $SearchCriteria)
    {
        $this->GetAdditives = $GetAdditives;
        $this->GetIndexes = $GetIndexes;
        $this->GetInvoice = $GetInvoice;
        $this->GetInvoicesMonitor = $GetInvoicesMonitor;
        $this->PageNumber = $PageNumber;
        $this->PageSize = $PageSize;
        $this->SearchCriteria = $SearchCriteria;
    }

    /**
     * @return bool
     */
    public function getGetAdditives()
    {
        return $this->GetAdditives;
    }

    /**
     * @param bool $GetAdditives
     * @return RetrieveCardsInput
     */
    public function withGetAdditives($GetAdditives)
    {
        $new = clone $this;
        $new->GetAdditives = $GetAdditives;

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
     * @return RetrieveCardsInput
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
    public function getGetInvoice()
    {
        return $this->GetInvoice;
    }

    /**
     * @param bool $GetInvoice
     * @return RetrieveCardsInput
     */
    public function withGetInvoice($GetInvoice)
    {
        $new = clone $this;
        $new->GetInvoice = $GetInvoice;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetInvoicesMonitor()
    {
        return $this->GetInvoicesMonitor;
    }

    /**
     * @param bool $GetInvoicesMonitor
     * @return RetrieveCardsInput
     */
    public function withGetInvoicesMonitor($GetInvoicesMonitor)
    {
        $new = clone $this;
        $new->GetInvoicesMonitor = $GetInvoicesMonitor;

        return $new;
    }

    /**
     * @return int
     */
    public function getPageNumber()
    {
        return $this->PageNumber;
    }

    /**
     * @param int $PageNumber
     * @return RetrieveCardsInput
     */
    public function withPageNumber($PageNumber)
    {
        $new = clone $this;
        $new->PageNumber = $PageNumber;

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
     * @return RetrieveCardsInput
     */
    public function withPageSize($PageSize)
    {
        $new = clone $this;
        $new->PageSize = $PageSize;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchCriteria
     */
    public function getSearchCriteria()
    {
        return $this->SearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchCriteria $SearchCriteria
     * @return RetrieveCardsInput
     */
    public function withSearchCriteria($SearchCriteria)
    {
        $new = clone $this;
        $new->SearchCriteria = $SearchCriteria;

        return $new;
    }


}

