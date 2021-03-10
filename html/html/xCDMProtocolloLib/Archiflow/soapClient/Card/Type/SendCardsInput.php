<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendCardsInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $CardIds = null;

    /**
     * @var bool
     */
    private $CheckUserWithPrivacy = null;

    /**
     * @var \ArchiflowWSCard\Type\ExtEMailConfig
     */
    private $ExtCfg = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
     */
    private $Groups = null;

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
     * @var \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @var bool $CheckUserWithPrivacy
     * @var \ArchiflowWSCard\Type\ExtEMailConfig $ExtCfg
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $Groups
     * @var string $Message
     * @var string $Note
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     * @var \ArchiflowWSCard\Type\ArrayOfUser $Users
     * @var bool $VisAllNote
     * @var bool $VisOnlyDoc
     */
    public function __construct($CardIds, $CheckUserWithPrivacy, $ExtCfg, $Groups, $Message, $Note, $Offices, $Users, $VisAllNote, $VisOnlyDoc)
    {
        $this->CardIds = $CardIds;
        $this->CheckUserWithPrivacy = $CheckUserWithPrivacy;
        $this->ExtCfg = $ExtCfg;
        $this->Groups = $Groups;
        $this->Message = $Message;
        $this->Note = $Note;
        $this->Offices = $Offices;
        $this->Users = $Users;
        $this->VisAllNote = $VisAllNote;
        $this->VisOnlyDoc = $VisOnlyDoc;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getCardIds()
    {
        return $this->CardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @return SendCardsInput
     */
    public function withCardIds($CardIds)
    {
        $new = clone $this;
        $new->CardIds = $CardIds;

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
     * @return SendCardsInput
     */
    public function withCheckUserWithPrivacy($CheckUserWithPrivacy)
    {
        $new = clone $this;
        $new->CheckUserWithPrivacy = $CheckUserWithPrivacy;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ExtEMailConfig
     */
    public function getExtCfg()
    {
        return $this->ExtCfg;
    }

    /**
     * @param \ArchiflowWSCard\Type\ExtEMailConfig $ExtCfg
     * @return SendCardsInput
     */
    public function withExtCfg($ExtCfg)
    {
        $new = clone $this;
        $new->ExtCfg = $ExtCfg;

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
     * @return SendCardsInput
     */
    public function withGroups($Groups)
    {
        $new = clone $this;
        $new->Groups = $Groups;

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
     * @return SendCardsInput
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
     * @return SendCardsInput
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
     * @return SendCardsInput
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

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
     * @return SendCardsInput
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
     * @return SendCardsInput
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
     * @return SendCardsInput
     */
    public function withVisOnlyDoc($VisOnlyDoc)
    {
        $new = clone $this;
        $new->VisOnlyDoc = $VisOnlyDoc;

        return $new;
    }


}

