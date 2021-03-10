<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class DeleteSearchModelResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $DeleteSearchModelResult = null;

    /**
     * @var bool
     */
    private $ret = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getDeleteSearchModelResult()
    {
        return $this->DeleteSearchModelResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $DeleteSearchModelResult
     * @return DeleteSearchModelResponse
     */
    public function withDeleteSearchModelResult($DeleteSearchModelResult)
    {
        $new = clone $this;
        $new->DeleteSearchModelResult = $DeleteSearchModelResult;

        return $new;
    }

    /**
     * @return bool
     */
    public function getRet()
    {
        return $this->ret;
    }

    /**
     * @param bool $ret
     * @return DeleteSearchModelResponse
     */
    public function withRet($ret)
    {
        $new = clone $this;
        $new->ret = $ret;

        return $new;
    }


}

