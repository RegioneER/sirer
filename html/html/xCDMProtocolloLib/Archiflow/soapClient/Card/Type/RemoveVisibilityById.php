<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class RemoveVisibilityById implements RequestInterface
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
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $UserIds = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $GroupIds = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $OfficeIds = null;

    /**
     * Constructor
     *
     * @var string $SessionId
     * @var \ArchiflowWSCard\Type\Guid $CardId
     * @var \ArchiflowWSCard\Type\ArrayOfint $UserIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $GroupIds
     * @var \ArchiflowWSCard\Type\ArrayOfint $OfficeIds
     */
    public function __construct($SessionId, $CardId, $UserIds, $GroupIds, $OfficeIds)
    {
        $this->SessionId = $SessionId;
        $this->CardId = $CardId;
        $this->UserIds = $UserIds;
        $this->GroupIds = $GroupIds;
        $this->OfficeIds = $OfficeIds;
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
     * @return RemoveVisibilityById
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
     * @return RemoveVisibilityById
     */
    public function withCardId($CardId)
    {
        $new = clone $this;
        $new->CardId = $CardId;

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
     * @return RemoveVisibilityById
     */
    public function withUserIds($UserIds)
    {
        $new = clone $this;
        $new->UserIds = $UserIds;

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
     * @return RemoveVisibilityById
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
    public function getOfficeIds()
    {
        return $this->OfficeIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $OfficeIds
     * @return RemoveVisibilityById
     */
    public function withOfficeIds($OfficeIds)
    {
        $new = clone $this;
        $new->OfficeIds = $OfficeIds;

        return $new;
    }


}

