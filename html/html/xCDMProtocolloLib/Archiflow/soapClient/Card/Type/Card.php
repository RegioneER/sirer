<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Card implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfAdditive
     */
    private $Additives = null;

    /**
     * @var int
     */
    private $ArchiveId = null;

    /**
     * @var \ArchiflowWSCard\Type\CardExpirationInfo
     */
    private $CardExpiration = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var int
     */
    private $CardProg = null;

    /**
     * @var string
     */
    private $ComputerizedClassification = null;

    /**
     * @var string
     */
    private $ComputerizedFolder = null;

    /**
     * @var \ArchiflowWSCard\Type\DocumentStatus
     */
    private $DocStatus = null;

    /**
     * @var string
     */
    private $DocumentExtension = null;

    /**
     * @var int
     */
    private $DocumentTypeId = null;

    /**
     * @var string
     */
    private $EncryptedCardId = null;

    /**
     * @var \ArchiflowWSCard\Type\ExternNotification
     */
    private $ExternMailNotification = null;

    /**
     * @var string
     */
    private $ExternMailNotificationXML = null;

    /**
     * @var bool
     */
    private $HasAdditionalData = null;

    /**
     * @var bool
     */
    private $HasAttachment = null;

    /**
     * @var bool
     */
    private $HasComputerizedClassification = null;

    /**
     * @var bool
     */
    private $HasComputerizedFolder = null;

    /**
     * @var \ArchiflowWSCard\Type\CardHasData
     */
    private $HasData = null;

    /**
     * @var bool
     */
    private $HasDocument = null;

    /**
     * @var bool
     */
    private $HasFolder = null;

    /**
     * @var bool
     */
    private $HasKeyVersions = null;

    /**
     * @var bool
     */
    private $HasNotes = null;

    /**
     * @var bool
     */
    private $HasPartialInvalidations = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfField
     */
    private $Indexes = null;

    /**
     * @var \ArchiflowWSCard\Type\Annotation
     */
    private $InvalidateAnnotation = null;

    /**
     * @var \ArchiflowWSCard\Type\InvoiceBase
     */
    private $Invoice = null;

    /**
     * @var bool
     */
    private $IsCC = null;

    /**
     * @var bool
     */
    private $IsCurrUserVisDoc = null;

    /**
     * @var bool
     */
    private $IsDocumentLocked = null;

    /**
     * @var bool
     */
    private $IsReadOnly = null;

    /**
     * @var bool
     */
    private $IsSigned = null;

    /**
     * @var bool
     */
    private $IsSignedPdf = null;

    /**
     * @var bool
     */
    private $IsSignedXml = null;

    /**
     * @var bool
     */
    private $IsSorted = null;

    /**
     * @var bool
     */
    private $IsStoredProtocol = null;

    /**
     * @var bool
     */
    private $IsValid = null;

    /**
     * @var bool
     */
    private $IsVisOnlyDoc = null;

    /**
     * @var bool
     */
    private $IsWf = null;

    /**
     * @var bool
     */
    private $IsWfReadOnly = null;

    /**
     * @var int
     */
    private $NumPages = null;

    /**
     * @var \ArchiflowWSCard\Type\CardOperationsFromList
     */
    private $OpsFromList = null;

    /**
     * @var string
     */
    private $OriginalFileName = null;

    /**
     * @var \ArchiflowWSCard\Type\ProcWF
     */
    private $ProcWF = null;

    /**
     * @var string
     */
    private $Progressive = null;

    /**
     * @var string
     */
    private $SignedExtension = null;

    /**
     * @var \ArchiflowWSCard\Type\CardStatus
     */
    private $Status = null;

    /**
     * @var string
     */
    private $StreamId = null;

    /**
     * @var string
     */
    private $StreamIdShared = null;

    /**
     * @var \ArchiflowWSCard\Type\TimeStampFileFormat
     */
    private $TimeStampFormat = null;

    /**
     * @var int
     */
    private $UserIdModifying = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfAdditive $Additives
     * @var int $ArchiveId
     * @var \ArchiflowWSCard\Type\CardExpirationInfo $CardExpiration
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var int $CardProg
     * @var string $ComputerizedClassification
     * @var string $ComputerizedFolder
     * @var \ArchiflowWSCard\Type\DocumentStatus $DocStatus
     * @var string $DocumentExtension
     * @var int $DocumentTypeId
     * @var string $EncryptedCardId
     * @var \ArchiflowWSCard\Type\ExternNotification $ExternMailNotification
     * @var string $ExternMailNotificationXML
     * @var bool $HasAdditionalData
     * @var bool $HasAttachment
     * @var bool $HasComputerizedClassification
     * @var bool $HasComputerizedFolder
     * @var \ArchiflowWSCard\Type\CardHasData $HasData
     * @var bool $HasDocument
     * @var bool $HasFolder
     * @var bool $HasKeyVersions
     * @var bool $HasNotes
     * @var bool $HasPartialInvalidations
     * @var \ArchiflowWSCard\Type\ArrayOfField $Indexes
     * @var \ArchiflowWSCard\Type\Annotation $InvalidateAnnotation
     * @var \ArchiflowWSCard\Type\InvoiceBase $Invoice
     * @var bool $IsCC
     * @var bool $IsCurrUserVisDoc
     * @var bool $IsDocumentLocked
     * @var bool $IsReadOnly
     * @var bool $IsSigned
     * @var bool $IsSignedPdf
     * @var bool $IsSignedXml
     * @var bool $IsSorted
     * @var bool $IsStoredProtocol
     * @var bool $IsValid
     * @var bool $IsVisOnlyDoc
     * @var bool $IsWf
     * @var bool $IsWfReadOnly
     * @var int $NumPages
     * @var \ArchiflowWSCard\Type\CardOperationsFromList $OpsFromList
     * @var string $OriginalFileName
     * @var \ArchiflowWSCard\Type\ProcWF $ProcWF
     * @var string $Progressive
     * @var string $SignedExtension
     * @var \ArchiflowWSCard\Type\CardStatus $Status
     * @var string $StreamId
     * @var string $StreamIdShared
     * @var \ArchiflowWSCard\Type\TimeStampFileFormat $TimeStampFormat
     * @var int $UserIdModifying
     */
    public function __construct($Additives, $ArchiveId, $CardExpiration, $CardId, $CardProg, $ComputerizedClassification, $ComputerizedFolder, $DocStatus, $DocumentExtension, $DocumentTypeId, $EncryptedCardId, $ExternMailNotification, $ExternMailNotificationXML, $HasAdditionalData, $HasAttachment, $HasComputerizedClassification, $HasComputerizedFolder, $HasData, $HasDocument, $HasFolder, $HasKeyVersions, $HasNotes, $HasPartialInvalidations, $Indexes, $InvalidateAnnotation, $Invoice, $IsCC, $IsCurrUserVisDoc, $IsDocumentLocked, $IsReadOnly, $IsSigned, $IsSignedPdf, $IsSignedXml, $IsSorted, $IsStoredProtocol, $IsValid, $IsVisOnlyDoc, $IsWf, $IsWfReadOnly, $NumPages, $OpsFromList, $OriginalFileName, $ProcWF, $Progressive, $SignedExtension, $Status, $StreamId, $StreamIdShared, $TimeStampFormat, $UserIdModifying)
    {
        $this->Additives = $Additives;
        $this->ArchiveId = $ArchiveId;
        $this->CardExpiration = $CardExpiration;
        $this->CardId = $CardId;
        $this->CardProg = $CardProg;
        $this->ComputerizedClassification = $ComputerizedClassification;
        $this->ComputerizedFolder = $ComputerizedFolder;
        $this->DocStatus = $DocStatus;
        $this->DocumentExtension = $DocumentExtension;
        $this->DocumentTypeId = $DocumentTypeId;
        $this->EncryptedCardId = $EncryptedCardId;
        $this->ExternMailNotification = $ExternMailNotification;
        $this->ExternMailNotificationXML = $ExternMailNotificationXML;
        $this->HasAdditionalData = $HasAdditionalData;
        $this->HasAttachment = $HasAttachment;
        $this->HasComputerizedClassification = $HasComputerizedClassification;
        $this->HasComputerizedFolder = $HasComputerizedFolder;
        $this->HasData = $HasData;
        $this->HasDocument = $HasDocument;
        $this->HasFolder = $HasFolder;
        $this->HasKeyVersions = $HasKeyVersions;
        $this->HasNotes = $HasNotes;
        $this->HasPartialInvalidations = $HasPartialInvalidations;
        $this->Indexes = $Indexes;
        $this->InvalidateAnnotation = $InvalidateAnnotation;
        $this->Invoice = $Invoice;
        $this->IsCC = $IsCC;
        $this->IsCurrUserVisDoc = $IsCurrUserVisDoc;
        $this->IsDocumentLocked = $IsDocumentLocked;
        $this->IsReadOnly = $IsReadOnly;
        $this->IsSigned = $IsSigned;
        $this->IsSignedPdf = $IsSignedPdf;
        $this->IsSignedXml = $IsSignedXml;
        $this->IsSorted = $IsSorted;
        $this->IsStoredProtocol = $IsStoredProtocol;
        $this->IsValid = $IsValid;
        $this->IsVisOnlyDoc = $IsVisOnlyDoc;
        $this->IsWf = $IsWf;
        $this->IsWfReadOnly = $IsWfReadOnly;
        $this->NumPages = $NumPages;
        $this->OpsFromList = $OpsFromList;
        $this->OriginalFileName = $OriginalFileName;
        $this->ProcWF = $ProcWF;
        $this->Progressive = $Progressive;
        $this->SignedExtension = $SignedExtension;
        $this->Status = $Status;
        $this->StreamId = $StreamId;
        $this->StreamIdShared = $StreamIdShared;
        $this->TimeStampFormat = $TimeStampFormat;
        $this->UserIdModifying = $UserIdModifying;
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
     * @return Card
     */
    public function withAdditives($Additives)
    {
        $new = clone $this;
        $new->Additives = $Additives;

        return $new;
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
     * @return Card
     */
    public function withArchiveId($ArchiveId)
    {
        $new = clone $this;
        $new->ArchiveId = $ArchiveId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardExpirationInfo
     */
    public function getCardExpiration()
    {
        return $this->CardExpiration;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardExpirationInfo $CardExpiration
     * @return Card
     */
    public function withCardExpiration($CardExpiration)
    {
        $new = clone $this;
        $new->CardExpiration = $CardExpiration;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $CardId
     * @return Card
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return int
     */
    public function getCardProg()
    {
        return $this->CardProg;
    }

    /**
     * @param int $CardProg
     * @return Card
     */
    public function withCardProg($CardProg)
    {
        $new = clone $this;
        $new->CardProg = $CardProg;

        return $new;
    }

    /**
     * @return string
     */
    public function getComputerizedClassification()
    {
        return $this->ComputerizedClassification;
    }

    /**
     * @param string $ComputerizedClassification
     * @return Card
     */
    public function withComputerizedClassification($ComputerizedClassification)
    {
        $new = clone $this;
        $new->ComputerizedClassification = $ComputerizedClassification;

        return $new;
    }

    /**
     * @return string
     */
    public function getComputerizedFolder()
    {
        return $this->ComputerizedFolder;
    }

    /**
     * @param string $ComputerizedFolder
     * @return Card
     */
    public function withComputerizedFolder($ComputerizedFolder)
    {
        $new = clone $this;
        $new->ComputerizedFolder = $ComputerizedFolder;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\DocumentStatus
     */
    public function getDocStatus()
    {
        return $this->DocStatus;
    }

    /**
     * @param \ArchiflowWSCard\Type\DocumentStatus $DocStatus
     * @return Card
     */
    public function withDocStatus($DocStatus)
    {
        $new = clone $this;
        $new->DocStatus = $DocStatus;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocumentExtension()
    {
        return $this->DocumentExtension;
    }

    /**
     * @param string $DocumentExtension
     * @return Card
     */
    public function withDocumentExtension($DocumentExtension)
    {
        $new = clone $this;
        $new->DocumentExtension = $DocumentExtension;

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
     * @return Card
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
    public function getEncryptedCardId()
    {
        return $this->EncryptedCardId;
    }

    /**
     * @param string $EncryptedCardId
     * @return Card
     */
    public function withEncryptedCardId($EncryptedCardId)
    {
        $new = clone $this;
        $new->EncryptedCardId = $EncryptedCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExternNotification
     */
    public function getExternMailNotification()
    {
        return $this->ExternMailNotification;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExternNotification $ExternMailNotification
     * @return Card
     */
    public function withExternMailNotification($ExternMailNotification)
    {
        $new = clone $this;
        $new->ExternMailNotification = $ExternMailNotification;

        return $new;
    }

    /**
     * @return string
     */
    public function getExternMailNotificationXML()
    {
        return $this->ExternMailNotificationXML;
    }

    /**
     * @param string $ExternMailNotificationXML
     * @return Card
     */
    public function withExternMailNotificationXML($ExternMailNotificationXML)
    {
        $new = clone $this;
        $new->ExternMailNotificationXML = $ExternMailNotificationXML;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasAdditionalData()
    {
        return $this->HasAdditionalData;
    }

    /**
     * @param bool $HasAdditionalData
     * @return Card
     */
    public function withHasAdditionalData($HasAdditionalData)
    {
        $new = clone $this;
        $new->HasAdditionalData = $HasAdditionalData;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasAttachment()
    {
        return $this->HasAttachment;
    }

    /**
     * @param bool $HasAttachment
     * @return Card
     */
    public function withHasAttachment($HasAttachment)
    {
        $new = clone $this;
        $new->HasAttachment = $HasAttachment;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasComputerizedClassification()
    {
        return $this->HasComputerizedClassification;
    }

    /**
     * @param bool $HasComputerizedClassification
     * @return Card
     */
    public function withHasComputerizedClassification($HasComputerizedClassification)
    {
        $new = clone $this;
        $new->HasComputerizedClassification = $HasComputerizedClassification;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasComputerizedFolder()
    {
        return $this->HasComputerizedFolder;
    }

    /**
     * @param bool $HasComputerizedFolder
     * @return Card
     */
    public function withHasComputerizedFolder($HasComputerizedFolder)
    {
        $new = clone $this;
        $new->HasComputerizedFolder = $HasComputerizedFolder;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardHasData
     */
    public function getHasData()
    {
        return $this->HasData;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardHasData $HasData
     * @return Card
     */
    public function withHasData($HasData)
    {
        $new = clone $this;
        $new->HasData = $HasData;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasDocument()
    {
        return $this->HasDocument;
    }

    /**
     * @param bool $HasDocument
     * @return Card
     */
    public function withHasDocument($HasDocument)
    {
        $new = clone $this;
        $new->HasDocument = $HasDocument;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasFolder()
    {
        return $this->HasFolder;
    }

    /**
     * @param bool $HasFolder
     * @return Card
     */
    public function withHasFolder($HasFolder)
    {
        $new = clone $this;
        $new->HasFolder = $HasFolder;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasKeyVersions()
    {
        return $this->HasKeyVersions;
    }

    /**
     * @param bool $HasKeyVersions
     * @return Card
     */
    public function withHasKeyVersions($HasKeyVersions)
    {
        $new = clone $this;
        $new->HasKeyVersions = $HasKeyVersions;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasNotes()
    {
        return $this->HasNotes;
    }

    /**
     * @param bool $HasNotes
     * @return Card
     */
    public function withHasNotes($HasNotes)
    {
        $new = clone $this;
        $new->HasNotes = $HasNotes;

        return $new;
    }

    /**
     * @return bool
     */
    public function getHasPartialInvalidations()
    {
        return $this->HasPartialInvalidations;
    }

    /**
     * @param bool $HasPartialInvalidations
     * @return Card
     */
    public function withHasPartialInvalidations($HasPartialInvalidations)
    {
        $new = clone $this;
        $new->HasPartialInvalidations = $HasPartialInvalidations;

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
     * @return Card
     */
    public function withIndexes($Indexes)
    {
        $new = clone $this;
        $new->Indexes = $Indexes;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Annotation
     */
    public function getInvalidateAnnotation()
    {
        return $this->InvalidateAnnotation;
    }

    /**
     * @param \ArchiflowWSCard\Type\Annotation $InvalidateAnnotation
     * @return Card
     */
    public function withInvalidateAnnotation($InvalidateAnnotation)
    {
        $new = clone $this;
        $new->InvalidateAnnotation = $InvalidateAnnotation;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\InvoiceBase
     */
    public function getInvoice()
    {
        return $this->Invoice;
    }

    /**
     * @param \ArchiflowWSCard\Type\InvoiceBase $Invoice
     * @return Card
     */
    public function withInvoice($Invoice)
    {
        $new = clone $this;
        $new->Invoice = $Invoice;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsCC()
    {
        return $this->IsCC;
    }

    /**
     * @param bool $IsCC
     * @return Card
     */
    public function withIsCC($IsCC)
    {
        $new = clone $this;
        $new->IsCC = $IsCC;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsCurrUserVisDoc()
    {
        return $this->IsCurrUserVisDoc;
    }

    /**
     * @param bool $IsCurrUserVisDoc
     * @return Card
     */
    public function withIsCurrUserVisDoc($IsCurrUserVisDoc)
    {
        $new = clone $this;
        $new->IsCurrUserVisDoc = $IsCurrUserVisDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsDocumentLocked()
    {
        return $this->IsDocumentLocked;
    }

    /**
     * @param bool $IsDocumentLocked
     * @return Card
     */
    public function withIsDocumentLocked($IsDocumentLocked)
    {
        $new = clone $this;
        $new->IsDocumentLocked = $IsDocumentLocked;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsReadOnly()
    {
        return $this->IsReadOnly;
    }

    /**
     * @param bool $IsReadOnly
     * @return Card
     */
    public function withIsReadOnly($IsReadOnly)
    {
        $new = clone $this;
        $new->IsReadOnly = $IsReadOnly;

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
     * @return Card
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
    public function getIsSignedPdf()
    {
        return $this->IsSignedPdf;
    }

    /**
     * @param bool $IsSignedPdf
     * @return Card
     */
    public function withIsSignedPdf($IsSignedPdf)
    {
        $new = clone $this;
        $new->IsSignedPdf = $IsSignedPdf;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsSignedXml()
    {
        return $this->IsSignedXml;
    }

    /**
     * @param bool $IsSignedXml
     * @return Card
     */
    public function withIsSignedXml($IsSignedXml)
    {
        $new = clone $this;
        $new->IsSignedXml = $IsSignedXml;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsSorted()
    {
        return $this->IsSorted;
    }

    /**
     * @param bool $IsSorted
     * @return Card
     */
    public function withIsSorted($IsSorted)
    {
        $new = clone $this;
        $new->IsSorted = $IsSorted;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsStoredProtocol()
    {
        return $this->IsStoredProtocol;
    }

    /**
     * @param bool $IsStoredProtocol
     * @return Card
     */
    public function withIsStoredProtocol($IsStoredProtocol)
    {
        $new = clone $this;
        $new->IsStoredProtocol = $IsStoredProtocol;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsValid()
    {
        return $this->IsValid;
    }

    /**
     * @param bool $IsValid
     * @return Card
     */
    public function withIsValid($IsValid)
    {
        $new = clone $this;
        $new->IsValid = $IsValid;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsVisOnlyDoc()
    {
        return $this->IsVisOnlyDoc;
    }

    /**
     * @param bool $IsVisOnlyDoc
     * @return Card
     */
    public function withIsVisOnlyDoc($IsVisOnlyDoc)
    {
        $new = clone $this;
        $new->IsVisOnlyDoc = $IsVisOnlyDoc;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsWf()
    {
        return $this->IsWf;
    }

    /**
     * @param bool $IsWf
     * @return Card
     */
    public function withIsWf($IsWf)
    {
        $new = clone $this;
        $new->IsWf = $IsWf;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsWfReadOnly()
    {
        return $this->IsWfReadOnly;
    }

    /**
     * @param bool $IsWfReadOnly
     * @return Card
     */
    public function withIsWfReadOnly($IsWfReadOnly)
    {
        $new = clone $this;
        $new->IsWfReadOnly = $IsWfReadOnly;

        return $new;
    }

    /**
     * @return int
     */
    public function getNumPages()
    {
        return $this->NumPages;
    }

    /**
     * @param int $NumPages
     * @return Card
     */
    public function withNumPages($NumPages)
    {
        $new = clone $this;
        $new->NumPages = $NumPages;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardOperationsFromList
     */
    public function getOpsFromList()
    {
        return $this->OpsFromList;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardOperationsFromList $OpsFromList
     * @return Card
     */
    public function withOpsFromList($OpsFromList)
    {
        $new = clone $this;
        $new->OpsFromList = $OpsFromList;

        return $new;
    }

    /**
     * @return string
     */
    public function getOriginalFileName()
    {
        return $this->OriginalFileName;
    }

    /**
     * @param string $OriginalFileName
     * @return Card
     */
    public function withOriginalFileName($OriginalFileName)
    {
        $new = clone $this;
        $new->OriginalFileName = $OriginalFileName;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ProcWF
     */
    public function getProcWF()
    {
        return $this->ProcWF;
    }

    /**
     * @param \ArchiflowWSCard\Type\ProcWF $ProcWF
     * @return Card
     */
    public function withProcWF($ProcWF)
    {
        $new = clone $this;
        $new->ProcWF = $ProcWF;

        return $new;
    }

    /**
     * @return string
     */
    public function getProgressive()
    {
        return $this->Progressive;
    }

    /**
     * @param string $Progressive
     * @return Card
     */
    public function withProgressive($Progressive)
    {
        $new = clone $this;
        $new->Progressive = $Progressive;

        return $new;
    }

    /**
     * @return string
     */
    public function getSignedExtension()
    {
        return $this->SignedExtension;
    }

    /**
     * @param string $SignedExtension
     * @return Card
     */
    public function withSignedExtension($SignedExtension)
    {
        $new = clone $this;
        $new->SignedExtension = $SignedExtension;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardStatus
     */
    public function getStatus()
    {
        return $this->Status;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardStatus $Status
     * @return Card
     */
    public function withStatus($Status)
    {
        $new = clone $this;
        $new->Status = $Status;

        return $new;
    }

    /**
     * @return string
     */
    public function getStreamId()
    {
        return $this->StreamId;
    }

    /**
     * @param string $StreamId
     * @return Card
     */
    public function withStreamId($StreamId)
    {
        $new = clone $this;
        $new->StreamId = $StreamId;

        return $new;
    }

    /**
     * @return string
     */
    public function getStreamIdShared()
    {
        return $this->StreamIdShared;
    }

    /**
     * @param string $StreamIdShared
     * @return Card
     */
    public function withStreamIdShared($StreamIdShared)
    {
        $new = clone $this;
        $new->StreamIdShared = $StreamIdShared;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\TimeStampFileFormat
     */
    public function getTimeStampFormat()
    {
        return $this->TimeStampFormat;
    }

    /**
     * @param \ArchiflowWSCard\Type\TimeStampFileFormat $TimeStampFormat
     * @return Card
     */
    public function withTimeStampFormat($TimeStampFormat)
    {
        $new = clone $this;
        $new->TimeStampFormat = $TimeStampFormat;

        return $new;
    }

    /**
     * @return int
     */
    public function getUserIdModifying()
    {
        return $this->UserIdModifying;
    }

    /**
     * @param int $UserIdModifying
     * @return Card
     */
    public function withUserIdModifying($UserIdModifying)
    {
        $new = clone $this;
        $new->UserIdModifying = $UserIdModifying;

        return $new;
    }

    /**
     * @param ArrayOfAdditive $Additives
     */
    public function setAdditives(ArrayOfAdditive $Additives)
    {
        $this->Additives = $Additives;
    }

    /**
     * @param int $ArchiveId
     */
    public function setArchiveId(int $ArchiveId)
    {
        $this->ArchiveId = $ArchiveId;
    }

    /**
     * @param CardExpirationInfo $CardExpiration
     */
    public function setCardExpiration(CardExpirationInfo $CardExpiration)
    {
        $this->CardExpiration = $CardExpiration;
    }

    /**
     * @param Guid $CardId
     */
    public function setCardId(string $CardId)
    {
        $this->CardId = $CardId;
    }

    /**
     * @param int $CardProg
     */
    public function setCardProg(int $CardProg)
    {
        $this->CardProg = $CardProg;
    }

    /**
     * @param string $ComputerizedClassification
     */
    public function setComputerizedClassification(string $ComputerizedClassification)
    {
        $this->ComputerizedClassification = $ComputerizedClassification;
    }

    /**
     * @param string $ComputerizedFolder
     */
    public function setComputerizedFolder(string $ComputerizedFolder)
    {
        $this->ComputerizedFolder = $ComputerizedFolder;
    }

    /**
     * @param DocumentStatus $DocStatus
     */
    public function setDocStatus(DocumentStatus $DocStatus)
    {
        $this->DocStatus = $DocStatus;
    }

    /**
     * @param string $DocumentExtension
     */
    public function setDocumentExtension(string $DocumentExtension)
    {
        $this->DocumentExtension = $DocumentExtension;
    }

    /**
     * @param int $DocumentTypeId
     */
    public function setDocumentTypeId(int $DocumentTypeId)
    {
        $this->DocumentTypeId = $DocumentTypeId;
    }

    /**
     * @param string $EncryptedCardId
     */
    public function setEncryptedCardId(string $EncryptedCardId)
    {
        $this->EncryptedCardId = $EncryptedCardId;
    }

    /**
     * @param ExternNotification $ExternMailNotification
     */
    public function setExternMailNotification(ExternNotification $ExternMailNotification)
    {
        $this->ExternMailNotification = $ExternMailNotification;
    }

    /**
     * @param string $ExternMailNotificationXML
     */
    public function setExternMailNotificationXML(string $ExternMailNotificationXML)
    {
        $this->ExternMailNotificationXML = $ExternMailNotificationXML;
    }

    /**
     * @param bool $HasAdditionalData
     */
    public function setHasAdditionalData(bool $HasAdditionalData)
    {
        $this->HasAdditionalData = $HasAdditionalData;
    }

    /**
     * @param bool $HasAttachment
     */
    public function setHasAttachment(bool $HasAttachment)
    {
        $this->HasAttachment = $HasAttachment;
    }

    /**
     * @param bool $HasComputerizedClassification
     */
    public function setHasComputerizedClassification(bool $HasComputerizedClassification)
    {
        $this->HasComputerizedClassification = $HasComputerizedClassification;
    }

    /**
     * @param bool $HasComputerizedFolder
     */
    public function setHasComputerizedFolder(bool $HasComputerizedFolder)
    {
        $this->HasComputerizedFolder = $HasComputerizedFolder;
    }

    /**
     * @param CardHasData $HasData
     */
    public function setHasData(CardHasData $HasData)
    {
        $this->HasData = $HasData;
    }

    /**
     * @param bool $HasDocument
     */
    public function setHasDocument(bool $HasDocument)
    {
        $this->HasDocument = $HasDocument;
    }

    /**
     * @param bool $HasFolder
     */
    public function setHasFolder(bool $HasFolder)
    {
        $this->HasFolder = $HasFolder;
    }

    /**
     * @param bool $HasKeyVersions
     */
    public function setHasKeyVersions(bool $HasKeyVersions)
    {
        $this->HasKeyVersions = $HasKeyVersions;
    }

    /**
     * @param bool $HasNotes
     */
    public function setHasNotes(bool $HasNotes)
    {
        $this->HasNotes = $HasNotes;
    }

    /**
     * @param bool $HasPartialInvalidations
     */
    public function setHasPartialInvalidations(bool $HasPartialInvalidations)
    {
        $this->HasPartialInvalidations = $HasPartialInvalidations;
    }

    /**
     * @param ArrayOfField $Indexes
     */
    public function setIndexes(ArrayOfField $Indexes)
    {
        $this->Indexes = $Indexes;
    }

    /**
     * @param Annotation $InvalidateAnnotation
     */
    public function setInvalidateAnnotation(Annotation $InvalidateAnnotation)
    {
        $this->InvalidateAnnotation = $InvalidateAnnotation;
    }

    /**
     * @param InvoiceBase $Invoice
     */
    public function setInvoice(InvoiceBase $Invoice)
    {
        $this->Invoice = $Invoice;
    }

    /**
     * @param bool $IsCC
     */
    public function setIsCC(bool $IsCC)
    {
        $this->IsCC = $IsCC;
    }

    /**
     * @param bool $IsCurrUserVisDoc
     */
    public function setIsCurrUserVisDoc(bool $IsCurrUserVisDoc)
    {
        $this->IsCurrUserVisDoc = $IsCurrUserVisDoc;
    }

    /**
     * @param bool $IsDocumentLocked
     */
    public function setIsDocumentLocked(bool $IsDocumentLocked)
    {
        $this->IsDocumentLocked = $IsDocumentLocked;
    }

    /**
     * @param bool $IsReadOnly
     */
    public function setIsReadOnly(bool $IsReadOnly)
    {
        $this->IsReadOnly = $IsReadOnly;
    }

    /**
     * @param bool $IsSigned
     */
    public function setIsSigned(bool $IsSigned)
    {
        $this->IsSigned = $IsSigned;
    }

    /**
     * @param bool $IsSignedPdf
     */
    public function setIsSignedPdf(bool $IsSignedPdf)
    {
        $this->IsSignedPdf = $IsSignedPdf;
    }

    /**
     * @param bool $IsSignedXml
     */
    public function setIsSignedXml(bool $IsSignedXml)
    {
        $this->IsSignedXml = $IsSignedXml;
    }

    /**
     * @param bool $IsSorted
     */
    public function setIsSorted(bool $IsSorted)
    {
        $this->IsSorted = $IsSorted;
    }

    /**
     * @param bool $IsStoredProtocol
     */
    public function setIsStoredProtocol(bool $IsStoredProtocol)
    {
        $this->IsStoredProtocol = $IsStoredProtocol;
    }

    /**
     * @param bool $IsValid
     */
    public function setIsValid(bool $IsValid)
    {
        $this->IsValid = $IsValid;
    }

    /**
     * @param bool $IsVisOnlyDoc
     */
    public function setIsVisOnlyDoc(bool $IsVisOnlyDoc)
    {
        $this->IsVisOnlyDoc = $IsVisOnlyDoc;
    }

    /**
     * @param bool $IsWf
     */
    public function setIsWf(bool $IsWf)
    {
        $this->IsWf = $IsWf;
    }

    /**
     * @param bool $IsWfReadOnly
     */
    public function setIsWfReadOnly(bool $IsWfReadOnly)
    {
        $this->IsWfReadOnly = $IsWfReadOnly;
    }

    /**
     * @param int $NumPages
     */
    public function setNumPages(int $NumPages)
    {
        $this->NumPages = $NumPages;
    }

    /**
     * @param CardOperationsFromList $OpsFromList
     */
    public function setOpsFromList(CardOperationsFromList $OpsFromList)
    {
        $this->OpsFromList = $OpsFromList;
    }

    /**
     * @param string $OriginalFileName
     */
    public function setOriginalFileName(string $OriginalFileName)
    {
        $this->OriginalFileName = $OriginalFileName;
    }

    /**
     * @param ProcWF $ProcWF
     */
    public function setProcWF(ProcWF $ProcWF)
    {
        $this->ProcWF = $ProcWF;
    }

    /**
     * @param string $Progressive
     */
    public function setProgressive(string $Progressive)
    {
        $this->Progressive = $Progressive;
    }

    /**
     * @param string $SignedExtension
     */
    public function setSignedExtension(string $SignedExtension)
    {
        $this->SignedExtension = $SignedExtension;
    }

    /**
     * @param CardStatus $Status
     */
    public function setStatus(CardStatus $Status)
    {
        $this->Status = $Status;
    }

    /**
     * @param string $StreamId
     */
    public function setStreamId(string $StreamId)
    {
        $this->StreamId = $StreamId;
    }

    /**
     * @param string $StreamIdShared
     */
    public function setStreamIdShared(string $StreamIdShared)
    {
        $this->StreamIdShared = $StreamIdShared;
    }

    /**
     * @param TimeStampFileFormat $TimeStampFormat
     */
    public function setTimeStampFormat(TimeStampFileFormat $TimeStampFormat)
    {
        $this->TimeStampFormat = $TimeStampFormat;
    }

    /**
     * @param int $UserIdModifying
     */
    public function setUserIdModifying(int $UserIdModifying)
    {
        $this->UserIdModifying = $UserIdModifying;
    }



}

