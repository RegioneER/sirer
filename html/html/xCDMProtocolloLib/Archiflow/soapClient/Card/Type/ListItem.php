<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ListItem implements RequestInterface
{

    /**
     * @var int
     */
    private $ClassificationId = null;

    /**
     * @var string
     */
    private $ClassificationLabel = null;

    /**
     * @var string
     */
    private $CodeValue = null;

    /**
     * @var string
     */
    private $DescriptionValue = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var bool
     */
    private $IsAdditive = null;

    /**
     * @var bool
     */
    private $IsExternal = null;

    /**
     * @var bool
     */
    private $UseId = null;

    /**
     * Constructor
     *
     * @var int $ClassificationId
     * @var string $ClassificationLabel
     * @var string $CodeValue
     * @var string $DescriptionValue
     * @var int $Id
     * @var bool $IsAdditive
     * @var bool $IsExternal
     * @var bool $UseId
     */
    public function __construct($ClassificationId, $ClassificationLabel, $CodeValue, $DescriptionValue, $Id, $IsAdditive, $IsExternal, $UseId)
    {
        $this->ClassificationId = $ClassificationId;
        $this->ClassificationLabel = $ClassificationLabel;
        $this->CodeValue = $CodeValue;
        $this->DescriptionValue = $DescriptionValue;
        $this->Id = $Id;
        $this->IsAdditive = $IsAdditive;
        $this->IsExternal = $IsExternal;
        $this->UseId = $UseId;
    }

    /**
     * @return int
     */
    public function getClassificationId()
    {
        return $this->ClassificationId;
    }

    /**
     * @param int $ClassificationId
     * @return ListItem
     */
    public function withClassificationId($ClassificationId)
    {
        $new = clone $this;
        $new->ClassificationId = $ClassificationId;

        return $new;
    }

    /**
     * @return string
     */
    public function getClassificationLabel()
    {
        return $this->ClassificationLabel;
    }

    /**
     * @param string $ClassificationLabel
     * @return ListItem
     */
    public function withClassificationLabel($ClassificationLabel)
    {
        $new = clone $this;
        $new->ClassificationLabel = $ClassificationLabel;

        return $new;
    }

    /**
     * @return string
     */
    public function getCodeValue()
    {
        return $this->CodeValue;
    }

    /**
     * @param string $CodeValue
     * @return ListItem
     */
    public function withCodeValue($CodeValue)
    {
        $new = clone $this;
        $new->CodeValue = $CodeValue;

        return $new;
    }

    /**
     * @return string
     */
    public function getDescriptionValue()
    {
        return $this->DescriptionValue;
    }

    /**
     * @param string $DescriptionValue
     * @return ListItem
     */
    public function withDescriptionValue($DescriptionValue)
    {
        $new = clone $this;
        $new->DescriptionValue = $DescriptionValue;

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
     * @return ListItem
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsAdditive()
    {
        return $this->IsAdditive;
    }

    /**
     * @param bool $IsAdditive
     * @return ListItem
     */
    public function withIsAdditive($IsAdditive)
    {
        $new = clone $this;
        $new->IsAdditive = $IsAdditive;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsExternal()
    {
        return $this->IsExternal;
    }

    /**
     * @param bool $IsExternal
     * @return ListItem
     */
    public function withIsExternal($IsExternal)
    {
        $new = clone $this;
        $new->IsExternal = $IsExternal;

        return $new;
    }

    /**
     * @return bool
     */
    public function getUseId()
    {
        return $this->UseId;
    }

    /**
     * @param bool $UseId
     * @return ListItem
     */
    public function withUseId($UseId)
    {
        $new = clone $this;
        $new->UseId = $UseId;

        return $new;
    }


}

