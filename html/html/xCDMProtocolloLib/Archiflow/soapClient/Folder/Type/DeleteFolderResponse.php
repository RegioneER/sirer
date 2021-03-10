<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DeleteFolderResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $DeleteFolderResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getDeleteFolderResult()
    {
        return $this->DeleteFolderResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $DeleteFolderResult
     * @return DeleteFolderResponse
     */
    public function withDeleteFolderResult($DeleteFolderResult)
    {
        $new = clone $this;
        $new->DeleteFolderResult = $DeleteFolderResult;

        return $new;
    }


}

