<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class DocumentType implements RequestInterface
{

    /**
     * @var string
     */
    private $AddInEmailMapping = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAdditive
     */
    private $Additives = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfshort
     */
    private $ArchiveIds = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentTypeArchiveDocumentTypeOptions
     */
    private $ArchivesOptions = null;

    /**
     * @var int
     */
    private $DefaultClassId = null;

    /**
     * @var int
     */
    private $DocumentTypeId = null;

    /**
     * @var string
     */
    private $DocumentTypeName = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfField
     */
    private $Indexes = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfIdField
     */
    private $InvoiceNotMappedFields = null;

    /**
     * @var bool
     */
    private $IsMandatoryRegType = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfboolean
     */
    private $Options = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfshort
     */
    private $PrivacyArchiveIds = null;

    /**
     * @var \ArchiflowWSCard\Type\WFProcessType
     */
    private $WorkflowProcessType = null;

    /**
     * Constructor
     *
     * @var string $AddInEmailMapping
     * @var \ArchiflowWSCard\Type\ArrayOfAdditive $Additives
     * @var \ArchiflowWSCard\Type\ArrayOfshort $ArchiveIds
     * @var \ArchiflowWSCard\Type\ArrayOfDocumentTypeArchiveDocumentTypeOptions
     * $ArchivesOptions
     * @var int $DefaultClassId
     * @var int $DocumentTypeId
     * @var string $DocumentTypeName
     * @var \ArchiflowWSCard\Type\ArrayOfField $Indexes
     * @var \ArchiflowWSCard\Type\ArrayOfIdField $InvoiceNotMappedFields
     * @var bool $IsMandatoryRegType
     * @var \ArchiflowWSCard\Type\ArrayOfboolean $Options
     * @var \ArchiflowWSCard\Type\ArrayOfshort $PrivacyArchiveIds
     * @var \ArchiflowWSCard\Type\WFProcessType $WorkflowProcessType
     */
    public function __construct($AddInEmailMapping, $Additives, $ArchiveIds, $ArchivesOptions, $DefaultClassId, $DocumentTypeId, $DocumentTypeName, $Indexes, $InvoiceNotMappedFields, $IsMandatoryRegType, $Options, $PrivacyArchiveIds, $WorkflowProcessType)
    {
        $this->AddInEmailMapping = $AddInEmailMapping;
        $this->Additives = $Additives;
        $this->ArchiveIds = $ArchiveIds;
        $this->ArchivesOptions = $ArchivesOptions;
        $this->DefaultClassId = $DefaultClassId;
        $this->DocumentTypeId = $DocumentTypeId;
        $this->DocumentTypeName = $DocumentTypeName;
        $this->Indexes = $Indexes;
        $this->InvoiceNotMappedFields = $InvoiceNotMappedFields;
        $this->IsMandatoryRegType = $IsMandatoryRegType;
        $this->Options = $Options;
        $this->PrivacyArchiveIds = $PrivacyArchiveIds;
        $this->WorkflowProcessType = $WorkflowProcessType;
    }

    /**
     * @return string
     */
    public function getAddInEmailMapping()
    {
        return $this->AddInEmailMapping;
    }

    /**
     * @param string $AddInEmailMapping
     * @return DocumentType
     */
    public function withAddInEmailMapping($AddInEmailMapping)
    {
        $new = clone $this;
        $new->AddInEmailMapping = $AddInEmailMapping;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfAdditive
     */
    public function getAdditives()
    {
        return $this->Additives;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfAdditive $Additives
     * @return DocumentType
     */
    public function withAdditives($Additives)
    {
        $new = clone $this;
        $new->Additives = $Additives;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfshort
     */
    public function getArchiveIds()
    {
        return $this->ArchiveIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfshort $ArchiveIds
     * @return DocumentType
     */
    public function withArchiveIds($ArchiveIds)
    {
        $new = clone $this;
        $new->ArchiveIds = $ArchiveIds;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfDocumentTypeArchiveDocumentTypeOptions
     */
    public function getArchivesOptions()
    {
        return $this->ArchivesOptions;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfDocumentTypeArchiveDocumentTypeOptions
     * $ArchivesOptions
     * @return DocumentType
     */
    public function withArchivesOptions($ArchivesOptions)
    {
        $new = clone $this;
        $new->ArchivesOptions = $ArchivesOptions;

        return $new;
    }

    /**
     * @return int
     */
    public function getDefaultClassId()
    {
        return $this->DefaultClassId;
    }

    /**
     * @param int $DefaultClassId
     * @return DocumentType
     */
    public function withDefaultClassId($DefaultClassId)
    {
        $new = clone $this;
        $new->DefaultClassId = $DefaultClassId;

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
     * @return DocumentType
     */
    public function withDocumentTypeId($DocumentTypeId)
    {
        $new = clone $this;
        $new->DocumentTypeId = $DocumentTypeId;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocumentTypeName()
    {
        return $this->DocumentTypeName;
    }

    /**
     * @param string $DocumentTypeName
     * @return DocumentType
     */
    public function withDocumentTypeName($DocumentTypeName)
    {
        $new = clone $this;
        $new->DocumentTypeName = $DocumentTypeName;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfField
     */
    public function getIndexes()
    {
        return $this->Indexes;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfField $Indexes
     * @return DocumentType
     */
    public function withIndexes($Indexes)
    {
        $new = clone $this;
        $new->Indexes = $Indexes;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfIdField
     */
    public function getInvoiceNotMappedFields()
    {
        return $this->InvoiceNotMappedFields;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfIdField $InvoiceNotMappedFields
     * @return DocumentType
     */
    public function withInvoiceNotMappedFields($InvoiceNotMappedFields)
    {
        $new = clone $this;
        $new->InvoiceNotMappedFields = $InvoiceNotMappedFields;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsMandatoryRegType()
    {
        return $this->IsMandatoryRegType;
    }

    /**
     * @param bool $IsMandatoryRegType
     * @return DocumentType
     */
    public function withIsMandatoryRegType($IsMandatoryRegType)
    {
        $new = clone $this;
        $new->IsMandatoryRegType = $IsMandatoryRegType;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfboolean
     */
    public function getOptions()
    {
        return $this->Options;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfboolean $Options
     * @return DocumentType
     */
    public function withOptions($Options)
    {
        $new = clone $this;
        $new->Options = $Options;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfshort
     */
    public function getPrivacyArchiveIds()
    {
        return $this->PrivacyArchiveIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfshort $PrivacyArchiveIds
     * @return DocumentType
     */
    public function withPrivacyArchiveIds($PrivacyArchiveIds)
    {
        $new = clone $this;
        $new->PrivacyArchiveIds = $PrivacyArchiveIds;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\WFProcessType
     */
    public function getWorkflowProcessType()
    {
        return $this->WorkflowProcessType;
    }

    /**
     * @param \ArchiflowWSCard\Type\WFProcessType $WorkflowProcessType
     * @return DocumentType
     */
    public function withWorkflowProcessType($WorkflowProcessType)
    {
        $new = clone $this;
        $new->WorkflowProcessType = $WorkflowProcessType;

        return $new;
    }


}

