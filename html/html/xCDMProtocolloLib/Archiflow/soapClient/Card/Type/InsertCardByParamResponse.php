<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertCardByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\InsertCardByParamOutput
     */
    private $InsertCardByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\InsertCardByParamOutput
     */
    public function getInsertCardByParamResult()
    {
        return $this->InsertCardByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\InsertCardByParamOutput $InsertCardByParamResult
     * @return InsertCardByParamResponse
     */
    public function withInsertCardByParamResult($InsertCardByParamResult)
    {
        $new = clone $this;
        $new->InsertCardByParamResult = $InsertCardByParamResult;

        return $new;
    }


}

