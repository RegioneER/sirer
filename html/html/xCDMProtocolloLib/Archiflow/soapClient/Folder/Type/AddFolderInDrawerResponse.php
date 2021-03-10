<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AddFolderInDrawerResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $AddFolderInDrawerResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getAddFolderInDrawerResult()
    {
        return $this->AddFolderInDrawerResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $AddFolderInDrawerResult
     * @return AddFolderInDrawerResponse
     */
    public function withAddFolderInDrawerResult($AddFolderInDrawerResult)
    {
        $new = clone $this;
        $new->AddFolderInDrawerResult = $AddFolderInDrawerResult;

        return $new;
    }


}

