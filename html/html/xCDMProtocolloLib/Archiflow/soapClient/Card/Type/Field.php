<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Field implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Color
     */
    private $DescriptionColor = null;

    /**
     * @var int
     */
    private $DocumentTypeId = null;

    /**
     * @var \ArchiflowWSCard\Type\ControlType
     */
    private $FieldControlType = null;

    /**
     * @var \ArchiflowWSCard\Type\DataType
     */
    private $FieldDataType = null;

    /**
     * @var string
     */
    private $FieldDescription = null;

    /**
     * @var \ArchiflowWSCard\Type\IdField
     */
    private $FieldId = null;

    /**
     * @var int
     */
    private $FieldIdList = null;

    /**
     * @var string
     */
    private $FieldValue = null;

    /**
     * @var string
     */
    private $FieldValueTo = null;

    /**
     * @var bool
     */
    private $IsDocumentName = null;

    /**
     * @var bool
     */
    private $IsEmptyList = null;

    /**
     * @var bool
     */
    private $IsExternalData = null;

    /**
     * @var bool
     */
    private $IsHidden = null;

    /**
     * @var bool
     */
    private $IsListAutomaticInsert = null;

    /**
     * @var bool
     */
    private $IsListDraftState = null;

    /**
     * @var bool
     */
    private $IsListInsertCode = null;

    /**
     * @var bool
     */
    private $IsListRelation = null;

    /**
     * @var bool
     */
    private $IsMailId = null;

    /**
     * @var bool
     */
    private $IsMultipleSelection = null;

    /**
     * @var bool
     */
    private $IsNotModify = null;

    /**
     * @var bool
     */
    private $IsNotNull = null;

    /**
     * @var bool
     */
    private $IsNotNullArchive = null;

    /**
     * @var bool
     */
    private $IsOfficeRelation = null;

    /**
     * @var bool
     */
    private $IsSystem = null;

    /**
     * @var \ArchiflowWSCard\Type\Language
     */
    private $Language = null;

    /**
     * @var int
     */
    private $Length = null;

    /**
     * @var \ArchiflowWSCard\Type\IdField
     */
    private $ListFieldChild = null;

    /**
     * @var \ArchiflowWSCard\Type\IdField
     */
    private $ListFieldParent = null;

    /**
     * @var \ArchiflowWSCard\Type\Color
     */
    private $ValueColor = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Color $DescriptionColor
     * @var int $DocumentTypeId
     * @var \ArchiflowWSCard\Type\ControlType $FieldControlType
     * @var \ArchiflowWSCard\Type\DataType $FieldDataType
     * @var string $FieldDescription
     * @var \ArchiflowWSCard\Type\IdField $FieldId
     * @var int $FieldIdList
     * @var string $FieldValue
     * @var string $FieldValueTo
     * @var bool $IsDocumentName
     * @var bool $IsEmptyList
     * @var bool $IsExternalData
     * @var bool $IsHidden
     * @var bool $IsListAutomaticInsert
     * @var bool $IsListDraftState
     * @var bool $IsListInsertCode
     * @var bool $IsListRelation
     * @var bool $IsMailId
     * @var bool $IsMultipleSelection
     * @var bool $IsNotModify
     * @var bool $IsNotNull
     * @var bool $IsNotNullArchive
     * @var bool $IsOfficeRelation
     * @var bool $IsSystem
     * @var \ArchiflowWSCard\Type\Language $Language
     * @var int $Length
     * @var \ArchiflowWSCard\Type\IdField $ListFieldChild
     * @var \ArchiflowWSCard\Type\IdField $ListFieldParent
     * @var \ArchiflowWSCard\Type\Color $ValueColor
     */
    public function __construct($DescriptionColor, $DocumentTypeId, $FieldControlType, $FieldDataType, $FieldDescription, $FieldId, $FieldIdList, $FieldValue, $FieldValueTo, $IsDocumentName, $IsEmptyList, $IsExternalData, $IsHidden, $IsListAutomaticInsert, $IsListDraftState, $IsListInsertCode, $IsListRelation, $IsMailId, $IsMultipleSelection, $IsNotModify, $IsNotNull, $IsNotNullArchive, $IsOfficeRelation, $IsSystem, $Language, $Length, $ListFieldChild, $ListFieldParent, $ValueColor)
    {
        $this->DescriptionColor = $DescriptionColor;
        $this->DocumentTypeId = $DocumentTypeId;
        $this->FieldControlType = $FieldControlType;
        $this->FieldDataType = $FieldDataType;
        $this->FieldDescription = $FieldDescription;
        $this->FieldId = $FieldId;
        $this->FieldIdList = $FieldIdList;
        $this->FieldValue = $FieldValue;
        $this->FieldValueTo = $FieldValueTo;
        $this->IsDocumentName = $IsDocumentName;
        $this->IsEmptyList = $IsEmptyList;
        $this->IsExternalData = $IsExternalData;
        $this->IsHidden = $IsHidden;
        $this->IsListAutomaticInsert = $IsListAutomaticInsert;
        $this->IsListDraftState = $IsListDraftState;
        $this->IsListInsertCode = $IsListInsertCode;
        $this->IsListRelation = $IsListRelation;
        $this->IsMailId = $IsMailId;
        $this->IsMultipleSelection = $IsMultipleSelection;
        $this->IsNotModify = $IsNotModify;
        $this->IsNotNull = $IsNotNull;
        $this->IsNotNullArchive = $IsNotNullArchive;
        $this->IsOfficeRelation = $IsOfficeRelation;
        $this->IsSystem = $IsSystem;
        $this->Language = $Language;
        $this->Length = $Length;
        $this->ListFieldChild = $ListFieldChild;
        $this->ListFieldParent = $ListFieldParent;
        $this->ValueColor = $ValueColor;
    }

    public static function createLite($DocumentTypeId, $FieldId, $FieldValue, $FieldValueTo, $IsDocumentName)
    {
        $instance = new self(null,0,"CtEdit","DtDate",null,"IfDateDoc",0,null,null,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,"Italian",0,"IfReference","IfReference",null);
        $instance->DocumentTypeId = $DocumentTypeId;
        $instance->FieldId = $FieldId;
        $instance->FieldValue = $FieldValue;
        $instance->FieldValueTo = $FieldValueTo;
        $instance->IsDocumentName = $IsDocumentName;
        return $instance;
    }

    /**
     * @return \ArchiflowWSCard\Type\Color
     */
    public function getDescriptionColor()
    {
        return $this->DescriptionColor;
    }

    /**
     * @param \ArchiflowWSCard\Type\Color $DescriptionColor
     * @return Field
     */
    public function withDescriptionColor($DescriptionColor)
    {
        $new = clone $this;
        $new->DescriptionColor = $DescriptionColor;

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
     * @return Field
     */
    public function withDocumentTypeId($DocumentTypeId)
    {
        $new = clone $this;
        $new->DocumentTypeId = $DocumentTypeId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ControlType
     */
    public function getFieldControlType()
    {
        return $this->FieldControlType;
    }

    /**
     * @param \ArchiflowWSCard\Type\ControlType $FieldControlType
     * @return Field
     */
    public function withFieldControlType($FieldControlType)
    {
        $new = clone $this;
        $new->FieldControlType = $FieldControlType;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\DataType
     */
    public function getFieldDataType()
    {
        return $this->FieldDataType;
    }

    /**
     * @param \ArchiflowWSCard\Type\DataType $FieldDataType
     * @return Field
     */
    public function withFieldDataType($FieldDataType)
    {
        $new = clone $this;
        $new->FieldDataType = $FieldDataType;

        return $new;
    }

    /**
     * @return string
     */
    public function getFieldDescription()
    {
        return $this->FieldDescription;
    }

    /**
     * @param string $FieldDescription
     * @return Field
     */
    public function withFieldDescription($FieldDescription)
    {
        $new = clone $this;
        $new->FieldDescription = $FieldDescription;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdField
     */
    public function getFieldId()
    {
        return $this->FieldId;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdField $FieldId
     * @return Field
     */
    public function withFieldId($FieldId)
    {
        $new = clone $this;
        $new->FieldId = $FieldId;

        return $new;
    }

    /**
     * @return int
     */
    public function getFieldIdList()
    {
        return $this->FieldIdList;
    }

    /**
     * @param int $FieldIdList
     * @return Field
     */
    public function withFieldIdList($FieldIdList)
    {
        $new = clone $this;
        $new->FieldIdList = $FieldIdList;

        return $new;
    }

    /**
     * @return string
     */
    public function getFieldValue()
    {
        return $this->FieldValue;
    }

    /**
     * @param string $FieldValue
     * @return Field
     */
    public function withFieldValue($FieldValue)
    {
        $new = clone $this;
        $new->FieldValue = $FieldValue;

        return $new;
    }

    /**
     * @return string
     */
    public function getFieldValueTo()
    {
        return $this->FieldValueTo;
    }

    /**
     * @param string $FieldValueTo
     * @return Field
     */
    public function withFieldValueTo($FieldValueTo)
    {
        $new = clone $this;
        $new->FieldValueTo = $FieldValueTo;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsDocumentName()
    {
        return $this->IsDocumentName;
    }

    /**
     * @param bool $IsDocumentName
     * @return Field
     */
    public function withIsDocumentName($IsDocumentName)
    {
        $new = clone $this;
        $new->IsDocumentName = $IsDocumentName;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsEmptyList()
    {
        return $this->IsEmptyList;
    }

    /**
     * @param bool $IsEmptyList
     * @return Field
     */
    public function withIsEmptyList($IsEmptyList)
    {
        $new = clone $this;
        $new->IsEmptyList = $IsEmptyList;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsExternalData()
    {
        return $this->IsExternalData;
    }

    /**
     * @param bool $IsExternalData
     * @return Field
     */
    public function withIsExternalData($IsExternalData)
    {
        $new = clone $this;
        $new->IsExternalData = $IsExternalData;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsHidden()
    {
        return $this->IsHidden;
    }

    /**
     * @param bool $IsHidden
     * @return Field
     */
    public function withIsHidden($IsHidden)
    {
        $new = clone $this;
        $new->IsHidden = $IsHidden;

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
     * @return Field
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
    public function getIsListDraftState()
    {
        return $this->IsListDraftState;
    }

    /**
     * @param bool $IsListDraftState
     * @return Field
     */
    public function withIsListDraftState($IsListDraftState)
    {
        $new = clone $this;
        $new->IsListDraftState = $IsListDraftState;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsListInsertCode()
    {
        return $this->IsListInsertCode;
    }

    /**
     * @param bool $IsListInsertCode
     * @return Field
     */
    public function withIsListInsertCode($IsListInsertCode)
    {
        $new = clone $this;
        $new->IsListInsertCode = $IsListInsertCode;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsListRelation()
    {
        return $this->IsListRelation;
    }

    /**
     * @param bool $IsListRelation
     * @return Field
     */
    public function withIsListRelation($IsListRelation)
    {
        $new = clone $this;
        $new->IsListRelation = $IsListRelation;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsMailId()
    {
        return $this->IsMailId;
    }

    /**
     * @param bool $IsMailId
     * @return Field
     */
    public function withIsMailId($IsMailId)
    {
        $new = clone $this;
        $new->IsMailId = $IsMailId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsMultipleSelection()
    {
        return $this->IsMultipleSelection;
    }

    /**
     * @param bool $IsMultipleSelection
     * @return Field
     */
    public function withIsMultipleSelection($IsMultipleSelection)
    {
        $new = clone $this;
        $new->IsMultipleSelection = $IsMultipleSelection;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsNotModify()
    {
        return $this->IsNotModify;
    }

    /**
     * @param bool $IsNotModify
     * @return Field
     */
    public function withIsNotModify($IsNotModify)
    {
        $new = clone $this;
        $new->IsNotModify = $IsNotModify;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsNotNull()
    {
        return $this->IsNotNull;
    }

    /**
     * @param bool $IsNotNull
     * @return Field
     */
    public function withIsNotNull($IsNotNull)
    {
        $new = clone $this;
        $new->IsNotNull = $IsNotNull;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsNotNullArchive()
    {
        return $this->IsNotNullArchive;
    }

    /**
     * @param bool $IsNotNullArchive
     * @return Field
     */
    public function withIsNotNullArchive($IsNotNullArchive)
    {
        $new = clone $this;
        $new->IsNotNullArchive = $IsNotNullArchive;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsOfficeRelation()
    {
        return $this->IsOfficeRelation;
    }

    /**
     * @param bool $IsOfficeRelation
     * @return Field
     */
    public function withIsOfficeRelation($IsOfficeRelation)
    {
        $new = clone $this;
        $new->IsOfficeRelation = $IsOfficeRelation;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsSystem()
    {
        return $this->IsSystem;
    }

    /**
     * @param bool $IsSystem
     * @return Field
     */
    public function withIsSystem($IsSystem)
    {
        $new = clone $this;
        $new->IsSystem = $IsSystem;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Language
     */
    public function getLanguage()
    {
        return $this->Language;
    }

    /**
     * @param \ArchiflowWSCard\Type\Language $Language
     * @return Field
     */
    public function withLanguage($Language)
    {
        $new = clone $this;
        $new->Language = $Language;

        return $new;
    }

    /**
     * @return int
     */
    public function getLength()
    {
        return $this->Length;
    }

    /**
     * @param int $Length
     * @return Field
     */
    public function withLength($Length)
    {
        $new = clone $this;
        $new->Length = $Length;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdField
     */
    public function getListFieldChild()
    {
        return $this->ListFieldChild;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdField $ListFieldChild
     * @return Field
     */
    public function withListFieldChild($ListFieldChild)
    {
        $new = clone $this;
        $new->ListFieldChild = $ListFieldChild;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\IdField
     */
    public function getListFieldParent()
    {
        return $this->ListFieldParent;
    }

    /**
     * @param \ArchiflowWSCard\Type\IdField $ListFieldParent
     * @return Field
     */
    public function withListFieldParent($ListFieldParent)
    {
        $new = clone $this;
        $new->ListFieldParent = $ListFieldParent;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Color
     */
    public function getValueColor()
    {
        return $this->ValueColor;
    }

    /**
     * @param \ArchiflowWSCard\Type\Color $ValueColor
     * @return Field
     */
    public function withValueColor($ValueColor)
    {
        $new = clone $this;
        $new->ValueColor = $ValueColor;

        return $new;
    }


}

