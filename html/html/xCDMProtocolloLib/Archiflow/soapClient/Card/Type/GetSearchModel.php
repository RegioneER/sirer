<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetSearchModel implements RequestInterface
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
     * @var string
     */
    private $modelName = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\ModelTypeFilter $modelTypeFilter
     * @var string $modelName
     */
    public function __construct($sessionId, $modelTypeFilter, $modelName)
    {
        $this->sessionId = $sessionId;
        $this->modelTypeFilter = $modelTypeFilter;
        $this->modelName = $modelName;
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
     * @return GetSearchModel
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
     * @return GetSearchModel
     */
    public function withModelTypeFilter($modelTypeFilter)
    {
        $new = clone $this;
        $new->modelTypeFilter = $modelTypeFilter;

        return $new;
    }

    /**
     * @return string
     */
    public function getModelName()
    {
        return $this->modelName;
    }

    /**
     * @param string $modelName
     * @return GetSearchModel
     */
    public function withModelName($modelName)
    {
        $new = clone $this;
        $new->modelName = $modelName;

        return $new;
    }


}

