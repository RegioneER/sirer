<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SearchCards implements RequestInterface
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
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\SearchCriteria $oSearchCriteria
     */
    public function __construct($strSessionId, $oSearchCriteria)
    {
        $this->strSessionId = $strSessionId;
        $this->oSearchCriteria = $oSearchCriteria;
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
     * @return SearchCards
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
     * @return SearchCards
     */
    public function withOSearchCriteria($oSearchCriteria)
    {
        $new = clone $this;
        $new->oSearchCriteria = $oSearchCriteria;

        return $new;
    }


}

