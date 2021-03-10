<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SendFolderByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\SendFolderOutput
     */
    private $SendFolderByParamResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\SendFolderOutput
     */
    public function getSendFolderByParamResult()
    {
        return $this->SendFolderByParamResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\SendFolderOutput $SendFolderByParamResult
     * @return SendFolderByParamResponse
     */
    public function withSendFolderByParamResult($SendFolderByParamResult)
    {
        $new = clone $this;
        $new->SendFolderByParamResult = $SendFolderByParamResult;

        return $new;
    }


}

