<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Status implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfChannel
     */
    private $ChannelsError = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfChannel
     */
    private $ChannelsOk = null;

    /**
     * @var string
     */
    private $Color = null;

    /**
     * @var string
     */
    private $ColorInError = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var int
     */
    private $TotalInError = null;

    /**
     * @var int
     */
    private $TotalLapseErrors = null;

    /**
     * @var int
     */
    private $TotalOk = null;

    /**
     * @var int
     */
    private $TotalTransitions = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfChannel $ChannelsError
     * @var \ArchiflowWSCard\Type\ArrayOfChannel $ChannelsOk
     * @var string $Color
     * @var string $ColorInError
     * @var string $Name
     * @var int $TotalInError
     * @var int $TotalLapseErrors
     * @var int $TotalOk
     * @var int $TotalTransitions
     */
    public function __construct($ChannelsError, $ChannelsOk, $Color, $ColorInError, $Name, $TotalInError, $TotalLapseErrors, $TotalOk, $TotalTransitions)
    {
        $this->ChannelsError = $ChannelsError;
        $this->ChannelsOk = $ChannelsOk;
        $this->Color = $Color;
        $this->ColorInError = $ColorInError;
        $this->Name = $Name;
        $this->TotalInError = $TotalInError;
        $this->TotalLapseErrors = $TotalLapseErrors;
        $this->TotalOk = $TotalOk;
        $this->TotalTransitions = $TotalTransitions;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfChannel
     */
    public function getChannelsError()
    {
        return $this->ChannelsError;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfChannel $ChannelsError
     * @return Status
     */
    public function withChannelsError($ChannelsError)
    {
        $new = clone $this;
        $new->ChannelsError = $ChannelsError;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfChannel
     */
    public function getChannelsOk()
    {
        return $this->ChannelsOk;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfChannel $ChannelsOk
     * @return Status
     */
    public function withChannelsOk($ChannelsOk)
    {
        $new = clone $this;
        $new->ChannelsOk = $ChannelsOk;

        return $new;
    }

    /**
     * @return string
     */
    public function getColor()
    {
        return $this->Color;
    }

    /**
     * @param string $Color
     * @return Status
     */
    public function withColor($Color)
    {
        $new = clone $this;
        $new->Color = $Color;

        return $new;
    }

    /**
     * @return string
     */
    public function getColorInError()
    {
        return $this->ColorInError;
    }

    /**
     * @param string $ColorInError
     * @return Status
     */
    public function withColorInError($ColorInError)
    {
        $new = clone $this;
        $new->ColorInError = $ColorInError;

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
     * @return Status
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
    public function getTotalInError()
    {
        return $this->TotalInError;
    }

    /**
     * @param int $TotalInError
     * @return Status
     */
    public function withTotalInError($TotalInError)
    {
        $new = clone $this;
        $new->TotalInError = $TotalInError;

        return $new;
    }

    /**
     * @return int
     */
    public function getTotalLapseErrors()
    {
        return $this->TotalLapseErrors;
    }

    /**
     * @param int $TotalLapseErrors
     * @return Status
     */
    public function withTotalLapseErrors($TotalLapseErrors)
    {
        $new = clone $this;
        $new->TotalLapseErrors = $TotalLapseErrors;

        return $new;
    }

    /**
     * @return int
     */
    public function getTotalOk()
    {
        return $this->TotalOk;
    }

    /**
     * @param int $TotalOk
     * @return Status
     */
    public function withTotalOk($TotalOk)
    {
        $new = clone $this;
        $new->TotalOk = $TotalOk;

        return $new;
    }

    /**
     * @return int
     */
    public function getTotalTransitions()
    {
        return $this->TotalTransitions;
    }

    /**
     * @param int $TotalTransitions
     * @return Status
     */
    public function withTotalTransitions($TotalTransitions)
    {
        $new = clone $this;
        $new->TotalTransitions = $TotalTransitions;

        return $new;
    }


}

