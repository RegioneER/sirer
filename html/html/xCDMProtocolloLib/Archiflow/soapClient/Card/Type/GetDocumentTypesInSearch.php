<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocumentTypesInSearch implements RequestInterface
{

    /**
     * @var string
     */
    private $sessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\SearchCriteria
     */
    private $searchCriteria = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\SearchCriteria $searchCriteria
     */
    public function __construct($sessionId, $searchCriteria)
    {
        $this->sessionId = $sessionId;
        $this->searchCriteria = $searchCriteria;
    }

    /**
     * @return string
     */
    public function getSessionId()
    {
        return $this->sessionId;
    }

    /**
     * @param string $sessionId
     * @return GetDocumentTypesInSearch
     */
    public function withSessionId($sessionId)
    {
        $new = clone $this;
        $new->sessionId = $sessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SearchCriteria
     */
    public function getSearchCriteria()
    {
        return $this->searchCriteria;
    }

    /**
     * @param \ArchiflowWSCard\Type\SearchCriteria $searchCriteria
     * @return GetDocumentTypesInSearch
     */
    public function withSearchCriteria($searchCriteria)
    {
        $new = clone $this;
        $new->searchCriteria = $searchCriteria;

        return $new;
    }


}

