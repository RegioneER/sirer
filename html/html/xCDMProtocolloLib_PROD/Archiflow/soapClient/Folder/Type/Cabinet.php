<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Cabinet implements RequestInterface
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
     * @var \ArchiflowWSFolder\Type\ArrayOfUser $Users
     */
    public function __construct($Code, $Groups, $Name, $Note, $Offices, $Users)
    {
        $this->Code = $Code;
        $this->Groups = $Groups;
        $this->Name = $Name;
        $this->Note = $Note;
        $this->Offices = $Offices;
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
     * @return Cabinet
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
     * @return Cabinet
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
     * @return Cabinet
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
     * @return Cabinet
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
     * @return Cabinet
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

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
     * @return Cabinet
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }


}

