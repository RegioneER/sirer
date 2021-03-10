<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RemoveVisibilityInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Guid
     */
    private $CardId = null;

    /**
     * @var bool
     */
    private $CheckUserWithPrivacy = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $GroupCCIds = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $GroupIds = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $OfficeCCIds = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $OfficeIds = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $UserCCIds = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $UserIds = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var bool $CheckUserWithPrivacy
     * @var \ArchiflowWSCard\Type\ArrayOfint $GroupCCIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $GroupIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $OfficeCCIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $OfficeIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $UserCCIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $UserIds
     */
    public function __construct($CardId, $CheckUserWithPrivacy, $GroupCCIds, $GroupIds, $OfficeCCIds, $OfficeIds, $UserCCIds, $UserIds)
    {
        $this->CardId = $CardId;
        $this->CheckUserWithPrivacy = $CheckUserWithPrivacy;
        $this->GroupCCIds = $GroupCCIds;
        $this->GroupIds = $GroupIds;
        $this->OfficeCCIds = $OfficeCCIds;
        $this->OfficeIds = $OfficeIds;
        $this->UserCCIds = $UserCCIds;
        $this->UserIds = $UserIds;
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
     * @return RemoveVisibilityInput
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

        return $new;
    }

    /**
     * @return bool
     */
    public function getCheckUserWithPrivacy()
    {
        return $this->CheckUserWithPrivacy;
    }

    /**
     * @param bool $CheckUserWithPrivacy
     * @return RemoveVisibilityInput
     */
    public function withCheckUserWithPrivacy($CheckUserWithPrivacy)
    {
        $new = clone $this;
        $new->CheckUserWithPrivacy = $CheckUserWithPrivacy;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getGroupCCIds()
    {
        return $this->GroupCCIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $GroupCCIds
     * @return RemoveVisibilityInput
     */
    public function withGroupCCIds($GroupCCIds)
    {
        $new = clone $this;
        $new->GroupCCIds = $GroupCCIds;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getGroupIds()
    {
        return $this->GroupIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $GroupIds
     * @return RemoveVisibilityInput
     */
    public function withGroupIds($GroupIds)
    {
        $new = clone $this;
        $new->GroupIds = $GroupIds;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getOfficeCCIds()
    {
        return $this->OfficeCCIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $OfficeCCIds
     * @return RemoveVisibilityInput
     */
    public function withOfficeCCIds($OfficeCCIds)
    {
        $new = clone $this;
        $new->OfficeCCIds = $OfficeCCIds;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getOfficeIds()
    {
        return $this->OfficeIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $OfficeIds
     * @return RemoveVisibilityInput
     */
    public function withOfficeIds($OfficeIds)
    {
        $new = clone $this;
        $new->OfficeIds = $OfficeIds;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getUserCCIds()
    {
        return $this->UserCCIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $UserCCIds
     * @return RemoveVisibilityInput
     */
    public function withUserCCIds($UserCCIds)
    {
        $new = clone $this;
        $new->UserCCIds = $UserCCIds;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getUserIds()
    {
        return $this->UserIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $UserIds
     * @return RemoveVisibilityInput
     */
    public function withUserIds($UserIds)
    {
        $new = clone $this;
        $new->UserIds = $UserIds;

        return $new;
    }


}

