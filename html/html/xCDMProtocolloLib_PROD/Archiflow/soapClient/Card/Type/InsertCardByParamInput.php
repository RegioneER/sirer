<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertCardByParamInput implements RequestInterface
{

    /**
     * @var bool
     */
    private $AutoCheckIn = null;

    /**
     * @var bool
     */
    private $AutomaticProtocol = null;

    /**
     * @var \ArchiflowWSCard\Type\CardBundle
     */
    private $Card = null;

    /**
     * @var bool
     */
    private $CheckUserWithPrivacy = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfClassificationFolder
     */
    private $ClassificationFolders = null;

    /**
     * @var bool
     */
    private $DisableExtEMail = null;

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
     * @var string
     */
    private $PressMarkModel = null;

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
    private $VisibilityAllNotes = null;

    /**
     * @var bool
     */
    private $VisibilityOnlyDoc = null;

    /**
     * Constructor
     *
     * @var bool $AutoCheckIn
     * @var bool $AutomaticProtocol
     * @var \ArchiflowWSCard\Type\CardBundle $Card
     * @var bool $CheckUserWithPrivacy
     * @var \ArchiflowWSCard\Type\ArrayOfClassificationFolder $ClassificationFolders
     * @var bool $DisableExtEMail
     * @var \ArchiflowWSCard\Type\ExtEMailConfig $ExtCfg
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $Groups
     * @var string $Message
     * @var string $Note
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     * @var string $PressMarkModel
     * @var bool $Sorted
     * @var \ArchiflowWSCard\Type\ArrayOfUser $Users
     * @var bool $VisibilityAllNotes
     * @var bool $VisibilityOnlyDoc
     */
    public function __construct($AutoCheckIn, $AutomaticProtocol, $Card, $CheckUserWithPrivacy, $ClassificationFolders, $DisableExtEMail, $ExtCfg, $Groups, $Message, $Note, $Offices, $PressMarkModel, $Sorted, $Users, $VisibilityAllNotes, $VisibilityOnlyDoc)
    {
        $this->AutoCheckIn = $AutoCheckIn;
        $this->AutomaticProtocol = $AutomaticProtocol;
        $this->Card = $Card;
        $this->CheckUserWithPrivacy = $CheckUserWithPrivacy;
        $this->ClassificationFolders = $ClassificationFolders;
        $this->DisableExtEMail = $DisableExtEMail;
        $this->ExtCfg = $ExtCfg;
        $this->Groups = $Groups;
        $this->Message = $Message;
        $this->Note = $Note;
        $this->Offices = $Offices;
        $this->PressMarkModel = $PressMarkModel;
        $this->Sorted = $Sorted;
        $this->Users = $Users;
        $this->VisibilityAllNotes = $VisibilityAllNotes;
        $this->VisibilityOnlyDoc = $VisibilityOnlyDoc;
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
     * @return InsertCardByParamInput
     */
    public function withAutoCheckIn($AutoCheckIn)
    {
        $new = clone $this;
        $new->AutoCheckIn = $AutoCheckIn;

        return $new;
    }

    /**
     * @return bool
     */
    public function getAutomaticProtocol()
    {
        return $this->AutomaticProtocol;
    }

    /**
     * @param bool $AutomaticProtocol
     * @return InsertCardByParamInput
     */
    public function withAutomaticProtocol($AutomaticProtocol)
    {
        $new = clone $this;
        $new->AutomaticProtocol = $AutomaticProtocol;

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
     * @return InsertCardByParamInput
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
     * @return InsertCardByParamInput
     */
    public function withCheckUserWithPrivacy($CheckUserWithPrivacy)
    {
        $new = clone $this;
        $new->CheckUserWithPrivacy = $CheckUserWithPrivacy;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfClassificationFolder
     */
    public function getClassificationFolders()
    {
        return $this->ClassificationFolders;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfClassificationFolder $ClassificationFolders
     * @return InsertCardByParamInput
     */
    public function withClassificationFolders($ClassificationFolders)
    {
        $new = clone $this;
        $new->ClassificationFolders = $ClassificationFolders;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDisableExtEMail()
    {
        return $this->DisableExtEMail;
    }

    /**
     * @param bool $DisableExtEMail
     * @return InsertCardByParamInput
     */
    public function withDisableExtEMail($DisableExtEMail)
    {
        $new = clone $this;
        $new->DisableExtEMail = $DisableExtEMail;

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
     * @return InsertCardByParamInput
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
     * @return InsertCardByParamInput
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
     * @return InsertCardByParamInput
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
     * @return InsertCardByParamInput
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
     * @return InsertCardByParamInput
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

        return $new;
    }

    /**
     * @return string
     */
    public function getPressMarkModel()
    {
        return $this->PressMarkModel;
    }

    /**
     * @param string $PressMarkModel
     * @return InsertCardByParamInput
     */
    public function withPressMarkModel($PressMarkModel)
    {
        $new = clone $this;
        $new->PressMarkModel = $PressMarkModel;

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
     * @return InsertCardByParamInput
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
     * @return InsertCardByParamInput
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
    public function getVisibilityAllNotes()
    {
        return $this->VisibilityAllNotes;
    }

    /**
     * @param bool $VisibilityAllNotes
     * @return InsertCardByParamInput
     */
    public function withVisibilityAllNotes($VisibilityAllNotes)
    {
        $new = clone $this;
        $new->VisibilityAllNotes = $VisibilityAllNotes;

        return $new;
    }

    /**
     * @return bool
     */
    public function getVisibilityOnlyDoc()
    {
        return $this->VisibilityOnlyDoc;
    }

    /**
     * @param bool $VisibilityOnlyDoc
     * @return InsertCardByParamInput
     */
    public function withVisibilityOnlyDoc($VisibilityOnlyDoc)
    {
        $new = clone $this;
        $new->VisibilityOnlyDoc = $VisibilityOnlyDoc;

        return $new;
    }


}

