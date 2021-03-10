<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ExternalAttachment implements RequestInterface
{

    /**
     * @var string
     */
    private $Content = null;

    /**
     * @var string
     */
    private $ContentType = null;

    /**
     * @var string
     */
    private $Digest = null;

    /**
     * @var string
     */
    private $Extension = null;

    /**
     * @var bool
     */
    private $IsInteroperability = null;

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
     * @var string
     */
    private $SignedExtension = null;

    /**
     * @var \ArchiflowWSCard\Type\UnsignedInt
     */
    private $Size = null;

    /**
     * @var \ArchiflowWSCard\Type\TimeStampFileFormat
     */
    private $TimeStampFormat = null;

    /**
     * @var int
     */
    private $VolumeID = null;

    /**
     * @var bool
     */
    private $WarningExtensionOff = null;

    /**
     * Constructor
     *
     * @var string $Content
     * @var string $ContentType
     * @var string $Digest
     * @var string $Extension
     * @var bool $IsInteroperability
     * @var bool $IsSigned
     * @var bool $IsSignedPdf
     * @var bool $IsSignedXml
     * @var bool $IsTimeStamp
     * @var string $SignedExtension
     * @var \ArchiflowWSCard\Type\UnsignedInt $Size
     * @var \ArchiflowWSCard\Type\TimeStampFileFormat $TimeStampFormat
     * @var int $VolumeID
     * @var bool $WarningExtensionOff
     */
    public function __construct($Content, $ContentType, $Digest, $Extension, $IsInteroperability, $IsSigned, $IsSignedPdf, $IsSignedXml, $IsTimeStamp, $SignedExtension, $Size, $TimeStampFormat, $VolumeID, $WarningExtensionOff)
    {
        $this->Content = $Content;
        $this->ContentType = $ContentType;
        $this->Digest = $Digest;
        $this->Extension = $Extension;
        $this->IsInteroperability = $IsInteroperability;
        $this->IsSigned = $IsSigned;
        $this->IsSignedPdf = $IsSignedPdf;
        $this->IsSignedXml = $IsSignedXml;
        $this->IsTimeStamp = $IsTimeStamp;
        $this->SignedExtension = $SignedExtension;
        $this->Size = $Size;
        $this->TimeStampFormat = $TimeStampFormat;
        $this->VolumeID = $VolumeID;
        $this->WarningExtensionOff = $WarningExtensionOff;
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
     * @return ExternalAttachment
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
     * @return ExternalAttachment
     */
    public function withContentType($ContentType)
    {
        $new = clone $this;
        $new->ContentType = $ContentType;

        return $new;
    }

    /**
     * @return string
     */
    public function getDigest()
    {
        return $this->Digest;
    }

    /**
     * @param string $Digest
     * @return ExternalAttachment
     */
    public function withDigest($Digest)
    {
        $new = clone $this;
        $new->Digest = $Digest;

        return $new;
    }

    /**
     * @return string
     */
    public function getExtension()
    {
        return $this->Extension;
    }

    /**
     * @param string $Extension
     * @return ExternalAttachment
     */
    public function withExtension($Extension)
    {
        $new = clone $this;
        $new->Extension = $Extension;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsInteroperability()
    {
        return $this->IsInteroperability;
    }

    /**
     * @param bool $IsInteroperability
     * @return ExternalAttachment
     */
    public function withIsInteroperability($IsInteroperability)
    {
        $new = clone $this;
        $new->IsInteroperability = $IsInteroperability;

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
     * @return ExternalAttachment
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
     * @return ExternalAttachment
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
     * @return ExternalAttachment
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
     * @return ExternalAttachment
     */
    public function withIsTimeStamp($IsTimeStamp)
    {
        $new = clone $this;
        $new->IsTimeStamp = $IsTimeStamp;

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
     * @return ExternalAttachment
     */
    public function withSignedExtension($SignedExtension)
    {
        $new = clone $this;
        $new->SignedExtension = $SignedExtension;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\UnsignedInt
     */
    public function getSize()
    {
        return $this->Size;
    }

    /**
     * @param \ArchiflowWSCard\Type\UnsignedInt $Size
     * @return ExternalAttachment
     */
    public function withSize($Size)
    {
        $new = clone $this;
        $new->Size = $Size;

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
     * @return ExternalAttachment
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
    public function getVolumeID()
    {
        return $this->VolumeID;
    }

    /**
     * @param int $VolumeID
     * @return ExternalAttachment
     */
    public function withVolumeID($VolumeID)
    {
        $new = clone $this;
        $new->VolumeID = $VolumeID;

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
     * @return ExternalAttachment
     */
    public function withWarningExtensionOff($WarningExtensionOff)
    {
        $new = clone $this;
        $new->WarningExtensionOff = $WarningExtensionOff;

        return $new;
    }


}

