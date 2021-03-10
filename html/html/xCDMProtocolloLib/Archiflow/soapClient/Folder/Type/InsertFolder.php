<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\RequestInterface;

class InsertFolder implements RequestInterface
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
     * @var bool
     */
    private $bCheckDuplicate = null;

    /**
     * Constructor
     *
     * @var string $strSessionId
     * @var \ArchiflowWSFolder\Type\Folder $oFolder
     * @var bool $bCheckDuplicate
     */
    public function __construct($strSessionId, $oFolder, $bCheckDuplicate)
    {
        $this->strSessionId = $strSessionId;
        $this->oFolder = $oFolder;
        $this->bCheckDuplicate = $bCheckDuplicate;
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
     * @return InsertFolder
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
     * @return InsertFolder
     */
    public function withOFolder($oFolder)
    {
        $new = clone $this;
        $new->oFolder = $oFolder;

        return $new;
    }

    /**
     * @return bool
     */
    public function getBCheckDuplicate()
    {
        return $this->bCheckDuplicate;
    }

    /**
     * @param bool $bCheckDuplicate
     * @return InsertFolder
     */
    public function withBCheckDuplicate($bCheckDuplicate)
    {
        $new = clone $this;
        $new->bCheckDuplicate = $bCheckDuplicate;

        return $new;
    }


}

