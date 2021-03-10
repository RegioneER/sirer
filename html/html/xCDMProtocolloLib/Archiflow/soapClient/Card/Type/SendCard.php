<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendCard implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $oCardId = null;

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
    private $bVisOnlyDoc = null;

    /**
     * @var bool
     */
    private $bVisAllNote = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\Guid $oCardId
     * @var \ArchiflowWSCard\Type\ArrayOfUser $oUsers
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $oGroups
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $oOffices
     * @var string $strNote
     * @var string $strMessage
     * @var bool $bVisOnlyDoc
     * @var bool $bVisAllNote
     */
    public function __construct($strSessionId, $oCardId, $oUsers, $oGroups, $oOffices, $strNote, $strMessage, $bVisOnlyDoc, $bVisAllNote)
    {
        $this->strSessionId = $strSessionId;
        $this->oCardId = $oCardId;
        $this->oUsers = $oUsers;
        $this->oGroups = $oGroups;
        $this->oOffices = $oOffices;
        $this->strNote = $strNote;
        $this->strMessage = $strMessage;
        $this->bVisOnlyDoc = $bVisOnlyDoc;
        $this->bVisAllNote = $bVisAllNote;
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
     * @return SendCard
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getOCardId()
    {
        return $this->oCardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $oCardId
     * @return SendCard
     */
    public function withOCardId($oCardId)
    {
        $new = clone $this;
        $new->oCardId = $oCardId;

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
     * @return SendCard
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
     * @return SendCard
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
     * @return SendCard
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
     * @return SendCard
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
     * @return SendCard
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
    public function getBVisOnlyDoc()
    {
        return $this->bVisOnlyDoc;
    }

    /**
     * @param bool $bVisOnlyDoc
     * @return SendCard
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
     * @return SendCard
     */
    public function withBVisAllNote($bVisAllNote)
    {
        $new = clone $this;
        $new->bVisAllNote = $bVisAllNote;

        return $new;
    }


}

