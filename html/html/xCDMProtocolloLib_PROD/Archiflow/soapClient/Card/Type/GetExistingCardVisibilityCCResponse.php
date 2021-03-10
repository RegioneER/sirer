<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetExistingCardVisibilityCCResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetExistingCardVisibilityCCResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $oCardUsers = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
     */
    private $oCardGroups = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $oCardOffices = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfUser
     */
    private $oCardUsersCC = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfGroup
     */
    private $oCardGroupsCC = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfOffice
     */
    private $oCardOfficesCC = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetExistingCardVisibilityCCResult()
    {
        return $this->GetExistingCardVisibilityCCResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetExistingCardVisibilityCCResult
     * @return GetExistingCardVisibilityCCResponse
     */
    public function withGetExistingCardVisibilityCCResult($GetExistingCardVisibilityCCResult)
    {
        $new = clone $this;
        $new->GetExistingCardVisibilityCCResult = $GetExistingCardVisibilityCCResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfUser
     */
    public function getOCardUsers()
    {
        return $this->oCardUsers;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfUser $oCardUsers
     * @return GetExistingCardVisibilityCCResponse
     */
    public function withOCardUsers($oCardUsers)
    {
        $new = clone $this;
        $new->oCardUsers = $oCardUsers;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getOCardGroups()
    {
        return $this->oCardGroups;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $oCardGroups
     * @return GetExistingCardVisibilityCCResponse
     */
    public function withOCardGroups($oCardGroups)
    {
        $new = clone $this;
        $new->oCardGroups = $oCardGroups;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfOffice
     */
    public function getOCardOffices()
    {
        return $this->oCardOffices;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOffice $oCardOffices
     * @return GetExistingCardVisibilityCCResponse
     */
    public function withOCardOffices($oCardOffices)
    {
        $new = clone $this;
        $new->oCardOffices = $oCardOffices;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfUser
     */
    public function getOCardUsersCC()
    {
        return $this->oCardUsersCC;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfUser $oCardUsersCC
     * @return GetExistingCardVisibilityCCResponse
     */
    public function withOCardUsersCC($oCardUsersCC)
    {
        $new = clone $this;
        $new->oCardUsersCC = $oCardUsersCC;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfGroup
     */
    public function getOCardGroupsCC()
    {
        return $this->oCardGroupsCC;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfGroup $oCardGroupsCC
     * @return GetExistingCardVisibilityCCResponse
     */
    public function withOCardGroupsCC($oCardGroupsCC)
    {
        $new = clone $this;
        $new->oCardGroupsCC = $oCardGroupsCC;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfOffice
     */
    public function getOCardOfficesCC()
    {
        return $this->oCardOfficesCC;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfOffice $oCardOfficesCC
     * @return GetExistingCardVisibilityCCResponse
     */
    public function withOCardOfficesCC($oCardOfficesCC)
    {
        $new = clone $this;
        $new->oCardOfficesCC = $oCardOfficesCC;

        return $new;
    }


}

