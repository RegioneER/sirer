<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Additive implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ControlType
     */
    private $AdditiveControlType = null;

    /**
     * @var \ArchiflowWSCard\Type\IdAdditive
     */
    private $AdditiveId = null;

    /**
     * @var int
     */
    private $AdditiveIdList = null;

    /**
     * @var string
     */
    private $AdditiveName = null;

    /**
     * @var string
     */
    private $AdditiveValue = null;

    /**
     * @var string
     */
    private $ImageContent = null;

    /**
     * @var bool
     */
    private $IsListAutomaticInsert = null;

    /**
     * @var bool
     */
    private $IsSigned = null;

    /**
     * @var bool
     */
    private $IsUserEnabledToSign = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ControlType $AdditiveControlType
     * @var \ArchiflowWSCard\Type\IdAdditive $AdditiveId
     * @var int $AdditiveIdList
     * @var string $AdditiveName
     * @var string $AdditiveValue
     * @var string $ImageContent
     * @var bool $IsListAutomaticInsert
     * @var bool $IsSigned
     * @var bool $IsUserEnabledToSign
     */
    public function __construct($AdditiveControlType, $AdditiveId, $AdditiveIdList, $AdditiveName, $AdditiveValue, $ImageContent, $IsListAutomaticInsert, $IsSigned, $IsUserEnabledToSign)
    {
        $this->AdditiveControlType = $AdditiveControlType;
        $this->AdditiveId = $AdditiveId;
        $this->AdditiveIdList = $AdditiveIdList;
        $this->AdditiveName = $AdditiveName;
        $this->AdditiveValue = $AdditiveValue;
        $this->ImageContent = $ImageContent;
        $this->IsListAutomaticInsert = $IsListAutomaticInsert;
        $this->IsSigned = $IsSigned;
        $this->IsUserEnabledToSign = $IsUserEnabledToSign;
    }

    /**
     * @return \ArchiflowWSCard\Type\ControlType
     */
    public function getAdditiveControlType()
    {
        return $this->AdditiveControlType;
    }

    /**
     * @param \ArchiflowWSCard\Type\ControlType $AdditiveControlType
     * @return Additive
     */
    public function withAdditiveControlType($AdditiveControlType)
    {
        $new = clone $this;
        $new->AdditiveControlType = $AdditiveControlType;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdAdditive
     */
    public function getAdditiveId()
    {
        return $this->AdditiveId;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdAdditive $AdditiveId
     * @return Additive
     */
    public function withAdditiveId($AdditiveId)
    {
        $new = clone $this;
        $new->AdditiveId = $AdditiveId;

        return $new;
    }

    /**
     * @return int
     */
    public function getAdditiveIdList()
    {
        return $this->AdditiveIdList;
    }

    /**
     * @param int $AdditiveIdList
     * @return Additive
     */
    public function withAdditiveIdList($AdditiveIdList)
    {
        $new = clone $this;
        $new->AdditiveIdList = $AdditiveIdList;

        return $new;
    }

    /**
     * @return string
     */
    public function getAdditiveName()
    {
        return $this->AdditiveName;
    }

    /**
     * @param string $AdditiveName
     * @return Additive
     */
    public function withAdditiveName($AdditiveName)
    {
        $new = clone $this;
        $new->AdditiveName = $AdditiveName;

        return $new;
    }

    /**
     * @return string
     */
    public function getAdditiveValue()
    {
        return $this->AdditiveValue;
    }

    /**
     * @param string $AdditiveValue
     * @return Additive
     */
    public function withAdditiveValue($AdditiveValue)
    {
        $new = clone $this;
        $new->AdditiveValue = $AdditiveValue;

        return $new;
    }

    /**
     * @return string
     */
    public function getImageContent()
    {
        return $this->ImageContent;
    }

    /**
     * @param string $ImageContent
     * @return Additive
     */
    public function withImageContent($ImageContent)
    {
        $new = clone $this;
        $new->ImageContent = $ImageContent;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsListAutomaticInsert()
    {
        return $this->IsListAutomaticInsert;
    }

    /**
     * @param bool $IsListAutomaticInsert
     * @return Additive
     */
    public function withIsListAutomaticInsert($IsListAutomaticInsert)
    {
        $new = clone $this;
        $new->IsListAutomaticInsert = $IsListAutomaticInsert;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsSigned()
    {
        return $this->IsSigned;
    }

    /**
     * @param bool $IsSigned
     * @return Additive
     */
    public function withIsSigned($IsSigned)
    {
        $new = clone $this;
        $new->IsSigned = $IsSigned;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsUserEnabledToSign()
    {
        return $this->IsUserEnabledToSign;
    }

    /**
     * @param bool $IsUserEnabledToSign
     * @return Additive
     */
    public function withIsUserEnabledToSign($IsUserEnabledToSign)
    {
        $new = clone $this;
        $new->IsUserEnabledToSign = $IsUserEnabledToSign;

        return $new;
    }


}

