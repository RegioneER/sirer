<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetSearchModels implements RequestInterface
{

    /**
     * @var string
     */
    private $sessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\ModelTypeFilter
     */
    private $modelTypeFilter = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\ModelTypeFilter $modelTypeFilter
     */
    public function __construct($sessionId, $modelTypeFilter)
    {
        $this->sessionId = $sessionId;
        $this->modelTypeFilter = $modelTypeFilter;
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
     * @return GetSearchModels
     */
    public function withSessionId($sessionId)
    {
        $new = clone $this;
        $new->sessionId = $sessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ModelTypeFilter
     */
    public function getModelTypeFilter()
    {
        return $this->modelTypeFilter;
    }

    /**
     * @param \ArchiflowWSCard\Type\ModelTypeFilter $modelTypeFilter
     * @return GetSearchModels
     */
    public function withModelTypeFilter($modelTypeFilter)
    {
        $new = clone $this;
        $new->modelTypeFilter = $modelTypeFilter;

        return $new;
    }


}

