<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class User implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Office
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
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
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
     * @var \ArchiflowWSCard\Type\Office
     */
    private $MainOffice = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $Offices = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUserRight
     */
    private $Rights = null;

    /**
     * @var \ArchiflowWSCard\Type\UserRightsConfig
     */
    private $RightsConfig = null;

    /**
     * @var \ArchiflowWSCard\Type\UserType
     */
    private $UserType = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Office $DefaultExecutiveOffice
     * @var string $Email
     * @var string $Email_WF
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $Groups
     * @var string $Id
     * @var bool $IsOnlyGED
     * @var bool $IsReadOnly
     * @var \ArchiflowWSCard\Type\Office $MainOffice
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     * @var \ArchiflowWSCard\Type\ArrayOfUserRight $Rights
     * @var \ArchiflowWSCard\Type\UserRightsConfig $RightsConfig
     * @var \ArchiflowWSCard\Type\UserType $UserType
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
     * @return \ArchiflowWSCard\Type\Office
     */
    public function getDefaultExecutiveOffice()
    {
        return $this->DefaultExecutiveOffice;
    }

    /**
     * @param \ArchiflowWSCard\Type\Office $DefaultExecutiveOffice
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
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getGroups()
    {
        return $this->Groups;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $Groups
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
     * @return \ArchiflowWSCard\Type\Office
     */
    public function getMainOffice()
    {
        return $this->MainOffice;
    }

    /**
     * @param \ArchiflowWSCard\Type\Office $MainOffice
     * @return User
     */
    public function withMainOffice($MainOffice)
    {
        $new = clone $this;
        $new->MainOffice = $MainOffice;

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
     * @return User
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfUserRight
     */
    public function getRights()
    {
        return $this->Rights;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfUserRight $Rights
     * @return User
     */
    public function withRights($Rights)
    {
        $new = clone $this;
        $new->Rights = $Rights;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\UserRightsConfig
     */
    public function getRightsConfig()
    {
        return $this->RightsConfig;
    }

    /**
     * @param \ArchiflowWSCard\Type\UserRightsConfig $RightsConfig
     * @return User
     */
    public function withRightsConfig($RightsConfig)
    {
        $new = clone $this;
        $new->RightsConfig = $RightsConfig;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\UserType
     */
    public function getUserType()
    {
        return $this->UserType;
    }

    /**
     * @param \ArchiflowWSCard\Type\UserType $UserType
     * @return User
     */
    public function withUserType($UserType)
    {
        $new = clone $this;
        $new->UserType = $UserType;

        return $new;
    }


}

