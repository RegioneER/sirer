<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SetCardsFoldersInput implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfguid
     */
    private $CardIds = null;

    /**
     * @var bool
     */
    private $DelExisting = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfint
     */
    private $FolderIds = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\ArrayOfguid $CardIds
     * @var bool $DelExisting
     * @var \ArchiflowWSFolder\Type\ArrayOfint $FolderIds
     */
    public function __construct($CardIds, $DelExisting, $FolderIds)
    {
        $this->CardIds = $CardIds;
        $this->DelExisting = $DelExisting;
        $this->FolderIds = $FolderIds;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfguid
     */
    public function getCardIds()
    {
        return $this->CardIds;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfguid $CardIds
     * @return SetCardsFoldersInput
     */
    public function withCardIds($CardIds)
    {
        $new = clone $this;
        $new->CardIds = $CardIds;

        return $new;
    }

    /**
     * @return bool
     */
    public function getDelExisting()
    {
        return $this->DelExisting;
    }

    /**
     * @param bool $DelExisting
     * @return SetCardsFoldersInput
     */
    public function withDelExisting($DelExisting)
    {
        $new = clone $this;
        $new->DelExisting = $DelExisting;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfint
     */
    public function getFolderIds()
    {
        return $this->FolderIds;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfint $FolderIds
     * @return SetCardsFoldersInput
     */
    public function withFolderIds($FolderIds)
    {
        $new = clone $this;
        $new->FolderIds = $FolderIds;

        return $new;
    }


}

