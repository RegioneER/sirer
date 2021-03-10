<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendFolder implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var int
     */
    private $folderId = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfUser
     */
    private $oUsers = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    private $oGroups = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    private $oOffices = null;

    /**
     * @var string
     */
    private $strMessage = null;

    /**
     * @var bool
     */
    private $bForceSend = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var int $folderId
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $oUsers
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup $oGroups
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice $oOffices
     * @var string $strMessage
     * @var bool $bForceSend
     */
    public function __construct($strSessionId, $folderId, $oUsers, $oGroups, $oOffices, $strMessage, $bForceSend)
    {
        $this->strSessionId = $strSessionId;
        $this->folderId = $folderId;
        $this->oUsers = $oUsers;
        $this->oGroups = $oGroups;
        $this->oOffices = $oOffices;
        $this->strMessage = $strMessage;
        $this->bForceSend = $bForceSend;
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
     * @return SendFolder
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return int
     */
    public function getFolderId()
    {
        return $this->folderId;
    }

    /**
     * @param int $folderId
     * @return SendFolder
     */
    public function withFolderId($folderId)
    {
        $new = clone $this;
        $new->folderId = $folderId;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfUser
     */
    public function getOUsers()
    {
        return $this->oUsers;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfUser $oUsers
     * @return SendFolder
     */
    public function withOUsers($oUsers)
    {
        $new = clone $this;
        $new->oUsers = $oUsers;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    public function getOGroups()
    {
        return $this->oGroups;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfGroup $oGroups
     * @return SendFolder
     */
    public function withOGroups($oGroups)
    {
        $new = clone $this;
        $new->oGroups = $oGroups;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    public function getOOffices()
    {
        return $this->oOffices;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfOffice $oOffices
     * @return SendFolder
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
    public function getStrMessage()
    {
        return $this->strMessage;
    }

    /**
     * @param string $strMessage
     * @return SendFolder
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
    public function getBForceSend()
    {
        return $this->bForceSend;
    }

    /**
     * @param bool $bForceSend
     * @return SendFolder
     */
    public function withBForceSend($bForceSend)
    {
        $new = clone $this;
        $new->bForceSend = $bForceSend;

        return $new;
    }


}

