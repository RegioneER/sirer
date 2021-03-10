<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AgrafEntityId implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $EntityId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $EntityType = null;

    /**
     * @var int
     */
    private $Version = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $EntityId
     * @var \ArchiflowWSCard\Type\Guid $EntityType
     * @var int $Version
     */
    public function __construct($EntityId, $EntityType, $Version)
    {
        $this->EntityId = $EntityId;
        $this->EntityType = $EntityType;
        $this->Version = $Version;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getEntityId()
    {
        return $this->EntityId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $EntityId
     * @return AgrafEntityId
     */
    public function withEntityId($EntityId)
    {
        $new = clone $this;
        $new->EntityId = $EntityId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getEntityType()
    {
        return $this->EntityType;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $EntityType
     * @return AgrafEntityId
     */
    public function withEntityType($EntityType)
    {
        $new = clone $this;
        $new->EntityType = $EntityType;

        return $new;
    }

    /**
     * @return int
     */
    public function getVersion()
    {
        return $this->Version;
    }

    /**
     * @param int $Version
     * @return AgrafEntityId
     */
    public function withVersion($Version)
    {
        $new = clone $this;
        $new->Version = $Version;

        return $new;
    }


}

