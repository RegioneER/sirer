<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SearchAgrafEntityId implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $EntityId = null;

    /**
     * @var \ArchiflowWSCard\Type\AgrafEntityType
     */
    private $EntityType = null;

    /**
     * @var string
     */
    private $TagId = null;

    /**
     * @var int
     */
    private $Version = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $EntityId
     * @var \ArchiflowWSCard\Type\AgrafEntityType $EntityType
     * @var string $TagId
     * @var int $Version
     */
    public function __construct($EntityId, $EntityType, $TagId, $Version)
    {
        $this->EntityId = $EntityId;
        $this->EntityType = $EntityType;
        $this->TagId = $TagId;
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
     * @return SearchAgrafEntityId
     */
    public function withEntityId($EntityId)
    {
        $new = clone $this;
        $new->EntityId = $EntityId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AgrafEntityType
     */
    public function getEntityType()
    {
        return $this->EntityType;
    }

    /**
     * @param \ArchiflowWSCard\Type\AgrafEntityType $EntityType
     * @return SearchAgrafEntityId
     */
    public function withEntityType($EntityType)
    {
        $new = clone $this;
        $new->EntityType = $EntityType;

        return $new;
    }

    /**
     * @return string
     */
    public function getTagId()
    {
        return $this->TagId;
    }

    /**
     * @param string $TagId
     * @return SearchAgrafEntityId
     */
    public function withTagId($TagId)
    {
        $new = clone $this;
        $new->TagId = $TagId;

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
     * @return SearchAgrafEntityId
     */
    public function withVersion($Version)
    {
        $new = clone $this;
        $new->Version = $Version;

        return $new;
    }


}

