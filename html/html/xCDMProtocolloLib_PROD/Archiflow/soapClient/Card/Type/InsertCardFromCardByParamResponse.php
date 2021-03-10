<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class InsertCardFromCardByParamResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\InsertCardFromCardOutput
     */
    private $InsertCardFromCardByParamResult = null;

    /**
     * @return \ArchiflowWSCard\Type\InsertCardFromCardOutput
     */
    public function getInsertCardFromCardByParamResult()
    {
        return $this->InsertCardFromCardByParamResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\InsertCardFromCardOutput
     * $InsertCardFromCardByParamResult
     * @return InsertCardFromCardByParamResponse
     */
    public function withInsertCardFromCardByParamResult($InsertCardFromCardByParamResult)
    {
        $new = clone $this;
        $new->InsertCardFromCardByParamResult = $InsertCardFromCardByParamResult;

        return $new;
    }


}

