<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class GetCardFoldersOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfFolder
     */
    private $Folders = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\ArrayOfFolder $Folders
     */
    public function __construct($Folders)
    {
        $this->Folders = $Folders;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfFolder
     */
    public function getFolders()
    {
        return $this->Folders;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfFolder $Folders
     * @return GetCardFoldersOutput
     */
    public function withFolders($Folders)
    {
        $new = clone $this;
        $new->Folders = $Folders;

        return $new;
    }


}

