<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetExistingCardVisibilityResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $GetExistingCardVisibilityResult = null;

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
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getGetExistingCardVisibilityResult()
    {
        return $this->GetExistingCardVisibilityResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $GetExistingCardVisibilityResult
     * @return GetExistingCardVisibilityResponse
     */
    public function withGetExistingCardVisibilityResult($GetExistingCardVisibilityResult)
    {
        $new = clone $this;
        $new->GetExistingCardVisibilityResult = $GetExistingCardVisibilityResult;

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
     * @return GetExistingCardVisibilityResponse
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
     * @return GetExistingCardVisibilityResponse
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
     * @return GetExistingCardVisibilityResponse
     */
    public function withOCardOffices($oCardOffices)
    {
        $new = clone $this;
        $new->oCardOffices = $oCardOffices;

        return $new;
    }


}

