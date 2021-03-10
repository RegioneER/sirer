<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class AutoCollationTemplate implements RequestInterface
{

    /**
     * @var int
     */
    private $ArchiveId = null;

    /**
     * @var \ArchiflowWSCard\Type\IdField
     */
    private $DescriptionFieldId = null;

    /**
     * @var int
     */
    private $DocumentTypeId = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var bool
     */
    private $IsAutoCreation = null;

    /**
     * @var bool
     */
    private $IsConfirmationRequired = null;

    /**
     * @var bool
     */
    private $IsDisabled = null;

    /**
     * @var bool
     */
    private $MergeVisibility = null;

    /**
     * @var string
     */
    private $Name = null;

    /**
     * @var \ArchiflowWSCard\Type\IdField
     */
    private $NameFieldId = null;

    /**
     * @var bool
     */
    private $RememberFirst = null;

    /**
     * Constructor
     *
     * @var int $ArchiveId
     * @var \ArchiflowWSCard\Type\IdField $DescriptionFieldId
     * @var int $DocumentTypeId
     * @var int $Id
     * @var bool $IsAutoCreation
     * @var bool $IsConfirmationRequired
     * @var bool $IsDisabled
     * @var bool $MergeVisibility
     * @var string $Name
     * @var \ArchiflowWSCard\Type\IdField $NameFieldId
     * @var bool $RememberFirst
     */
    public function __construct($ArchiveId, $DescriptionFieldId, $DocumentTypeId, $Id, $IsAutoCreation, $IsConfirmationRequired, $IsDisabled, $MergeVisibility, $Name, $NameFieldId, $RememberFirst)
    {
        $this->ArchiveId = $ArchiveId;
        $this->DescriptionFieldId = $DescriptionFieldId;
        $this->DocumentTypeId = $DocumentTypeId;
        $this->Id = $Id;
        $this->IsAutoCreation = $IsAutoCreation;
        $this->IsConfirmationRequired = $IsConfirmationRequired;
        $this->IsDisabled = $IsDisabled;
        $this->MergeVisibility = $MergeVisibility;
        $this->Name = $Name;
        $this->NameFieldId = $NameFieldId;
        $this->RememberFirst = $RememberFirst;
    }

    /**
     * @return int
     */
    public function getArchiveId()
    {
        return $this->ArchiveId;
    }

    /**
     * @param int $ArchiveId
     * @return AutoCollationTemplate
     */
    public function withArchiveId($ArchiveId)
    {
        $new = clone $this;
        $new->ArchiveId = $ArchiveId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdField
     */
    public function getDescriptionFieldId()
    {
        return $this->DescriptionFieldId;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdField $DescriptionFieldId
     * @return AutoCollationTemplate
     */
    public function withDescriptionFieldId($DescriptionFieldId)
    {
        $new = clone $this;
        $new->DescriptionFieldId = $DescriptionFieldId;

        return $new;
    }

    /**
     * @return int
     */
    public function getDocumentTypeId()
    {
        return $this->DocumentTypeId;
    }

    /**
     * @param int $DocumentTypeId
     * @return AutoCollationTemplate
     */
    public function withDocumentTypeId($DocumentTypeId)
    {
        $new = clone $this;
        $new->DocumentTypeId = $DocumentTypeId;

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
     * @return AutoCollationTemplate
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
    public function getIsAutoCreation()
    {
        return $this->IsAutoCreation;
    }

    /**
     * @param bool $IsAutoCreation
     * @return AutoCollationTemplate
     */
    public function withIsAutoCreation($IsAutoCreation)
    {
        $new = clone $this;
        $new->IsAutoCreation = $IsAutoCreation;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsConfirmationRequired()
    {
        return $this->IsConfirmationRequired;
    }

    /**
     * @param bool $IsConfirmationRequired
     * @return AutoCollationTemplate
     */
    public function withIsConfirmationRequired($IsConfirmationRequired)
    {
        $new = clone $this;
        $new->IsConfirmationRequired = $IsConfirmationRequired;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsDisabled()
    {
        return $this->IsDisabled;
    }

    /**
     * @param bool $IsDisabled
     * @return AutoCollationTemplate
     */
    public function withIsDisabled($IsDisabled)
    {
        $new = clone $this;
        $new->IsDisabled = $IsDisabled;

        return $new;
    }

    /**
     * @return bool
     */
    public function getMergeVisibility()
    {
        return $this->MergeVisibility;
    }

    /**
     * @param bool $MergeVisibility
     * @return AutoCollationTemplate
     */
    public function withMergeVisibility($MergeVisibility)
    {
        $new = clone $this;
        $new->MergeVisibility = $MergeVisibility;

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
     * @return AutoCollationTemplate
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdField
     */
    public function getNameFieldId()
    {
        return $this->NameFieldId;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdField $NameFieldId
     * @return AutoCollationTemplate
     */
    public function withNameFieldId($NameFieldId)
    {
        $new = clone $this;
        $new->NameFieldId = $NameFieldId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRememberFirst()
    {
        return $this->RememberFirst;
    }

    /**
     * @param bool $RememberFirst
     * @return AutoCollationTemplate
     */
    public function withRememberFirst($RememberFirst)
    {
        $new = clone $this;
        $new->RememberFirst = $RememberFirst;

        return $new;
    }


}

