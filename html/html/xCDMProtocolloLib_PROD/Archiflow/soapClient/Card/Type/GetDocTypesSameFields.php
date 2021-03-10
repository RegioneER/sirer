<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocTypesSameFields implements RequestInterface
{

    /**
     * @var string
     */
    private $sessionId = null;

    /**
     * @var int
     */
    private $docTypeId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfshort
     */
    private $archiveIds = null;

    /**
     * @var \ArchiflowWSCard\Type\AccessLevel
     */
    private $accessLevel = null;

    /**
     * Constructor
     *
     * @var string $sessionId
     * @var int $docTypeId
     * @var \ArchiflowWSCard\Type\ArrayOfshort $archiveIds
     * @var \ArchiflowWSCard\Type\AccessLevel $accessLevel
     */
    public function __construct($sessionId, $docTypeId, $archiveIds, $accessLevel)
    {
        $this->sessionId = $sessionId;
        $this->docTypeId = $docTypeId;
        $this->archiveIds = $archiveIds;
        $this->accessLevel = $accessLevel;
    }

    /**
     * @return string
     */
    public function getSessionId()
    {
        return $this->sessionId;
    }

    /**
     * @param string $sessionId
     * @return GetDocTypesSameFields
     */
    public function withSessionId($sessionId)
    {
        $new = clone $this;
        $new->sessionId = $sessionId;

        return $new;
    }

    /**
     * @return int
     */
    public function getDocTypeId()
    {
        return $this->docTypeId;
    }

    /**
     * @param int $docTypeId
     * @return GetDocTypesSameFields
     */
    public function withDocTypeId($docTypeId)
    {
        $new = clone $this;
        $new->docTypeId = $docTypeId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfshort
     */
    public function getArchiveIds()
    {
        return $this->archiveIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfshort $archiveIds
     * @return GetDocTypesSameFields
     */
    public function withArchiveIds($archiveIds)
    {
        $new = clone $this;
        $new->archiveIds = $archiveIds;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AccessLevel
     */
    public function getAccessLevel()
    {
        return $this->accessLevel;
    }

    /**
     * @param \ArchiflowWSCard\Type\AccessLevel $accessLevel
     * @return GetDocTypesSameFields
     */
    public function withAccessLevel($accessLevel)
    {
        $new = clone $this;
        $new->accessLevel = $accessLevel;

        return $new;
    }


}

