<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertParameters implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\CheckDuplicatiType
     */
    private $CheckDupType = null;

    /**
     * @var bool
     */
    private $IsVerifySignedFile = null;

    /**
     * @var bool
     */
    private $bIsAutomaticProtocol = null;

    /**
     * @var bool
     */
    private $bSorted = null;

    /**
     * @var bool
     */
    private $bSyncWF = null;

    /**
     * @var bool
     */
    private $bVisAllNote = null;

    /**
     * @var bool
     */
    private $bVisOnlyDoc = null;

    /**
     * @var \ArchiflowWSCard\Type\ExtEMailConfig
     */
    private $extCfg = null;

    /**
     * @var \ArchiflowWSCard\Type\CardBundle
     */
    private $oCard = null;

    /**
     * @var string
     */
    private $strMessage = null;

    /**
     * @var string
     */
    private $strNote = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\CheckDuplicatiType $CheckDupType
     * @var bool $IsVerifySignedFile
     * @var bool $bIsAutomaticProtocol
     * @var bool $bSorted
     * @var bool $bSyncWF
     * @var bool $bVisAllNote
     * @var bool $bVisOnlyDoc
     * @var \ArchiflowWSCard\Type\ExtEMailConfig $extCfg
     * @var \ArchiflowWSCard\Type\CardBundle $oCard
     * @var string $strMessage
     * @var string $strNote
     */
    public function __construct($CheckDupType, $IsVerifySignedFile, $bIsAutomaticProtocol, $bSorted, $bSyncWF, $bVisAllNote, $bVisOnlyDoc, $extCfg, $oCard, $strMessage, $strNote)
    {
        $this->CheckDupType = $CheckDupType;
        $this->IsVerifySignedFile = $IsVerifySignedFile;
        $this->bIsAutomaticProtocol = $bIsAutomaticProtocol;
        $this->bSorted = $bSorted;
        $this->bSyncWF = $bSyncWF;
        $this->bVisAllNote = $bVisAllNote;
        $this->bVisOnlyDoc = $bVisOnlyDoc;
        $this->extCfg = $extCfg;
        $this->oCard = $oCard;
        $this->strMessage = $strMessage;
        $this->strNote = $strNote;
    }

    /**
     * @return \ArchiflowWSCard\Type\CheckDuplicatiType
     */
    public function getCheckDupType()
    {
        return $this->CheckDupType;
    }

    /**
     * @param \ArchiflowWSCard\Type\CheckDuplicatiType $CheckDupType
     * @return InsertParameters
     */
    public function withCheckDupType($CheckDupType)
    {
        $new = clone $this;
        $new->CheckDupType = $CheckDupType;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsVerifySignedFile()
    {
        return $this->IsVerifySignedFile;
    }

    /**
     * @param bool $IsVerifySignedFile
     * @return InsertParameters
     */
    public function withIsVerifySignedFile($IsVerifySignedFile)
    {
        $new = clone $this;
        $new->IsVerifySignedFile = $IsVerifySignedFile;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBIsAutomaticProtocol()
    {
        return $this->bIsAutomaticProtocol;
    }

    /**
     * @param bool $bIsAutomaticProtocol
     * @return InsertParameters
     */
    public function withBIsAutomaticProtocol($bIsAutomaticProtocol)
    {
        $new = clone $this;
        $new->bIsAutomaticProtocol = $bIsAutomaticProtocol;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBSorted()
    {
        return $this->bSorted;
    }

    /**
     * @param bool $bSorted
     * @return InsertParameters
     */
    public function withBSorted($bSorted)
    {
        $new = clone $this;
        $new->bSorted = $bSorted;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBSyncWF()
    {
        return $this->bSyncWF;
    }

    /**
     * @param bool $bSyncWF
     * @return InsertParameters
     */
    public function withBSyncWF($bSyncWF)
    {
        $new = clone $this;
        $new->bSyncWF = $bSyncWF;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBVisAllNote()
    {
        return $this->bVisAllNote;
    }

    /**
     * @param bool $bVisAllNote
     * @return InsertParameters
     */
    public function withBVisAllNote($bVisAllNote)
    {
        $new = clone $this;
        $new->bVisAllNote = $bVisAllNote;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBVisOnlyDoc()
    {
        return $this->bVisOnlyDoc;
    }

    /**
     * @param bool $bVisOnlyDoc
     * @return InsertParameters
     */
    public function withBVisOnlyDoc($bVisOnlyDoc)
    {
        $new = clone $this;
        $new->bVisOnlyDoc = $bVisOnlyDoc;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExtEMailConfig
     */
    public function getExtCfg()
    {
        return $this->extCfg;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExtEMailConfig $extCfg
     * @return InsertParameters
     */
    public function withExtCfg($extCfg)
    {
        $new = clone $this;
        $new->extCfg = $extCfg;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardBundle
     */
    public function getOCard()
    {
        return $this->oCard;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardBundle $oCard
     * @return InsertParameters
     */
    public function withOCard($oCard)
    {
        $new = clone $this;
        $new->oCard = $oCard;

        return $new;
    }

    /**
     * @return string
     */
    public function getStrMessage()
    {
        return $this->strMessage;
    }

    /**
     * @param string $strMessage
     * @return InsertParameters
     */
    public function withStrMessage($strMessage)
    {
        $new = clone $this;
        $new->strMessage = $strMessage;

        return $new;
    }

    /**
     * @return string
     */
    public function getStrNote()
    {
        return $this->strNote;
    }

    /**
     * @param string $strNote
     * @return InsertParameters
     */
    public function withStrNote($strNote)
    {
        $new = clone $this;
        $new->strNote = $strNote;

        return $new;
    }


}

