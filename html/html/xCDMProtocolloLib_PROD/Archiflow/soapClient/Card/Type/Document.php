<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Document implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var string
     */
    private $Content = null;

    /**
     * @var string
     */
    private $ContentType = null;

    /**
     * @var \DateTime
     */
    private $DateModify = null;

    /**
     * @var \ArchiflowWSCard\Type\FileTypes
     */
    private $DisplayType = null;

    /**
     * @var string
     */
    private $DocDigest = null;

    /**
     * @var string
     */
    private $DocumentExtension = null;

    /**
     * @var string
     */
    private $DocumentFullExtension = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $DocumentGuid = null;

    /**
     * @var string
     */
    private $DocumentTitle = null;

    /**
     * @var int
     */
    private $FileSize = null;

    /**
     * @var bool
     */
    private $IsLocked = null;

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
    private $IsTimeStamp = null;

    /**
     * @var int
     */
    private $NumPages = null;

    /**
     * @var string
     */
    private $OriginalFileName = null;

    /**
     * @var string
     */
    private $SignedExtension = null;

    /**
     * @var \ArchiflowWSCard\Type\TimeStampFileFormat
     */
    private $TimeStampFormat = null;

    /**
     * @var int
     */
    private $Version = null;

    /**
     * @var bool
     */
    private $WarningExtensionOff = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var string $Content
     * @var string $ContentType
     * @var \DateTime $DateModify
     * @var \ArchiflowWSCard\Type\FileTypes $DisplayType
     * @var string $DocDigest
     * @var string $DocumentExtension
     * @var string $DocumentFullExtension
     * @var \ArchiflowWSCard\Type\Guid $DocumentGuid
     * @var string $DocumentTitle
     * @var int $FileSize
     * @var bool $IsLocked
     * @var bool $IsReadOnly
     * @var bool $IsSigned
     * @var bool $IsSignedPdf
     * @var bool $IsSignedXml
     * @var bool $IsTimeStamp
     * @var int $NumPages
     * @var string $OriginalFileName
     * @var string $SignedExtension
     * @var \ArchiflowWSCard\Type\TimeStampFileFormat $TimeStampFormat
     * @var int $Version
     * @var bool $WarningExtensionOff
     */
    public function __construct($CardId, $Content, $ContentType, $DateModify, $DisplayType, $DocDigest, $DocumentExtension, $DocumentFullExtension, $DocumentGuid, $DocumentTitle, $FileSize, $IsLocked, $IsReadOnly, $IsSigned, $IsSignedPdf, $IsSignedXml, $IsTimeStamp, $NumPages, $OriginalFileName, $SignedExtension, $TimeStampFormat, $Version, $WarningExtensionOff)
    {
        $this->CardId = $CardId;
        $this->Content = $Content;
        $this->ContentType = $ContentType;
        $this->DateModify = $DateModify;
        $this->DisplayType = $DisplayType;
        $this->DocDigest = $DocDigest;
        $this->DocumentExtension = $DocumentExtension;
        $this->DocumentFullExtension = $DocumentFullExtension;
        $this->DocumentGuid = $DocumentGuid;
        $this->DocumentTitle = $DocumentTitle;
        $this->FileSize = $FileSize;
        $this->IsLocked = $IsLocked;
        $this->IsReadOnly = $IsReadOnly;
        $this->IsSigned = $IsSigned;
        $this->IsSignedPdf = $IsSignedPdf;
        $this->IsSignedXml = $IsSignedXml;
        $this->IsTimeStamp = $IsTimeStamp;
        $this->NumPages = $NumPages;
        $this->OriginalFileName = $OriginalFileName;
        $this->SignedExtension = $SignedExtension;
        $this->TimeStampFormat = $TimeStampFormat;
        $this->Version = $Version;
        $this->WarningExtensionOff = $WarningExtensionOff;
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
     * @return Document
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return string
     */
    public function getContent()
    {
        return $this->Content;
    }

    /**
     * @param string $Content
     * @return Document
     */
    public function withContent($Content)
    {
        $new = clone $this;
        $new->Content = $Content;

        return $new;
    }

    /**
     * @return string
     */
    public function getContentType()
    {
        return $this->ContentType;
    }

    /**
     * @param string $ContentType
     * @return Document
     */
    public function withContentType($ContentType)
    {
        $new = clone $this;
        $new->ContentType = $ContentType;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDateModify()
    {
        return $this->DateModify;
    }

    /**
     * @param \DateTime $DateModify
     * @return Document
     */
    public function withDateModify($DateModify)
    {
        $new = clone $this;
        $new->DateModify = $DateModify;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\FileTypes
     */
    public function getDisplayType()
    {
        return $this->DisplayType;
    }

    /**
     * @param \ArchiflowWSCard\Type\FileTypes $DisplayType
     * @return Document
     */
    public function withDisplayType($DisplayType)
    {
        $new = clone $this;
        $new->DisplayType = $DisplayType;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocDigest()
    {
        return $this->DocDigest;
    }

    /**
     * @param string $DocDigest
     * @return Document
     */
    public function withDocDigest($DocDigest)
    {
        $new = clone $this;
        $new->DocDigest = $DocDigest;

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
     * @return Document
     */
    public function withDocumentExtension($DocumentExtension)
    {
        $new = clone $this;
        $new->DocumentExtension = $DocumentExtension;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocumentFullExtension()
    {
        return $this->DocumentFullExtension;
    }

    /**
     * @param string $DocumentFullExtension
     * @return Document
     */
    public function withDocumentFullExtension($DocumentFullExtension)
    {
        $new = clone $this;
        $new->DocumentFullExtension = $DocumentFullExtension;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getDocumentGuid()
    {
        return $this->DocumentGuid;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $DocumentGuid
     * @return Document
     */
    public function withDocumentGuid($DocumentGuid)
    {
        $new = clone $this;
        $new->DocumentGuid = $DocumentGuid;

        return $new;
    }

    /**
     * @return string
     */
    public function getDocumentTitle()
    {
        return $this->DocumentTitle;
    }

    /**
     * @param string $DocumentTitle
     * @return Document
     */
    public function withDocumentTitle($DocumentTitle)
    {
        $new = clone $this;
        $new->DocumentTitle = $DocumentTitle;

        return $new;
    }

    /**
     * @return int
     */
    public function getFileSize()
    {
        return $this->FileSize;
    }

    /**
     * @param int $FileSize
     * @return Document
     */
    public function withFileSize($FileSize)
    {
        $new = clone $this;
        $new->FileSize = $FileSize;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsLocked()
    {
        return $this->IsLocked;
    }

    /**
     * @param bool $IsLocked
     * @return Document
     */
    public function withIsLocked($IsLocked)
    {
        $new = clone $this;
        $new->IsLocked = $IsLocked;

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
     * @return Document
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
     * @return Document
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
     * @return Document
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
     * @return Document
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
    public function getIsTimeStamp()
    {
        return $this->IsTimeStamp;
    }

    /**
     * @param bool $IsTimeStamp
     * @return Document
     */
    public function withIsTimeStamp($IsTimeStamp)
    {
        $new = clone $this;
        $new->IsTimeStamp = $IsTimeStamp;

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
     * @return Document
     */
    public function withNumPages($NumPages)
    {
        $new = clone $this;
        $new->NumPages = $NumPages;

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
     * @return Document
     */
    public function withOriginalFileName($OriginalFileName)
    {
        $new = clone $this;
        $new->OriginalFileName = $OriginalFileName;

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
     * @return Document
     */
    public function withSignedExtension($SignedExtension)
    {
        $new = clone $this;
        $new->SignedExtension = $SignedExtension;

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
     * @return Document
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
    public function getVersion()
    {
        return $this->Version;
    }

    /**
     * @param int $Version
     * @return Document
     */
    public function withVersion($Version)
    {
        $new = clone $this;
        $new->Version = $Version;

        return $new;
    }

    /**
     * @return bool
     */
    public function getWarningExtensionOff()
    {
        return $this->WarningExtensionOff;
    }

    /**
     * @param bool $WarningExtensionOff
     * @return Document
     */
    public function withWarningExtensionOff($WarningExtensionOff)
    {
        $new = clone $this;
        $new->WarningExtensionOff = $WarningExtensionOff;

        return $new;
    }


}

