<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Folder implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfguid
     */
    private $CardIds = null;

    /**
     * @var int
     */
    private $Code = null;

    /**
     * @var \DateTime
     */
    private $Date = null;

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
    private $Name = null;

    /**
     * @var string
     */
    private $Note = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    private $OfficesRead = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    private $OfficesWrite = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfDrawer
     */
    private $ParentDrawers = null;

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
     * @var \ArchiflowWSFolder\Type\ArrayOfguid $CardIds
     * @var int $Code
     * @var \DateTime $Date
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup $GroupsRead
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup $GroupsWrite
     * @var string $Name
     * @var string $Note
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice $OfficesRead
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice $OfficesWrite
     * @var \ArchiflowWSFolder\Type\ArrayOfDrawer $ParentDrawers
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $UsersRead
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $UsersWrite
     */
    public function __construct($CardIds, $Code, $Date, $GroupsRead, $GroupsWrite, $Name, $Note, $OfficesRead, $OfficesWrite, $ParentDrawers, $UsersRead, $UsersWrite)
    {
        $this->CardIds = $CardIds;
        $this->Code = $Code;
        $this->Date = $Date;
        $this->GroupsRead = $GroupsRead;
        $this->GroupsWrite = $GroupsWrite;
        $this->Name = $Name;
        $this->Note = $Note;
        $this->OfficesRead = $OfficesRead;
        $this->OfficesWrite = $OfficesWrite;
        $this->ParentDrawers = $ParentDrawers;
        $this->UsersRead = $UsersRead;
        $this->UsersWrite = $UsersWrite;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfguid
     */
    public function getCardIds()
    {
        return $this->CardIds;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfguid $CardIds
     * @return Folder
     */
    public function withCardIds($CardIds)
    {
        $new = clone $this;
        $new->CardIds = $CardIds;

        return $new;
    }

    /**
     * @return int
     */
    public function getCode()
    {
        return $this->Code;
    }

    /**
     * @param int $Code
     * @return Folder
     */
    public function withCode($Code)
    {
        $new = clone $this;
        $new->Code = $Code;

        return $new;
    }

    /**
     * @return \DateTime
     */
    public function getDate()
    {
        return $this->Date;
    }

    /**
     * @param \DateTime $Date
     * @return Folder
     */
    public function withDate($Date)
    {
        $new = clone $this;
        $new->Date = $Date;

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
     * @return Folder
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
     * @return Folder
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
    public function getName()
    {
        return $this->Name;
    }

    /**
     * @param string $Name
     * @return Folder
     */
    public function withName($Name)
    {
        $new = clone $this;
        $new->Name = $Name;

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
     * @return Folder
     */
    public function withNote($Note)
    {
        $new = clone $this;
        $new->Note = $Note;

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
     * @return Folder
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
     * @return Folder
     */
    public function withOfficesWrite($OfficesWrite)
    {
        $new = clone $this;
        $new->OfficesWrite = $OfficesWrite;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfDrawer
     */
    public function getParentDrawers()
    {
        return $this->ParentDrawers;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfDrawer $ParentDrawers
     * @return Folder
     */
    public function withParentDrawers($ParentDrawers)
    {
        $new = clone $this;
        $new->ParentDrawers = $ParentDrawers;

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
     * @return Folder
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
     * @return Folder
     */
    public function withUsersWrite($UsersWrite)
    {
        $new = clone $this;
        $new->UsersWrite = $UsersWrite;

        return $new;
    }


}

