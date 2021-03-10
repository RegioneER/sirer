<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class Office implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $ChildOffices = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
     */
    private $ExecutiveOfficeGroups = null;

    /**
     * @var bool
     */
    private $IsExecutiveOffice = null;

    /**
     * @var string
     */
    private $OfficePath = null;

    /**
     * @var int
     */
    private $ParentId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $Users = null;

    /**
     * @var int
     */
    private $VisibilityWeight = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $ChildOffices
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $ExecutiveOfficeGroups
     * @var bool $IsExecutiveOffice
     * @var string $OfficePath
     * @var int $ParentId
     * @var \ArchiflowWSCard\Type\ArrayOfUser $Users
     * @var int $VisibilityWeight
     */
    public function __construct($ChildOffices, $ExecutiveOfficeGroups, $IsExecutiveOffice, $OfficePath, $ParentId, $Users, $VisibilityWeight)
    {
        $this->ChildOffices = $ChildOffices;
        $this->ExecutiveOfficeGroups = $ExecutiveOfficeGroups;
        $this->IsExecutiveOffice = $IsExecutiveOffice;
        $this->OfficePath = $OfficePath;
        $this->ParentId = $ParentId;
        $this->Users = $Users;
        $this->VisibilityWeight = $VisibilityWeight;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfOffice
     */
    public function getChildOffices()
    {
        return $this->ChildOffices;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOffice $ChildOffices
     * @return Office
     */
    public function withChildOffices($ChildOffices)
    {
        $new = clone $this;
        $new->ChildOffices = $ChildOffices;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getExecutiveOfficeGroups()
    {
        return $this->ExecutiveOfficeGroups;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $ExecutiveOfficeGroups
     * @return Office
     */
    public function withExecutiveOfficeGroups($ExecutiveOfficeGroups)
    {
        $new = clone $this;
        $new->ExecutiveOfficeGroups = $ExecutiveOfficeGroups;

        return $new;
    }

    /**
     * @return bool
     */
    public function getIsExecutiveOffice()
    {
        return $this->IsExecutiveOffice;
    }

    /**
     * @param bool $IsExecutiveOffice
     * @return Office
     */
    public function withIsExecutiveOffice($IsExecutiveOffice)
    {
        $new = clone $this;
        $new->IsExecutiveOffice = $IsExecutiveOffice;

        return $new;
    }

    /**
     * @return string
     */
    public function getOfficePath()
    {
        return $this->OfficePath;
    }

    /**
     * @param string $OfficePath
     * @return Office
     */
    public function withOfficePath($OfficePath)
    {
        $new = clone $this;
        $new->OfficePath = $OfficePath;

        return $new;
    }

    /**
     * @return int
     */
    public function getParentId()
    {
        return $this->ParentId;
    }

    /**
     * @param int $ParentId
     * @return Office
     */
    public function withParentId($ParentId)
    {
        $new = clone $this;
        $new->ParentId = $ParentId;

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
     * @return Office
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

        return $new;
    }

    /**
     * @return int
     */
    public function getVisibilityWeight()
    {
        return $this->VisibilityWeight;
    }

    /**
     * @param int $VisibilityWeight
     * @return Office
     */
    public function withVisibilityWeight($VisibilityWeight)
    {
        $new = clone $this;
        $new->VisibilityWeight = $VisibilityWeight;

        return $new;
    }


}

