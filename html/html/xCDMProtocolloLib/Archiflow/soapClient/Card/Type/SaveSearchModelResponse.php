<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class SaveSearchModelResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $SaveSearchModelResult = null;

    /**
     * @var bool
     */
    private $ret = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getSaveSearchModelResult()
    {
        return $this->SaveSearchModelResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $SaveSearchModelResult
     * @return SaveSearchModelResponse
     */
    public function withSaveSearchModelResult($SaveSearchModelResult)
    {
        $new = clone $this;
        $new->SaveSearchModelResult = $SaveSearchModelResult;

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
     * @return SaveSearchModelResponse
     */
    public function withRet($ret)
    {
        $new = clone $this;
        $new->ret = $ret;

        return $new;
    }


}

