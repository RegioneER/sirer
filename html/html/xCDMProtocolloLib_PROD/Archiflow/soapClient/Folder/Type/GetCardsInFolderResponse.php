<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardsInFolderResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\GetCardsInFolderOutput
     */
    private $GetCardsInFolderResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\GetCardsInFolderOutput
     */
    public function getGetCardsInFolderResult()
    {
        return $this->GetCardsInFolderResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\GetCardsInFolderOutput $GetCardsInFolderResult
     * @return GetCardsInFolderResponse
     */
    public function withGetCardsInFolderResult($GetCardsInFolderResult)
    {
        $new = clone $this;
        $new->GetCardsInFolderResult = $GetCardsInFolderResult;

        return $new;
    }


}

