<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetFolderResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $GetFolderResult = null;

    /**
     * @var \ArchiflowWSFolder\Type\Folder
     */
    private $oFolder = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getGetFolderResult()
    {
        return $this->GetFolderResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $GetFolderResult
     * @return GetFolderResponse
     */
    public function withGetFolderResult($GetFolderResult)
    {
        $new = clone $this;
        $new->GetFolderResult = $GetFolderResult;

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
     * @return GetFolderResponse
     */
    public function withOFolder($oFolder)
    {
        $new = clone $this;
        $new->oFolder = $oFolder;

        return $new;
    }


}

