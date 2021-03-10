<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SearchAgrafOptionsTag implements RequestInterface
{

    /**
     * @var string
     */
    private $AgrafNoteSearch = null;

    /**
     * @var bool
     */
    private $EnableGroupSearch = null;

    /**
     * @var \ArchiflowWSCard\Type\AgrafMatchMode
     */
    private $MatchMode = null;

    /**
     * @var string
     */
    private $TagId = null;

    /**
     * Constructor
     *
     * @var string $AgrafNoteSearch
     * @var bool $EnableGroupSearch
     * @var \ArchiflowWSCard\Type\AgrafMatchMode $MatchMode
     * @var string $TagId
     */
    public function __construct($AgrafNoteSearch, $EnableGroupSearch, $MatchMode, $TagId)
    {
        $this->AgrafNoteSearch = $AgrafNoteSearch;
        $this->EnableGroupSearch = $EnableGroupSearch;
        $this->MatchMode = $MatchMode;
        $this->TagId = $TagId;
    }

    /**
     * @return string
     */
    public function getAgrafNoteSearch()
    {
        return $this->AgrafNoteSearch;
    }

    /**
     * @param string $AgrafNoteSearch
     * @return SearchAgrafOptionsTag
     */
    public function withAgrafNoteSearch($AgrafNoteSearch)
    {
        $new = clone $this;
        $new->AgrafNoteSearch = $AgrafNoteSearch;

        return $new;
    }

    /**
     * @return bool
     */
    public function getEnableGroupSearch()
    {
        return $this->EnableGroupSearch;
    }

    /**
     * @param bool $EnableGroupSearch
     * @return SearchAgrafOptionsTag
     */
    public function withEnableGroupSearch($EnableGroupSearch)
    {
        $new = clone $this;
        $new->EnableGroupSearch = $EnableGroupSearch;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafMatchMode
     */
    public function getMatchMode()
    {
        return $this->MatchMode;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafMatchMode $MatchMode
     * @return SearchAgrafOptionsTag
     */
    public function withMatchMode($MatchMode)
    {
        $new = clone $this;
        $new->MatchMode = $MatchMode;

        return $new;
    }

    /**
     * @return string
     */
    public function getTagId()
    {
        return $this->TagId;
    }

    /**
     * @param string $TagId
     * @return SearchAgrafOptionsTag
     */
    public function withTagId($TagId)
    {
        $new = clone $this;
        $new->TagId = $TagId;

        return $new;
    }


}

