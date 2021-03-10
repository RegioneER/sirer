<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SendFolderResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $SendFolderResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getSendFolderResult()
    {
        return $this->SendFolderResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $SendFolderResult
     * @return SendFolderResponse
     */
    public function withSendFolderResult($SendFolderResult)
    {
        $new = clone $this;
        $new->SendFolderResult = $SendFolderResult;

        return $new;
    }


}

