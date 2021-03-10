<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CheckCreateZipCardsDataOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $ErrorCardId = null;

    /**
     * @var \ArchiflowWSCard\Type\CreatingZipError
     */
    private $ErrorCode = null;

    /**
     * @var string
     */
    private $ErrorDescription = null;

    /**
     * @var \ArchiflowWSCard\Type\AsynchOperationStatus
     */
    private $Status = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $ZipFileId = null;

    /**
     * @var string
     */
    private $ZipFileName = null;

    /**
     * @var int
     */
    private $ZipFileSize = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $ErrorCardId
     * @var \ArchiflowWSCard\Type\CreatingZipError $ErrorCode
     * @var string $ErrorDescription
     * @var \ArchiflowWSCard\Type\AsynchOperationStatus $Status
     * @var \ArchiflowWSCard\Type\Guid $ZipFileId
     * @var string $ZipFileName
     * @var int $ZipFileSize
     */
    public function __construct($ErrorCardId, $ErrorCode, $ErrorDescription, $Status, $ZipFileId, $ZipFileName, $ZipFileSize)
    {
        $this->ErrorCardId = $ErrorCardId;
        $this->ErrorCode = $ErrorCode;
        $this->ErrorDescription = $ErrorDescription;
        $this->Status = $Status;
        $this->ZipFileId = $ZipFileId;
        $this->ZipFileName = $ZipFileName;
        $this->ZipFileSize = $ZipFileSize;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getErrorCardId()
    {
        return $this->ErrorCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $ErrorCardId
     * @return CheckCreateZipCardsDataOutput
     */
    public function withErrorCardId($ErrorCardId)
    {
        $new = clone $this;
        $new->ErrorCardId = $ErrorCardId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CreatingZipError
     */
    public function getErrorCode()
    {
        return $this->ErrorCode;
    }

    /**
     * @param \ArchiflowWSCard\Type\CreatingZipError $ErrorCode
     * @return CheckCreateZipCardsDataOutput
     */
    public function withErrorCode($ErrorCode)
    {
        $new = clone $this;
        $new->ErrorCode = $ErrorCode;

        return $new;
    }

    /**
     * @return string
     */
    public function getErrorDescription()
    {
        return $this->ErrorDescription;
    }

    /**
     * @param string $ErrorDescription
     * @return CheckCreateZipCardsDataOutput
     */
    public function withErrorDescription($ErrorDescription)
    {
        $new = clone $this;
        $new->ErrorDescription = $ErrorDescription;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AsynchOperationStatus
     */
    public function getStatus()
    {
        return $this->Status;
    }

    /**
     * @param \ArchiflowWSCard\Type\AsynchOperationStatus $Status
     * @return CheckCreateZipCardsDataOutput
     */
    public function withStatus($Status)
    {
        $new = clone $this;
        $new->Status = $Status;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getZipFileId()
    {
        return $this->ZipFileId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $ZipFileId
     * @return CheckCreateZipCardsDataOutput
     */
    public function withZipFileId($ZipFileId)
    {
        $new = clone $this;
        $new->ZipFileId = $ZipFileId;

        return $new;
    }

    /**
     * @return string
     */
    public function getZipFileName()
    {
        return $this->ZipFileName;
    }

    /**
     * @param string $ZipFileName
     * @return CheckCreateZipCardsDataOutput
     */
    public function withZipFileName($ZipFileName)
    {
        $new = clone $this;
        $new->ZipFileName = $ZipFileName;

        return $new;
    }

    /**
     * @return int
     */
    public function getZipFileSize()
    {
        return $this->ZipFileSize;
    }

    /**
     * @param int $ZipFileSize
     * @return CheckCreateZipCardsDataOutput
     */
    public function withZipFileSize($ZipFileSize)
    {
        $new = clone $this;
        $new->ZipFileSize = $ZipFileSize;

        return $new;
    }


}

