<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SearchFoldersResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $SearchFoldersResult = null;

    /**
     * @var \ArchiflowWSFolder\Type\ArrayOfFolder
     */
    private $oFolders = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getSearchFoldersResult()
    {
        return $this->SearchFoldersResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $SearchFoldersResult
     * @return SearchFoldersResponse
     */
    public function withSearchFoldersResult($SearchFoldersResult)
    {
        $new = clone $this;
        $new->SearchFoldersResult = $SearchFoldersResult;

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
     * @return SearchFoldersResponse
     */
    public function withOFolders($oFolders)
    {
        $new = clone $this;
        $new->oFolders = $oFolders;

        return $new;
    }


}

