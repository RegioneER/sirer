<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Cabinet implements RequestInterface
{

    /**
     * @var int
     */
    private $Code = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
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
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $Offices = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $Users = null;

    /**
     * Constructor
     *
     * @var int $Code
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $Groups
     * @var string $Name
     * @var string $Note
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     * @var \ArchiflowWSCard\Type\ArrayOfUser $Users
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
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getGroups()
    {
        return $this->Groups;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $Groups
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
     * @return \ArchiflowWSCard\Type\ArrayOfOffice
     */
    public function getOffices()
    {
        return $this->Offices;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     * @return Cabinet
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
     * @return Cabinet
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }


}

