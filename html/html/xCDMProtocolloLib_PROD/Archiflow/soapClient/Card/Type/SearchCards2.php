<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SearchCards2 implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchCriteria
     */
    private $oSearchCriteria = null;

    /**
     * @var int
     */
    private $nItemsToSearch = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\SearchCriteria $oSearchCriteria
     * @var int $nItemsToSearch
     */
    public function __construct($strSessionId, $oSearchCriteria, $nItemsToSearch)
    {
        $this->strSessionId = $strSessionId;
        $this->oSearchCriteria = $oSearchCriteria;
        $this->nItemsToSearch = $nItemsToSearch;
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
     * @return SearchCards2
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchCriteria
     */
    public function getOSearchCriteria()
    {
        return $this->oSearchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchCriteria $oSearchCriteria
     * @return SearchCards2
     */
    public function withOSearchCriteria($oSearchCriteria)
    {
        $new = clone $this;
        $new->oSearchCriteria = $oSearchCriteria;

        return $new;
    }

    /**
     * @return int
     */
    public function getNItemsToSearch()
    {
        return $this->nItemsToSearch;
    }

    /**
     * @param int $nItemsToSearch
     * @return SearchCards2
     */
    public function withNItemsToSearch($nItemsToSearch)
    {
        $new = clone $this;
        $new->nItemsToSearch = $nItemsToSearch;

        return $new;
    }


}

