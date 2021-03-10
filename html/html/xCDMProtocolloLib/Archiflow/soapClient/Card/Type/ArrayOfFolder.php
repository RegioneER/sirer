<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ArrayOfFolder implements RequestInterface
{

    /**
     * @var \ArchiflowWSCard\Type\Folder
     */
    private $Folder = null;

    /**
     * Constructor
     *
     * @var \ArchiflowWSCard\Type\Folder $Folder
     */
    public function __construct($Folder)
    {
        $this->Folder = $Folder;
    }

    /**
     * @return \ArchiflowWSCard\Type\Folder
     */
    public function getFolder()
    {
        return $this->Folder;
    }

    /**
     * @param \ArchiflowWSCard\Type\Folder $Folder
     * @return ArrayOfFolder
     */
    public function withFolder($Folder)
    {
        $new = clone $this;
        $new->Folder = $Folder;

        return $new;
    }


}

