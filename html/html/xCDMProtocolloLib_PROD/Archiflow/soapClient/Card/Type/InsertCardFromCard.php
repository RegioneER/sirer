<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertCardFromCard implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\CardBundle
     */
    private $oCard = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $oUsers = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
     */
    private $oGroups = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $oOffices = null;

    /**
     * @var string
     */
    private $strNote = null;

    /**
     * @var string
     */
    private $strMessage = null;

    /**
     * @var bool
     */
    private $bIsAutomaticProtocol = null;

    /**
     * @var bool
     */
    private $bVisOnlyDoc = null;

    /**
     * @var bool
     */
    private $bVisAllNote = null;

    /**
     * @var bool
     */
    private $bSorted = null;

    /**
     * @var bool
     */
    private $bAutoCheckIn = null;

    /**
     * @var \ArchiflowWSCard\Type\DuplicateInfo
     */
    private $oDupInfo = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\CardBundle $oCard
     * @var \ArchiflowWSCard\Type\ArrayOfUser $oUsers
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $oGroups
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $oOffices
     * @var string $strNote
     * @var string $strMessage
     * @var bool $bIsAutomaticProtocol
     * @var bool $bVisOnlyDoc
     * @var bool $bVisAllNote
     * @var bool $bSorted
     * @var bool $bAutoCheckIn
     * @var \ArchiflowWSCard\Type\DuplicateInfo $oDupInfo
     */
    public function __construct($strSessionId, $oCard, $oUsers, $oGroups, $oOffices, $strNote, $strMessage, $bIsAutomaticProtocol, $bVisOnlyDoc, $bVisAllNote, $bSorted, $bAutoCheckIn, $oDupInfo)
    {
        $this->strSessionId = $strSessionId;
        $this->oCard = $oCard;
        $this->oUsers = $oUsers;
        $this->oGroups = $oGroups;
        $this->oOffices = $oOffices;
        $this->strNote = $strNote;
        $this->strMessage = $strMessage;
        $this->bIsAutomaticProtocol = $bIsAutomaticProtocol;
        $this->bVisOnlyDoc = $bVisOnlyDoc;
        $this->bVisAllNote = $bVisAllNote;
        $this->bSorted = $bSorted;
        $this->bAutoCheckIn = $bAutoCheckIn;
        $this->oDupInfo = $oDupInfo;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return InsertCardFromCard
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

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
     * @return InsertCardFromCard
     */
    public function withOCard($oCard)
    {
        $new = clone $this;
        $new->oCard = $oCard;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfUser
     */
    public function getOUsers()
    {
        return $this->oUsers;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfUser $oUsers
     * @return InsertCardFromCard
     */
    public function withOUsers($oUsers)
    {
        $new = clone $this;
        $new->oUsers = $oUsers;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getOGroups()
    {
        return $this->oGroups;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $oGroups
     * @return InsertCardFromCard
     */
    public function withOGroups($oGroups)
    {
        $new = clone $this;
        $new->oGroups = $oGroups;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfOffice
     */
    public function getOOffices()
    {
        return $this->oOffices;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOffice $oOffices
     * @return InsertCardFromCard
     */
    public function withOOffices($oOffices)
    {
        $new = clone $this;
        $new->oOffices = $oOffices;

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
     * @return InsertCardFromCard
     */
    public function withStrNote($strNote)
    {
        $new = clone $this;
        $new->strNote = $strNote;

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
     * @return InsertCardFromCard
     */
    public function withStrMessage($strMessage)
    {
        $new = clone $this;
        $new->strMessage = $strMessage;

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
     * @return InsertCardFromCard
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
    public function getBVisOnlyDoc()
    {
        return $this->bVisOnlyDoc;
    }

    /**
     * @param bool $bVisOnlyDoc
     * @return InsertCardFromCard
     */
    public function withBVisOnlyDoc($bVisOnlyDoc)
    {
        $new = clone $this;
        $new->bVisOnlyDoc = $bVisOnlyDoc;

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
     * @return InsertCardFromCard
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
    public function getBSorted()
    {
        return $this->bSorted;
    }

    /**
     * @param bool $bSorted
     * @return InsertCardFromCard
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
    public function getBAutoCheckIn()
    {
        return $this->bAutoCheckIn;
    }

    /**
     * @param bool $bAutoCheckIn
     * @return InsertCardFromCard
     */
    public function withBAutoCheckIn($bAutoCheckIn)
    {
        $new = clone $this;
        $new->bAutoCheckIn = $bAutoCheckIn;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\DuplicateInfo
     */
    public function getODupInfo()
    {
        return $this->oDupInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\DuplicateInfo $oDupInfo
     * @return InsertCardFromCard
     */
    public function withODupInfo($oDupInfo)
    {
        $new = clone $this;
        $new->oDupInfo = $oDupInfo;

        return $new;
    }


}

