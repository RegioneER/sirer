<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class FoldersForAutoCollateResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $FoldersForAutoCollateResult = null;

    /**
     * @var \ArchiflowWSCard\Type\ArrayOfFolder
     */
    private $folders = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getFoldersForAutoCollateResult()
    {
        return $this->FoldersForAutoCollateResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $FoldersForAutoCollateResult
     * @return FoldersForAutoCollateResponse
     */
    public function withFoldersForAutoCollateResult($FoldersForAutoCollateResult)
    {
        $new = clone $this;
        $new->FoldersForAutoCollateResult = $FoldersForAutoCollateResult;

        return $new;
    }

    /**
     * @return \ArchiflowWSCard\Type\ArrayOfFolder
     */
    public function getFolders()
    {
        return $this->folders;
    }

    /**
     * @param \ArchiflowWSCard\Type\ArrayOfFolder $folders
     * @return FoldersForAutoCollateResponse
     */
    public function withFolders($folders)
    {
        $new = clone $this;
        $new->folders = $folders;

        return $new;
    }


}

