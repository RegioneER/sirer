<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfFolder implements RequestInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\Folder
     */
    private $Folder = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSFolder\Type\Folder $Folder
     */
    public function __construct($Folder)
    {
        $this->Folder = $Folder;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Folder
     */
    public function getFolder()
    {
        return $this->Folder;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Folder $Folder
     * @return ArrayOfFolder
     */
    public function withFolder($Folder)
    {
        $new = clone $this;
        $new->Folder = $Folder;

        return $new;
    }


}

