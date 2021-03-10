<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertFolderResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $InsertFolderResult = null;

    /**
     * @var int
     */
    private $newFolderId = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getInsertFolderResult()
    {
        return $this->InsertFolderResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $InsertFolderResult
     * @return InsertFolderResponse
     */
    public function withInsertFolderResult($InsertFolderResult)
    {
        $new = clone $this;
        $new->InsertFolderResult = $InsertFolderResult;

        return $new;
    }

    /**
     * @return int
     */
    public function getNewFolderId()
    {
        return $this->newFolderId;
    }

    /**
     * @param int $newFolderId
     * @return InsertFolderResponse
     */
    public function withNewFolderId($newFolderId)
    {
        $new = clone $this;
        $new->newFolderId = $newFolderId;

        return $new;
    }


}

