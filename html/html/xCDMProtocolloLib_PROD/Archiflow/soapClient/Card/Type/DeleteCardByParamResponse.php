<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DeleteCardByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\DeleteCardOutput
     */
    private $DeleteCardByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\DeleteCardOutput
     */
    public function getDeleteCardByParamResult()
    {
        return $this->DeleteCardByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\DeleteCardOutput $DeleteCardByParamResult
     * @return DeleteCardByParamResponse
     */
    public function withDeleteCardByParamResult($DeleteCardByParamResult)
    {
        $new = clone $this;
        $new->DeleteCardByParamResult = $DeleteCardByParamResult;

        return $new;
    }


}

