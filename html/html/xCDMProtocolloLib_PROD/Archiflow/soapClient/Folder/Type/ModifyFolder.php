<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class ModifyFolder implements RequestInterface
{

    /**
     * @var string
     */
    private $strSessionId = null;

    /**
     * @var \ArchiflowWSFolder\Type\Folder
     */
    private $oFolder = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSFolder\Type\Folder $oFolder
     */
    public function __construct($strSessionId, $oFolder)
    {
        $this->strSessionId = $strSessionId;
        $this->oFolder = $oFolder;
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
     * @return ModifyFolder
     */
    public function withStrSessionId($strSessionId)
    {
        $new = clone $this;
        $new->strSessionId = $strSessionId;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\Folder
     */
    public function getOFolder()
    {
        return $this->oFolder;
    }

    /**
     * @param \ArchiflowWSFolder\Type\Folder $oFolder
     * @return ModifyFolder
     */
    public function withOFolder($oFolder)
    {
        $new = clone $this;
        $new->oFolder = $oFolder;

        return $new;
    }


}

