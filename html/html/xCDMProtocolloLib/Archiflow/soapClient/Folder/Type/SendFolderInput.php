<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SendFolderInput implements RequestInterface
{

    /**
     * @var int
     */
    private $FolderId = null;

    /**
     * @var bool
     */
    private $ForceSend = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    private $Groups = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    private $GroupsRead = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    private $GroupsWrite = null;

    /**
     * @var string
     */
    private $Message = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    private $Offices = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    private $OfficesRead = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    private $OfficesWrite = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfUser
     */
    private $Users = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfUser
     */
    private $UsersRead = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfUser
     */
    private $UsersWrite = null;

    /**
     * Constructor
     *
     * @var int $FolderId
     * @var bool $ForceSend
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup $Groups
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup $GroupsRead
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup $GroupsWrite
     * @var string $Message
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice $Offices
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice $OfficesRead
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice $OfficesWrite
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $Users
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $UsersRead
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $UsersWrite
     */
    public function __construct($FolderId, $ForceSend, $Groups, $GroupsRead, $GroupsWrite, $Message, $Offices, $OfficesRead, $OfficesWrite, $Users, $UsersRead, $UsersWrite)
    {
        $this->FolderId = $FolderId;
        $this->ForceSend = $ForceSend;
        $this->Groups = $Groups;
        $this->GroupsRead = $GroupsRead;
        $this->GroupsWrite = $GroupsWrite;
        $this->Message = $Message;
        $this->Offices = $Offices;
        $this->OfficesRead = $OfficesRead;
        $this->OfficesWrite = $OfficesWrite;
        $this->Users = $Users;
        $this->UsersRead = $UsersRead;
        $this->UsersWrite = $UsersWrite;
    }

    /**
     * @return int
     */
    public function getFolderId()
    {
        return $this->FolderId;
    }

    /**
     * @param int $FolderId
     * @return SendFolderInput
     */
    public function withFolderId($FolderId)
    {
        $new = clone $this;
        $new->FolderId = $FolderId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getForceSend()
    {
        return $this->ForceSend;
    }

    /**
     * @param bool $ForceSend
     * @return SendFolderInput
     */
    public function withForceSend($ForceSend)
    {
        $new = clone $this;
        $new->ForceSend = $ForceSend;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    public function getGroups()
    {
        return $this->Groups;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfGroup $Groups
     * @return SendFolderInput
     */
    public function withGroups($Groups)
    {
        $new = clone $this;
        $new->Groups = $Groups;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    public function getGroupsRead()
    {
        return $this->GroupsRead;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfGroup $GroupsRead
     * @return SendFolderInput
     */
    public function withGroupsRead($GroupsRead)
    {
        $new = clone $this;
        $new->GroupsRead = $GroupsRead;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    public function getGroupsWrite()
    {
        return $this->GroupsWrite;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfGroup $GroupsWrite
     * @return SendFolderInput
     */
    public function withGroupsWrite($GroupsWrite)
    {
        $new = clone $this;
        $new->GroupsWrite = $GroupsWrite;

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
     * @return SendFolderInput
     */
    public function withMessage($Message)
    {
        $new = clone $this;
        $new->Message = $Message;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    public function getOffices()
    {
        return $this->Offices;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfOffice $Offices
     * @return SendFolderInput
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    public function getOfficesRead()
    {
        return $this->OfficesRead;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfOffice $OfficesRead
     * @return SendFolderInput
     */
    public function withOfficesRead($OfficesRead)
    {
        $new = clone $this;
        $new->OfficesRead = $OfficesRead;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    public function getOfficesWrite()
    {
        return $this->OfficesWrite;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfOffice $OfficesWrite
     * @return SendFolderInput
     */
    public function withOfficesWrite($OfficesWrite)
    {
        $new = clone $this;
        $new->OfficesWrite = $OfficesWrite;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfUser
     */
    public function getUsers()
    {
        return $this->Users;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfUser $Users
     * @return SendFolderInput
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfUser
     */
    public function getUsersRead()
    {
        return $this->UsersRead;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfUser $UsersRead
     * @return SendFolderInput
     */
    public function withUsersRead($UsersRead)
    {
        $new = clone $this;
        $new->UsersRead = $UsersRead;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfUser
     */
    public function getUsersWrite()
    {
        return $this->UsersWrite;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfUser $UsersWrite
     * @return SendFolderInput
     */
    public function withUsersWrite($UsersWrite)
    {
        $new = clone $this;
        $new->UsersWrite = $UsersWrite;

        return $new;
    }


}

