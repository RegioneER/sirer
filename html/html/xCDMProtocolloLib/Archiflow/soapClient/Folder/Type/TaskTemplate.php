<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class TaskTemplate implements RequestInterface
{

    /**
     * @var string
     */
    private $Description = null;

    /**
     * @var int
     */
    private $DueDateDays = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var int
     */
    private $Options = null;

    /**
     * @var int
     */
    private $Priority = null;

    /**
     * Constructor
     *
     * @var string $Description
     * @var int $DueDateDays
     * @var int $Id
     * @var string $Name
     * @var int $Options
     * @var int $Priority
     */
    public function __construct($Description, $DueDateDays, $Id, $Name, $Options, $Priority)
    {
        $this->Description = $Description;
        $this->DueDateDays = $DueDateDays;
        $this->Id = $Id;
        $this->Name = $Name;
        $this->Options = $Options;
        $this->Priority = $Priority;
    }

    /**
     * @return string
     */
    public function getDescription()
    {
        return $this->Description;
    }

    /**
     * @param string $Description
     * @return TaskTemplate
     */
    public function withDescription($Description)
    {
        $new = clone $this;
        $new->Description = $Description;

        return $new;
    }

    /**
     * @return int
     */
    public function getDueDateDays()
    {
        return $this->DueDateDays;
    }

    /**
     * @param int $DueDateDays
     * @return TaskTemplate
     */
    public function withDueDateDays($DueDateDays)
    {
        $new = clone $this;
        $new->DueDateDays = $DueDateDays;

        return $new;
    }

    /**
     * @return int
     */
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param int $Id
     * @return TaskTemplate
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

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
     * @return TaskTemplate
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return int
     */
    public function getOptions()
    {
        return $this->Options;
    }

    /**
     * @param int $Options
     * @return TaskTemplate
     */
    public function withOptions($Options)
    {
        $new = clone $this;
        $new->Options = $Options;

        return $new;
    }

    /**
     * @return int
     */
    public function getPriority()
    {
        return $this->Priority;
    }

    /**
     * @param int $Priority
     * @return TaskTemplate
     */
    public function withPriority($Priority)
    {
        $new = clone $this;
        $new->Priority = $Priority;

        return $new;
    }


}

