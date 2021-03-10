<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendEntity implements RequestInterface
{

    /**
     * @var string
     */
    private $Description = null;

    /**
     * @var \ArchiflowWSCard\Type\EntityType
     */
    private $EntityType = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var int
     */
    private $Level = null;

    /**
     * @var int
     */
    private $ParentId = null;

    /**
     * @var \ArchiflowWSCard\Type\SendingType
     */
    private $SendingType = null;

    /**
     * @var int
     */
    private $Status = null;

    /**
     * @var \ArchiflowWSCard\Type\TaskTemplate
     */
    private $TaskTemplate = null;

    /**
     * @var bool
     */
    private $bCC = null;

    /**
     * Constructor
     *
     * @var string $Description
     * @var \ArchiflowWSCard\Type\EntityType $EntityType
     * @var int $Id
     * @var int $Level
     * @var int $ParentId
     * @var \ArchiflowWSCard\Type\SendingType $SendingType
     * @var int $Status
     * @var \ArchiflowWSCard\Type\TaskTemplate $TaskTemplate
     * @var bool $bCC
     */
    public function __construct($Description, $EntityType, $Id, $Level, $ParentId, $SendingType, $Status, $TaskTemplate, $bCC)
    {
        $this->Description = $Description;
        $this->EntityType = $EntityType;
        $this->Id = $Id;
        $this->Level = $Level;
        $this->ParentId = $ParentId;
        $this->SendingType = $SendingType;
        $this->Status = $Status;
        $this->TaskTemplate = $TaskTemplate;
        $this->bCC = $bCC;
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
     * @return SendEntity
     */
    public function withDescription($Description)
    {
        $new = clone $this;
        $new->Description = $Description;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\EntityType
     */
    public function getEntityType()
    {
        return $this->EntityType;
    }

    /**
     * @param \ArchiflowWSCard\Type\EntityType $EntityType
     * @return SendEntity
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
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param int $Id
     * @return SendEntity
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }

    /**
     * @return int
     */
    public function getLevel()
    {
        return $this->Level;
    }

    /**
     * @param int $Level
     * @return SendEntity
     */
    public function withLevel($Level)
    {
        $new = clone $this;
        $new->Level = $Level;

        return $new;
    }

    /**
     * @return int
     */
    public function getParentId()
    {
        return $this->ParentId;
    }

    /**
     * @param int $ParentId
     * @return SendEntity
     */
    public function withParentId($ParentId)
    {
        $new = clone $this;
        $new->ParentId = $ParentId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\SendingType
     */
    public function getSendingType()
    {
        return $this->SendingType;
    }

    /**
     * @param \ArchiflowWSCard\Type\SendingType $SendingType
     * @return SendEntity
     */
    public function withSendingType($SendingType)
    {
        $new = clone $this;
        $new->SendingType = $SendingType;

        return $new;
    }

    /**
     * @return int
     */
    public function getStatus()
    {
        return $this->Status;
    }

    /**
     * @param int $Status
     * @return SendEntity
     */
    public function withStatus($Status)
    {
        $new = clone $this;
        $new->Status = $Status;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\TaskTemplate
     */
    public function getTaskTemplate()
    {
        return $this->TaskTemplate;
    }

    /**
     * @param \ArchiflowWSCard\Type\TaskTemplate $TaskTemplate
     * @return SendEntity
     */
    public function withTaskTemplate($TaskTemplate)
    {
        $new = clone $this;
        $new->TaskTemplate = $TaskTemplate;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBCC()
    {
        return $this->bCC;
    }

    /**
     * @param bool $bCC
     * @return SendEntity
     */
    public function withBCC($bCC)
    {
        $new = clone $this;
        $new->bCC = $bCC;

        return $new;
    }


}

