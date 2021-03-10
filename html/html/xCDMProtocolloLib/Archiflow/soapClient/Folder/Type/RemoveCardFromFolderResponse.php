<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class RemoveCardFromFolderResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $RemoveCardFromFolderResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getRemoveCardFromFolderResult()
    {
        return $this->RemoveCardFromFolderResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $RemoveCardFromFolderResult
     * @return RemoveCardFromFolderResponse
     */
    public function withRemoveCardFromFolderResult($RemoveCardFromFolderResult)
    {
        $new = clone $this;
        $new->RemoveCardFromFolderResult = $RemoveCardFromFolderResult;

        return $new;
    }


}

