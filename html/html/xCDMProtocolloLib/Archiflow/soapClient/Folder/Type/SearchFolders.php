<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SearchFolders implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var string
     */
    private $name = null;

    /**
     * @var \DateTime
     */
    private $dateFrom = null;

    /**
     * @var \DateTime
     */
    private $dateTo = null;

    /**
     * @var bool
     */
    private $bGetVisibility = null;

    /**
     * @var bool
     */
    private $bGetCardIds = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var string $name
     * @var \DateTime $dateFrom
     * @var \DateTime $dateTo
     * @var bool $bGetVisibility
     * @var bool $bGetCardIds
     */
    public function __construct($strSessionId, $name, $dateFrom, $dateTo, $bGetVisibility, $bGetCardIds)
    {
        $this->strSessionId = $strSessionId;
        $this->name = $name;
        $this->dateFrom = $dateFrom;
        $this->dateTo = $dateTo;
        $this->bGetVisibility = $bGetVisibility;
        $this->bGetCardIds = $bGetCardIds;
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
     * @return SearchFolders
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return string
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * @param string $name
     * @return SearchFolders
     */
    public function withName($name)
    {
        $new = clone $this;
        $new->name = $name;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDateFrom()
    {
        return $this->dateFrom;
    }

    /**
     * @param \DateTime $dateFrom
     * @return SearchFolders
     */
    public function withDateFrom($dateFrom)
    {
        $new = clone $this;
        $new->dateFrom = $dateFrom;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDateTo()
    {
        return $this->dateTo;
    }

    /**
     * @param \DateTime $dateTo
     * @return SearchFolders
     */
    public function withDateTo($dateTo)
    {
        $new = clone $this;
        $new->dateTo = $dateTo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetVisibility()
    {
        return $this->bGetVisibility;
    }

    /**
     * @param bool $bGetVisibility
     * @return SearchFolders
     */
    public function withBGetVisibility($bGetVisibility)
    {
        $new = clone $this;
        $new->bGetVisibility = $bGetVisibility;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBGetCardIds()
    {
        return $this->bGetCardIds;
    }

    /**
     * @param bool $bGetCardIds
     * @return SearchFolders
     */
    public function withBGetCardIds($bGetCardIds)
    {
        $new = clone $this;
        $new->bGetCardIds = $bGetCardIds;

        return $new;
    }


}

