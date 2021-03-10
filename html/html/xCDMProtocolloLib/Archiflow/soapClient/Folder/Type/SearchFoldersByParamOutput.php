<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class SearchFoldersByParamOutput implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfFolder
     */
    private $Folders = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\ArrayOfFolder $Folders
     */
    public function __construct($Folders)
    {
        $this->Folders = $Folders;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfFolder
     */
    public function getFolders()
    {
        return $this->Folders;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfFolder $Folders
     * @return SearchFoldersByParamOutput
     */
    public function withFolders($Folders)
    {
        $new = clone $this;
        $new->Folders = $Folders;

        return $new;
    }


}

