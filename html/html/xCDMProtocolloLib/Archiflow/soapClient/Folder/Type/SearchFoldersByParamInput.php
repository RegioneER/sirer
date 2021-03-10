<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SearchFoldersByParamInput implements RequestInterface
{

    /**
     * @var \DateTime
     */
    private $DateFrom = null;

    /**
     * @var \DateTime
     */
    private $DateTo = null;

    /**
     * @var bool
     */
    private $GetCardIds = null;

    /**
     * @var bool
     */
    private $GetNotInDrawers = null;

    /**
     * @var bool
     */
    private $GetVisibility = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var string
     */
    private $Note = null;

    /**
     * Constructor
     *
     * @var \DateTime $DateFrom
     * @var \DateTime $DateTo
     * @var bool $GetCardIds
     * @var bool $GetNotInDrawers
     * @var bool $GetVisibility
     * @var string $Name
     * @var string $Note
     */
    public function __construct($DateFrom, $DateTo, $GetCardIds, $GetNotInDrawers, $GetVisibility, $Name, $Note)
    {
        $this->DateFrom = $DateFrom;
        $this->DateTo = $DateTo;
        $this->GetCardIds = $GetCardIds;
        $this->GetNotInDrawers = $GetNotInDrawers;
        $this->GetVisibility = $GetVisibility;
        $this->Name = $Name;
        $this->Note = $Note;
    }

    /**
     * @return \DateTime
     */
    public function getDateFrom()
    {
        return $this->DateFrom;
    }

    /**
     * @param \DateTime $DateFrom
     * @return SearchFoldersByParamInput
     */
    public function withDateFrom($DateFrom)
    {
        $new = clone $this;
        $new->DateFrom = $DateFrom;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDateTo()
    {
        return $this->DateTo;
    }

    /**
     * @param \DateTime $DateTo
     * @return SearchFoldersByParamInput
     */
    public function withDateTo($DateTo)
    {
        $new = clone $this;
        $new->DateTo = $DateTo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetCardIds()
    {
        return $this->GetCardIds;
    }

    /**
     * @param bool $GetCardIds
     * @return SearchFoldersByParamInput
     */
    public function withGetCardIds($GetCardIds)
    {
        $new = clone $this;
        $new->GetCardIds = $GetCardIds;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetNotInDrawers()
    {
        return $this->GetNotInDrawers;
    }

    /**
     * @param bool $GetNotInDrawers
     * @return SearchFoldersByParamInput
     */
    public function withGetNotInDrawers($GetNotInDrawers)
    {
        $new = clone $this;
        $new->GetNotInDrawers = $GetNotInDrawers;

        return $new;
    }

    /**
     * @return bool
     */
    public function getGetVisibility()
    {
        return $this->GetVisibility;
    }

    /**
     * @param bool $GetVisibility
     * @return SearchFoldersByParamInput
     */
    public function withGetVisibility($GetVisibility)
    {
        $new = clone $this;
        $new->GetVisibility = $GetVisibility;

        return $new;
    }

    /**
     * @return string
     */
    public function getName()
    {
        return $this->Name;
    }

    /**
     * @param string $Name
     * @return SearchFoldersByParamInput
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return string
     */
    public function getNote()
    {
        return $this->Note;
    }

    /**
     * @param string $Note
     * @return SearchFoldersByParamInput
     */
    public function withNote($Note)
    {
        $new = clone $this;
        $new->Note = $Note;

        return $new;
    }


}

