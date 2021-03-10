<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ClassificationFolder implements RequestInterface
{

    /**
     * @var int
     */
    private $ClassificationId = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfint
     */
    private $FolderIds = null;

    /**
     * Constructor
     *
     * @var int $ClassificationId
     * @var \ArchiflowWSCard\Type\ArrayOfint $FolderIds
     */
    public function __construct($ClassificationId, $FolderIds)
    {
        $this->ClassificationId = $ClassificationId;
        $this->FolderIds = $FolderIds;
    }

    /**
     * @return int
     */
    public function getClassificationId()
    {
        return $this->ClassificationId;
    }

    /**
     * @param int $ClassificationId
     * @return ClassificationFolder
     */
    public function withClassificationId($ClassificationId)
    {
        $new = clone $this;
        $new->ClassificationId = $ClassificationId;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfint
     */
    public function getFolderIds()
    {
        return $this->FolderIds;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfint $FolderIds
     * @return ClassificationFolder
     */
    public function withFolderIds($FolderIds)
    {
        $new = clone $this;
        $new->FolderIds = $FolderIds;

        return $new;
    }


}

