<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RetrieveCardsFromSearchModel2 implements RequestInterface
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
     * @var int
     */
    private $nPageNumber = null;

    /**
     * @var int
     */
    private $nPageSize = null;

    /**
     * @var bool
     */
    private $bGetIndexes = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var \ArchiflowWSCard\Type\ModelTypeFilter $modelTypeFilter
     * @var string $modelName
     * @var int $nPageNumber
     * @var int $nPageSize
     * @var bool $bGetIndexes
     */
    public function __construct($sessionId, $modelTypeFilter, $modelName, $nPageNumber, $nPageSize, $bGetIndexes)
    {
        $this->sessionId = $sessionId;
        $this->modelTypeFilter = $modelTypeFilter;
        $this->modelName = $modelName;
        $this->nPageNumber = $nPageNumber;
        $this->nPageSize = $nPageSize;
        $this->bGetIndexes = $bGetIndexes;
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
     * @return RetrieveCardsFromSearchModel2
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
     * @return RetrieveCardsFromSearchModel2
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
     * @return RetrieveCardsFromSearchModel2
     */
    public function withModelName($modelName)
    {
        $new = clone $this;
        $new->modelName = $modelName;

        return $new;
    }

    /**
     * @return int
     */
    public function getNPageNumber()
    {
        return $this->nPageNumber;
    }

    /**
     * @param int $nPageNumber
     * @return RetrieveCardsFromSearchModel2
     */
    public function withNPageNumber($nPageNumber)
    {
        $new = clone $this;
        $new->nPageNumber = $nPageNumber;

        return $new;
    }

    /**
     * @return int
     */
    public function getNPageSize()
    {
        return $this->nPageSize;
    }

    /**
     * @param int $nPageSize
     * @return RetrieveCardsFromSearchModel2
     */
    public function withNPageSize($nPageSize)
    {
        $new = clone $this;
        $new->nPageSize = $nPageSize;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetIndexes()
    {
        return $this->bGetIndexes;
    }

    /**
     * @param bool $bGetIndexes
     * @return RetrieveCardsFromSearchModel2
     */
    public function withBGetIndexes($bGetIndexes)
    {
        $new = clone $this;
        $new->bGetIndexes = $bGetIndexes;

        return $new;
    }


}

