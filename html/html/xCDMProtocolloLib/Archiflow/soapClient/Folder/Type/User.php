<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class User implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Office
     */
    private $DefaultExecutiveOffice = null;

    /**
     * @var string
     */
    private $Email = null;

    /**
     * @var string
     */
    private $Email_WF = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup
     */
    private $Groups = null;

    /**
     * @var string
     */
    private $Id = null;

    /**
     * @var bool
     */
    private $IsOnlyGED = null;

    /**
     * @var bool
     */
    private $IsReadOnly = null;

    /**
     * @var \ArchiflowWSFolder\Type\Office
     */
    private $MainOffice = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice
     */
    private $Offices = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfUserRight
     */
    private $Rights = null;

    /**
     * @var \ArchiflowWSFolder\Type\UserRightsConfig
     */
    private $RightsConfig = null;

    /**
     * @var \ArchiflowWSFolder\Type\UserType
     */
    private $UserType = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Office $DefaultExecutiveOffice
     * @var string $Email
     * @var string $Email_WF
     * @var \ArchiflowWSFolder\Type\ArrayOfGroup $Groups
     * @var string $Id
     * @var bool $IsOnlyGED
     * @var bool $IsReadOnly
     * @var \ArchiflowWSFolder\Type\Office $MainOffice
     * @var \ArchiflowWSFolder\Type\ArrayOfOffice $Offices
     * @var \ArchiflowWSFolder\Type\ArrayOfUserRight $Rights
     * @var \ArchiflowWSFolder\Type\UserRightsConfig $RightsConfig
     * @var \ArchiflowWSFolder\Type\UserType $UserType
     */
    public function __construct($DefaultExecutiveOffice, $Email, $Email_WF, $Groups, $Id, $IsOnlyGED, $IsReadOnly, $MainOffice, $Offices, $Rights, $RightsConfig, $UserType)
    {
        $this->DefaultExecutiveOffice = $DefaultExecutiveOffice;
        $this->Email = $Email;
        $this->Email_WF = $Email_WF;
        $this->Groups = $Groups;
        $this->Id = $Id;
        $this->IsOnlyGED = $IsOnlyGED;
        $this->IsReadOnly = $IsReadOnly;
        $this->MainOffice = $MainOffice;
        $this->Offices = $Offices;
        $this->Rights = $Rights;
        $this->RightsConfig = $RightsConfig;
        $this->UserType = $UserType;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Office
     */
    public function getDefaultExecutiveOffice()
    {
        return $this->DefaultExecutiveOffice;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Office $DefaultExecutiveOffice
     * @return User
     */
    public function withDefaultExecutiveOffice($DefaultExecutiveOffice)
    {
        $new = clone $this;
        $new->DefaultExecutiveOffice = $DefaultExecutiveOffice;

        return $new;
    }

    /**
     * @return string
     */
    public function getEmail()
    {
        return $this->Email;
    }

    /**
     * @param string $Email
     * @return User
     */
    public function withEmail($Email)
    {
        $new = clone $this;
        $new->Email = $Email;

        return $new;
    }

    /**
     * @return string
     */
    public function getEmail_WF()
    {
        return $this->Email_WF;
    }

    /**
     * @param string $Email_WF
     * @return User
     */
    public function withEmail_WF($Email_WF)
    {
        $new = clone $this;
        $new->Email_WF = $Email_WF;

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
     * @return User
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
    public function getId()
    {
        return $this->Id;
    }

    /**
     * @param string $Id
     * @return User
     */
    public function withId($Id)
    {
        $new = clone $this;
        $new->Id = $Id;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsOnlyGED()
    {
        return $this->IsOnlyGED;
    }

    /**
     * @param bool $IsOnlyGED
     * @return User
     */
    public function withIsOnlyGED($IsOnlyGED)
    {
        $new = clone $this;
        $new->IsOnlyGED = $IsOnlyGED;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsReadOnly()
    {
        return $this->IsReadOnly;
    }

    /**
     * @param bool $IsReadOnly
     * @return User
     */
    public function withIsReadOnly($IsReadOnly)
    {
        $new = clone $this;
        $new->IsReadOnly = $IsReadOnly;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Office
     */
    public function getMainOffice()
    {
        return $this->MainOffice;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Office $MainOffice
     * @return User
     */
    public function withMainOffice($MainOffice)
    {
        $new = clone $this;
        $new->MainOffice = $MainOffice;

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
     * @return User
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfUserRight
     */
    public function getRights()
    {
        return $this->Rights;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfUserRight $Rights
     * @return User
     */
    public function withRights($Rights)
    {
        $new = clone $this;
        $new->Rights = $Rights;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\UserRightsConfig
     */
    public function getRightsConfig()
    {
        return $this->RightsConfig;
    }

    /**
     * @param \ArchiflowWSFolder\Type\UserRightsConfig $RightsConfig
     * @return User
     */
    public function withRightsConfig($RightsConfig)
    {
        $new = clone $this;
        $new->RightsConfig = $RightsConfig;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\UserType
     */
    public function getUserType()
    {
        return $this->UserType;
    }

    /**
     * @param \ArchiflowWSFolder\Type\UserType $UserType
     * @return User
     */
    public function withUserType($UserType)
    {
        $new = clone $this;
        $new->UserType = $UserType;

        return $new;
    }


}

