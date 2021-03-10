<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetDocumentTypesFromArchives implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSCard\Type\AccessLevel
     */
    private $enAccessLevel = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfshort
     */
    private $archiveIds = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSCard\Type\AccessLevel $enAccessLevel
     * @var \ArchiflowWSCard\Type\ArrayOfshort $archiveIds
     */
    public function __construct($strSessionId, $enAccessLevel, $archiveIds)
    {
        $this->strSessionId = $strSessionId;
        $this->enAccessLevel = $enAccessLevel;
        $this->archiveIds = $archiveIds;
    }

    /**
     * @return string
     */
    public function getStrSessionId()
    {
        return $this->strSessionId;
    }

    /**
     * @param string $strSessionId
     * @return GetDocumentTypesFromArchives
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\AccessLevel
     */
    public function getEnAccessLevel()
    {
        return $this->enAccessLevel;
    }

    /**
     * @param \ArchiflowWSCard\Type\AccessLevel $enAccessLevel
     * @return GetDocumentTypesFromArchives
     */
    public function withEnAccessLevel($enAccessLevel)
    {
        $new = clone $this;
        $new->enAccessLevel = $enAccessLevel;

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
     * @return GetDocumentTypesFromArchives
     */
    public function withArchiveIds($archiveIds)
    {
        $new = clone $this;
        $new->archiveIds = $archiveIds;

        return $new;
    }


}

