<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class CheckPrivacyVisibilityInput implements RequestInterface
{

    /**
     * @var int
     */
    private $ArchiveId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfguid
     */
    private $CardIds = null;

    /**
     * @var int
     */
    private $DocTypeId = null;

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
     * @var int $ArchiveId
     * @var \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @var int $DocTypeId
     * @var \ArchiflowWSCard\Type\ArrayOfint $GroupCCIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $GroupIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $OfficeCCIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $OfficeIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $UserCCIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $UserIds
     */
    public function __construct($ArchiveId, $CardIds, $DocTypeId, $GroupCCIds, $GroupIds, $OfficeCCIds, $OfficeIds, $UserCCIds, $UserIds)
    {
        $this->ArchiveId = $ArchiveId;
        $this->CardIds = $CardIds;
        $this->DocTypeId = $DocTypeId;
        $this->GroupCCIds = $GroupCCIds;
        $this->GroupIds = $GroupIds;
        $this->OfficeCCIds = $OfficeCCIds;
        $this->OfficeIds = $OfficeIds;
        $this->UserCCIds = $UserCCIds;
        $this->UserIds = $UserIds;
    }

    /**
     * @return int
     */
    public function getArchiveId()
    {
        return $this->ArchiveId;
    }

    /**
     * @param int $ArchiveId
     * @return CheckPrivacyVisibilityInput
     */
    public function withArchiveId($ArchiveId)
    {
        $new = clone $this;
        $new->ArchiveId = $ArchiveId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfguid
     */
    public function getCardIds()
    {
        return $this->CardIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfguid $CardIds
     * @return CheckPrivacyVisibilityInput
     */
    public function withCardIds($CardIds)
    {
        $new = clone $this;
        $new->CardIds = $CardIds;

        return $new;
    }

    /**
     * @return int
     */
    public function getDocTypeId()
    {
        return $this->DocTypeId;
    }

    /**
     * @param int $DocTypeId
     * @return CheckPrivacyVisibilityInput
     */
    public function withDocTypeId($DocTypeId)
    {
        $new = clone $this;
        $new->DocTypeId = $DocTypeId;

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
     * @return CheckPrivacyVisibilityInput
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
     * @return CheckPrivacyVisibilityInput
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
     * @return CheckPrivacyVisibilityInput
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
     * @return CheckPrivacyVisibilityInput
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
     * @return CheckPrivacyVisibilityInput
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
     * @return CheckPrivacyVisibilityInput
     */
    public function withUserIds($UserIds)
    {
        $new = clone $this;
        $new->UserIds = $UserIds;

        return $new;
    }


}

