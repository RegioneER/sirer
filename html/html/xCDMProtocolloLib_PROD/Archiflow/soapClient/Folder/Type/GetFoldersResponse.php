<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetFoldersResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $GetFoldersResult = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfFolder
     */
    private $oFolders = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getGetFoldersResult()
    {
        return $this->GetFoldersResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $GetFoldersResult
     * @return GetFoldersResponse
     */
    public function withGetFoldersResult($GetFoldersResult)
    {
        $new = clone $this;
        $new->GetFoldersResult = $GetFoldersResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSFolder\Type\ArrayOfFolder
     */
    public function getOFolders()
    {
        return $this->oFolders;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ArrayOfFolder $oFolders
     * @return GetFoldersResponse
     */
    public function withOFolders($oFolders)
    {
        $new = clone $this;
        $new->oFolders = $oFolders;

        return $new;
    }


}

