<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RetrieveCards implements RequestInterface
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
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\SearchCriteria $oSearchCriteria
     * @var int $nPageNumber
     * @var int $nPageSize
     * @var bool $bGetIndexes
     */
    public function __construct($strSessionId, $oSearchCriteria, $nPageNumber, $nPageSize, $bGetIndexes)
    {
        $this->strSessionId = $strSessionId;
        $this->oSearchCriteria = $oSearchCriteria;
        $this->nPageNumber = $nPageNumber;
        $this->nPageSize = $nPageSize;
        $this->bGetIndexes = $bGetIndexes;
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
     * @return RetrieveCards
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
     * @return RetrieveCards
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
    public function getNPageNumber()
    {
        return $this->nPageNumber;
    }

    /**
     * @param int $nPageNumber
     * @return RetrieveCards
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
     * @return RetrieveCards
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
     * @return RetrieveCards
     */
    public function withBGetIndexes($bGetIndexes)
    {
        $new = clone $this;
        $new->bGetIndexes = $bGetIndexes;

        return $new;
    }


}

