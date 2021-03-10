<?php

namespace ArchiflowWSFolder\Type;

use Phpro\SoapClient\Type\ResultInterface;

class ModifyDrawerResponse implements ResultInterface
{

    /**
     * @var \ArchiflowWSFolder\Type\ResultInfo
     */
    private $ModifyDrawerResult = null;

    /**
     * @return \ArchiflowWSFolder\Type\ResultInfo
     */
    public function getModifyDrawerResult()
    {
        return $this->ModifyDrawerResult;
    }

    /**
     * @param \ArchiflowWSFolder\Type\ResultInfo $ModifyDrawerResult
     * @return ModifyDrawerResponse
     */
    public function withModifyDrawerResult($ModifyDrawerResult)
    {
        $new = clone $this;
        $new->ModifyDrawerResult = $ModifyDrawerResult;

        return $new;
    }


}

