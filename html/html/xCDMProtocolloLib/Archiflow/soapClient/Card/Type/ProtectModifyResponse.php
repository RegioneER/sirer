<?php

namespace ArchiflowWSCard\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ProtectModifyResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSCard\Type\ResultInfo
     */
    private $ProtectModifyResult = null;

    /**
     * @return \ArchiflowWSCard\Type\ResultInfo
     */
    public function getProtectModifyResult()
    {
        return $this->ProtectModifyResult;
    }

    /**
     * @param \ArchiflowWSCard\Type\ResultInfo $ProtectModifyResult
     * @return ProtectModifyResponse
     */
    public function withProtectModifyResult($ProtectModifyResult)
    {
        $new = clone $this;
        $new->ProtectModifyResult = $ProtectModifyResult;

        return $new;
    }


}

