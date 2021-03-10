<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SdiInfo implements RequestInterface
{

    /**
     * @var string
     */
    private $DocumentType = null;

    /**
     * @var string
     */
    private $FileId = null;

    /**
     * @var string
     */
    private $FileName = null;

    /**
     * @var int
     */
    private $Id = null;

    /**
     * @var string
     */
    private $RecipientCode = null;

    /**
     * @var string
     */
    private $SendingId = null;

    /**
     * @var string
     */
    private $TransmissionFormat = null;

    /**
     * Constructor
     *
     * @var string $DocumentType
     * @var string $FileId
     * @var string $FileName
     * @var int $Id
     * @var string $RecipientCode
     * @var string $SendingId
     * @var string $TransmissionFormat
     */
    public function __construct($DocumentType, $FileId, $FileName, $Id, $RecipientCode, $SendingId, $TransmissionFormat)
    {
        $this->DocumentType = $DocumentType;
        $this->FileId = $FileId;
        $this->FileName = $FileName;
        $this->Id = $Id;
        $this->RecipientCode = $RecipientCode;
        $this->SendingId = $SendingId;
        $this->TransmissionFormat = $TransmissionFormat;
    }

    /**
     * @return string
     */
    public function getDocumentType()
    {
        return $this->DocumentType;
    }

    /**
     * @param string $DocumentType
     * @return SdiInfo
     */
    public function withDocumentType($DocumentType)
    {
        $new = clone $this;
        $new->DocumentType = $DocumentType;

        return $new;
    }

    /**
     * @return string
     */
    public function getFileId()
    {
        return $this->FileId;
    }

    /**
     * @param string $FileId
     * @return SdiInfo
     */
    public function withFileId($FileId)
    {
        $new = clone $this;
        $new->FileId = $FileId;

        return $new;
    }

    /**
     * @return string
     */
    public function getFileName()
    {
        return $this->FileName;
    }

    /**
     * @param string $FileName
     * @return SdiInfo
     */
    public function withFileName($FileName)
    {
        $new = clone $this;
        $new->FileName = $FileName;

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
     * @return SdiInfo
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }

    /**
     * @return string
     */
    public function getRecipientCode()
    {
        return $this->RecipientCode;
    }

    /**
     * @param string $RecipientCode
     * @return SdiInfo
     */
    public function withRecipientCode($RecipientCode)
    {
        $new = clone $this;
        $new->RecipientCode = $RecipientCode;

        return $new;
    }

    /**
     * @return string
     */
    public function getSendingId()
    {
        return $this->SendingId;
    }

    /**
     * @param string $SendingId
     * @return SdiInfo
     */
    public function withSendingId($SendingId)
    {
        $new = clone $this;
        $new->SendingId = $SendingId;

        return $new;
    }

    /**
     * @return string
     */
    public function getTransmissionFormat()
    {
        return $this->TransmissionFormat;
    }

    /**
     * @param string $TransmissionFormat
     * @return SdiInfo
     */
    public function withTransmissionFormat($TransmissionFormat)
    {
        $new = clone $this;
        $new->TransmissionFormat = $TransmissionFormat;

        return $new;
    }


}

