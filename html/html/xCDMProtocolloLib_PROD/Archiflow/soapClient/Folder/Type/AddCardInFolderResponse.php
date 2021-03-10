<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class AddCardInFolderResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $AddCardInFolderResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getAddCardInFolderResult()
    {
        return $this->AddCardInFolderResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $AddCardInFolderResult
     * @return AddCardInFolderResponse
     */
    public function withAddCardInFolderResult($AddCardInFolderResult)
    {
        $new = clone $this;
        $new->AddCardInFolderResult = $AddCardInFolderResult;

        return $new;
    }


}

