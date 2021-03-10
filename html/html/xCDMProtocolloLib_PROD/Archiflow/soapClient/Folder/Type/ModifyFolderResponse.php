<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ModifyFolderResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $ModifyFolderResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getModifyFolderResult()
    {
        return $this->ModifyFolderResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $ModifyFolderResult
     * @return ModifyFolderResponse
     */
    public function withModifyFolderResult($ModifyFolderResult)
    {
        $new = clone $this;
        $new->ModifyFolderResult = $ModifyFolderResult;

        return $new;
    }


}

