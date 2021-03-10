<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertCard implements RequestInterface
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
     */
    public function __construct($strSessionId, $oCard, $oUsers, $oGroups, $oOffices, $strNote, $strMessage, $bIsAutomaticProtocol, $bVisOnlyDoc, $bVisAllNote, $bSorted)
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
     * @return InsertCard
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
     * @return InsertCard
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
     * @return InsertCard
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
     * @return InsertCard
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
     * @return InsertCard
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
     * @return InsertCard
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
     * @return InsertCard
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
     * @return InsertCard
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
     * @return InsertCard
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
     * @return InsertCard
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
     * @return InsertCard
     */
    public function withBSorted($bSorted)
    {
        $new = clone $this;
        $new->bSorted = $bSorted;

        return $new;
    }


}

