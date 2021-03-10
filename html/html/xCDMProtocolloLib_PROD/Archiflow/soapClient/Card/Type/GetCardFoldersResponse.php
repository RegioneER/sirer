<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class GetCardFoldersResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\GetCardFoldersOutput
     */
    private $GetCardFoldersResult = null;

    /**
     * @return \ArchiflowWSCard\Type\GetCardFoldersOutput
     */
    public function getGetCardFoldersResult()
    {
        return $this->GetCardFoldersResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\GetCardFoldersOutput $GetCardFoldersResult
     * @return GetCardFoldersResponse
     */
    public function withGetCardFoldersResult($GetCardFoldersResult)
    {
        $new = clone $this;
        $new->GetCardFoldersResult = $GetCardFoldersResult;

        return $new;
    }


}

