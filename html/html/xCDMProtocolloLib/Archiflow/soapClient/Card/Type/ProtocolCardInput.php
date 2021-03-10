<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ProtocolCardInput implements RequestInterface
{

    /**
     * @var bool
     */
    private $AutoCheckIn = null;

    /**
     * @var \ArchiflowWSCard\Type\CardBundle
     */
    private $Card = null;

    /**
     * @var bool
     */
    private $CheckUserWithPrivacy = null;

    /**
     * @var \ArchiflowWSCard\Type\DuplicateInfo
     */
    private $DupInfo = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
     */
    private $Groups = null;

    /**
     * @var bool
     */
    private $IsAutomaticProtocol = null;

    /**
     * @var string
     */
    private $Message = null;

    /**
     * @var string
     */
    private $Note = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $Offices = null;

    /**
     * @var bool
     */
    private $Sorted = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $Users = null;

    /**
     * @var bool
     */
    private $VisAllNote = null;

    /**
     * @var bool
     */
    private $VisOnlyDoc = null;

    /**
     * Constructor
     *
     * @var bool $AutoCheckIn
     * @var \ArchiflowWSCard\Type\CardBundle $Card
     * @var bool $CheckUserWithPrivacy
     * @var \ArchiflowWSCard\Type\DuplicateInfo $DupInfo
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $Groups
     * @var bool $IsAutomaticProtocol
     * @var string $Message
     * @var string $Note
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     * @var bool $Sorted
     * @var \ArchiflowWSCard\Type\ArrayOfUser $Users
     * @var bool $VisAllNote
     * @var bool $VisOnlyDoc
     */
    public function __construct($AutoCheckIn, $Card, $CheckUserWithPrivacy, $DupInfo, $Groups, $IsAutomaticProtocol, $Message, $Note, $Offices, $Sorted, $Users, $VisAllNote, $VisOnlyDoc)
    {
        $this->AutoCheckIn = $AutoCheckIn;
        $this->Card = $Card;
        $this->CheckUserWithPrivacy = $CheckUserWithPrivacy;
        $this->DupInfo = $DupInfo;
        $this->Groups = $Groups;
        $this->IsAutomaticProtocol = $IsAutomaticProtocol;
        $this->Message = $Message;
        $this->Note = $Note;
        $this->Offices = $Offices;
        $this->Sorted = $Sorted;
        $this->Users = $Users;
        $this->VisAllNote = $VisAllNote;
        $this->VisOnlyDoc = $VisOnlyDoc;
    }

    /**
     * @return bool
     */
    public function getAutoCheckIn()
    {
        return $this->AutoCheckIn;
    }

    /**
     * @param bool $AutoCheckIn
     * @return ProtocolCardInput
     */
    public function withAutoCheckIn($AutoCheckIn)
    {
        $new = clone $this;
        $new->AutoCheckIn = $AutoCheckIn;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\CardBundle
     */
    public function getCard()
    {
        return $this->Card;
    }

    /**
     * @param \ArchiflowWSCard\Type\CardBundle $Card
     * @return ProtocolCardInput
     */
    public function withCard($Card)
    {
        $new = clone $this;
        $new->Card = $Card;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCheckUserWithPrivacy()
    {
        return $this->CheckUserWithPrivacy;
    }

    /**
     * @param bool $CheckUserWithPrivacy
     * @return ProtocolCardInput
     */
    public function withCheckUserWithPrivacy($CheckUserWithPrivacy)
    {
        $new = clone $this;
        $new->CheckUserWithPrivacy = $CheckUserWithPrivacy;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\DuplicateInfo
     */
    public function getDupInfo()
    {
        return $this->DupInfo;
    }

    /**
     * @param \ArchiflowWSCard\Type\DuplicateInfo $DupInfo
     * @return ProtocolCardInput
     */
    public function withDupInfo($DupInfo)
    {
        $new = clone $this;
        $new->DupInfo = $DupInfo;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getGroups()
    {
        return $this->Groups;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $Groups
     * @return ProtocolCardInput
     */
    public function withGroups($Groups)
    {
        $new = clone $this;
        $new->Groups = $Groups;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsAutomaticProtocol()
    {
        return $this->IsAutomaticProtocol;
    }

    /**
     * @param bool $IsAutomaticProtocol
     * @return ProtocolCardInput
     */
    public function withIsAutomaticProtocol($IsAutomaticProtocol)
    {
        $new = clone $this;
        $new->IsAutomaticProtocol = $IsAutomaticProtocol;

        return $new;
    }

    /**
     * @return string
     */
    public function getMessage()
    {
        return $this->Message;
    }

    /**
     * @param string $Message
     * @return ProtocolCardInput
     */
    public function withMessage($Message)
    {
        $new = clone $this;
        $new->Message = $Message;

        return $new;
    }

    /**
     * @return string
     */
    public function getNote()
    {
        return $this->Note;
    }

    /**
     * @param string $Note
     * @return ProtocolCardInput
     */
    public function withNote($Note)
    {
        $new = clone $this;
        $new->Note = $Note;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfOffice
     */
    public function getOffices()
    {
        return $this->Offices;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     * @return ProtocolCardInput
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

        return $new;
    }

    /**
     * @return bool
     */
    public function getSorted()
    {
        return $this->Sorted;
    }

    /**
     * @param bool $Sorted
     * @return ProtocolCardInput
     */
    public function withSorted($Sorted)
    {
        $new = clone $this;
        $new->Sorted = $Sorted;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfUser
     */
    public function getUsers()
    {
        return $this->Users;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfUser $Users
     * @return ProtocolCardInput
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }

    /**
     * @return bool
     */
    public function getVisAllNote()
    {
        return $this->VisAllNote;
    }

    /**
     * @param bool $VisAllNote
     * @return ProtocolCardInput
     */
    public function withVisAllNote($VisAllNote)
    {
        $new = clone $this;
        $new->VisAllNote = $VisAllNote;

        return $new;
    }

    /**
     * @return bool
     */
    public function getVisOnlyDoc()
    {
        return $this->VisOnlyDoc;
    }

    /**
     * @param bool $VisOnlyDoc
     * @return ProtocolCardInput
     */
    public function withVisOnlyDoc($VisOnlyDoc)
    {
        $new = clone $this;
        $new->VisOnlyDoc = $VisOnlyDoc;

        return $new;
    }


}

