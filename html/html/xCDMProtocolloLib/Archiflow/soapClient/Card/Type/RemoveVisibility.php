<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RemoveVisibility implements RequestInterface
{

    /**
     * @var string
     */
    private $SessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $Users = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
     */
    private $Groups = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $Offices = null;

    /**
     * Constructor
     *
     * @var string $SessionId
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var \ArchiflowWSCard\Type\ArrayOfUser $Users
     * @var \ArchiflowWSCard\Type\ArrayOfGroup $Groups
     * @var \ArchiflowWSCard\Type\ArrayOfOffice $Offices
     */
    public function __construct($SessionId, $CardId, $Users, $Groups, $Offices)
    {
        $this->SessionId = $SessionId;
        $this->CardId = $CardId;
        $this->Users = $Users;
        $this->Groups = $Groups;
        $this->Offices = $Offices;
    }

    /**
     * @return string
     */
    public function getSessionId()
    {
        return $this->SessionId;
    }

    /**
     * @param string $SessionId
     * @return RemoveVisibility
     */
    public function withSessionId($SessionId)
    {
        $new = clone $this;
        $new->SessionId = $SessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\Guid
     */
    public function getCardId()
    {
        return $this->CardId;
    }

    /**
     * @param \ArchiflowWSCard\Type\Guid $CardId
     * @return RemoveVisibility
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

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
     * @return RemoveVisibility
     */
    public function withUsers($Users)
    {
        $new = clone $this;
        $new->Users = $Users;

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
     * @return RemoveVisibility
     */
    public function withGroups($Groups)
    {
        $new = clone $this;
        $new->Groups = $Groups;

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
     * @return RemoveVisibility
     */
    public function withOffices($Offices)
    {
        $new = clone $this;
        $new->Offices = $Offices;

        return $new;
    }


}

