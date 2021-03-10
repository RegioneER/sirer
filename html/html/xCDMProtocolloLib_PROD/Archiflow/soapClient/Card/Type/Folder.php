<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Folder implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
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
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
     */
    private $GroupsRead = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
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
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $OfficesRead = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $OfficesWrite = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfDrawer
     */
    private $ParentDrawers = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $UsersRead = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $UsersWrite = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @var int $Code
     * @var \DateTime $Date
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $GroupsRead
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $GroupsWrite
     * @var string $Name
     * @var string $Note
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $OfficesRead
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $OfficesWrite
     * @var \ArchiflowWSCard\Type\ArrayOfDrawer $ParentDrawers
     * @var \ArchiflowWSCard\Type\ArrayOfUser $UsersRead
     * @var \ArchiflowWSCard\Type\ArrayOfUser $UsersWrite
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
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getCardIds()
    {
        return $this->CardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $CardIds
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
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getGroupsRead()
    {
        return $this->GroupsRead;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $GroupsRead
     * @return Folder
     */
    public function withGroupsRead($GroupsRead)
    {
        $new = clone $this;
        $new->GroupsRead = $GroupsRead;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getGroupsWrite()
    {
        return $this->GroupsWrite;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $GroupsWrite
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
     * @return \ArchiflowWSCard\Type\ArrayOfOffice
     */
    public function getOfficesRead()
    {
        return $this->OfficesRead;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOffice $OfficesRead
     * @return Folder
     */
    public function withOfficesRead($OfficesRead)
    {
        $new = clone $this;
        $new->OfficesRead = $OfficesRead;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfOffice
     */
    public function getOfficesWrite()
    {
        return $this->OfficesWrite;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOffice $OfficesWrite
     * @return Folder
     */
    public function withOfficesWrite($OfficesWrite)
    {
        $new = clone $this;
        $new->OfficesWrite = $OfficesWrite;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfDrawer
     */
    public function getParentDrawers()
    {
        return $this->ParentDrawers;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfDrawer $ParentDrawers
     * @return Folder
     */
    public function withParentDrawers($ParentDrawers)
    {
        $new = clone $this;
        $new->ParentDrawers = $ParentDrawers;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfUser
     */
    public function getUsersRead()
    {
        return $this->UsersRead;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfUser $UsersRead
     * @return Folder
     */
    public function withUsersRead($UsersRead)
    {
        $new = clone $this;
        $new->UsersRead = $UsersRead;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfUser
     */
    public function getUsersWrite()
    {
        return $this->UsersWrite;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfUser $UsersWrite
     * @return Folder
     */
    public function withUsersWrite($UsersWrite)
    {
        $new = clone $this;
        $new->UsersWrite = $UsersWrite;

        return $new;
    }


}

