<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Drawer implements RequestInterface
{

    /**
     * @var int
     */
    private $Code = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    private $Groups = null;

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
    private $Offices = null;

    /**
     * @var \ArchiflowWSFolder\Type\Cabinet
     */
    private $ParentCabinet = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfUser
     */
    private $Users = null;

    /**
     * Constructor
     *
     * @var int $Code
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup $Groups
     * @var string $Name
     * @var string $Note
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice $Offices
     * @var \ArchiflowWSFolder\Type\Cabinet $ParentCabinet
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $Users
     */
    public function __construct($Code, $Groups, $Name, $Note, $Offices, $ParentCabinet, $Users)
    {
        $this->Code = $Code;
        $this->Groups = $Groups;
        $this->Name = $Name;
        $this->Note = $Note;
        $this->Offices = $Offices;
        $this->ParentCabinet = $ParentCabinet;
        $this->Users = $Users;
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
     * @return Drawer
     */
    public function withCode($Code)
    {
        $new = clone $this;
        $new->Code = $Code;

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
     * @return Drawer
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
    public function getName()
    {
        return $this->Name;
    }

    /**
     * @param string $Name
     * @return Drawer
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
     * @return Drawer
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
    public function getOffices()
    {
        return $this->Offices;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfOffice $Offices
     * @return Drawer
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Cabinet
     */
    public function getParentCabinet()
    {
        return $this->ParentCabinet;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Cabinet $ParentCabinet
     * @return Drawer
     */
    public function withParentCabinet($ParentCabinet)
    {
        $new = clone $this;
        $new->ParentCabinet = $ParentCabinet;

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
     * @return Drawer
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }


}

